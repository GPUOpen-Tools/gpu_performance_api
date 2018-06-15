# Makefile for VkColorCube

PROJECT_NAME=VkColorCube
DEPTH = ../../../../
include $(DEPTH)/Build/Linux/Common.mk

PRE_BUILD_ACTION=./CompileShaders.sh $(OUTPUT_BIN_DIR) $(VK_SDK_DIR)

TARGET = $(OUTPUT_BIN_DIR)/$(PROJECT_NAME)$(TARGET_SUFFIX)

INCLUDES =	-I. \
		-I$(GPACOMMON_DIR) \
		-I$(AMD_VK_EXT_DIR) \
		-I$(VK_INCLUDE_DIR)

LIBS = \
	$(STANDARD_LIBS) \
	$(VK_LIB_DIR)/libvulkan.so \
	-lxcb

LIBPATH = $(COMMON_LIB_PATHS)

OBJS	= \
	./$(OBJ_DIR)/vkcolorcube.o

include $(DEPTH)/Build/Linux/CommonTargets.mk


