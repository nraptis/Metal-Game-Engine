//
//  core_os.m
//  CoreDemo
//
//  Created by Nick Raptis on 9/26/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//


#include "os_core_outlets.h"
#include "core_includes.h"
#include "FList.hpp"
#include "FString.h"

#include <sys/time.h>
#include <sys/stat.h>
#include <time.h>

#include <fcntl.h>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cstdlib>
#include <dirent.h>

#include <pthread.h>
#include <sys/utsname.h>


using namespace std;

#define JAVA_OUTLET_CLASS "com/froggy/game/JavaOutlets"

jobject _objJNIHelper = 0;
jclass _clsJNIHelper = 0;

char mPrintBuffer[2048];

void Log(const char *pText, ...) {

    if ((pText != 0) && (_objJNIHelper != 0)) {

        JNIEnv *env = os_getJNIEnv();
        if (env) {

            va_list argptr;
            va_start(argptr, pText);
            vsprintf(mPrintBuffer, pText, argptr);
            va_end(argptr);
            
            jstring name = env->NewStringUTF(mPrintBuffer);
            jmethodID mid = env->GetMethodID(_clsJNIHelper, "JavaLog", "(Ljava/lang/String;)V");
            
            if (mid) {
                env->CallVoidMethod(_objJNIHelper, mid, name);
            }
            env->DeleteLocalRef(name);
        }
    }
}

void os_initialize_outlets() {
    if (gJVM) {
        JNIEnv *env = os_getJNIEnv();
        if (env) {
            if (_clsJNIHelper == 0) {
                jclass cls = os_getClassID(env);
                _clsJNIHelper = (jclass) env->NewGlobalRef(cls);
                jmethodID constructor = env->GetMethodID(_clsJNIHelper, "<init>", "()V");
                _objJNIHelper = env->NewObject(_clsJNIHelper, constructor);
                _objJNIHelper = env->NewGlobalRef(_objJNIHelper);
            }
        }
    }
}

JNIEnv *os_getJNIEnv() {
    JNIEnv *aENV = 0;
    if (gJVM != 0) {
        jint ret = gJVM->GetEnv((void**)&aENV, JNI_VERSION_1_4);
        switch (ret) {
            case JNI_OK :
                return aENV;
                
            case JNI_EDETACHED :
                // Thread not attached
                
                // TODO : If calling AttachCurrentThread() on a native thread
                // must call DetachCurrentThread() in future.
                // see: http://developer.android.com/guide/practices/design/jni.html
                
                if (gJVM->AttachCurrentThread(&aENV, NULL) < 0) {
                    Log("Failed to get the environment using AttachCurrentThread()\n");
                    return 0;
                } else {
                    return aENV;
                }
            case JNI_EVERSION :
                // Cannot recover from this error
                Log("JNI interface version 1.4 not supported\n");
            default :
                Log("Failed to get the environment using GetEnv()\n");
                return 0;
        }
    }
    return aENV;
}

jclass os_getClassID(JNIEnv *pEnv) {
    jclass aClass = pEnv->FindClass(JAVA_OUTLET_CLASS);
    if (!aClass) {
        Log("Failed to find class of %s", JAVA_OUTLET_CLASS);
    }
    return aClass;
}


void os_execute_on_main_thread(void (*pFunc)()) {
    
}

void os_detach_thread(void (*theFunction)(void *theArg), void* theArg) {
    pthread_t aThread;
    pthread_attr_t aAttr;
    pthread_attr_init(&aAttr);
    pthread_attr_setdetachstate(&aAttr, PTHREAD_CREATE_DETACHED);
    pthread_create(&aThread,&aAttr, (void*(*)(void*))theFunction, theArg);
}

void os_sleep(int pTime) {
    usleep(pTime * 1000);
}

bool os_updates_in_background() {
    return true;
}

bool os_draws_in_background() {
    return true;
}


pthread_mutex_t gInterfaceMutex = PTHREAD_MUTEX_INITIALIZER;

void os_interface_mutex_enter() {
    pthread_mutex_lock( &gInterfaceMutex );
}

void os_interface_mutex_leave() {
    pthread_mutex_unlock( &gInterfaceMutex );
}


FList gThreadLockList;
pthread_mutex_t gThreadMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t gGraphicsThreadMutex = PTHREAD_MUTEX_INITIALIZER;

int os_create_thread_lock() {
    pthread_mutex_lock( &gThreadMutex );
    
    pthread_mutex_unlock( &gThreadMutex );
    
    return -1;
}

bool os_thread_lock_exists(int pLockIndex) {
    if (pLockIndex >= 0 && pLockIndex < gThreadLockList.mCount) {
        return true;
    }
    return false;
}

void os_delete_thread_lock(int pLockIndex) {
    pthread_mutex_lock( &gThreadMutex );

    
    pthread_mutex_unlock( &gThreadMutex );
}

void os_delete_all_thread_locks() {
    pthread_mutex_lock( &gThreadMutex );

    
    pthread_mutex_unlock( &gThreadMutex );
}

void os_lock_thread(int pLockIndex) {
    pthread_mutex_lock( &gThreadMutex );

    
    pthread_mutex_unlock( &gThreadMutex );
}

void os_unlock_thread(int pLockIndex) {
    pthread_mutex_lock( &gThreadMutex );

    
    pthread_mutex_unlock( &gThreadMutex );
}

void os_lock_graphics_thread(int pLockIndex) {
    pthread_mutex_lock( &gGraphicsThreadMutex );

    
    pthread_mutex_unlock( &gGraphicsThreadMutex );
}

void os_unlock_graphics_thread(int pLockIndex) {
    pthread_mutex_lock( &gGraphicsThreadMutex );

    
    pthread_mutex_unlock( &gGraphicsThreadMutex );
}


bool os_fileExists(const char *pFilePath) {
    bool aReturn = false;

    jmethodID aMethodID = 0;

    if((gJVM != 0) && (pFilePath != 0))
    {
        JNIEnv *aENV = os_getJNIEnv();

        jclass aClass = os_getClassID(aENV);

        if((aENV != 0) && (aClass != 0))
        {
            aMethodID = aENV->GetMethodID(aClass, "fileExists", "(Ljava/lang/String;)Z");

            if(aMethodID)
            {
                jstring aPath = aENV->NewStringUTF(pFilePath);
                aReturn = aENV->CallBooleanMethod(_objJNIHelper, aMethodID, aPath);
                aENV->DeleteLocalRef(aPath);
            }
        }
    }

    return aReturn;
}

bool os_fileExists(FString pFilePath) {
    return os_fileExists((const char *)(pFilePath.c()));
}

bool os_is_portrait() {
#ifdef ORIENTATION_LANDSCAPE
    return false;
#else
    return true;
#endif
    
}

#define NANOS_IN_SECOND 1000000000
unsigned int os_system_time() {
        struct timespec res;
        clock_gettime(CLOCK_MONOTONIC, &res);
        return (res.tv_sec * NANOS_IN_SECOND) + res.tv_nsec;

}

unsigned char *os_read_file(const char *pFileName, unsigned int &pLength) {

    pLength = 0;
    unsigned char *aData = 0;

    jmethodID aMethodID = 0;

    if((gJVM != 0) && (pFileName != 0)) {
        JNIEnv *aEnv = os_getJNIEnv();

        jclass aClass = os_getClassID(aEnv);

        if ((aEnv != 0) && (aClass != 0)) {
            aMethodID = aEnv->GetMethodID(aClass, "readFileLength", "(Ljava/lang/String;)I");

            if(aMethodID) {
                jstring aFileName = aEnv->NewStringUTF(pFileName);

                pLength = aEnv->CallIntMethod(_objJNIHelper, aMethodID, aFileName);

                if(pLength > 0) {
                    aMethodID = aEnv->GetMethodID(aClass, "readFileData", "(Ljava/lang/String;[B)V");

                    if(aMethodID)
                    {
                        jbyteArray aArray = aEnv->NewByteArray(pLength + 1);

                        aEnv->CallVoidMethod(_objJNIHelper, aMethodID, aFileName, aArray);

                        jbyte *aByte = aEnv->GetByteArrayElements(aArray, 0);

                        aData = new unsigned char [pLength];

                        memcpy(aData, aByte, pLength);

                        aEnv->ReleaseByteArrayElements(aArray, aByte, 0);
                        aEnv->DeleteLocalRef(aArray);

                        Log("** LOADED [%s] [%d]\n", pFileName, pLength);
                    }
                    else
                    {
                        pLength = 0;
                    }
                }
                else
                {
                    pLength = 0;
                }

                aEnv->DeleteLocalRef(aFileName);
            }
        }
    }

    return aData;


    
}

bool os_write_file(const char *pFileName, unsigned char *pData, unsigned int pLength)
{
    bool aReturn = false;

    jmethodID aMethodID = 0;

    if((gJVM != 0) && (pFileName != 0) && (pLength > 0))
    {
        JNIEnv *aEnv = os_getJNIEnv();
        jclass aClass = os_getClassID(aEnv);

        if((aEnv != 0) && (aClass != 0))
        {
            aMethodID = aEnv->GetMethodID(aClass, "writeFileData", "(Ljava/lang/String;[BI)Z");

            if(aMethodID)
            {
                jbyteArray aArray = aEnv->NewByteArray(pLength + 1);
                jbyte *aByte = aEnv->GetByteArrayElements(aArray, 0);

                memcpy(aByte, pData, pLength);

                jstring aPath = aEnv->NewStringUTF(pFileName);
                aReturn = aEnv->CallBooleanMethod(_objJNIHelper, aMethodID, aPath, aArray, pLength);
                aEnv->DeleteLocalRef(aPath);

                if((aReturn == false) && (gDirDocuments.mLength > 0))
                {
                    FString aDocPath = gDirDocuments + pFileName;

                    aPath = aEnv->NewStringUTF(aDocPath.c());
                    aReturn = aEnv->CallBooleanMethod(_objJNIHelper, aMethodID, aPath, aArray, pLength);
                    aEnv->DeleteLocalRef(aPath);

                }

                aEnv->ReleaseByteArrayElements(aArray, aByte, 0);
                aEnv->DeleteLocalRef(aArray);
            }
        }
    }
    return aReturn;
}

FString os_getBundleDirectory()
{
    FString aPath;
    aPath += "/";
    
    Log("Bundle: [%s]\n", aPath.c());
    
    return aPath;
}

FString os_getDocumentsDirectory() {
    FString aPath;
    aPath += "/";
    
    Log("Documents: [%s]\n", aPath.c());
    
    return aPath;
}

void os_load_image_to_buffer(char *pFile, unsigned int *pData)
{
    jmethodID aMethodID;
    JNIEnv *aEnv = os_getJNIEnv();

    if(aEnv)
    {
        jstring aJavaFileName = aEnv->NewStringUTF(pFile);
        aMethodID = aEnv->GetMethodID(_clsJNIHelper, "loadBitmap", "(Ljava/lang/String;)Landroid/graphics/Bitmap;");

        jobject aBitmap = aEnv->CallObjectMethod(_objJNIHelper, aMethodID, aJavaFileName);
        aEnv->DeleteLocalRef(aJavaFileName);

        if(aBitmap)
        {
            aMethodID = aEnv->GetMethodID(_clsJNIHelper, "getBitmapWidth", "(Landroid/graphics/Bitmap;)I");
            int aWidth = aEnv->CallIntMethod(_objJNIHelper, aMethodID, aBitmap);

            aMethodID = aEnv->GetMethodID(_clsJNIHelper, "getBitmapHeight", "(Landroid/graphics/Bitmap;)I");
            int aHeight = aEnv->CallIntMethod(_objJNIHelper, aMethodID, aBitmap);

            if((aWidth > 0) && (aHeight > 0))
            {
                int aArea = aWidth * aHeight;

                jintArray aArray = aEnv->NewIntArray(aArea);

                aMethodID = aEnv->GetMethodID(_clsJNIHelper, "getBitmapPixels", "(Landroid/graphics/Bitmap;[I)V");
                aEnv->CallVoidMethod(_objJNIHelper, aMethodID, aBitmap, aArray);

                aMethodID = aEnv->GetMethodID(_clsJNIHelper, "closeBitmap", "(Landroid/graphics/Bitmap;)V");
                aEnv->CallVoidMethod(_objJNIHelper, aMethodID, aBitmap);

                //aData = new unsigned int[aArea];
                jint *aPixels = aEnv->GetIntArrayElements(aArray, 0);

                unsigned char *aPixelBytesOriginal = (unsigned char *)aPixels;
                unsigned char *aDataBytesOriginal = (unsigned char *)pData;

                unsigned char *aPixelBytes = aPixelBytesOriginal;
                unsigned char *aDataBytes = aDataBytesOriginal;

                int aByteLength = aArea * 4;

                unsigned char *aPixelShelf = &(aPixelBytesOriginal[aByteLength]);

                aPixelBytes = &(aPixelBytesOriginal[2]);
                aDataBytes = &(aDataBytesOriginal[0]);
                while(aPixelBytes < aPixelShelf)
                {
                    *aDataBytes = *aPixelBytes;
                    aPixelBytes += 4;
                    aDataBytes += 4;
                }

                aPixelBytes = &(aPixelBytesOriginal[1]);
                aDataBytes = &(aDataBytesOriginal[1]);
                while(aPixelBytes < aPixelShelf)
                {
                    *aDataBytes = *aPixelBytes;
                    aPixelBytes += 4;
                    aDataBytes += 4;
                }

                aPixelBytes = &(aPixelBytesOriginal[0]);
                aDataBytes = &(aDataBytesOriginal[2]);
                while(aPixelBytes < aPixelShelf)
                {
                    *aDataBytes = *aPixelBytes;
                    aPixelBytes += 4;
                    aDataBytes += 4;
                }

                aPixelBytes = &(aPixelBytesOriginal[3]);
                aDataBytes = &(aDataBytesOriginal[3]);
                while(aPixelBytes < aPixelShelf)
                {
                    *aDataBytes = *aPixelBytes;
                    aPixelBytes += 4;
                    aDataBytes += 4;
                }

                aEnv->ReleaseIntArrayElements(aArray, aPixels, 0);
                aEnv->DeleteLocalRef(aArray);
            }
            else
            {
                aMethodID = aEnv->GetMethodID(_clsJNIHelper, "closeBitmap", "(Landroid/graphics/Bitmap;)V");
                aEnv->CallVoidMethod(_objJNIHelper, aMethodID, aBitmap);
            }
        }
    }
}

void os_set_graphics_context() {
    jmethodID aMethodID;
    JNIEnv *aEnv = os_getJNIEnv();

    if(aEnv)
    {
        aMethodID = aEnv->GetMethodID(_clsJNIHelper, "setOpenGLContext", "()V");

        //aMethodID = aEnv->GetMethodID(_clsJNIHelper, "closeBitmap", "(Landroid/graphics/Bitmap;)V");
        aEnv->CallVoidMethod(_objJNIHelper, aMethodID);


    }
}

unsigned int *os_load_image(char *pFile,int &pWidth, int &pHeight) {
    pWidth = 0;
    pHeight = 0;

    Log("Load Bitmap... [%s]\n", pFile);

    unsigned int *aData = 0;

    jmethodID aMethodID;
    JNIEnv *aEnv = os_getJNIEnv();

    if(aEnv)
    {
        jstring aJavaFileName = aEnv->NewStringUTF(pFile);
        aMethodID = aEnv->GetMethodID(_clsJNIHelper, "loadBitmap", "(Ljava/lang/String;)Landroid/graphics/Bitmap;");

        jobject aBitmap = aEnv->CallObjectMethod(_objJNIHelper, aMethodID, aJavaFileName);
        aEnv->DeleteLocalRef(aJavaFileName);

        Log("Load Bitmap 2... [%s]\n", pFile);

        if(aBitmap)
        {

            aMethodID = aEnv->GetMethodID(_clsJNIHelper, "getBitmapWidth", "(Landroid/graphics/Bitmap;)I");
            pWidth = aEnv->CallIntMethod(_objJNIHelper, aMethodID, aBitmap);

            aMethodID = aEnv->GetMethodID(_clsJNIHelper, "getBitmapHeight", "(Landroid/graphics/Bitmap;)I");
            pHeight = aEnv->CallIntMethod(_objJNIHelper, aMethodID, aBitmap);

            Log("Load Bitmap 3... [%d x %d]\n", pWidth, pHeight);

            if((pWidth > 0) && (pHeight > 0))
            {
                int aArea = pWidth * pHeight;

                jintArray aArray = aEnv->NewIntArray(aArea);

                aMethodID = aEnv->GetMethodID(_clsJNIHelper, "getBitmapPixels", "(Landroid/graphics/Bitmap;[I)V");
                aEnv->CallVoidMethod(_objJNIHelper, aMethodID, aBitmap, aArray);

                aMethodID = aEnv->GetMethodID(_clsJNIHelper, "closeBitmap", "(Landroid/graphics/Bitmap;)V");
                aEnv->CallVoidMethod(_objJNIHelper, aMethodID, aBitmap);

                aData = new unsigned int[aArea];
                jint *aPixels = aEnv->GetIntArrayElements(aArray, 0);

                unsigned char *aPixelBytesOriginal = (unsigned char *)aPixels;
                unsigned char *aDataBytesOriginal = (unsigned char *)aData;

                unsigned char *aPixelBytes = aPixelBytesOriginal;
                unsigned char *aDataBytes = aDataBytesOriginal;

                int aByteLength = aArea * 4;

                unsigned char *aPixelShelf = &(aPixelBytesOriginal[aByteLength]);

                aPixelBytes = &(aPixelBytesOriginal[2]);
                aDataBytes = &(aDataBytesOriginal[0]);
                while(aPixelBytes < aPixelShelf)
                {
                    *aDataBytes = *aPixelBytes;
                    aPixelBytes += 4;
                    aDataBytes += 4;
                }

                aPixelBytes = &(aPixelBytesOriginal[1]);
                aDataBytes = &(aDataBytesOriginal[1]);
                while(aPixelBytes < aPixelShelf)
                {
                    *aDataBytes = *aPixelBytes;
                    aPixelBytes += 4;
                    aDataBytes += 4;
                }

                aPixelBytes = &(aPixelBytesOriginal[0]);
                aDataBytes = &(aDataBytesOriginal[2]);
                while(aPixelBytes < aPixelShelf)
                {
                    *aDataBytes = *aPixelBytes;
                    aPixelBytes += 4;
                    aDataBytes += 4;
                }

                aPixelBytes = &(aPixelBytesOriginal[3]);
                aDataBytes = &(aDataBytesOriginal[3]);
                while(aPixelBytes < aPixelShelf)
                {
                    *aDataBytes = *aPixelBytes;
                    aPixelBytes += 4;
                    aDataBytes += 4;
                }

                aEnv->ReleaseIntArrayElements(aArray, aPixels, 0);
                aEnv->DeleteLocalRef(aArray);
            }
            else
            {
                aMethodID = aEnv->GetMethodID(_clsJNIHelper, "closeBitmap", "(Landroid/graphics/Bitmap;)V");
                aEnv->CallVoidMethod(_objJNIHelper, aMethodID, aBitmap);

                pWidth = 0;
                pHeight = 0;
            }
        }
    }
    return aData;
}

void os_exportPNGImage(unsigned int *pData, const char *pFilePath, int pWidth, int pHeight) {
    
}

void os_exportJPEGImage(unsigned int *pData, const char *pFilePath, int pWidth, int pHeight, float pQuality) {
    
}

void os_exportToPhotoLibrary(unsigned int *pData, int pWidth, int pHeight) {
    
}


bool os_createDirectory(const char *pDirectory)
{
    bool aReturn = false;
    
    
    return aReturn;
}


void os_getTestDirectory(FString *pString) {
    if (pString) {
        pString->Set("/Users/nraptis/Desktop/Exports/");
    }
}

void os_getFilesInDirectory(const char *pFilePath, FList *pList) {
    
}

void os_getFilesInDirectoryRecursive(const char *pFilePath, FList *pList) {
    if(pList)
    {
    DIR *dp;
    
    struct dirent *ep;
    
    dp = opendir ("./");
    char sf[1024];
    
    if(dp != NULL)
    {
        ep = readdir(dp);
        if(ep)
        {
            //aLoops1++;
            //Log("LOOPS1 = %d\n", aLoops1);
            
            //{
                
                char *n;
                DIR *dirp;
                struct dirent *direntp;
                
                dirp = opendir(pFilePath);
                
                if(dirp != NULL)
                {
                    //aLoops2 = 0;
                    for(;;)
                    {
                        //aLoops2++;
                        //Log("\tLOOPS2 = %d\n", aLoops2);
                        direntp = readdir( dirp );
                        
                        if(direntp == NULL)
                        {
                            break;
                        }
                        
                        n=direntp->d_name;
                        if (strcmp(n,".")!=0 && strcmp(n,"..")!=0)
                        {
                            strcpy(sf, pFilePath);
                            strcat(sf,n);
                            
                            FString *aString = new FString(sf);
                            
                            Log("FileDir = [%s]\n", aString->c());
                            
                            pList->Add(aString);
                            
                            //remove(sf);
                        }
                        
                        
                    }
                    closedir( dirp );
                    
                }
            }
            
            //puts (ep->d_name);
        //}
        
        //(void)closedir(dp);
    }
    }
}

void os_getAllResources(const char *pFilePath, FList *pList)
{
    
}
