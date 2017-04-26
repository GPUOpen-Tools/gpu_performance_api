#!/bin/bash

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

# API-specific build control
bBuildOpenGL=true
bBuildOpenGLES=true
bBuildOpenCL=true
bBuildHSA=true

REL_ROOT=
BUILD=0

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
   elif [ "$1" = "skipopengl" ]; then
      bBuildOpenGL=false
   elif [ "$1" = "skipopengles" ]; then
      bBuildOpenGLES=false
   elif [ "$1" = "skipopencl" ]; then
      bBuildOpenCL=false
   elif [ "$1" = "skiphsa" ]; then
      bBuildHSA=false
   elif [ "$1" = "incremental" ]; then
      bIncrementalBuild=true
   elif [ "$1" = "quick" ]; then
      bIncrementalBuild=true
   fi
   shift
done

LOGFILE=$GPAROOT/Build/Linux/GPUPerfAPI_Build.log
GPASRC=$GPAROOT/Src
CL=$GPASRC/GPUPerfAPICL
HSA=$GPASRC/GPUPerfAPIHSA
GL=$GPASRC/GPUPerfAPIGL
GLES=$GPASRC/GPUPerfAPIGLES
COUNTERS=$GPASRC/GPUPerfAPICounters
COUNTERGENERATOR=$GPASRC/GPUPerfAPICounterGenerator
GPA_COMMON=$GPASRC/GPUPerfAPI-Common
GPA_DEVICEINFO=$GPASRC/DeviceInfo

GLLIB=libGPUPerfAPIGL$DEBUG_SUFFIX.so
GLESLIB=libGPUPerfAPIGLES$DEBUG_SUFFIX.so
CLLIB=libGPUPerfAPICL$DEBUG_SUFFIX.so
HSALIB=libGPUPerfAPIHSA$DEBUG_SUFFIX.so
COUNTERSLIB=libGPUPerfAPICounters$DEBUG_SUFFIX.so
COUNTERGENERATORLIB=libGPUPerfAPICounterGenerator$DEBUG_SUFFIX.a
GPA_COMMONLIB=libGPUPerfAPI-Common$DEBUG_SUFFIX.a
GPA_DEVICEINFOLIB=libDeviceInfo$DEBUG_SUFFIX.a

GLLIB32=libGPUPerfAPIGL32$DEBUG_SUFFIX.so
GLESLIB32=libGPUPerfAPIGLES32$DEBUG_SUFFIX.so
CLLIB32=libGPUPerfAPICL32$DEBUG_SUFFIX.so
COUNTERSLIB32=libGPUPerfAPICounters32$DEBUG_SUFFIX.so
COUNTERGENERATORLIB32=libGPUPerfAPICounterGenerator32$DEBUG_SUFFIX.a
GPA_COMMONLIB32=libGPUPerfAPI-Common32$DEBUG_SUFFIX.a
GPA_DEVICEINFOLIB32=libDeviceInfo32$DEBUG_SUFFIX.a

GLLIB_INTERNAL=libGPUPerfAPIGL$DEBUG_SUFFIX-Internal.so
GLESLIB_INTERNAL=libGPUPerfAPIGLES$DEBUG_SUFFIX-Internal.so
CLLIB_INTERNAL=libGPUPerfAPICL$DEBUG_SUFFIX-Internal.so
HSALIB_INTERNAL=libGPUPerfAPIHSA$DEBUG_SUFFIX-Internal.so
COUNTERSLIB_INTERNAL=libGPUPerfAPICounters$DEBUG_SUFFIX-Internal.so
COUNTERGENERATORLIB_INTERNAL=libGPUPerfAPICounterGenerator$DEBUG_SUFFIX-Internal.a
GPA_COMMONLIB_INTERNAL=libGPUPerfAPI-Common$DEBUG_SUFFIX-Internal.a
GPA_DEVICEINFOLIB_INTERNAL=libDeviceInfo$DEBUG_SUFFIX-Internal.a

GLLIB32_INTERNAL=libGPUPerfAPIGL32$DEBUG_SUFFIX-Internal.so
GLESLIB32_INTERNAL=libGPUPerfAPIGLES32$DEBUG_SUFFIX-Internal.so
CLLIB32_INTERNAL=libGPUPerfAPICL32$DEBUG_SUFFIX-Internal.so
COUNTERSLIB32_INTERNAL=libGPUPerfAPICounters32$DEBUG_SUFFIX-Internal.so
COUNTERGENERATORLIB32_INTERNAL=libGPUPerfAPICounterGenerator32$DEBUG_SUFFIX-Internal.a
GPA_COMMONLIB32_INTERNAL=libGPUPerfAPI-Common32$DEBUG_SUFFIX-Internal.a
GPA_DEVICEINFOLIB32_INTERNAL=libDeviceInfo32$DEBUG_SUFFIX-Internal.a

BUILD_DIR_BASE=$GPAROOT/Build
BUILD_DIR=$BUILD_DIR_BASE/Linux

# retrieve version number from Windows Jenkins configuration file file
VERSION_NUMBER_FILE=$GPA_COMMON/GPAVersion.h

VER_MAJOR=$(grep -E "#define GPA_MAJOR_VERSION\s*[0-9]+" $VERSION_NUMBER_FILE | awk '{print $3}')
VER_MINOR=$(grep -E "#define GPA_MINOR_VERSION\s*[0-9]+" $VERSION_NUMBER_FILE | awk '{print $3}')
VER_MAJOR_MINOR=$VER_MAJOR.$VER_MINOR
VER=$VER_MAJOR_MINOR.$BUILD

CPU_COUNT=`cat /proc/cpuinfo | grep processor | wc -l`

BUILD_DIRS="$GPA_COMMON $GPA_DEVICEINFO $COUNTERGENERATOR $COUNTERS"

if $bBuildOpenGL ; then
   BUILD_DIRS="$BUILD_DIRS $GL"
fi

if $bBuildOpenGLES ; then
   BUILD_DIRS="$BUILD_DIRS $GLES"
fi

if $bBuildOpenCL ; then
   BUILD_DIRS="$BUILD_DIRS $CL"
fi

if $bBuildHSA ; then
   BUILD_DIRS="$BUILD_DIRS $HSA"
fi

for SUBDIR in $BUILD_DIRS; do
   BASENAME=`basename $SUBDIR`

   #delete old build
   if !($bIncrementalBuild) ; then
      make -C $SUBDIR spotless >> $LOGFILE 2>&1
   fi

   #make 64 bit
   echo "Build ${BASENAME}, 64-bit..." | tee -a $LOGFILE

   if ! make -C $SUBDIR -j$CPU_COUNT $HSA_DIR_OVERRIDE ${MAKE_TARGET} >> $LOGFILE 2>&1; then
      echo "Failed to build ${BASENAME}, 64 bit"
      exit 1
   fi

   #make 64 bit Internal
   if $bBuildInternal ; then
      if ! make -C $SUBDIR -j$CPU_COUNT $HSA_DIR_OVERRIDE ${MAKE_TARGET}Internal  >> $LOGFILE 2>&1; then
         echo "Failed to build ${BASENAME}, 64 bit, Internal"
         exit 1
      fi
   fi

   if $b32bitbuild; then
      if [ "$SUBDIR" != "$HSA" ]; then
         #make 32 bit
         echo "Build ${BASENAME}, 32-bit..." | tee -a $LOGFILE

         if ! make -C $SUBDIR -j$CPU_COUNT $HSA_DIR_OVERRIDE ${MAKE_TARGET}x86 >> $LOGFILE 2>&1; then
            echo "Failed to build ${BASENAME}, 32 bit"
            exit 1
         fi

         #make 32 bit Internal
         if $bBuildInternal ; then
            if ! make -C $SUBDIR -j$CPU_COUNT $HSA_DIR_OVERRIDE ${MAKE_TARGET}Internalx86  >> $LOGFILE 2>&1; then
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
   cd $BUILD_DIR
   mkdir $ZIP_DIR_NAME
   cd $ZIP_DIR_NAME
   mkdir Bin
   mkdir Bin/Linx64
   mkdir Bin/Linx86
   cp $CL/$CLLIB ./Bin/Linx64/
   cp $HSA/$HSALIB ./Bin/Linx64/
   cp $GL/$GLLIB ./Bin/Linx64/
   cp $GLES/$GLESLIB ./Bin/Linx64/
   cp $CL/$CLLIB32 ./Bin/Linx86/
   cp $GL/$GLLIB32 ./Bin/Linx86/
   cp $GLES/$GLESLIB32 ./Bin/Linx86/
   cp $COUNTERS/$COUNTERSLIB ./Bin/Linx64/
   cp $COUNTERS/$COUNTERSLIB32 ./Bin/Linx86/
   mkdir Include
   cp ../../../Src/GPUPerfAPI-Common/GPUPerfAPI.h ./Include/
   cp ../../../Src/GPUPerfAPI-Common/GPUPerfAPIFunctionTypes.h ./Include/
   cp ../../../Src/GPUPerfAPI-Common/GPUPerfAPITypes.h ./Include/
   cp ../../../Src/GPUPerfAPI-Common/GPUPerfAPI-Private.h ./Include/
   cp ../../../Src/GPUPerfAPI-Common/GPUPerfAPIFunctionTypes-Private.h ./Include/
   cp ../../../Src/GPUPerfAPI-Common/GPUPerfAPITypes-Private.h ./Include/
   cp ../../../Src/GPUPerfAPI-Common/GPAFunctions.h ./Include/
   cp ../../../Src/GPUPerfAPI-Common/GPUPerfAPI-HSA.h ./Include/
   cp ../../../Src/GPUPerfAPI-Common/GPUPerfAPIOS.h ./Include/
   cp ../../../Src/GPUPerfAPICounters/GPUPerfAPICounters.h ./Include/
   cp ../../../Src/GPUPerfAPICounterGenerator/GPACounterGenerator.h ./Include/
   cp ../../../Src/GPUPerfAPICounterGenerator/GPAICounterAccessor.h ./Include/
   cp ../../../Src/GPUPerfAPICounterGenerator/GPAICounterScheduler.h ./Include/
   cp ../../../Doc/GPUPerfAPI-UserGuide.pdf .
   cp ../../../LICENSE .
   cp ../../../Doc/thirdpartylicenses.txt .
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
      cp $CL/$CLLIB_INTERNAL ./Bin-Internal/Linx64/
      cp $HSA/$HSALIB_INTERNAL ./Bin-Internal/Linx64/
      cp $GL/$GLLIB_INTERNAL ./Bin-Internal/Linx64/
      cp $GLES/$GLESLIB_INTERNAL ./Bin-Internal/Linx64/
      cp $COUNTERS/$COUNTERSLIB_INTERNAL ./Bin-Internal/Linx64/

      cp $CL/$CLLIB32_INTERNAL ./Bin-Internal/Linx86/
      cp $GL/$GLLIB32_INTERNAL ./Bin-Internal/Linx86/
      cp $GLES/$GLESLIB32_INTERNAL ./Bin-Internal/Linx86/
      cp $COUNTERS/$COUNTERSLIB32_INTERNAL ./Bin-Internal/Linx86/

      cd ..
      tar cvzf GPUPerfAPI.$VER-lnx-Promotion.tgz $ZIP_DIR_NAME/
   fi
fi

echo "Build Complete" | tee -a $LOGFILE
