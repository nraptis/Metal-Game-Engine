#ifndef CORE_INCLUDES_ANDROID_H
#define CORE_INCLUDES_ANDROID_H

#include <android/log.h>
#include <android/sensor.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>

#include <jni.h>

#include <EGL/egl.h>
#include <GLES/gl.h>
//#include <GLES/egl.h>

extern JNIEnv *gJNIEnv;
extern JavaVM *gJVM;

#endif
