# Makefile for GPUPerfAPI-Common

PROJECT_NAME=GPUPerfAPI-Common
DEPTH = ../..
include $(DEPTH)/Build/Linux/Common.mk

TARGETLIB = $(OUTPUT_LIB_DIR)/lib$(PROJECT_NAME)$(TARGET_SUFFIX).a

INCLUDES =	-I. \
		-I$(GPACG_DIR) \
		-I$(ADL_DIR)/include \
		-I$(ADLUTIL_DIR) \
		-I$(DEVICEINFO_DIR) \
		-I$(TSINGLETON_DIR) \
		-I$(AMDTMUTEX_DIR) \
		-I$(DYNAMICLIBRARYMODULE_DIR)

LIB_OBJS	= \
	./$(OBJ_DIR)/ADLUtil.o \
	./$(OBJ_DIR)/DynamicLibraryModule.o \
	./$(OBJ_DIR)/GPACommandList.o \
	./$(OBJ_DIR)/GPAContext.o \
	./$(OBJ_DIR)/GPACustomHWValidationManager.o \
	./$(OBJ_DIR)/GPAHWInfo.o \
	./$(OBJ_DIR)/GPAImplementor.o \
	./$(OBJ_DIR)/GPAPass.o \
	./$(OBJ_DIR)/GPASample.o \
	./$(OBJ_DIR)/GPAUniqueObject.o \
	./$(OBJ_DIR)/GPASession.o \
	./$(OBJ_DIR)/Logging.o \

include $(DEPTH)/Build/Linux/CommonTargets.mk

