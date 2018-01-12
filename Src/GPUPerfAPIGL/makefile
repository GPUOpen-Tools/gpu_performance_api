# makefile for GPUPerfAPIGL

PROJECT_NAME=GPUPerfAPIGL
DEPTH = ../..
include $(DEPTH)/Build/Linux/Common.mk

TARGETSO = $(OUTPUT_BIN_DIR)/lib$(PROJECT_NAME)$(TARGET_SUFFIX).so

ADDL_DEFINES = -DGLX_GLXEXT_PROTOTYPES

INCLUDES =	-I. \
		-I$(GPACOMMON_DIR) \
		-I$(GPACG_DIR) \
		-I$(GL_DIR)/Include \
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

LIBPATH = $(COMMON_LIB_PATHS)

SO_OBJS	= \
	./$(OBJ_DIR)/GLCounterDataRequest.o \
	./$(OBJ_DIR)/GLCounterDataRequestManager.o \
	./$(OBJ_DIR)/ASICInfo.o \
	./$(OBJ_DIR)/GPUPerfAPIGL.o \
	./$(OBJ_DIR)/GLPerfMonitorCache.o

include $(DEPTH)/Build/Linux/CommonTargets.mk

