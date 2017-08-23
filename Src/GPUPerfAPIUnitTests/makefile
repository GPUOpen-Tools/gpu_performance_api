# Makefile for GPUPerfAPIUnitTests

DEPTH = ../..
include $(DEPTH)/Build/Linux/Common.mk

TARGET = GPUPerfAPIUnitTests$(TARGET_SUFFIX)

POST_BUILD_ACTION = cp ../GPUPerfAPICounters/libGPUPerfAPICounters$(TARGET_SUFFIX).so .

INCLUDES =	-I. \
		-I$(GPACOMMON_DIR) \
		-I$(GPACG_DIR) \
		-I$(GPACOUNTERS_DIR) \
		-I$(DEVICEINFO_DIR) \
		-I$(TSINGLETON_DIR) \
		-I$(GTEST_DIR)/include \
		-I$(AMD_VK_EXT_DIR) \
		-I$(VK_INCLUDE_DIR) \
		-I$(VK_INCLUDE_DIR)/vulkan \

LIBS = \
	$(GTEST_LIBS) \
	$(COMMON_LIBS) \
	$(COMMON_DEVICEINFO_LIB) \
	$(STANDARD_LIBS) \

LIBPATH = $(COMMON_LIB_PATHS)

OBJS	= \
	./$(OBJ_DIR)/CounterGeneratorTests.o \
	./$(OBJ_DIR)/CounterGeneratorCLTests.o \
	./$(OBJ_DIR)/CounterGeneratorGLTests.o \
	./$(OBJ_DIR)/CounterGeneratorHSATests.o \
	./$(OBJ_DIR)/CounterGeneratorVKTests.o \
	./$(OBJ_DIR)/CounterSchedulerTests.o \
	./$(OBJ_DIR)/GPUPerfAPIUnitTests.o \
	./$(OBJ_DIR)/PublicCountersCLGfx7.o \
	./$(OBJ_DIR)/PublicCountersCLGfx6.o \
	./$(OBJ_DIR)/PublicCountersCLGfx8.o \
	./$(OBJ_DIR)/PublicCountersCLGfx9.o \
	./$(OBJ_DIR)/PublicCountersGLGfx6.o \
	./$(OBJ_DIR)/PublicCountersGLGfx7.o \
	./$(OBJ_DIR)/PublicCountersGLGfx8.o \
	./$(OBJ_DIR)/PublicCountersGLGfx9.o \
	./$(OBJ_DIR)/PublicCountersHSAGfx7.o \
	./$(OBJ_DIR)/PublicCountersHSAGfx8.o \
	./$(OBJ_DIR)/PublicCountersHSAGfx9.o \
	./$(OBJ_DIR)/PublicCountersVKGfx7.o \
	./$(OBJ_DIR)/PublicCountersVKGfx8.o \
	./$(OBJ_DIR)/PublicCountersVKGfx9.o \
	./$(OBJ_DIR)/SWCountersVK.o \

$(OBJ_DIR)/%.o: counters/%.cpp
	$(BUILD_SRC)

include $(DEPTH)/Build/Linux/CommonTargets.mk

