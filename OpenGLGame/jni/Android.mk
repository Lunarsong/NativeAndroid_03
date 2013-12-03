LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := Engine
LOCAL_CFLAGS    := -Werror
LOCAL_SRC_FILES := Engine.cpp Application.cpp RendererES2.cpp
LOCAL_LDLIBS    := -llog -lGLESv2 -lEGL

include $(BUILD_SHARED_LIBRARY)
