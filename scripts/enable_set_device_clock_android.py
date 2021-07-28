#!/usr/bin/python3
##=============================================================================
## Copyright (c) 2019-2021 Advanced Micro Devices, Inc. All rights reserved.
## \author AMD Developer Tools Team
## \file
## \brief Script to change the file permission for device clock setting on Android
##=============================================================================
#
import argparse
import os.path
import sys
import subprocess
import platform

parser = argparse.ArgumentParser(description="Changes the file permission for device clock setting on Android")
parser.add_argument("-t", "--target", required=True, help="IP address of Android device")
parser.add_argument("-d", "--device", help="adb device ID, as seen in 'adb devices'. This or -i must be specified when multiple devices are available.")
parser.add_argument("-i", "--infer", action="store", metavar="PORT", nargs="?", const="5555", help="Specify this when using ADB over TCP/IP, to infer the -d argument from the -t one. This option saves you from having to specify the device IP address twice. Port 5555 is used if no port is specified. This or -d must be specified when multiple devices are available.")
args = parser.parse_args()

# Check that we have adb in PATH, that it sees a device and the device is
# in a usable state
proc = subprocess.Popen(["adb", "--help"], stdout=subprocess.DEVNULL)
proc.communicate()
if proc.returncode != 0:
    sys.stderr.write("Error: adb not in PATH\n")
    exit(1)

proc = subprocess.Popen(["adb", "devices"], stdout=subprocess.PIPE)
output = proc.communicate()[0].decode()
if proc.returncode != 0:
    sys.stderr.write("Error: unexpected error querying adb devices\n")
    exit(1)

lines = output.strip().splitlines()
if lines[0] != "List of devices attached":
    sys.stderr.write("Error: unexpected output from 'adb devices'\n")
    exit(1)

if len(lines) > 2 and not (args.device or args.infer):
    sys.stderr.write("Error: Multiple Android devices available; must specify one with -d or -i\n")
    for line in lines[1:]:
        sys.stderr.write("   {}\n".format(line))
    exit(1)

device = args.device
if device is None and args.infer:
    device = args.target + ":" + args.infer

if device is None:
    proc = subprocess.Popen(["adb", "get-serialno"], stdout=subprocess.PIPE)
    device = proc.communicate()[0].decode().strip()

proc = subprocess.Popen(["adb", "-s", device, "get-state"], stdout=subprocess.PIPE)
output = proc.communicate()[0].decode().strip()
if proc.returncode != 0:
    # No need for explicit message; adb already reported device not found
    exit(1)
if output != "device":
    sys.stderr.write("Error: adb device is not in a usable state\n")
    exit(1)

# sysfs permission needs to be changed:
subprocess.call(["adb", "-s", device, "shell", "su", "root", "chmod", "766", "/sys/class/drm/card0/device/power_dpm_force_performance_level"])
