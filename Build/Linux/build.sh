#!/bin/bash
set -u

#define path
GPAROOT=`dirname $(readlink -f "$0")`/../..

# Command line args

# Generate internal build
bBuildInternal=false

# Generate zip file
bZip=false

# Build number
BUILD=0

# Skip 32-bit build
b32bitbuild=true

# Incremental build
bIncrementalBuild=false

# Debug build requested
bDebugBuild=false
MAKE_TARGET=
DEBUG_SUFFIX=

# HSA directory override
HSA_DIR_OVERRIDE=

# Vulkan include directory override
VK_INC_DIR_OVERRIDE=

# API-specific build control
bBuildOpenGL=true
bBuildOpenGLES=true
bBuildVK=true
bBuildOpenCL=true
bBuildHSA=true

# Tests build control
bBuildTests=true

REL_ROOT=
BUILD=0

# GoogleTest Lib directory override
GTEST_LIB_DIR_OVERRIDE=

# GoogleTest 32-bit Lib directory override
GTEST_LIB_DIR_OVERRIDE32=

# Additional compiler defines override
ADDITIONAL_COMPILER_DEFINES_OVERRIDE="ADDITIONAL_COMPILER_DEFINES_FROM_BUILD_SCRIPT="

# Set build flag
while [ "$*" != "" ]
do
   if [ "$1" = "build-internal" ]; then
      bBuildInternal=true
   elif [ "$1" = "zip" ]; then
      bZip=true
   elif [ "$1" = "skip32bitbuild" ]; then
      b32bitbuild=false
   elif [ "$1" = "bldnum" ]; then
      shift
      BUILD="$1"
   elif [ "$1" = "debug" ]; then
      bDebugBuild=true
      MAKE_TARGET=Dbg
      DEBUG_SUFFIX=-d
   elif [ "$1" = "hsadir" ]; then
      shift
      HSA_DIR_OVERRIDE="HSA_DIR=$1"
   elif [ "$1" = "vkincdir" ]; then
      shift
      VK_INC_DIR_OVERRIDE="VK_INCLUDE_DIR=$1"
   elif [ "$1" = "skipopengl" ]; then
      bBuildOpenGL=false
   elif [ "$1" = "skipopengles" ]; then
      bBuildOpenGLES=false
   elif [ "$1" = "skipvulkan" ]; then
      bBuildVK=false
   elif [ "$1" = "skipopencl" ]; then
      bBuildOpenCL=false
   elif [ "$1" = "skiphsa" ]; then
      bBuildHSA=false
   elif [ "$1" = "skiptests" ]; then
      bBuildTests=false
   elif [ "$1" = "incremental" ]; then
      bIncrementalBuild=true
   elif [ "$1" = "quick" ]; then
      bIncrementalBuild=true
   elif [ "$1" = "gtestlibdir" ]; then
      shift
      GTEST_LIB_DIR_OVERRIDE="GTEST_LIBS=$1/libgtest.a"
   elif [ "$1" = "gtestlibdir32" ]; then
      shift
      GTEST_LIB_DIR_OVERRIDE32="GTEST_LIBS32=$1/libgtest.a"
   elif [ "$1" = "additionaldefines" ]; then
      shift
      ADDITIONAL_COMPILER_DEFINES_OVERRIDE="ADDITIONAL_COMPILER_DEFINES_FROM_BUILD_SCRIPT=$1"
   fi
   shift
done

LOGFILE=$GPAROOT/Build/Linux/GPUPerfAPI_Build.log
GPASRC=$GPAROOT/Src
GPUPERFAPI=$GPASRC/GPUPerfAPI
CL=$GPASRC/GPUPerfAPICL
HSA=$GPASRC/GPUPerfAPIHSA
GL=$GPASRC/GPUPerfAPIGL
GLES=$GPASRC/GPUPerfAPIGLES
VK=$GPASRC/GPUPerfAPIVk
COUNTERS=$GPASRC/GPUPerfAPICounters
COUNTERGENERATOR=$GPASRC/GPUPerfAPICounterGenerator
GPA_COMMON=$GPASRC/GPUPerfAPI-Common
GPA_DEVICEINFO=$GPASRC/DeviceInfo
UNITTESTS=$GPASRC/GPUPerfAPIUnitTests
GPADOC=$GPAROOT/Doc

GPAOUTPUT=$GPAROOT/Output
GPAOUTPUT_BIN=$GPAOUTPUT/bin
GPAOUTPUT_LIB=$GPAOUTPUT/lib

GLLIB=libGPUPerfAPIGL$DEBUG_SUFFIX.so
GLESLIB=libGPUPerfAPIGLES$DEBUG_SUFFIX.so
VKLIB=libGPUPerfAPIVK$DEBUG_SUFFIX.so
CLLIB=libGPUPerfAPICL$DEBUG_SUFFIX.so
HSALIB=libGPUPerfAPIHSA$DEBUG_SUFFIX.so
COUNTERSLIB=libGPUPerfAPICounters$DEBUG_SUFFIX.so
COUNTERGENERATORLIB=libGPUPerfAPICounterGenerator$DEBUG_SUFFIX.a
GPA_COMMONLIB=libGPUPerfAPI-Common$DEBUG_SUFFIX.a
GPA_DEVICEINFOLIB=libDeviceInfo$DEBUG_SUFFIX.a

GLLIB32=libGPUPerfAPIGL32$DEBUG_SUFFIX.so
GLESLIB32=libGPUPerfAPIGLES32$DEBUG_SUFFIX.so
VKLIB32=libGPUPerfAPIVK32$DEBUG_SUFFIX.so
CLLIB32=libGPUPerfAPICL32$DEBUG_SUFFIX.so
COUNTERSLIB32=libGPUPerfAPICounters32$DEBUG_SUFFIX.so
COUNTERGENERATORLIB32=libGPUPerfAPICounterGenerator32$DEBUG_SUFFIX.a
GPA_COMMONLIB32=libGPUPerfAPI-Common32$DEBUG_SUFFIX.a
GPA_DEVICEINFOLIB32=libDeviceInfo32$DEBUG_SUFFIX.a

GLLIB_INTERNAL=libGPUPerfAPIGL$DEBUG_SUFFIX-Internal.so
GLESLIB_INTERNAL=libGPUPerfAPIGLES$DEBUG_SUFFIX-Internal.so
VKLIB_INTERNAL=libGPUPerfAPIVK$DEBUG_SUFFIX-Internal.so
CLLIB_INTERNAL=libGPUPerfAPICL$DEBUG_SUFFIX-Internal.so
HSALIB_INTERNAL=libGPUPerfAPIHSA$DEBUG_SUFFIX-Internal.so
COUNTERSLIB_INTERNAL=libGPUPerfAPICounters$DEBUG_SUFFIX-Internal.so
COUNTERGENERATORLIB_INTERNAL=libGPUPerfAPICounterGenerator$DEBUG_SUFFIX-Internal.a
GPA_COMMONLIB_INTERNAL=libGPUPerfAPI-Common$DEBUG_SUFFIX-Internal.a
GPA_DEVICEINFOLIB_INTERNAL=libDeviceInfo$DEBUG_SUFFIX-Internal.a

GLLIB32_INTERNAL=libGPUPerfAPIGL32$DEBUG_SUFFIX-Internal.so
GLESLIB32_INTERNAL=libGPUPerfAPIGLES32$DEBUG_SUFFIX-Internal.so
VKLIB32_INTERNAL=libGPUPerfAPIVK32$DEBUG_SUFFIX-Internal.so
CLLIB32_INTERNAL=libGPUPerfAPICL32$DEBUG_SUFFIX-Internal.so
COUNTERSLIB32_INTERNAL=libGPUPerfAPICounters32$DEBUG_SUFFIX-Internal.so
COUNTERGENERATORLIB32_INTERNAL=libGPUPerfAPICounterGenerator32$DEBUG_SUFFIX-Internal.a
GPA_COMMONLIB32_INTERNAL=libGPUPerfAPI-Common32$DEBUG_SUFFIX-Internal.a
GPA_DEVICEINFOLIB32_INTERNAL=libDeviceInfo32$DEBUG_SUFFIX-Internal.a

UNITTEST=GPUPerfAPIUnitTests$DEBUG_SUFFIX
UNITTEST32=GPUPerfAPIUnitTests32$DEBUG_SUFFIX
UNITTEST_INTERNAL=GPUPerfAPIUnitTests$DEBUG_SUFFIX-Internal
UNITTEST32_INTERNAL=GPUPerfAPIUnitTests32$DEBUG_SUFFIX-Internal

BUILD_DIR_BASE=$GPAROOT/Build
BUILD_DIR=$BUILD_DIR_BASE/Linux

# retrieve version number from Windows Jenkins configuration file file
VERSION_NUMBER_FILE=$GPA_COMMON/GPAVersion.h

VER_MAJOR=$(grep -E "#define GPA_MAJOR_VERSION\s*[0-9]+" $VERSION_NUMBER_FILE | awk '{print $3}')
VER_MINOR=$(grep -E "#define GPA_MINOR_VERSION\s*[0-9]+" $VERSION_NUMBER_FILE | awk '{print $3}')
VER_MAJOR_MINOR=$VER_MAJOR.$VER_MINOR
VER=$VER_MAJOR_MINOR.$BUILD

CPU_COUNT=`cat /proc/cpuinfo | grep processor | wc -l`

BUILD_DIRS="$GPUPERFAPI $GPA_COMMON $GPA_DEVICEINFO $COUNTERGENERATOR $COUNTERS"

if $bBuildOpenGL ; then
   BUILD_DIRS="$BUILD_DIRS $GL"
fi

if $bBuildOpenGLES ; then
   BUILD_DIRS="$BUILD_DIRS $GLES"
fi

if $bBuildVK ; then
   BUILD_DIRS="$BUILD_DIRS $VK"
fi

if $bBuildOpenCL ; then
   BUILD_DIRS="$BUILD_DIRS $CL"
fi

if $bBuildHSA ; then
   BUILD_DIRS="$BUILD_DIRS $HSA"
fi

if $bBuildTests ; then
   BUILD_DIRS="$BUILD_DIRS $UNITTESTS"
fi

for SUBDIR in $BUILD_DIRS; do
   BASENAME=`basename $SUBDIR`

   #delete old build
   if !($bIncrementalBuild) ; then
      make -C $SUBDIR spotless >> $LOGFILE 2>&1
   fi

   #make 64 bit
   echo "Build ${BASENAME}, 64-bit..." | tee -a $LOGFILE

   if ! make -C $SUBDIR -j$CPU_COUNT $HSA_DIR_OVERRIDE $VK_INC_DIR_OVERRIDE $GTEST_LIB_DIR_OVERRIDE "$ADDITIONAL_COMPILER_DEFINES_OVERRIDE" ${MAKE_TARGET} >> $LOGFILE 2>&1; then
      echo "Failed to build ${BASENAME}, 64 bit"
      exit 1
   fi

   #make 64 bit Internal
   if $bBuildInternal ; then
      if ! make -C $SUBDIR -j$CPU_COUNT $HSA_DIR_OVERRIDE $VK_INC_DIR_OVERRIDE $GTEST_LIB_DIR_OVERRIDE "$ADDITIONAL_COMPILER_DEFINES_OVERRIDE" ${MAKE_TARGET}Internal  >> $LOGFILE 2>&1; then
         echo "Failed to build ${BASENAME}, 64 bit, Internal"
         exit 1
      fi
   fi

   if $b32bitbuild; then
      if [ "$SUBDIR" != "$HSA" ]; then
         #make 32 bit
         echo "Build ${BASENAME}, 32-bit..." | tee -a $LOGFILE

         if ! make -C $SUBDIR -j$CPU_COUNT $HSA_DIR_OVERRIDE $VK_INC_DIR_OVERRIDE $GTEST_LIB_DIR_OVERRIDE32 "$ADDITIONAL_COMPILER_DEFINES_OVERRIDE" ${MAKE_TARGET}x86 >> $LOGFILE 2>&1; then
            echo "Failed to build ${BASENAME}, 32 bit"
            exit 1
         fi

         #make 32 bit Internal
         if $bBuildInternal ; then
            if ! make -C $SUBDIR -j$CPU_COUNT $HSA_DIR_OVERRIDE $VK_INC_DIR_OVERRIDE $GTEST_LIB_DIR_OVERRIDE32 "$ADDITIONAL_COMPILER_DEFINES_OVERRIDE" ${MAKE_TARGET}Internalx86  >> $LOGFILE 2>&1; then
               echo "Failed to build ${BASENAME}, 32 bit, Internal"
               exit 1
            fi
         fi
      fi
   fi
done

#-----------------------------------------
#copy to bin folder
#-----------------------------------------

if $bZip ; then
   echo "Generate tarball..." | tee -a $LOGFILE
   ZIP_DIR_NAME=${VER_MAJOR}_${VER_MINOR}
   cd $GPAOUTPUT
   mkdir $ZIP_DIR_NAME
   cd $ZIP_DIR_NAME
   mkdir Bin
   mkdir Bin/Linx64
   mkdir Bin/Linx86
   cp $GPAOUTPUT_BIN/$CLLIB ./Bin/Linx64/
   cp $GPAOUTPUT_BIN/$HSALIB ./Bin/Linx64/
   cp $GPAOUTPUT_BIN/$GLLIB ./Bin/Linx64/
   cp $GPAOUTPUT_BIN/$GLESLIB ./Bin/Linx64/
   cp $GPAOUTPUT_BIN/$VKLIB ./Bin/Linx64/
   cp $GPAOUTPUT_BIN/$CLLIB32 ./Bin/Linx86/
   cp $GPAOUTPUT_BIN/$GLLIB32 ./Bin/Linx86/
   cp $GPAOUTPUT_BIN/$GLESLIB32 ./Bin/Linx86/
   cp $GPAOUTPUT_BIN/$VKLIB32 ./Bin/Linx86/
   cp $GPAOUTPUT_BIN/$COUNTERSLIB ./Bin/Linx64/
   cp $GPAOUTPUT_BIN/$COUNTERSLIB32 ./Bin/Linx86/
   mkdir Include
   cp $GPA_COMMON/GPUPerfAPI.h ./Include/
   cp $GPA_COMMON/GPUPerfAPIFunctionTypes.h ./Include/
   cp $GPA_COMMON/GPUPerfAPITypes.h ./Include/
   cp $GPA_COMMON/GPAFunctions.h ./Include/
   cp $GPA_COMMON/GPUPerfAPI-HSA.h ./Include/
   cp $GPA_COMMON/GPUPerfAPI-VK.h ./Include/
   cp $GPA_COMMON/GPAInterfaceLoader.h ./Include/
   cp $COUNTERS/GPUPerfAPICounters.h ./Include/
   cp $COUNTERGENERATOR/GPACounterGenerator.h ./Include/
   cp $COUNTERGENERATOR/IGPACounterAccessor.h ./Include/
   cp $COUNTERGENERATOR/IGPACounterScheduler.h ./Include/
   cp $GPADOC/GPUPerfAPI-UserGuide.pdf .
   cp $GPAROOT/LICENSE .
   cp $GPADOC/thirdpartylicenses.txt .
   cd ..
   tar cvzf GPUPerfAPI.$VER-lnx.tgz $ZIP_DIR_NAME/

   #-----------------------------------------
   #copy to bin-Internal folder
   #-----------------------------------------
   if $bBuildInternal ; then
      cd $ZIP_DIR_NAME
      mkdir Bin-Internal
      mkdir Bin-Internal/Linx64
      mkdir Bin-Internal/Linx86

      # internal libs
      cp $GPAOUTPUT_BIN/$CLLIB_INTERNAL ./Bin-Internal/Linx64/
      cp $GPAOUTPUT_BIN/$HSALIB_INTERNAL ./Bin-Internal/Linx64/
      cp $GPAOUTPUT_BIN/$GLLIB_INTERNAL ./Bin-Internal/Linx64/
      cp $GPAOUTPUT_BIN/$GLESLIB_INTERNAL ./Bin-Internal/Linx64/
      cp $GPAOUTPUT_BIN/$VKLIB_INTERNAL ./Bin-Internal/Linx64/
      cp $GPAOUTPUT_BIN/$COUNTERSLIB_INTERNAL ./Bin-Internal/Linx64/

      cp $GPAOUTPUT_BIN/$CLLIB32_INTERNAL ./Bin-Internal/Linx86/
      cp $GPAOUTPUT_BIN/$GLLIB32_INTERNAL ./Bin-Internal/Linx86/
      cp $GPAOUTPUT_BIN/$GLESLIB32_INTERNAL ./Bin-Internal/Linx86/
      cp $GPAOUTPUT_BIN/$VKLIB32_INTERNAL ./Bin-Internal/Linx86/
      cp $GPAOUTPUT_BIN/$COUNTERSLIB32_INTERNAL ./Bin-Internal/Linx86/

      cd ..
      tar cvzf GPUPerfAPI.$VER-lnx-Promotion.tgz $ZIP_DIR_NAME/
   fi
fi

if [ -z ${LD_LIBRARY_PATH+x} ]; then
   LD_LIBRARY_PATH=
fi

if $bBuildTests ; then
   LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$GPAOUTPUT_BIN $GPAOUTPUT_BIN/$UNITTEST --gtest_output=xml:$GPAOUTPUT/$UNITTEST.xml

   if $b32bitbuild ; then
      LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$GPAOUTPUT_BIN $GPAOUTPUT_BIN/$UNITTEST32 --gtest_output=xml:$GPAOUTPUT/$UNITTEST32.xml
   fi

   if $bBuildInternal ; then
      LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$GPAOUTPUT_BIN $GPAOUTPUT_BIN/$UNITTEST_INTERNAL --gtest_output=xml:$GPAOUTPUT/$UNITTEST_INTERNAL.xml

      if $b32bitbuild ; then
         LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$GPAOUTPUT_BIN $GPAOUTPUT_BIN/$UNITTEST32_INTERNAL --gtest_output=xml:$GPAOUTPUT/$UNITTEST32_INTERNAL.xml
      fi
   fi
fi

echo "Build Complete" | tee -a $LOGFILE
