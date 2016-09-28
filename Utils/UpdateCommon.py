#! /usr/bin/python
#
# Simple script to update a set of common directories that are needed as dependencies of the current project

import os
import string
import subprocess
import sys

# GPUPerfAPI git project to folder map definitions
# - GitHubMapping
from UpdateCommonMap import *

# to allow the script to be run from anywhere - not just the cwd - store the absolute path to the script file
scriptRoot = os.path.dirname(os.path.realpath(__file__))

# for each GitHub dependency - test if it has already been fetched - if not, then fetch it, 
# otherwise update it to top of tree

for key in GitHubMapping:
    # convert targetPath to OS specific format
    tmppath = os.path.join(scriptRoot, "..", GitHubMapping[key])
    # clean up path, collapsing any ../ and converting / to \ for Windows
    targetPath = os.path.normpath(tmppath)
    if os.path.isdir(targetPath):
        print("\nDirectory " + targetPath + " exists, using 'git pull' to get latest")
        p = subprocess.Popen(["git","pull"], cwd=targetPath)
        p.wait();
    else:
        print("\nDirectory " + targetPath + " does not exist, using 'git clone' to get latest")
        gitamdRoot = "https://github.com/GPUOpen-Tools/" + key
        commandArgs = ["git", "clone", gitamdRoot, targetPath]
        p = subprocess.Popen( commandArgs )
        p.wait()

