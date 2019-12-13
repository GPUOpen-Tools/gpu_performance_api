#!/bin/bash

##=============================================================================
## Copyright (c) 2019 Advanced Micro Devices, Inc. All rights reserved.
## \author AMD Developer Tools Team
## \file
## \brief Script to change the file permission for device clock setting on Android
##=============================================================================
#

function ShowHelp
{
    echo "Usage:"
    echo "    $0 -t <IP address[:port]>"
    echo
    echo "    -t  --target <IP address[:port]>"
    echo "            IP address and port for the target android device, if port is not specified, adb default port is used"
    echo "    -h, --help"
    echo "            Display this help and exit"
}

adb_exists=`adb --version`

if [ $# -eq 0 ]; then
    ShowHelp
    exit 1
fi

if [ -z "$adb_exists" ]
then
    echo "adb not found. Please install adb."
    exit 1
fi

while [[ $# -gt 0 ]]; do
  option="$1"
  case ${option} in
    -t|--target)
      target="$2"
      shift # past argument
      shift # past value
      ;;
    -h|--help)
      ShowHelp
      exit 0
      ;;
    *)
      echo "ERROR: Unsupported option ${option}. See Usage"
      echo
      ShowHelp
      exit 1
      ;;
  esac
done

function VerifyTargetInConnectedDevices
{
    adb_connected_device_list=`adb devices | grep ${target}`
}

target_connected=0

VerifyTargetInConnectedDevices
if [ -z "${adb_connected_device_list}" ]
then
    adb_connect=`adb connect ${target}`

    VerifyTargetInConnectedDevices
    if [ -z "${adb_connected_device_list}" ]
    then
        echo "Failed to connect ${target}"
        echo $adb_connect
        exit 1
    else
        echo "Successfully connected to ${target}"
        target_connected=1
    fi
else
    echo "$target already connected"
    target_connected=1
fi

if [ $target_connected -eq 1 ]
then
    # target is connected, change the permission of the file
    change_permission=`adb -s $target shell chmod 766 /sys/class/drm/card0/device/power_dpm_force_performance_level`
    if [ -z "$change_permission" ]
    then
        file_permission=`adb -s $target shell ls -l /sys/class/drm/card0/device/power_dpm_force_performance_level`
        echo "File permission changed successfully"
        echo "$file_permission"
    fi
fi




