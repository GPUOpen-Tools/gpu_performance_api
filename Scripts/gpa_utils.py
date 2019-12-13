#!/usr/bin/python
## Copyright (c) 2019 Advanced Micro Devices, Inc. All rights reserved.
# Utility Python Script for gpa

import sys
import zipfile
import tarfile
import os
import subprocess
import urllib

if sys.version_info.major == 3:
    import urllib.request

# Write files to a valid archive
def WriteFileToArchive(archive_handle, file_absolute_path, file_path_in_archive):
    if archive_handle is not None:
        if sys.platform == "win32":
            archive_handle.write(file_absolute_path, file_path_in_archive)
        else:
            archive_handle.add(file_absolute_path, file_path_in_archive)

# Creates an archive handle for given archive name
def CreateArchive(archive_file_name):
    if sys.platform == "win32":
        archive_handle = zipfile.ZipFile(archive_file_name, 'w', zipfile.ZIP_DEFLATED)
    else:
        archive_handle = tarfile.open(archive_file_name, 'w:gz')
    return archive_handle

# Returns the SHA of the HEAD of the repo on local machine
def GetGitLocalRepoHead(git_local_repo_path):
    if os.path.isdir(git_local_repo_path):
        # current_dir = os.getcwd()
        # os.chdir(git_local_repo_path)
        try:
            git_process = subprocess.Popen(["git", "-C", git_local_repo_path,   \
             "rev-list", "-1", "HEAD"], shell=False, stdout=subprocess.PIPE)
        except subprocess.CalledProcessError as error:
            print("process creation for git rev-list failed")

        git_process.wait()
        revision = git_process.communicate()[0]
        revision_str = revision.decode()
        revision_str = revision_str.strip()
        # os.chdir(current_dir)
        return revision_str
    return None

# Downloads file from URL
def Download(source_url, dest_dir, file_name):
    # Assuming path is absolute
    if False == os.path.isabs(dest_dir):
        print("Destination path is not valid")
        return False

    # clean up path, collapsing any ../ and converting / to \ for Windows
    dest_dir = os.path.normpath(dest_dir)

    if False == os.path.isdir(dest_dir):
        os.makedirs(dest_dir)

    dest_path = os.path.join(dest_dir, file_name)
    print("Downloading " + file_name + " to " + dest_dir)

    if sys.version_info.major < 3:
        urllib.urlretrieve(source_url, dest_path)
    else:
        urllib.request.urlretrieve(source_url, dest_path)

    if (os.path.isfile(dest_path)):
        print("File Downloaded Successfully")
        return True
    else:
        print("Unable to download file")
        return False
