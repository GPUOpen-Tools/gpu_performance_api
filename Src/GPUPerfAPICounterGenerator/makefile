# Makefile for GPUPerfAPICounterGenerator

DEPTH = ../..
include $(DEPTH)/Build/Linux/Common.mk

TARGETLIB = libGPUPerfAPICounterGenerator$(TARGET_SUFFIX).a

INCLUDES =	-I. \
		-I$(GPACOMMON_DIR) \
		-I$(ADL_DIR)/include \
		-I$(ADLUTIL_DIR) \
		-I$(AMDTMUTEX_DIR) \
		-I$(DEVICEINFO_DIR) \
		-I$(TSINGLETON_DIR) \
		-I$(GL_DIR)/Include \
		-I$(HSA_DIR)/include/hsa \
		-I$(AMD_VK_EXT_DIR) \
		-I$(VK_INCLUDE_DIR) \
		-I$(VK_INCLUDE_DIR)/vulkan \

LIB_OBJS	= \
	./$(OBJ_DIR)/GPAPublicCounters.o \
	./$(OBJ_DIR)/GPACounterGenerator.o \
	./$(OBJ_DIR)/GPACounterGeneratorSchedulerManager.o \
	./$(OBJ_DIR)/GPACounterGeneratorBase.o \
	./$(OBJ_DIR)/GPACounterGeneratorCL.o \
	./$(OBJ_DIR)/GPACounterGeneratorGL.o \
	./$(OBJ_DIR)/GPACounterGeneratorHSA.o \
	./$(OBJ_DIR)/GPACounterGeneratorVK.o \
	./$(OBJ_DIR)/GPACounterGeneratorVKBase.o \
	./$(OBJ_DIR)/GPACounterGeneratorVKNonAMD.o \
	./$(OBJ_DIR)/GPACounterSchedulerBase.o \
	./$(OBJ_DIR)/GPACounterSchedulerCL.o \
	./$(OBJ_DIR)/GPACounterSchedulerGL.o \
	./$(OBJ_DIR)/GPACounterSchedulerHSA.o \
	./$(OBJ_DIR)/GPACounterSchedulerVK.o \
	./$(OBJ_DIR)/GPAInternalCountersGfx6.o \
	./$(OBJ_DIR)/GPAInternalCountersGfx7.o \
	./$(OBJ_DIR)/GPAInternalCountersGfx8.o \
	./$(OBJ_DIR)/GPAInternalCountersGfx9.o \
	./$(OBJ_DIR)/GPAInternalCountersFiji.o \
	./$(OBJ_DIR)/InternalCountersCLGfx6.o \
	./$(OBJ_DIR)/InternalCountersCLGfx7.o \
	./$(OBJ_DIR)/InternalCountersCLGfx8.o \
	./$(OBJ_DIR)/InternalCountersCLGfx9.o \
	./$(OBJ_DIR)/InternalCountersGLGfx6.o \
	./$(OBJ_DIR)/InternalCountersGLGfx7.o \
	./$(OBJ_DIR)/InternalCountersGLGfx8.o \
	./$(OBJ_DIR)/InternalCountersGLGfx9.o \
	./$(OBJ_DIR)/InternalCountersHSAGfx7.o \
	./$(OBJ_DIR)/InternalCountersHSAGfx8.o \
	./$(OBJ_DIR)/InternalCountersHSAGfx9.o \
	./$(OBJ_DIR)/InternalCountersVKGfx7.o \
	./$(OBJ_DIR)/InternalCountersVKGfx8.o \
	./$(OBJ_DIR)/InternalCountersVKGfx9.o \
	./$(OBJ_DIR)/PublicCounterDefsCLGfx6.o \
	./$(OBJ_DIR)/PublicCounterDefsCLGfx7.o \
	./$(OBJ_DIR)/PublicCounterDefsCLGfx8.o \
	./$(OBJ_DIR)/PublicCounterDefsCLGfx9.o \
	./$(OBJ_DIR)/PublicCounterDefsGLGfx6.o \
	./$(OBJ_DIR)/PublicCounterDefsGLGfx7.o \
	./$(OBJ_DIR)/PublicCounterDefsGLGfx8.o \
	./$(OBJ_DIR)/PublicCounterDefsGLGfx9.o \
	./$(OBJ_DIR)/PublicCounterDefsHSAGfx7.o \
	./$(OBJ_DIR)/PublicCounterDefsHSAGfx8.o \
	./$(OBJ_DIR)/PublicCounterDefsHSAGfx9.o \
	./$(OBJ_DIR)/PublicCounterDefsVKGfx7.o \
	./$(OBJ_DIR)/PublicCounterDefsVKGfx8.o \
	./$(OBJ_DIR)/PublicCounterDefsVKGfx9.o \
	./$(OBJ_DIR)/GPASwCounterManager.o \
	./$(OBJ_DIR)/GLEntryPoints.o

include $(DEPTH)/Build/Linux/CommonTargets.mk

