# Makefile for GPUPerfAPI-Common

DEPTH = ..
include $(DEPTH)/Build/Linux/Common.mk

TARGETLIB = libGPUPerfAPI-Common$(TARGET_SUFFIX).a

INCLUDES =	-I. \
		-I$(ADL_DIR)/include \
		-I$(ADLUTIL_DIR) \
		-I$(DEVICEINFO_DIR) \
		-I$(TSINGLETON_DIR) \
		-I$(AMDTMUTEX_DIR) \
		-I$(DYNAMICLIBRARYMODULE_DIR)

LIB_OBJS	= \
	./$(OBJ_DIR)/ADLUtil.o \
	./$(OBJ_DIR)/AMDTMutex.o \
	./$(OBJ_DIR)/GPAContextState.o \
	./$(OBJ_DIR)/GPAHWInfo.o \
	./$(OBJ_DIR)/GPASessionRequests.o \
	./$(OBJ_DIR)/GPACustomHWValidationManager.o \
	./$(OBJ_DIR)/GPUPerfAPI.o \
	./$(OBJ_DIR)/Logging.o \
	./$(OBJ_DIR)/DynamicLibraryModule.o

include $(DEPTH)/Build/Linux/CommonTargets.mk

