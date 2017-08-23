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

LIBS = \
	$(COMMON_LIBS) \
	$(COMMON_DEVICEINFO_LIB) \
	$(STANDARD_LIBS)

LIBPATH = $(COMMON_LIB_PATHS)

SO_OBJS = \
	./$(OBJ_DIR)/GPAContextStateVk.o \
	./$(OBJ_DIR)/GPUPerfAPIVk.o \
	./$(OBJ_DIR)/VkCommandListSwQueries.o \
	./$(OBJ_DIR)/VkCommandListSWQueryGroup.o \
	./$(OBJ_DIR)/VkCounterDataRequestProxy.o \
	./$(OBJ_DIR)/VkDataRequest.o \
	./$(OBJ_DIR)/VkHardwareCounterDataRequest.o \
	./$(OBJ_DIR)/VkSoftwareCounterDataRequest.o \

include $(DEPTH)/Build/Linux/CommonTargets.mk
