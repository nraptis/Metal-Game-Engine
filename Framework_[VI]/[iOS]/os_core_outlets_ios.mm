//
//  core_os.m
//  CoreDemo
//
//  Created by Nick Raptis on 9/26/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

#include "RecursiveLockWrapper.h"

#include "os_core_outlets.h"
#include "core_includes.h"

#include <sys/time.h>
#include <sys/stat.h>
//#include <ofstream>

#include <fcntl.h>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cstdlib>
#include <dirent.h>
#include <chrono>


#include <pthread.h>
#include <sys/utsname.h>

#import <mach/mach.h>
#import <mach/mach_host.h>
#import <mach/mach_time.h>

using namespace std;

pthread_mutex_t gThreadMutex = PTHREAD_MUTEX_INITIALIZER;
NSMutableSet *gLockStrongReferenceSet = [[NSMutableSet alloc] init];
FList gThreadLockList;

dispatch_semaphore_t gLockSemaphore;
//[gLockStrongReferenceSet addObject: gLockSemaphore];


void os_initialize_outlets() {
    Log("Initialize Outlets...\n");
    
    gThreadLockList.Size(128);
    
    gLockSemaphore = dispatch_semaphore_create(1);
    [gLockStrongReferenceSet addObject: gLockSemaphore];
    
}

/*
void os_execute_on_main_thread(void (*pFunc)()) {
    if ([NSThread isMainThread]) {
        pFunc();
    } else {
        dispatch_sync(dispatch_get_main_queue(), ^{
            pFunc();
        });
    }
}
*/

void os_detach_thread(void (*theFunction)(void *theArg), void* theArg) {
    pthread_t aThread;
    pthread_attr_t aAttr;
    pthread_attr_init(&aAttr);
    pthread_attr_setdetachstate(&aAttr, PTHREAD_CREATE_DETACHED);
    pthread_create(&aThread,&aAttr, (void*(*)(void*))theFunction, theArg);
}

void os_sleep(int pTime) {
    usleep(pTime * 100);
}

bool os_updates_in_background() {
    return true;
}

bool os_draws_in_background() {
    return true;
}



/*
pthread_mutex_t gFrameMutex = PTHREAD_MUTEX_INITIALIZER;

void os_frame_mutex_enter() {
    Log("os_frame_mutex_enter()\n");
    pthread_mutex_lock( &gFrameMutex );
}

void os_frame_mutex_leave() {
    Log("os_frame_mutex_leave()\n");
    pthread_mutex_unlock( &gFrameMutex );
}


pthread_mutex_t gInterfaceMutex = PTHREAD_MUTEX_INITIALIZER;
void os_interface_mutex_enter() {
    pthread_mutex_lock( &gInterfaceMutex );
}

void os_interface_mutex_leave() {
    pthread_mutex_unlock( &gInterfaceMutex );
}
*/




//Since having a collision when creating locks can cause a potential
//freeze-up, we need to make sure only one lock uperation occurs at
//any one time... Mutexes lock up, so we do it the old fashioned way.
//volatile static bool gLockActionActive = false;

int os_create_thread_lock() {
    
    //dispatch_semaphore_wait(gLockSemaphore, DISPATCH_TIME_FOREVER);
    //while (gLockActionActive) {
    //    usleep(200);
    //}
    //gLockActionActive = true;
    //pthread_mutex_lock( &gThreadMutex );
    RecursiveLockWrapper *aContainer = [[RecursiveLockWrapper alloc] init];
    [gLockStrongReferenceSet addObject: aContainer];
    //aContainer.lock = [[NSRecursiveLock alloc] init];
    
    aContainer.semaphore = dispatch_semaphore_create(1);
    
    
    int aResult = gThreadLockList.mCount;
    gThreadLockList.Add((__bridge void *)aContainer);
    //gLockActionActive = false;
    //pthread_mutex_unlock( &gThreadMutex );
    
    
    //dispatch_semaphore_signal(gLockSemaphore);
    return aResult;
}

bool os_thread_lock_exists(int pLockIndex) {
    if (pLockIndex >= 0 && pLockIndex < gThreadLockList.mCount) {
        return true;
    }
    return false;
}

void os_delete_thread_lock(int pLockIndex) {
    //while (gLockActionActive) {
    //    usleep(200);
    //}
    //gLockActionActive = true;
    //dispatch_semaphore_wait(gLockSemaphore, DISPATCH_TIME_FOREVER);
    
    if (pLockIndex >= 0 && pLockIndex < gThreadLockList.mCount) {
        RecursiveLockWrapper *aContainer = ((__bridge RecursiveLockWrapper *)gThreadLockList.mData[pLockIndex]);
        //[aContainer.lock unlock];
        
        dispatch_semaphore_signal(aContainer.semaphore);
        
        [gLockStrongReferenceSet removeObject: aContainer];
        gThreadLockList.RemoveAtIndex(pLockIndex);
    }

    
    //dispatch_semaphore_signal(gLockSemaphore);
}

void os_delete_all_thread_locks() {
    //dispatch_semaphore_wait(gLockSemaphore, DISPATCH_TIME_FOREVER);
    
    
    for (int i=0;i<gThreadLockList.mCount;i++) {
        RecursiveLockWrapper *aContainer = ((__bridge RecursiveLockWrapper *)gThreadLockList.mData[i]);
        dispatch_semaphore_signal(aContainer.semaphore);
    }
    gThreadLockList.RemoveAll();
    [gLockStrongReferenceSet removeAllObjects];
    
    
    //dispatch_semaphore_signal(gLockSemaphore);
}

void os_lock_thread(int pLockIndex) {
    
    //dispatch_semaphore_wait(gLockSemaphore, DISPATCH_TIME_FOREVER);
    
    
    if (pLockIndex >= 0 && pLockIndex < gThreadLockList.mCount) {
        RecursiveLockWrapper *aContainer = ((__bridge RecursiveLockWrapper *)gThreadLockList.mData[pLockIndex]);
        
        dispatch_semaphore_wait(aContainer.semaphore, DISPATCH_TIME_FOREVER);
        
        //[aContainer.lock lock];
    }
    
    //dispatch_semaphore_signal(gLockSemaphore);
}

void os_unlock_thread(int pLockIndex) {
    
    //dispatch_semaphore_wait(gLockSemaphore, DISPATCH_TIME_FOREVER);
    
    
    if (pLockIndex >= 0 && pLockIndex < gThreadLockList.mCount) {
        RecursiveLockWrapper *aContainer = ((__bridge RecursiveLockWrapper *)gThreadLockList.mData[pLockIndex]);
        dispatch_semaphore_signal(aContainer.semaphore);
    }
    
    //dispatch_semaphore_signal(gLockSemaphore);
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

void os_log(const char *pMessage)
{
    NSLog(@"%s", pMessage);
}

unsigned int os_system_time() {
    
    unsigned long aMili =
    chrono::system_clock::now().time_since_epoch() /
    chrono::milliseconds(1);
    return (unsigned int)aMili;
    
    //timeval aTime;
    //gettimeofday(&aTime, NULL);
    //return aTime.tv_usec * 1000 + aTime.tv_usec / 1000;
    
    /*
    const int64_t aMillion = 1000000;
    static mach_timebase_info_data_t aInfo;
    if (aInfo.denom == 0) {
        mach_timebase_info(&aInfo);
    }
    return (int)((mach_absolute_time()*aInfo.numer)/(aMillion*aInfo.denom));
    */
}

unsigned char *os_read_file(const char *pFileName, unsigned int &pLength) {
    unsigned char *aReturn = nil;
    pLength = 0;
    if (pFileName) {
        int aFile=open(pFileName, O_RDONLY);
        if (aFile == -1) aFile = open(FString(gDirBundle + pFileName).c(), O_RDONLY);
        if (aFile == -1) aFile = open(FString(gDirDocuments + pFileName).c(), O_RDONLY);
        if (aFile != -1) {
            struct stat aFileStats;
            if(fstat(aFile,&aFileStats) == 0)pLength=(unsigned int)aFileStats.st_size;
            if(pLength >= 1)
            {
                aReturn = new unsigned char[pLength+32];
                read(aFile, aReturn, pLength);
            }
            else
            {
                pLength = 0;
            }
            close(aFile);
        }
    }
    
    return aReturn;
    
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
    
	CFURLRef aResourceURL = CFBundleCopyBundleURL(CFBundleGetMainBundle());
	CFStringRef aStringRef = CFURLCopyFileSystemPath(aResourceURL, kCFURLPOSIXPathStyle);
	CFRelease(aResourceURL);
	char aCharPath[1024];
	CFStringGetCString(aStringRef,aCharPath,FILENAME_MAX,kCFStringEncodingASCII);
	CFRelease(aStringRef);
    
    aPath = aCharPath;
    
    aPath += "/";
    
    Log("Bundle: [%s]\n", aPath.c());
    
    return aPath;
}

FString os_getDocumentsDirectory()
{
    FString aPath;
    
    NSArray *aPathArray = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,NSUserDomainMask,YES);
    NSString *aDocumentDirectory = [aPathArray objectAtIndex:0];
	//char aCharPath[1024];
    //[docDir getCString:aCharPath maxLength:PATH_MAX encoding:NSASCIIStringEncoding];
    aPath = [aDocumentDirectory UTF8String];
    
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

unsigned int *os_load_image(char *pFile,int &pWidth, int &pHeight)
{
    UIImage *aImage;
    NSString *aPath=[NSString stringWithUTF8String:pFile];
    
    aImage = [UIImage imageWithContentsOfFile:aPath];
    
    //if(aImage == nil)aImage = [UIImage imageNamed:aPath];
    
    pWidth=0;
    pHeight=0;
    
    unsigned int *aData=0;
    
    if (aImage) {
        if (aImage.size.width>0&&aImage.size.height>0) {
            pWidth= (int)(aImage.size.width * aImage.scale + 0.5f);
            pHeight= (int)(aImage.size.height * aImage.scale + 0.5f);
            
            CGImageRef aCGImage=aImage.CGImage;
            aData = new unsigned int[(unsigned int)(pWidth*pHeight)];
            CGColorSpaceRef aColorSpace=CGColorSpaceCreateDeviceRGB();
            CGContextRef aCGContext=CGBitmapContextCreate(aData, pWidth, pHeight, 8, pWidth*4, aColorSpace, kCGImageAlphaPremultipliedLast);
            CGContextClearRect(aCGContext, CGRectMake(0, 0, pWidth, pHeight));
            CGContextDrawImage(aCGContext,CGRectMake(0, 0, pWidth, pHeight),aCGImage);
            CGContextRelease(aCGContext);
            CGColorSpaceRelease(aColorSpace);
        }
    }
    return aData;
}



void os_exportPNGImage(UIImage *pImage, const char *pFilePath)
{
	NSData *aImageData = UIImagePNGRepresentation(pImage);
	[aImageData writeToFile:[[NSString alloc] initWithUTF8String:(pFilePath)] atomically:YES];
}

void os_exportJPEGImage(UIImage *pImage, const char *pFilePath, float pQuality)
{
	NSData *aImageData = UIImageJPEGRepresentation(pImage, pQuality);
	[aImageData writeToFile:[[NSString alloc] initWithUTF8String:(pFilePath)] atomically:YES];
}

bool os_exportToPhotoLibrary(UIImage *pImage)
{
    UIImageWriteToSavedPhotosAlbum(pImage, nil, nil, nil);
    
    /*
    ALAssetsLibrary *library = [[ALAssetsLibrary alloc] init];
    [library writeImageToSavedPhotosAlbum:[pImage CGImage]
                              orientation:(ALAssetOrientation)[pImage imageOrientation]
                          completionBlock:^(NSURL *assetURL, NSError *error)
     {
         //NSLog(@"Image Export Error[ %@ ]", error);
         
         if(error)
         {
             
         }
     }];
    */
    
    return true;
}

void os_exportPNGImage(unsigned int *pData, const char *pFilePath, int pWidth, int pHeight)
{
	UIImage *aImage;
	CGColorSpaceRef aColorSpace=CGColorSpaceCreateDeviceRGB();
	CGContextRef aBitmap = CGBitmapContextCreate(pData, pWidth, pHeight, 8, pWidth*4, aColorSpace, kCGImageAlphaPremultipliedLast);
	CGImageRef aRef = CGBitmapContextCreateImage(aBitmap);
	aImage = [[UIImage alloc] initWithCGImage:aRef];
	os_exportPNGImage(aImage, pFilePath);
	
	CGContextRelease(aBitmap);
}

void os_exportJPEGImage(unsigned int *pData, const char *pFilePath, int pWidth, int pHeight, float pQuality)
{
	UIImage *aImage;
	CGColorSpaceRef aColorSpace=CGColorSpaceCreateDeviceRGB();
	CGContextRef aBitmap = CGBitmapContextCreate(pData, pWidth, pHeight, 8, pWidth*4, aColorSpace, kCGImageAlphaPremultipliedLast);
	CGImageRef aRef = CGBitmapContextCreateImage(aBitmap);
	aImage = [[UIImage alloc] initWithCGImage:aRef];
	os_exportJPEGImage(aImage, pFilePath,pQuality);
	CGContextRelease(aBitmap);
}

void os_exportToPhotoLibrary(unsigned int *pData, int pWidth, int pHeight)
{
	UIImage *aImage;
	CGColorSpaceRef aColorSpace=CGColorSpaceCreateDeviceRGB();
	CGContextRef aBitmap = CGBitmapContextCreate(pData, pWidth, pHeight, 8, pWidth*4, aColorSpace, kCGImageAlphaPremultipliedLast);
	CGImageRef aRef = CGBitmapContextCreateImage(aBitmap);
	aImage = [[UIImage alloc] initWithCGImage:aRef];
	
	os_exportToPhotoLibrary(aImage);
    
	CGContextRelease(aBitmap);
}


bool os_createDirectory(const char *pDirectory)
{
    bool aReturn = false;
    
    
    return aReturn;
}


void os_getTestDirectory(FString *pString)
{
    if(pString)
    {
        pString->Set("/Users/nraptis/Desktop/Exports/");
    }
}

void os_getFilesInDirectory(const char *pFilePath, FList *pList)
{
    
}

void os_getFilesInDirectoryRecursive(const char *pFilePath, FList *pList)
{
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


