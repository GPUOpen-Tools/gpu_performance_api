# makefile for GPUPerfAPIGLES

PROJECT_NAME=GPUPerfAPIGLES
DEPTH = ../..
include $(DEPTH)/Build/Linux/Common.mk

TARGETSO = $(OUTPUT_BIN_DIR)/lib$(PROJECT_NAME)$(TARGET_SUFFIX).so

ADDL_DEFINES = -DGLX_GLXEXT_PROTOTYPES -DGLES

INCLUDES =	-I. \
		-I$(GPACOMMON_DIR) \
		-I$(GPACG_DIR) \
		-I$(GLES_DIR)/Include \
		-I$(ADL_DIR)/include \
		-I$(ADLUTIL_DIR) \
		-I$(AMDTMUTEX_DIR) \
		-I$(DEVICEINFO_DIR) \
		-I$(TSINGLETON_DIR)

LIBS = \
	$(GPUPERFAPI_LIB) \
	$(COMMON_LIBS) \
	$(COMMON_DEVICEINFO_LIB) \
	$(STANDARD_LIBS)

LIBPATH = $(COMMON_LIB_PATHS) $(GLES_LIB_DIR)

SO_OBJS = \
	./$(OBJ_DIR)/GLGPAImplementor.o \
	./$(OBJ_DIR)/GLGPACommandList.o \
	./$(OBJ_DIR)/GLGPAContext.o \
	./$(OBJ_DIR)/GLGPAPass.o \
	./$(OBJ_DIR)/GLGPASample.o \
	./$(OBJ_DIR)/GLGPASession.o \
	./$(OBJ_DIR)/ASICInfo.o \

include $(DEPTH)/Build/Linux/CommonTargets.mk

