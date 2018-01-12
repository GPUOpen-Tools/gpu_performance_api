# Makefile for GPUPerfAPICL

PROJECT_NAME=GPUPerfAPICL
DEPTH = ../..
include $(DEPTH)/Build/Linux/Common.mk

TARGETSO = $(OUTPUT_BIN_DIR)/lib$(PROJECT_NAME)$(TARGET_SUFFIX).so

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
	$(GPUPERFAPI_LIB) \
	$(COMMON_LIBS) \
	$(COMMON_DEVICEINFO_LIB) \
	$(STANDARD_LIBS)

LIBPATH = $(COMMON_LIB_PATHS)

SO_OBJS	= \
	./$(OBJ_DIR)/CLGPAImplementor.o \
	./$(OBJ_DIR)/CLGPACommandList.o \
	./$(OBJ_DIR)/CLGPAContext.o \
	./$(OBJ_DIR)/CLGPAPass.o \
	./$(OBJ_DIR)/CLGPASample.o \
	./$(OBJ_DIR)/CLGPASession.o \
	./$(OBJ_DIR)/CLPerfCounterAMDExtension.o \
	./$(OBJ_DIR)/CLPerfCounterBlock.o \
	./$(OBJ_DIR)/OpenCLModule.o

include $(DEPTH)/Build/Linux/CommonTargets.mk
