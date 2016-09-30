# Makefile for GPUPerfAPICL

DEPTH = ../..
include $(DEPTH)/Build/Linux/Common.mk

TARGETSO = libGPUPerfAPICL$(TARGET_SUFFIX).so

TARGET = $(GPATARGET)

INCLUDES =	-I. \
		-I$(GPACOMMON_DIR) \
		-I$(GPACG_DIR) \
		-I$(ATI_STREAM_SDK_DIR)/include \
		-I$(ADL_DIR)/include \
		-I$(ADLUTIL_DIR) \
		-I$(DEVICEINFO_DIR) \
		-I$(TSINGLETON_DIR) \
		-I$(DYNAMICLIBRARYMODULE_DIR)

LIBS = \
	$(COMMON_LIBS) \
	$(COMMON_DEVICEINFO_LIB) \
	$(STANDARD_LIBS)

LIBPATH = $(COMMON_LIB_PATHS)

SO_OBJS	= \
	./$(OBJ_DIR)/GPUPerfAPICL.o \
	./$(OBJ_DIR)/CLCounterDataRequest.o \
	./$(OBJ_DIR)/CLPerfCounterAMDExtension.o \
	./$(OBJ_DIR)/CLPerfCounterBlock.o \
	./$(OBJ_DIR)/OpenCLModule.o

include $(DEPTH)/Build/Linux/CommonTargets.mk

