#!/usr/bin/python3
## Copyright (c) 2019-2024 Advanced Micro Devices, Inc. All rights reserved.
# GPA Packaging script

import argparse
import os
import sys
import tarfile
import zipfile

script_dir = os.path.dirname(os.path.realpath(__file__))
gpa_root   = os.path.normpath(os.path.join(script_dir, ".."))
sys.path.append(gpa_root)

# Global variables updated within the script.
major    = 0
minor    = 0
update   = 0
revision = 0
version_string = ""
archive_suffix = ""
executable_32bit_suffix = ""
executable_64bit_suffix = ""
shared_library_prefix   = ""
shared_library_32bit_suffix = ""
shared_library_64bit_suffix = ""

# Creates an archive handle for given archive name
def CreateArchive(archive_file_name):
    if sys.platform == "win32":
        archive_handle = zipfile.ZipFile(archive_file_name, 'w', zipfile.ZIP_DEFLATED)
    else:
        archive_handle = tarfile.open(archive_file_name, 'w:gz')
    print("Created archive %s at %s" % (archive_handle, archive_file_name))
    return archive_handle

# Write files to a valid archive
def WriteFileToArchive(archive_handle, file_absolute_path, file_path_in_archive):
    print("Adding file to archive: %s (as %s)" % (file_absolute_path, file_path_in_archive))
    if archive_handle is not None:
        if sys.platform == "win32":
            archive_handle.write(file_absolute_path, file_path_in_archive)
        else:
            archive_handle.add(file_absolute_path, file_path_in_archive)

arg_parser = argparse.ArgumentParser(description="GPA packaging arguments")
arg_parser.add_argument("--buildartifactsdir", help="GPA build artifacts directory")
arg_parser.add_argument("--buildnumber", type=int, help="GPA build number")
arg_parser.add_argument("--debug", action="store_true", help="Set to true to package debug bits")
arg_parser.add_argument("--archiveoutdir", help="Package output directory")
arg_parser.add_argument("--docsdir", help="GPA docs output directory")
arg_parser.add_argument("--android", action="store_true", help="Set to true to package android artifacts")
arg_parser.add_argument("--skip32bit", action="store_true", help="Set to true to skip 32-bit binaries")
arg_parser.add_argument("--suffix", action="store", required=False, help="A suffix to append to the package name (useful for unofficial builds)")


args = arg_parser.parse_args()


# Extract the GPA version number.
version_file_data = open(os.path.normpath(os.path.join(gpa_root, "source", "gpu_perf_api_common", "gpa_version.h")))
for line in version_file_data:
    if 'define GPA_MAJOR_VERSION ' in line:
        major = (line.split()[2])
    if 'define GPA_MINOR_VERSION ' in line:
        minor = (line.split()[2])
    if 'define GPA_UPDATE_VERSION ' in line:
        update = (line.split()[2])
    if 'define GPA_BUILD_NUMBER ' in line:
        revision = (line.split()[2])
        if args.buildnumber is not None:
            revision = args.buildnumber

version_string = str(major) + "." + str(minor) + "." + str(update) + "." + str(revision)


# Create the archive's suffix (ie: <GPUPerfAPI>[-Debug][-Android|-Linux]-<version>.[zip|tgz])
if args.debug:
    archive_suffix = archive_suffix + "-Debug"


if args.android:
    archive_suffix = archive_suffix + "-Android"
elif sys.platform == "linux":
    archive_suffix = archive_suffix + "-Linux"

archive_suffix = archive_suffix + "-" + version_string

if args.suffix is not None:
    archive_suffix = archive_suffix + "-" + args.suffix

if sys.platform == "win32":
    archive_suffix = archive_suffix + ".zip"
else:
    archive_suffix = archive_suffix + ".tgz"


# Create suffix for executables and shared libraries.
if sys.platform == "win32":
    executable_64bit_suffix     = executable_64bit_suffix     + "-x64"
    shared_library_64bit_suffix = shared_library_64bit_suffix + "-x64"
else:
    shared_library_prefix       = "lib"
    executable_32bit_suffix     = executable_32bit_suffix     + "32"
    shared_library_32bit_suffix = shared_library_32bit_suffix + "32"

if args.debug == True:
    executable_32bit_suffix     = executable_32bit_suffix     + "-d"
    executable_64bit_suffix     = executable_64bit_suffix     + "-d"
    shared_library_32bit_suffix = shared_library_32bit_suffix + "-d"
    shared_library_64bit_suffix = shared_library_64bit_suffix + "-d"


if sys.platform == "win32":
    executable_32bit_suffix     = executable_32bit_suffix     + ".exe"
    executable_64bit_suffix     = executable_64bit_suffix     + ".exe"
    shared_library_32bit_suffix = shared_library_32bit_suffix + ".dll"
    shared_library_64bit_suffix = shared_library_64bit_suffix + ".dll"
elif sys.platform == "darwin":
    shared_library_32bit_suffix = shared_library_32bit_suffix + ".dylib"
    shared_library_64bit_suffix = shared_library_64bit_suffix + ".dylib"
else:
    shared_library_32bit_suffix = shared_library_32bit_suffix + ".so"
    shared_library_64bit_suffix = shared_library_64bit_suffix + ".so"


def CreatePackage(args, archive_output_dir, binary_32bit_dir, binary_64bit_dir, sphinx_docs_dir, package_32_bit):
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

    if sys.platform.startswith("linux") or sys.platform == "win32":
        _gpa_binaries.append("GPUPerfAPIVK")
        _gpa_binaries.append("GPUPerfAPIGL")

    if sys.platform == "win32":
        _gpa_binaries.append("GPUPerfAPIDX11")
        _gpa_binaries.append("GPUPerfAPIDX12")
        _gpa_binaries.append("GPUPerfAPIDXGetAMDDeviceInfo")
        _gpa_binaries.append("GPUPerfAPICL")

    _other_files=["NOTICES.txt",
                 "LICENSE.txt"]

    if not os.path.exists(archive_output_dir):
        os.makedirs(archive_output_dir, exist_ok=True)
    os.chdir(archive_output_dir)
    gpa_archive_handle = CreateArchive("GPUPerfAPI" + archive_suffix)
    gpa_archive_root_name = str(major) + "_" + str(minor)

    if gpa_archive_handle is not None:
        if package_32_bit and not args.android:
            for target in _gpa_binaries:
                if target == "GPUPerfAPIGLES":
                    continue
                if sys.platform.startswith("linux"):
                    if target == "GPUPerfAPICL":
                        continue
                current_target_binary = shared_library_prefix + target + shared_library_32bit_suffix
                current_target_binary_abs_path = os.path.normpath(os.path.join(binary_32bit_dir, current_target_binary))
                current_target_path_in_archive = os.path.join(gpa_archive_root_name, "Bin")
                if sys.platform == "win32":
                    current_target_path_in_archive = os.path.join(current_target_path_in_archive, "x86",
                                                                    current_target_binary)
                else:
                    current_target_path_in_archive = os.path.join(current_target_path_in_archive, "Linx86",
                                                                    current_target_binary)
                WriteFileToArchive(gpa_archive_handle,
                                   current_target_binary_abs_path,
                                   current_target_path_in_archive)
        for target in _gpa_binaries:
            if args.android:
                if target == "GPUPerfAPICL":
                    continue
                if target == "GPUPerfAPIGL":
                    continue
            else:
                if target == "GPUPerfAPIGLES":
                    continue

            current_target_binary = shared_library_prefix + target + shared_library_64bit_suffix
            current_target_binary_abs_path = os.path.normpath(os.path.join(binary_64bit_dir, current_target_binary))
            current_target_path_in_archive = os.path.join(gpa_archive_root_name, "Bin")
            if sys.platform == "win32" or args.android:
                current_target_path_in_archive = os.path.join(current_target_path_in_archive, "x64", current_target_binary)
            else:
                current_target_path_in_archive = os.path.join(current_target_path_in_archive, "Linx64", current_target_binary)
            WriteFileToArchive(gpa_archive_handle, current_target_binary_abs_path, current_target_path_in_archive)

        ## Add GPA headers
        for header_path in _public_header_files:
            header_source_abs_path = os.path.normpath(os.path.join(gpa_root, "include", "gpu_performance_api", header_path))
            header_in_archive = os.path.normpath(os.path.join(gpa_archive_root_name, "Include", "gpu_performance_api", header_path))
            WriteFileToArchive(gpa_archive_handle, header_source_abs_path, header_in_archive)

        ## add old GPA headers (deprecated)
        for header_path in _old_includes:
            header_source_abs_path = os.path.normpath(os.path.join(gpa_root, "include", header_path))
            header_in_archive = os.path.normpath(os.path.join(gpa_archive_root_name, "Include", header_path))
            WriteFileToArchive(gpa_archive_handle, header_source_abs_path, header_in_archive)

        ## add new headers that are still in the old location (deprecated)
        for header_path in _public_header_files:
            header_source_abs_path = os.path.normpath(os.path.join(gpa_root, "include", header_path))
            header_in_archive = os.path.normpath(os.path.join(gpa_archive_root_name, "Include", header_path))
            WriteFileToArchive(gpa_archive_handle, header_source_abs_path, header_in_archive)


        for other_file in _other_files:
            other_file_abs_path = os.path.normpath(os.path.join(gpa_root, other_file))
            other_file_in_archive = os.path.normpath(os.path.join(gpa_archive_root_name, other_file))
            WriteFileToArchive(gpa_archive_handle, other_file_abs_path, other_file_in_archive)

        if (sphinx_docs_dir is not None) and (sphinx_docs_dir != ""):
            # Write docs
            gpa_docs_dir = os.path.normpath(os.path.join(sphinx_docs_dir, "html"))
            gpa_docs_dir_str = str(gpa_docs_dir)
            gpa_docs_dir_info = os.walk(gpa_docs_dir)

            if sys.platform == "win32":
                doc_folder_str = "\\docs"
            else:
                doc_folder_str = "/docs"

            file_count = 0
            for dirs, sub_dirs, files in gpa_docs_dir_info:
                for file in files:
                    file_count = file_count + 1
                    doc_file_abs_path = os.path.join(dirs, file)
                    doc_file_abs_path = os.path.normpath(doc_file_abs_path)
                    doc_file_abs_path_str = str(doc_file_abs_path)
                    doc_file_in_archive = gpa_archive_root_name + doc_folder_str + \
                                            doc_file_abs_path_str.split(gpa_docs_dir_str)[1]
                    WriteFileToArchive(gpa_archive_handle, doc_file_abs_path, doc_file_in_archive)

            if file_count == 0:
                raise Exception("Failed to find html documentation")

if (sys.platform == "win32") and args.android:
    print("Android packaging is not supported on Windows")
    sys.exit(1)

# Update directory to output the generated archive.
gpa_archive_out_dir = os.path.normpath(os.path.join(gpa_root, "build", "output"))
if args.archiveoutdir is not None:
    gpa_archive_out_dir = args.archiveoutdir

# Build the path to the compiled binaries.
config_str = "release"
config_suffix = ""
if args.debug:
    config_str = "debug"

if args.android:
    config_suffix = config_suffix + "_android"


if args.buildartifactsdir is not None:
    gpa_64bit_artifacts_dir = args.buildartifactsdir
    gpa_32bit_artifacts_dir = args.buildartifactsdir
else:
    gpa_64bit_artifacts_dir = os.path.normpath(os.path.join(gpa_root, "build", "output", config_str + "_x64" + config_suffix))
    gpa_32bit_artifacts_dir = os.path.normpath(os.path.join(gpa_root, "build", "output", config_str + "_x86" + config_suffix))


CreatePackage(args,
              archive_output_dir = gpa_archive_out_dir,
              binary_32bit_dir = gpa_32bit_artifacts_dir,
              binary_64bit_dir = gpa_64bit_artifacts_dir,
              sphinx_docs_dir = args.docsdir,
              package_32_bit = (not args.skip32bit))

