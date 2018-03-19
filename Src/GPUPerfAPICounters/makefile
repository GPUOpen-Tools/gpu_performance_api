# Makefile for GPUPerfAPICounters

PROJECT_NAME=GPUPerfAPICounters
DEPTH = ../..
include $(DEPTH)/Build/Linux/Common.mk

TARGETSO = $(OUTPUT_BIN_DIR)/lib$(PROJECT_NAME)$(TARGET_SUFFIX).so

INCLUDES =	-I. \
		-I$(GPACOMMON_DIR) \
		-I$(GPACG_DIR) \
		-I$(ADL_DIR)/include \
		-I$(ADLUTIL_DIR) \
		-I$(DEVICEINFO_DIR) \
		-I$(TSINGLETON_DIR)

LIBS = \
	$(COMMON_LIBS) \
	$(COMMON_DEVICEINFO_LIB) \
	$(STANDARD_LIBS)

LIBPATH = $(COMMON_LIB_PATHS)

SO_OBJS	= \
	./$(OBJ_DIR)/GPUPerfAPICounters.o

include $(DEPTH)/Build/Linux/CommonTargets.mk

