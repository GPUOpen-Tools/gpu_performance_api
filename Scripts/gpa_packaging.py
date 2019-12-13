#!/usr/bin/python3
## Copyright (c) 2019 Advanced Micro Devices, Inc. All rights reserved.
# GPA Packaging script

import os
import sys
import argparse
import gpa_utils as GpaUtils

gpa_package_args = argparse.ArgumentParser(description="GPA packaging arguments")
gpa_package_args.add_argument("--buildartifactsdir", help="GPA build artifacts directory")
gpa_package_args.add_argument("--buildnumber", help="GPA build number")
gpa_package_args.add_argument("--debug", action="store_true", help="Set to true to package debug bits")
gpa_package_args.add_argument("--archiveoutdir", help="Package output directory")

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
    def CreatePackage(self, archive_output_dir, build_artifacts_dir, package_32_bit, is_debug, build_number, additional_suffix):
        gpa_build_artifacts_dir = self.gpa_build_artifacts_dir_
        gpa_archive_out_dir = self.gpa_build_artifacts_dir_

        config_str = "release"
        if is_debug == True:
            config_str = "debug"

        if build_artifacts_dir is not None:
            gpa_build_artifacts_dir = build_artifacts_dir
        else:
            gpa_build_artifacts_dir = os.path.normpath(os.path.join(gpa_build_artifacts_dir, config_str))

        if archive_output_dir is not None:
            gpa_archive_out_dir = archive_output_dir

        if self.GetGpaVersion(build_number):
            version_str = str(self.major_version_) + "." + str(self.minor_version_)

            if self.update_version_ != str(0):
                version_str = version_str + "." + str(self.update_version_)

            if self.build_number_ != str(0):
                version_str = version_str + "." + str(self.build_number_)

            archive_name = self.archive_name_

            if is_debug:
                archive_name = archive_name + "-debug"

            if additional_suffix is not None:
                archive_name = archive_name + str(additional_suffix)

            archive_name = archive_name + str("-") + version_str

            if sys.platform == "win32":
                archive_name = archive_name + ".zip"
            else:
                archive_name = archive_name + ".tgz"

            os.chdir(gpa_archive_out_dir)
            gpa_archive_handle = GpaUtils.CreateArchive(archive_name)
            gpa_archive_root_name = str(self.major_version_) + "_" + str(self.minor_version_)

            if gpa_archive_handle is not None:
                if package_32_bit:
                    for target in self.binaries_:
                        if sys.platform.startswith("linux"):
                            if target is "GPUPerfAPICL":
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
                for target in self.binaries_:
                    current_target_binary = GetGpaBinaryName(target, False, is_debug, False, additional_suffix)
                    current_target_binary_abs_path = os.path.normpath(os.path.join(gpa_build_artifacts_dir,
                                                                                   current_target_binary))
                    current_target_path_in_archive = os.path.join(gpa_archive_root_name, "Bin")
                    if sys.platform == "win32":
                        current_target_path_in_archive = os.path.join(current_target_path_in_archive, "x64",
                                                                      current_target_binary)
                    else:
                        current_target_path_in_archive = os.path.join(current_target_path_in_archive, "Linx64",
                                                                      current_target_binary)
                    GpaUtils.WriteFileToArchive(gpa_archive_handle,
                                                                    current_target_binary_abs_path,
                                                                    current_target_path_in_archive)

                ## add GPA headers
                for header_path in self.common_includes_:
                    header_source_abs_path = os.path.normpath(os.path.join(self.gpa_root_dir_, "Src", "GPUPerfAPI-Common",
                                                                           header_path))
                    header_in_archive = os.path.normpath(os.path.join(gpa_archive_root_name, "Include", header_path))
                    GpaUtils.WriteFileToArchive(gpa_archive_handle, header_source_abs_path,
                                                                    header_in_archive)

                for header_path in self.counter_generator_:
                    header_source_abs_path = os.path.normpath(os.path.join(self.gpa_root_dir_, "Src",
                                                                           "GPUPerfAPICounterGenerator", header_path))
                    header_in_archive = os.path.normpath(os.path.join(gpa_archive_root_name, "Include", header_path))
                    GpaUtils.WriteFileToArchive(gpa_archive_handle,
                                                                    header_source_abs_path, header_in_archive)

                for other_file in self.other_files_:
                    other_file_abs_path = os.path.normpath(os.path.join(self.gpa_root_dir_, other_file))
                    other_file_in_archive = os.path.normpath(os.path.join(gpa_archive_root_name, other_file))
                    GpaUtils.WriteFileToArchive(gpa_archive_handle, other_file_abs_path,
                                                                    other_file_in_archive)

                # Write docs
                gpa_docs_dir = os.path.normpath(os.path.join(gpa_build_artifacts_dir, "../", "docs", "html"))
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

    # Returns the gpa version
    def GetGpaVersion(self, build_number_in):
        gpa_version_abs_path = os.path.normpath(os.path.join(self.gpa_root_dir_, self.version_file_))
        if os.path.exists(gpa_version_abs_path):
            with open(gpa_version_abs_path) as gpa_version_info:
                # get major, minor, and update values
                for line in gpa_version_info:
                    if 'define GPA_MAJOR_VERSION ' in line:
                        self.major_version_ = (line.split()[2])
                    if 'define GPA_MINOR_VERSION ' in line:
                        self.minor_version_ = (line.split()[2])
                    if 'define GPA_UPDATE_VERSION ' in line:
                        self.update_version_ = (line.split()[2])
                    if 'define GPA_BUILD_NUMBER ' in line:
                        self.build_number_ = (line.split()[2])
                        if build_number_in != 0:
                            self.build_number_=build_number_in
            return True
        else:
            return False

    # Constructor
    def __init__(self):
        super().__init__()

    archive_name_="GPUPerfAPI"
    common_includes_=["GPUPerfAPI.h",
                    "GPUPerfAPIStub.h",
                    "GPUPerfAPITypes.h",
                    "GPUPerfAPIFunctionTypes.h",
                    "GPAFunctions.h",
                    "GPUPerfAPI-VK.h",
                    "GPAInterfaceLoader.h"]

    counter_generator_=[ "GPACounterGenerator.h",
                        "IGPACounterAccessor.h",
                        "IGPACounterScheduler.h"]

    binaries_=["GPUPerfAPIVK",
            "GPUPerfAPIGL",
            "GPUPerfAPICL",
            "GPUPerfAPICounters"]

    if sys.platform == "win32":
        binaries_.append("GPUPerfAPIDX11")
        binaries_.append("GPUPerfAPIDX12")

    other_files_=["NOTICES.txt",
                 "LICENSE"]

    version_file_="Src/GPUPerfAPI-Common/GPAVersion.h"
    major_version_=0
    minor_version_=0
    update_version_=0
    build_number_=0
    script_dir_ = os.path.dirname(os.path.realpath(__file__))
    gpa_root_dir_ = os.path.normpath(os.path.join(script_dir_, "../"))
    gpa_build_artifacts_dir_ = os.path.normpath(os.path.join(gpa_root_dir_, "Output"))

if __name__ == "__main__":
    gpa_package_parsed_args = gpa_package_args.parse_args()

    gpa_build_out_dir = None
    gpa_package_out_dir = None
    gpa_build_number = 0
    debug_build = False

    if gpa_package_parsed_args.debug == True:
        debug_build = True

    if gpa_package_parsed_args.buildartifactsdir is not None:
        gpa_build_out_dir = gpa_package_parsed_args.buildartifactsdir

    if gpa_package_parsed_args.archiveoutdir is not None:
        gpa_package_out_dir = gpa_package_args.archiveoutdir

    if gpa_package_parsed_args.buildnumber != None:
        gpa_build_number = gpa_build_number + gpa_package_parsed_args.buildnumber

    gpa_package = GpaPackage()
    gpa_package.CreatePackage(archive_output_dir=gpa_package_out_dir,
                              build_artifacts_dir=gpa_build_out_dir,
                              is_debug=debug_build,
                              package_32_bit=True,
                              build_number=gpa_build_number,
                              additional_suffix=None)





