#!/usr/bin/python
## Copyright (c) 2019 Advanced Micro Devices, Inc. All rights reserved.
# Utility Python Script for gpa

import sys
import zipfile
import tarfile
import os
import subprocess
import urllib

SHELLARG = False
# The environment variable SHELL is only set for Cygwin or Linux
SHELLTYPE = os.environ.get('SHELL')
if ( SHELLTYPE == None ):
    # running on windows under default shell
    SHELLARG = True

if sys.version_info.major == 3:
    import urllib.request

# Write files to a valid archive
def WriteFileToArchive(archive_handle, file_absolute_path, file_path_in_archive):
    print("Adding file to archive %s: %s (as %s)" % (archive_handle, file_absolute_path, file_path_in_archive))
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
    print("Created archive %s at %s" % (archive_handle, archive_file_name))
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

def SwitchToBranchOrRef(localrepopath, branch_or_ref):
    if os.path.isdir(localrepopath):
        currentDir = os.getcwd()
        os.chdir(localrepopath)
        commandArgs = ["git", "checkout", branch_or_ref]
        try:
            sys.stdout.flush()
            p = subprocess.check_call(commandArgs, shell=SHELLARG)
            sys.stdout.flush()
            sys.stderr.flush()
            os.chdir(currentDir)
        except subprocess.CalledProcessError as e:
            print ("'git clone' failed with returncode: %d\n" % e.returncode)
            os.chdir(currentDir)
            sys.stderr.flush()
            sys.exit(1)

def CloneGitRepo(remote, branch, target):
    target = os.path.normpath(target)

    commandArgs = ["git", "clone", remote, target]

    try:
        sys.stdout.flush()
        subprocess.check_call(commandArgs, shell=SHELLARG)
        sys.stdout.flush()
        sys.stderr.flush()
    except subprocess.CalledProcessError as e:
        print ("'git clone' failed with returncode: %d\n" % e.returncode)
        sys.stderr.flush()
        return False

    # Use SwitchToBranchOrRef so that both branch names and commit hashes are supported.
    if branch is not None:
        SwitchToBranchOrRef(target, branch)

    return True

# verify a branch exists in a repository.
def VerifyBranch(repo_source, commit):
    reqd_commit = commit
    branch_found = False
    # reqd_commit may be "None". In this case return false to tell the caller to use a different branch.
    if reqd_commit is None:
        branch_found = False
    else:
        # Determine if branch exists in repository.
        # Assume master branch always exists.
        if reqd_commit == "master":
            branch_found = True
        else:
            branch_ref = "refs/heads/" + reqd_commit
            ls_remote_cmd = ["git", "ls-remote", repo_source, branch_ref]
            try:
                sys.stdout.flush()
                cmd_output = subprocess.check_output(ls_remote_cmd, shell=SHELLARG)
                sys.stdout.flush()
                sys.stderr.flush()
            except subprocess.CalledProcessError as e:
                print("Error attempting to query %s for information about branch %s."%(repo_source, commit))
                print("ReturnCode: %d"%e.returncode)
                sys.exit(1)
            if len(cmd_output) == 0:
                print("Git reference %s does not exist in %s."%(commit, repo_source))
                branch_found = False
            else:
                # output is in format "<sha_of_commit>     refs/heads/<branch_name>
                (commit_sha, commit_ref_dirty) = cmd_output.split(b'\t')
                commit_ref = commit_ref_dirty.replace(b'\n', b'')
                if commit_ref == branch_ref.encode():
                    branch_found = True
                else:
                    branch_found = False

    return branch_found
