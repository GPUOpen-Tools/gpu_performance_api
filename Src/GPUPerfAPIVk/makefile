# makefile for GPUPerfAPIVK

PROJECT_NAME=GPUPerfAPIVK
DEPTH = ../..
include $(DEPTH)/Build/Linux/Common.mk

TARGETSO = $(OUTPUT_BIN_DIR)/lib$(PROJECT_NAME)$(TARGET_SUFFIX).so

INCLUDES =	-I. \
		-I$(GPACOMMON_DIR) \
		-I$(GPACG_DIR) \
		-I$(ADL_DIR)/include \
		-I$(ADLUTIL_DIR) \
		-I$(AMDTMUTEX_DIR) \
		-I$(DEVICEINFO_DIR) \
		-I$(TSINGLETON_DIR) \
		-I$(AMD_VK_EXT_DIR) \
		-I$(VK_INCLUDE_DIR)

LIBS = \
	$(GPUPERFAPI_LIB) \
	$(COMMON_LIBS) \
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
