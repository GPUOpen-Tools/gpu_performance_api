#!/usr/bin/python3
## Copyright (c) 2019-2020 Advanced Micro Devices, Inc. All rights reserved.
# GPA Packaging script

import os
import sys
import argparse
import gpa_utils as GpaUtils

gpa_package_args = argparse.ArgumentParser(description="GPA packaging arguments")
gpa_package_args.add_argument("--buildartifactsdir", help="GPA build artifacts directory")
gpa_package_args.add_argument("--buildnumber", type=int, help="GPA build number")
gpa_package_args.add_argument("--debug", action="store_true", help="Set to true to package debug bits")
gpa_package_args.add_argument("--archiveoutdir", help="Package output directory")
gpa_package_args.add_argument("--docsdir", help="GPA docs output directory")
gpa_package_args.add_argument("--android", action="store_true", help="Set to true to package android artifacts")
gpa_package_args.add_argument("--skip32bit", action="store_true", help="Set to true to skip 32-bit binaries")

# Returns the full name for GPA binaries
def GetGpaBinaryName(binary_name, is_executable, is_debug, is_32_bit, additional_suffix):
    debug_suffix = ""
    if is_debug == True:
        debug_suffix = "-d"

    platform_suffix = ""
    platform_prefix=""
    binary_extension=""

    if sys.platform == "win32":
        if is_executable == True:
            binary_extension = ".exe"
        else:
            binary_extension = ".dll"
        if is_32_bit == False:
            platform_suffix = "-x64"
    else:
        if is_executable == False:
            if sys.platform == "darwin":
                binary_extension = ".dylib"
            else:
                binary_extension = ".so"
            platform_prefix="lib"
        if is_32_bit == True:
            platform_suffix = "32"

    additional_suffix_str=""
    if additional_suffix is not None:
        additional_suffix_str = str(additional_suffix)

    gpa_binary_name = platform_prefix + binary_name + platform_suffix + debug_suffix + additional_suffix_str + binary_extension
    return gpa_binary_name

class GpaPackage:
    def GetArchiveNameWithGpaVersion(self, archive_name_without_version, build_number_in, is_debug, additional_suffix):
        archive_name_with_gpa_version = archive_name_without_version

        if self.GetGpaVersion(build_number_in):
            version_str = str(self._major_version) + "." + str(self._minor_version) + "." + str(self._update_version) + "." + str(self._build_number)

            if is_debug:
                archive_name_with_gpa_version = archive_name_with_gpa_version + "-debug"

            if additional_suffix is not None:
                archive_name_with_gpa_version = archive_name_with_gpa_version + str(additional_suffix)

            archive_name_with_gpa_version = archive_name_with_gpa_version + str("-") + version_str

            if sys.platform == "win32":
                archive_name_with_gpa_version = archive_name_with_gpa_version + ".zip"
            else:
                archive_name_with_gpa_version = archive_name_with_gpa_version + ".tgz"

        return archive_name_with_gpa_version

    def CreatePackage(self, archive_output_dir, build_artifacts_dir, sphinx_docs_dir, package_32_bit, is_debug, android, build_number, additional_suffix):
        gpa_build_artifacts_dir = self._gpa_build_artifacts_dir
        gpa_archive_out_dir = self._gpa_build_artifacts_dir

        if sphinx_docs_dir is None:
            sphinx_docs_dir = self._gpa_build_artifacts_dir

        config_str = "release"
        if is_debug == True:
            config_str = "debug"

        if build_artifacts_dir is not None:
            gpa_build_artifacts_dir = build_artifacts_dir
        else:
            gpa_build_artifacts_dir = os.path.normpath(os.path.join(gpa_build_artifacts_dir, config_str))

        if archive_output_dir is not None:
            gpa_archive_out_dir = archive_output_dir

        archive_name = self.GetArchiveNameWithGpaVersion(self._gpa_archive_name, build_number, is_debug, additional_suffix)

        if not os.path.exists(gpa_archive_out_dir):
            os.makedirs(gpa_archive_out_dir, exist_ok=True)
        os.chdir(gpa_archive_out_dir)
        gpa_archive_handle = GpaUtils.CreateArchive(archive_name)
        gpa_archive_root_name = str(self._major_version) + "_" + str(self._minor_version)

        if gpa_archive_handle is not None:
            if package_32_bit and not android:
                for target in self._gpa_binaries:
                    if target == "GPUPerfAPIGLES":
                        continue
                    if sys.platform.startswith("linux"):
                        if target == "GPUPerfAPICL":
                            continue
                    current_target_binary = GetGpaBinaryName(target, False, is_debug, True, additional_suffix)
                    current_target_binary_abs_path = os.path.normpath(
                        os.path.join(gpa_build_artifacts_dir, current_target_binary))
                    current_target_path_in_archive = os.path.join(gpa_archive_root_name, "Bin")
                    if sys.platform == "win32":
                        current_target_path_in_archive = os.path.join(current_target_path_in_archive, "x86",
                                                                        current_target_binary)
                    else:
                        current_target_path_in_archive = os.path.join(current_target_path_in_archive, "Linx86",
                                                                        current_target_binary)
                    GpaUtils.WriteFileToArchive(gpa_archive_handle,
                                                                    current_target_binary_abs_path,
                                                                    current_target_path_in_archive)
            for target in self._gpa_binaries:
                if android:
                    if target == "GPUPerfAPICL":
                        continue
                    if target == "GPUPerfAPIGL":
                        continue
                else:
                    if target == "GPUPerfAPIGLES":
                        continue

                current_target_binary = GetGpaBinaryName(target, False, is_debug, False, additional_suffix)
                current_target_binary_abs_path = os.path.normpath(os.path.join(gpa_build_artifacts_dir,
                                                                                current_target_binary))
                current_target_path_in_archive = os.path.join(gpa_archive_root_name, "Bin")
                if sys.platform == "win32" or android:
                    current_target_path_in_archive = os.path.join(current_target_path_in_archive, "x64",
                                                                    current_target_binary)
                else:
                    current_target_path_in_archive = os.path.join(current_target_path_in_archive, "Linx64",
                                                                    current_target_binary)
                GpaUtils.WriteFileToArchive(gpa_archive_handle,
                                                                current_target_binary_abs_path,
                                                                current_target_path_in_archive)

            ## Add GPA headers
            for header_path in self._public_header_files:
                header_source_abs_path = os.path.normpath(os.path.join(self._gpa_root_dir, "include", "gpu_performance_api", header_path))
                header_in_archive = os.path.normpath(os.path.join(gpa_archive_root_name, "Include", "gpu_performance_api", header_path))
                GpaUtils.WriteFileToArchive(gpa_archive_handle, header_source_abs_path,
                                                                header_in_archive)

            ## add old GPA headers (deprecated)
            for header_path in self._old_includes:
                header_source_abs_path = os.path.normpath(os.path.join(self._gpa_root_dir, "include", header_path))
                header_in_archive = os.path.normpath(os.path.join(gpa_archive_root_name, "Include", header_path))
                GpaUtils.WriteFileToArchive(gpa_archive_handle, header_source_abs_path,
                                                                header_in_archive)

            ## add new headers that are still in the old location (deprecated)
            for header_path in self._public_header_files:
                header_source_abs_path = os.path.normpath(os.path.join(self._gpa_root_dir, "include", header_path))
                header_in_archive = os.path.normpath(os.path.join(gpa_archive_root_name, "Include", header_path))
                GpaUtils.WriteFileToArchive(gpa_archive_handle, header_source_abs_path,
                                                                header_in_archive)


            for other_file in self._other_files:
                other_file_abs_path = os.path.normpath(os.path.join(self._gpa_root_dir, other_file))
                other_file_in_archive = os.path.normpath(os.path.join(gpa_archive_root_name, other_file))
                GpaUtils.WriteFileToArchive(gpa_archive_handle, other_file_abs_path,
                                                                other_file_in_archive)

            # Write docs
            gpa_docs_dir = os.path.normpath(os.path.join(gpa_build_artifacts_dir, sphinx_docs_dir, "html"))
            gpa_docs_dir_str = str(gpa_docs_dir)
            gpa_docs_dir_info = os.walk(gpa_docs_dir)

            if sys.platform == "win32":
                doc_folder_str = "\\docs"
            else:
                doc_folder_str = "/docs"

            for dirs, sub_dirs, files in gpa_docs_dir_info:
                for file in files:
                    doc_file_abs_path = os.path.join(dirs, file)
                    doc_file_abs_path = os.path.normpath(doc_file_abs_path)
                    doc_file_abs_path_str = str(doc_file_abs_path)
                    doc_file_in_archive = gpa_archive_root_name + doc_folder_str + \
                                            doc_file_abs_path_str.split(gpa_docs_dir_str)[1]
                    GpaUtils.WriteFileToArchive(gpa_archive_handle, doc_file_abs_path,
                                                                    doc_file_in_archive)
            # Add android specific script file
            if android == True:
                _android_device_connect_script_file = os.path.normpath(os.path.join(self._gpa_root_dir, "scripts", self._android_device_connect_script))
                _android_device_connect_script_file_in_archive = os.path.normpath(os.path.join(gpa_archive_root_name, self._android_device_connect_script))

                GpaUtils.WriteFileToArchive(gpa_archive_handle, _android_device_connect_script_file,
                                                                _android_device_connect_script_file_in_archive)

    # Returns the gpa version
    def GetGpaVersion(self, _build_numberin):
        gpa_version_abs_path = os.path.normpath(os.path.join(self._gpa_root_dir, self._version_file))
        if os.path.exists(gpa_version_abs_path):
            with open(gpa_version_abs_path) as gpa_version_info:
                # get major, minor, and update values
                for line in gpa_version_info:
                    if 'define GPA_MAJOR_VERSION ' in line:
                        self._major_version = (line.split()[2])
                    if 'define GPA_MINOR_VERSION ' in line:
                        self._minor_version = (line.split()[2])
                    if 'define GPA_UPDATE_VERSION ' in line:
                        self._update_version = (line.split()[2])
                    if 'define GPA_BUILD_NUMBER ' in line:
                        self._build_number = (line.split()[2])
                        if _build_numberin != 0:
                            self._build_number=_build_numberin
            return True
        else:
            return False

    # Constructor
    def __init__(self):
        super().__init__()

    _gpa_archive_name="GPUPerfAPI"
    _old_includes=[ "GPUPerfAPI.h",
                    "GPUPerfAPIStub.h",
                    "GPUPerfAPITypes.h",
                    "GPUPerfAPIFunctionTypes.h",
                    "GPAFunctions.h",
                    "GPUPerfAPI-VK.h",
                    "GPAInterfaceLoader.h"]

    _public_header_files=["gpu_perf_api.h",
                          "gpu_perf_api_function_types.h",
                          "gpu_perf_api_functions.h",
                          "gpu_perf_api_interface_loader.h",
                          "gpu_perf_api_stub.h",
                          "gpu_perf_api_types.h",
                          "gpu_perf_api_vk.h",
                          "gpu_perf_api_counters.h"]

    _gpa_binaries=["GPUPerfAPICounters"]

    if sys.platform == "win32" or sys.platform.startswith("linux"):
        _gpa_binaries.append("GPUPerfAPIVK")
        _gpa_binaries.append("GPUPerfAPIGL")

    if sys.platform == "win32":
        _gpa_binaries.append("GPUPerfAPIDX11")
        _gpa_binaries.append("GPUPerfAPIDX12")
        _gpa_binaries.append("GPUPerfAPIDXGetAMDDeviceInfo")
        _gpa_binaries.append("GPUPerfAPICL")

    _other_files=["NOTICES.txt",
                 "LICENSE"]

    _version_file="source/gpu_perf_api_common/gpa_version.h"
    _android_device_connect_script = "enable_set_device_clock_android.py"
    _major_version=0
    _minor_version=0
    _update_version=0
    _build_number=0
    _script_dir = os.path.dirname(os.path.realpath(__file__))
    _gpa_root_dir = os.path.normpath(os.path.join(_script_dir, "../"))
    _gpa_build_artifacts_dir = os.path.normpath(os.path.join(_gpa_root_dir, "output"))

if __name__ == "__main__":
    gpa_package_parsed_args = gpa_package_args.parse_args()

    gpa_build_out_dir = None
    gpa_package_out_dir = None
    gpa_docs_dir = None
    gpa_build_number = 0
    debug_build = False
    is_android = False
    package_32_bit_binaries=True

    if gpa_package_parsed_args.android == True:
        is_android = gpa_package_parsed_args.android

    if (sys.platform == "win32") and is_android == True:
        print("Android packaging is not supported on Windows")
        exit

    if gpa_package_parsed_args.debug == True:
        debug_build = True

    if gpa_package_parsed_args.buildartifactsdir is not None:
        gpa_build_out_dir = gpa_package_parsed_args.buildartifactsdir

    if gpa_package_parsed_args.archiveoutdir is not None:
        gpa_package_out_dir = gpa_package_parsed_args.archiveoutdir

    if gpa_package_parsed_args.archiveoutdir is not None:
        gpa_docs_dir = gpa_package_parsed_args.docsdir

    if gpa_package_parsed_args.buildnumber != None:
        gpa_build_number = gpa_build_number + gpa_package_parsed_args.buildnumber

    if gpa_package_parsed_args.skip32bit == True:
        package_32_bit_binaries = False

    gpa_package = GpaPackage()
    gpa_package.CreatePackage(archive_output_dir=gpa_package_out_dir,
                              build_artifacts_dir=gpa_build_out_dir,
                              sphinx_docs_dir=gpa_docs_dir,
                              is_debug=debug_build,
                              package_32_bit=package_32_bit_binaries,
                              android=is_android,
                              build_number=gpa_build_number,
                              additional_suffix=None)





