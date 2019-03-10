//
//  core_os.m
//  CoreDemo
//
//  Created by Nick Raptis on 9/26/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#include "os_core_outlets.h"
#include "core_includes.h"

#include <sys/time.h>
#include <sys/stat.h>

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

#import <mach/mach.h>
#import <mach/mach_host.h>
#import <mach/mach_time.h>


using namespace std;

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

jmethodID os_getMethodInfo(const char *methodName, const char *paramCode) {
    jmethodID aMethodID = 0;
    gJNIEnv = os_getJNIEnv();
    if (gJNIEnv == 0) {
        Log("Null Environment..\n");
    } else {
        jclass aClass = gJNIEnv->FindClass(JAVA_OUTLET_CLASS);
        if (!aClass) {
            Log("Failed to find class of %s", JAVA_OUTLET_CLASS);
        }
        aMethodID = gJNIEnv->GetMethodID(aClass, methodName, paramCode);
        if (aMethodID == 0) {
            Log("Failed to find method id of %s", methodName);
        }
    }
    return aMethodID;
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
    if (pFilePath) aReturn = access(pFilePath,0) == 0;
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

unsigned int os_system_time() {
    const int64_t aMillion = 1000000;
    static mach_timebase_info_data_t aInfo;
    if (aInfo.denom == 0) {
        mach_timebase_info(&aInfo);
    }
    return (int)((mach_absolute_time()*aInfo.numer)/(aMillion*aInfo.denom));
}

unsigned char *os_read_file(const char *pFileName, unsigned int &pLength) {
    Log("1 - [%s]\n", pFileName);
    
    pLength = 0;
    unsigned char *aData = 0;
    
    
    jmethodID aMethodID = 0;
    if ((gJVM != 0) && (pFileName != 0)) {
        //jmethodID mid;
        
        
        JNIEnv *aENV = os_getJNIEnv();
        
        jclass aClass = os_getClassID(aENV);
        
        Log("2 - [%s]\n", pFileName);
        
        
        if ((aENV != 0) && (aClass != 0)) {
            aMethodID = aENV->GetMethodID(aClass, "readFileLength", "(Ljava/lang/String;)I");
            
            Log("3 - [%s] (%d)\n", pFileName, aMethodID);
            
            if(aMethodID)
            {
                Log("4 - [%s]\n", pFileName);
                
                
                jstring aFileName = aENV->NewStringUTF(pFileName);
                
                Log("5 - [%s]\n", pFileName);
                
                //jobject png = env->CallObjectMethod(_objJNIHelper, mid, name, true);
                
                pLength = aENV->CallIntMethod(_objJNIHelper, aMethodID, aFileName);
                
                Log("6 - [%s] (%d)\n", pFileName, pLength);
                
                
                if(pLength > 0)
                {
                    Log("7 - [%s] (%d)\n", pFileName, pLength);
                    
                    
                    jbyteArray aArray = aENV->NewByteArray(pLength + 1);
                    
                    //env->NewGlobalRef(array);
                    
                    //mid = env->GetMethodID(_clsJNIHelper, "getBitmapPixels", "(Landroid/graphics/Bitmap;[I)V");
                    //env->CallVoidMethod(_objJNIHelper, mid, png, array);
                    
                    aMethodID = aENV->GetMethodID(aClass, "readFileData", "(Ljava/lang/String;[B)V");
                    
                    Log("8 - [%s] (%d)\n", pFileName, aMethodID);
                    
                    
                    if (aMethodID) {
                        
                        Log("9 - [%s] (%d)\n", pFileName, pLength);
                        
                        
                        aENV->CallVoidMethod(_objJNIHelper, aMethodID, aFileName, aArray);
                        
                        Log("10 - [%s] (%d)\n", pFileName, pLength);
                        
                        
                        //jintArray array = env->NewIntArray(width * height);
                        //env->NewGlobalRef(array);
                        //mid = env->GetMethodID(_clsJNIHelper, "getBitmapPixels", "(Landroid/graphics/Bitmap;[I)V");
                        //env->CallVoidMethod(_objJNIHelper, mid, png, array);
                        
                        
                        
                        //jint *pixels = env->GetIntArrayElements(array, 0);
                        aData = (unsigned char *)aENV->GetByteArrayElements(aArray, 0);
                        
                        
                    }
                    else
                        
                    {
                        Log("F-1 - [%s] (%d)\n", pFileName, pLength);
                        
                        pLength = 0;
                    }
                    
                    
                    
                    
                    
                    //env->CallVoidMethod(_objJNIHelper, mid, aFileName,
                    
                    
                    
                    //readFileData(String pPath, byte[] pData, int pLength)
                    
                }
                else
                    
                {
                    Log("F-2 - [%s] (%d)\n", pFileName, pLength);
                    
                    pLength = 0;
                }
                
                
                
                Log("10 - [%s] (%d)\n", pFileName, pLength);
                
                aENV->DeleteLocalRef(aFileName);
                
                Log("20 - [%s]\n", pFileName);
                
                
                
                
                if(pLength > 0)
                {
                    
                }
                
            }
            
        }
    }
    
    
    
    
    
    return aData;
    
}

bool os_write_file(const char *pFileName, unsigned char *pData, unsigned int pLength)
{
    if(pFileName == 0)
    {
        return false;
    }
    
    int aFile = creat(pFileName,S_IREAD|S_IWRITE);
    //int aFile = creat(pFileName,S_IWRITE);
    //Log("File 1.1 = [%d]\n", aFile);
    
    close(aFile);
    
    aFile = open(pFileName, O_RDWR);
    //Log("File 1.2 = [%d]\n", aFile);
    
    
    if(aFile != -1)
    {
        write(aFile, pData, pLength);
        close(aFile);
        
        return true;
    }
    else
    {
        FString aPath = FString(gDirDocuments + pFileName);
        
        //Log("Write Path = [%s]\n", aPath.c());
        
        aFile = creat(aPath.c(), S_IREAD|S_IWRITE);
        //Log("File.1 2 = [%d]\n", aFile);
        
        
        //aFile = creat(aPath.c(),S_IWRITE);
        close(aFile);
        
        aFile = open(aPath.c(), O_RDWR);
        //Log("File 2.2 = [%d]\n", aFile);
        
        if(aFile != -1)
        {
            write(aFile, pData, pLength);
            close(aFile);
            
            return true;
        }
    }
    
    return false;
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
    UIImage *aImage;
    NSString *aPath=[NSString stringWithUTF8String:pFile];
    
    aImage = [UIImage imageWithContentsOfFile:aPath];
    
    //if(aImage == nil)aImage = [UIImage imageNamed:aPath];
    
    int aWidth = 0;
    int aHeight = 0;
    
    if(aImage)
    {
        if(aImage.size.width>0&&aImage.size.height>0)
        {
            aWidth = aImage.size.width;
            aHeight = aImage.size.height;
            
            CGImageRef aCGImage=aImage.CGImage;
            //aData = new unsigned int[(unsigned int)(pWidth*pHeight)];
            
            CGColorSpaceRef aColorSpace=CGColorSpaceCreateDeviceRGB();
            CGContextRef aCGContext=CGBitmapContextCreate(pData, aWidth, aHeight, 8, aWidth*4, aColorSpace, kCGImageAlphaPremultipliedLast);
            CGContextClearRect(aCGContext, CGRectMake(0, 0, aWidth, aHeight));
            CGContextDrawImage(aCGContext,CGRectMake(0, 0, aWidth, aHeight),aCGImage);
            CGContextRelease(aCGContext);
            CGColorSpaceRelease(aColorSpace);
        }
    }
}

unsigned int *os_load_image(char *pFile,int &pWidth, int &pHeight) {
    pWidth = 0;
    pHeight = 0;
    
    unsigned int *aData = 0;
    
    if (gJVM) {
        jmethodID mid;
        
        
        JNIEnv *env = os_getJNIEnv();
        
        
        if (env) {
            jstring name = env->NewStringUTF(pFile);
            
            mid = env->GetMethodID(_clsJNIHelper, "openBitmap",
                                   "(Ljava/lang/String;Z)Landroid/graphics/Bitmap;");
            
            jobject png = env->CallObjectMethod(_objJNIHelper, mid, name, true);
            env->DeleteLocalRef(name);
            
            if (png) {
                mid = env->GetMethodID(_clsJNIHelper, "getBitmapWidth", "(Landroid/graphics/Bitmap;)I");
                pWidth = env->CallIntMethod(_objJNIHelper, mid, png);
                
                mid = env->GetMethodID(_clsJNIHelper, "getBitmapHeight", "(Landroid/graphics/Bitmap;)I");
                pHeight = env->CallIntMethod(_objJNIHelper, mid, png);
                
                /* Get pixels */
                
                if ((pWidth > 0) && (pHeight > 0)) {
                    jintArray array = env->NewIntArray(pWidth * pHeight);
                    
                    //env->NewGlobalRef(array);
                    
                    mid = env->GetMethodID(_clsJNIHelper, "getBitmapPixels", "(Landroid/graphics/Bitmap;[I)V");
                    env->CallVoidMethod(_objJNIHelper, mid, png, array);
                    
                    
                    //jintArray array = env->NewIntArray(width * height);
                    //env->NewGlobalRef(array);
                    //mid = env->GetMethodID(_clsJNIHelper, "getBitmapPixels", "(Landroid/graphics/Bitmap;[I)V");
                    //env->CallVoidMethod(_objJNIHelper, mid, png, array);
                    
                    
                    
                    //jint *pixels = env->GetIntArrayElements(array, 0);
                    aData = (unsigned int *)env->GetIntArrayElements(array, 0);
                    
                    
                    
                    //Log("Loaded bitmap %s, width %d height %d\n", pFile, pWidth, pHeight);
                    
                    
                    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
                    
                    //env->ReleaseIntArrayElements(array, pixels, 0);
                    
                    //env->DeleteGlobalRef(array);
                    
                } else {
                    pWidth = 0;
                    pHeight = 0;
                }
                
                mid = env->GetMethodID(_clsJNIHelper, "closeBitmap", "(Landroid/graphics/Bitmap;)V");
                
                env->CallVoidMethod(_objJNIHelper, mid, png);
            }
        }
    }
    return aData;
}



void os_exportPNGImage(UIImage *pImage, const char *pFilePath) {
    
}

void os_exportJPEGImage(UIImage *pImage, const char *pFilePath, float pQuality) {
    
}

bool os_exportToPhotoLibrary(UIImage *pImage) {
    return true;
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
