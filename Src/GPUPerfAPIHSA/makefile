# Makefile for GPUPerfAPIHSA

DEPTH = ../..
include $(DEPTH)/Build/Linux/Common.mk

TARGETSO = libGPUPerfAPIHSA$(TARGET_SUFFIX).so
ADDL_DEFINES = -DAMD_INTERNAL_BUILD

INCLUDES =	-I. \
		-I$(GPACOMMON_DIR) \
		-I$(GPACG_DIR) \
		-I$(HSA_DIR)/include \
		-I$(HSA_DIR)/include/hsa \
		-I$(ADL_DIR)/include \
		-I$(ADLUTIL_DIR) \
		-I$(DEVICEINFO_DIR) \
		-I$(TSINGLETON_DIR) \
		-I$(GPUPERFAPIUTILS_DIR) \
		-I$(DYNAMICLIBRARYMODULE_DIR)

LIBS = \
	$(COMMON_LIBS) \
	$(COMMON_DEVICEINFO_LIB) \
	$(STANDARD_LIBS)

LIBPATH = $(COMMON_LIB_PATHS)

SO_OBJS	= \
	./$(OBJ_DIR)/GPUPerfAPIHSA.o \
	./$(OBJ_DIR)/HSACounterDataRequest.o \
	./$(OBJ_DIR)/GPUPerfAPIRegistry.o \
	./$(OBJ_DIR)/HSAModule.o \
	./$(OBJ_DIR)/HSAToolsRTModule.o \
	./$(OBJ_DIR)/GPUPerfAPIHSAAgent.o

include $(DEPTH)/Build/Linux/CommonTargets.mk

