# makefile for GPUPerfAPIVK

DEPTH = ../..
include $(DEPTH)/Build/Linux/Common.mk

TARGETSO = libGPUPerfAPIVK$(TARGET_SUFFIX).so

INCLUDES =	-I. \
		-I$(GPACOMMON_DIR) \
		-I$(GPACG_DIR) \
		-I$(ADL_DIR)/include \
		-I$(ADLUTIL_DIR) \
		-I$(AMDTMUTEX_DIR) \
		-I$(DEVICEINFO_DIR) \
		-I$(TSINGLETON_DIR) \
		-I$(AMD_VK_EXT_DIR) \
		-I$(VK_INCLUDE_DIR) \
		-I$(VK_INCLUDE_DIR)/vulkan \
		-I$(VK_SOURCE_DIR)/layers \
		-I$(VK_SOURCE_DIR)/loader \
		-I$(VK_SDK_DIR)/glslang/SPIRV \

LIBS = \
	-Wl,--whole-archive -lGPUPerfAPI-Common$(TARGET_SUFFIX) -Wl,--no-whole-archive -lGPUPerfAPICounterGenerator$(TARGET_SUFFIX) \
	$(COMMON_DEVICEINFO_LIB) \
	$(STANDARD_LIBS)

LIBPATH = $(COMMON_LIB_PATHS)

SO_OBJS = \
	./$(OBJ_DIR)/VkGPAImplementor.o \
	./$(OBJ_DIR)/VkCommandListSwQueries.o \
	./$(OBJ_DIR)/VkCommandListSWQueryGroup.o \
	./$(OBJ_DIR)/VkEntrypoints.o \
	./$(OBJ_DIR)/VkGPAPass.o \
	./$(OBJ_DIR)/VkGPASample.o \
	./$(OBJ_DIR)/VkGPACommandList.o \
	./$(OBJ_DIR)/VkGPAContext.o \
	./$(OBJ_DIR)/VkGPASession.o \
	./$(OBJ_DIR)/VkGPAHardwareSample.o \
	./$(OBJ_DIR)/VkGPASoftwareSample.o \
	./$(OBJ_DIR)/VkUtils.o \

include $(DEPTH)/Build/Linux/CommonTargets.mk
