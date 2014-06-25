/*
 * main.h
 *
 *  Created on: 21 июня 2014 г.
 *      Author: victor
 */

#ifndef MAIN_H_
#define MAIN_H_


#define OGRE_STATIC_GLES2
#define OGRE_STATIC_ParticleFX
#define OGRE_STATIC_OctreeSceneManager


#include <jni.h>
#include <errno.h>


#include <stdlib.h>
#include <stdio.h>


#include <EGL/egl.h>
#include <android/log.h>

#include <android/input.h>
#include <android/sensor.h>
#include <android_native_app_glue.h>
#include <android/native_window_jni.h>

#include "Ogre.h"
#include "OgreRenderWindow.h"
#include "OgreStringConverter.h"
#include "RTShaderHelper.h"
#include "OgreAndroidEGLWindow.h"
#include "OgreAPKFileSystemArchive.h"
#include "OgreAPKZipArchive.h"

#include "OgreOverlayManager.h"
#include "OgreOverlayContainer.h"
#include "OgreTextAreaOverlayElement.h"
#include "OgreOverlaySystem.h"

#include "OgreStaticPluginLoader.h"


#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, "", __VA_ARGS__))
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "", __VA_ARGS__))
#define LOGF(...) ((void)__android_log_print(ANDROID_LOG_FATAL, "", __VA_ARGS__))
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_example_android_livecubes_cube1_CubeWallpaper1
 * Method:    NativeDrawFrame
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_android_livecubes_cube1_CubeWallpaper1_NativeDrawFrame
  (JNIEnv *, jobject);

/*
 * Class:     com_example_android_livecubes_cube1_CubeWallpaper1
 * Method:    NativeOnCreate
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_example_android_livecubes_cube1_CubeWallpaper1_NativeOnCreate
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_example_android_livecubes_cube1_CubeWallpaper1
 * Method:    NativeOnDestroy
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_android_livecubes_cube1_CubeWallpaper1_NativeOnDestroy
  (JNIEnv *, jobject);

/*
 * Class:     com_example_android_livecubes_cube1_CubeWallpaper1
 * Method:    NativeOnShow
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_android_livecubes_cube1_CubeWallpaper1_NativeOnShow
  (JNIEnv *, jobject);

/*
 * Class:     com_example_android_livecubes_cube1_CubeWallpaper1
 * Method:    NativeOnHide
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_android_livecubes_cube1_CubeWallpaper1_NativeOnHide
  (JNIEnv *, jobject);

/*
 * Class:     com_example_android_livecubes_cube1_CubeWallpaper1
 * Method:    NativeOnSurfaceChanged
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_com_example_android_livecubes_cube1_CubeWallpaper1_NativeOnSurfaceChanged
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     com_example_android_livecubes_cube1_CubeWallpaper1
 * Method:    NativeSurfaceCreated
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_example_android_livecubes_cube1_CubeWallpaper1_NativeSurfaceCreated
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_example_android_livecubes_cube1_CubeWallpaper1
 * Method:    NativeOnSurfaceDestroyed
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_android_livecubes_cube1_CubeWallpaper1_NativeOnSurfaceDestroyed
  (JNIEnv *, jobject);

/*
 * Class:     com_example_android_livecubes_cube1_CubeWallpaper1
 * Method:    NativeOnOffsetsChanged
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_android_livecubes_cube1_CubeWallpaper1_NativeOnOffsetsChanged
  (JNIEnv *, jobject);

/*
 * Class:     com_example_android_livecubes_cube1_CubeWallpaper1
 * Method:    NativeOnTouchEvent
 * Signature: (FFI)V
 */
JNIEXPORT void JNICALL Java_com_example_android_livecubes_cube1_CubeWallpaper1_NativeOnTouchEvent
  (JNIEnv *, jobject, jfloat, jfloat, jint);

#ifdef __cplusplus
}
#endif


#endif /* MAIN_H_ */
