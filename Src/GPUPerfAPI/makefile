# Makefile for GPUPerfAPI

PROJECT_NAME=GPUPerfAPI
DEPTH = ../..
include $(DEPTH)/Build/Linux/Common.mk

TARGETLIB = $(OUTPUT_LIB_DIR)/lib$(PROJECT_NAME)$(TARGET_SUFFIX).a

INCLUDES =	-I. \
		-I$(GPACOMMON_DIR) \
		-I$(GPACG_DIR) \
		-I$(DEVICEINFO_DIR) \

LIB_OBJS	= \
	./$(OBJ_DIR)/GPUPerfAPI.o \

include $(DEPTH)/Build/Linux/CommonTargets.mk

