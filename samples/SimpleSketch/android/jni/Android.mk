LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := SimpleSketch

CHR_SRC = ../../../../src
UTF8_CPP_SRC = ../../../../../../include/utf8-cpp

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../src
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/$(CHR_SRC)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/$(UTF8_CPP_SRC)

FILE_LIST := $(wildcard $(LOCAL_PATH)/../../src/*.cpp)
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_SRC_FILES += $(CHR_SRC)/chronotext/InputSource.cpp
LOCAL_SRC_FILES += $(CHR_SRC)/chronotext/ScreenManager.cpp
LOCAL_SRC_FILES += $(CHR_SRC)/chronotext/cinder/CinderApp.cpp
LOCAL_SRC_FILES += $(CHR_SRC)/chronotext/cinder/CinderSketchSimple.cpp
LOCAL_SRC_FILES += $(CHR_SRC)/chronotext/font/FontMatrix.cpp
LOCAL_SRC_FILES += $(CHR_SRC)/chronotext/font/XFont.cpp
LOCAL_SRC_FILES += $(CHR_SRC)/chronotext/font/XFontSequence.cpp
LOCAL_SRC_FILES += $(CHR_SRC)/chronotext/maths/Matrix2D.cpp
LOCAL_SRC_FILES += $(CHR_SRC)/chronotext/os/Handler.cpp
LOCAL_SRC_FILES += $(CHR_SRC)/chronotext/os/Looper.cpp
LOCAL_SRC_FILES += $(CHR_SRC)/chronotext/os/MessageQueue.cpp
LOCAL_SRC_FILES += $(CHR_SRC)/chronotext/path/ASPC.cpp
LOCAL_SRC_FILES += $(CHR_SRC)/chronotext/path/FollowablePath.cpp
LOCAL_SRC_FILES += $(CHR_SRC)/chronotext/path/SplinePath.cpp
LOCAL_SRC_FILES += $(CHR_SRC)/chronotext/text/FontHelper.cpp
LOCAL_SRC_FILES += $(CHR_SRC)/chronotext/text/FontManager.cpp
LOCAL_SRC_FILES += $(CHR_SRC)/chronotext/text/WordWrapper.cpp
LOCAL_SRC_FILES += $(CHR_SRC)/chronotext/texture/PVRHelper.cpp
LOCAL_SRC_FILES += $(CHR_SRC)/chronotext/texture/Sprite.cpp
LOCAL_SRC_FILES += $(CHR_SRC)/chronotext/texture/Texture.cpp
LOCAL_SRC_FILES += $(CHR_SRC)/chronotext/texture/TextureAtlas.cpp
LOCAL_SRC_FILES += $(CHR_SRC)/chronotext/texture/TextureAtlasManager.cpp
LOCAL_SRC_FILES += $(CHR_SRC)/chronotext/texture/TextureAtlasAnimation.cpp
LOCAL_SRC_FILES += $(CHR_SRC)/chronotext/texture/TextureHelper.cpp
LOCAL_SRC_FILES += $(CHR_SRC)/chronotext/texture/TextureManager.cpp
LOCAL_SRC_FILES += $(CHR_SRC)/chronotext/time/Clock.cpp
LOCAL_SRC_FILES += $(CHR_SRC)/chronotext/time/MasterClock.cpp
LOCAL_SRC_FILES += $(CHR_SRC)/chronotext/utils/Utils.cpp

#$(info $(LOCAL_C_INCLUDES))
#$(info $(LOCAL_SRC_FILES))

LOCAL_CFLAGS := -ffast-math -O3
#LOCAL_CFLAGS := -g

LOCAL_LDLIBS := -landroid
LOCAL_STATIC_LIBRARIES := cinder boost_system boost_filesystem freeimage ft2 android_native_app_glue

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
$(call import-module,cinder)
$(call import-module,boost)
