/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// OpenGL ES 2.0 code
#include "core_app_shell.h"
#include "os_core_app_shell.h"
#include "os_core_outlets.h"
#include "os_core_includes.h"


#include "GFXApp.hpp"

#include <jni.h>
#include <android/log.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "core_app_shell.h"
#include "os_core_graphics.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define  LOG_TAG    "libgl2jni"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

JNIEnv *gJNIEnv = 0;
JavaVM *gJVM = 0;

static void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}

static void checkGlError(const char* op) {
    for (GLint error = glGetError(); error; error
            = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

auto gVertexShader =
    "attribute vec4 vPosition;\n"
    "void main() {\n"
    "  gl_Position = vPosition;\n"
    "}\n";

auto gFragmentShader =
    "precision mediump float;\n"
    "void main() {\n"
    "  gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
    "}\n";

GLuint loadShader(GLenum shaderType, const char* pSource) {

    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char* buf = (char*) malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE("Could not compile shader %d:\n%s\n",
                            shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

GLuint createProgram(const char* pVertexSource, const char* pFragmentSource) {
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
    if (!vertexShader) {
        return 0;
    }

    GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
    if (!pixelShader) {
        return 0;
    }

    GLuint program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertexShader);
        checkGlError("glAttachShader");
        glAttachShader(program, pixelShader);
        checkGlError("glAttachShader");
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char* buf = (char*) malloc(bufLength);
                if (buf) {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    LOGE("Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

const GLfloat gTriangleVertices[] = { 0.0f, 0.5f, -0.5f, -0.5f,
        0.5f, -0.5f };

extern "C" {
    JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellPreinitialize(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellSetAudioBufferAttributes(JNIEnv* env, jobject obj, int pSampleRate, int pBufferSize);
    JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellInitialize(JNIEnv * env, jobject obj,  jint width, jint height);
    JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellGraphicsReady(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellDetachRunLoop(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellSetSize(JNIEnv* env, jobject obj, int pWidth, int pHeight);
    JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellSetDirectoryBundle(JNIEnv* env, jobject obj, jstring pFilePath);
    JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellSetDirectoryDocuments(JNIEnv* env, jobject obj, jstring pFilePath);
    JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellFrame(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellTouchBegin(JNIEnv* env, jobject obj, float pX, float pY, int pIndex, int pCount);
    JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellTouchMove(JNIEnv* env, jobject obj, float pX, float pY, int pIndex, int pCount);
    JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellTouchRelease(JNIEnv* env, jobject obj, float pX, float pY, int pIndex, int pCount);
    JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellTouchCancel(JNIEnv* env, jobject obj, float pX, float pY, int pIndex, int pCount);
    JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellExit(JNIEnv* env, jobject obj);
    JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellPause(JNIEnv* env, jobject obj);
    JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellResume(JNIEnv* env, jobject obj);
    JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellMemoryWarning(bool pSevre);
    JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellPurchaseSuccessful(const char *pName);
    JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellPurchaseFailed(const char *pName);
    JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellPurchaseCanceled(const char *pName);
    JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellAdBannerSetHeight(const char *pName);
    JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellAdBannerLoadFailed();
    JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellAdBannerLoadSuccessful();
    JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellKeyPress(int pKey);
};

//JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height)
//{

//Java_com_froggy_game_

//JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_init(JNIEnv * env, jobject obj,

JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellPreinitialize(JNIEnv* env, jobject obj) {
    LOGI("********~~~~~~~~\n~~~~~~~~~~~~~\nNativeAppShellPreinitialize\n\n~~~~~~~\n");
    gJNIEnv = env;
    gJNIEnv->GetJavaVM(&gJVM);
    gApp = new GFXApp();
    gOpenGLEngine = new OpenGLEngine();
}

JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellSetAudioBufferAttributes(JNIEnv* env, jobject obj, int pSampleRate, int pBufferSize) {
    LOGI("Setting Audio Attribs [%d] --> [%d]\n", pSampleRate, pBufferSize);
    sound_setAudioAttributes(pSampleRate, pBufferSize);
}

JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellInitialize(JNIEnv* env, jobject obj,  jint width, jint height) {
    LOGI("NativeAppShellInitialize = [%d x %d]\n",
         width, height);
    AppShellSetDeviceSize(width, height);
    AppShellSetVirtualFrame(0, 0, width, height);
    AppShellInitialize(ENV_ANDROID);

}

JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellFrame(JNIEnv * env, jobject obj)  {
    AppShellFrame();
}

JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellDetachRunLoop(JNIEnv * env, jobject obj) {

}

JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellGraphicsReady(JNIEnv * env, jobject obj) {
    LOGI("Graphics Is Ready!!!\n");
    if (gOpenGLEngine) {
        gOpenGLEngine->SetUp();
        AppShellLoad();
    } else {
        LOGI("Graphics Is NOT ready...!!!\n");
    }
}

JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellSetSize(JNIEnv* env, jobject obj, int pWidth, int pHeight) {
    AppShellSetDeviceSize(pWidth, pHeight);
}

JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellSetDirectoryBundle(JNIEnv* env, jobject obj, jstring pFilePath)
{
    const char *aFilePath = env->GetStringUTFChars(pFilePath, 0);
    Log("BUNDLE = [%s]\n", aFilePath);

    AppShellSetDirectoryBundle(aFilePath);
    env->ReleaseStringUTFChars(pFilePath, aFilePath);


    //AppShellSetDirectoryBundle(pPath);
}

JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellSetDirectoryDocuments(JNIEnv* env, jobject obj, jstring pFilePath)
{
    const char *aFilePath = env->GetStringUTFChars(pFilePath, 0);
    Log("Docs = [%s]\n", aFilePath);

    AppShellSetDirectoryDocuments(aFilePath);
    env->ReleaseStringUTFChars(pFilePath, aFilePath);

    //AppShellSetDirectoryDocuments(pPath);
}

JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellTouchBegin(JNIEnv* env, jobject obj, float pX, float pY, int pIndex, int pCount) {
    AppShellTouchDownDroid(pX, pY, pIndex, pCount);
}

JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellTouchMove(JNIEnv* env, jobject obj, float pX, float pY, int pIndex, int pCount) {
    AppShellTouchMoveDroid(pX, pY, pIndex, pCount);
}

JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellTouchRelease(JNIEnv* env, jobject obj, float pX, float pY, int pIndex, int pCount) {
    AppShellTouchUpDroid(pX, pY, pIndex, pCount);
}

JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellTouchCancel(JNIEnv* env, jobject obj, float pX, float pY, int pIndex, int pCount) {
    AppShellTouchCanceledDroid(pX, pY, pIndex, pCount);
}

JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellExit(JNIEnv* env, jobject obj) {
    AppShellExit();
}

JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellPause(JNIEnv* env, jobject obj) {
    AppShellPause();
}

JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellResume(JNIEnv* env, jobject obj) {
    AppShellResume();
}

JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellMemoryWarning(bool pSevre)
{

}

JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellPurchaseSuccessful(const char *pName)
{

}

JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellPurchaseFailed(const char *pName)
{

}

JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellPurchaseCanceled(const char *pName)
{

}

JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellAdBannerSetHeight(const char *pName)
{

}

JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellAdBannerLoadFailed()
{

}

JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellAdBannerLoadSuccessful()
{

}

JNIEXPORT void JNICALL Java_com_froggy_game_GL2JNILib_NativeAppShellKeyPress(int pKey)
{

}


