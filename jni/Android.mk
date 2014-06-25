LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)


OGER_PATH := /home/victor/eclipse/include/Ogre


LOCAL_MODULE    := LiveWall


LOCAL_LDLIBS	:= -landroid -lc -lm -ldl -llog -lEGL -lGLESv2 -lz

LOCAL_LDLIBS	+= -L$(OGER_PATH)/lib/armeabi-v7a
LOCAL_LDLIBS	+= -L$(OGER_PATH)/Dependencies/lib/armeabi-v7a

LOCAL_LDLIBS	+= $(OGER_PATH)/Dependencies/lib/armeabi-v7a/libzlib.a
LOCAL_LDLIBS	+= $(OGER_PATH)/Dependencies/lib/armeabi-v7a/libglcpp-library.a

LOCAL_LDLIBS	+= $(OGER_PATH)/lib/armeabi-v7a/libPlugin_ParticleFXStatic.a
LOCAL_LDLIBS	+= $(OGER_PATH)/lib/armeabi-v7a/libPlugin_OctreeSceneManagerStatic.a
LOCAL_LDLIBS	+= $(OGER_PATH)/lib/armeabi-v7a/libRenderSystem_GLES2Static.a
LOCAL_LDLIBS	+= $(OGER_PATH)/lib/armeabi-v7a/libOgreRTShaderSystemStatic.a
LOCAL_LDLIBS	+= $(OGER_PATH)/lib/armeabi-v7a/libOgreOverlayStatic.a
LOCAL_LDLIBS	+= $(OGER_PATH)/lib/armeabi-v7a/libOgreMainStatic.a

LOCAL_LDLIBS	+= $(OGER_PATH)/Dependencies/lib/armeabi-v7a/libzzip.a
LOCAL_LDLIBS	+= $(OGER_PATH)/Dependencies/lib/armeabi-v7a/libFreeImage.a
LOCAL_LDLIBS	+= $(OGER_PATH)/Dependencies/lib/armeabi-v7a/libfreetype.a
LOCAL_LDLIBS	+= $(OGER_PATH)/Dependencies/lib/armeabi-v7a/libOIS.a
LOCAL_LDLIBS	+= $(OGER_PATH)/Dependencies/lib/armeabi-v7a/libmesa.a
LOCAL_LDLIBS	+= $(OGER_PATH)/Dependencies/lib/armeabi-v7a/libglsl_optimizer.a
LOCAL_LDLIBS	+= $(OGER_PATH)/Dependencies/lib/armeabi-v7a/libsupc++.a
LOCAL_LDLIBS	+= $(OGER_PATH)/Dependencies/lib/armeabi-v7a/libstdc++.a

LOCAL_LDLIBS	+= ./obj/local/armeabi-v7a/libcpufeatures.a
LOCAL_STATIC_LIBRARIES := android_native_app_glue cpufeatures


LOCAL_CFLAGS := -DGL_GLEXT_PROTOTYPES=1
LOCAL_CFLAGS += -I$(OGER_PATH)/include/Build
LOCAL_CFLAGS += -I$(OGER_PATH)/include/OgreMain
LOCAL_CFLAGS += -I$(OGER_PATH)/include/OgreMain/Android/
LOCAL_CFLAGS += -I$(OGER_PATH)/include/RenderSystems/GLES2
LOCAL_CFLAGS += -I$(OGER_PATH)/include/RenderSystems/GLES2/EGL
LOCAL_CFLAGS += -I$(OGER_PATH)/include/RenderSystems/GLES2/EGL/Android
LOCAL_CFLAGS += -I$(OGER_PATH)/include/RenderSystems/GLES2/EGL/WIN32
LOCAL_CFLAGS += -I$(OGER_PATH)/include/RenderSystems/GLES2/EGL/X11
LOCAL_CFLAGS += -I$(OGER_PATH)/include/Components/Overlay
LOCAL_CFLAGS += -I$(OGER_PATH)/include/Components/RTShaderSystem
LOCAL_CFLAGS += -I$(OGER_PATH)/include/PlugIns/ParticleFX
LOCAL_CFLAGS += -I$(OGER_PATH)/include/PlugIns/OctreeSceneManager
LOCAL_CFLAGS += -I$(OGER_PATH)/include/Dependencies/include
LOCAL_CFLAGS += -I$(OGER_PATH)/include/Dependencies/include/OIS 
LOCAL_CFLAGS += -I$(OGER_PATH)/include/Dependencies/include/freetype 
LOCAL_CFLAGS += -I$(OGER_PATH)/include/Dependencies/include/zzip 
 

LOCAL_CFLAGS += -I$(ANDROID_NDK)/sources/cpufeatures

LOCAL_CFLAGS += -fexceptions -frtti -x c++ -D___ANDROID___ -DANDROID -DZZIP_OMIT_CONFIG_H -DUSE_RTSHADER_SYSTEM=1 
 

LOCAL_SRC_FILES := LiveWall.cpp
  
include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/cpufeatures) 
$(call import-module,android/native_app_glue) 


