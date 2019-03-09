//
//  PlatformGraphicsInterface.cpp
//  Apex
//
//  Created by Nicholas Raptis on 12/14/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#include "PlatformGraphicsInterface.hpp"
#include "FApp.hpp"
#include "OpenGLViewController.h"
#import <UIKit/UIKit.h>

PlatformGraphicsInterface::PlatformGraphicsInterface() {
    mLastTime = 0.0f;
}

PlatformGraphicsInterface::~PlatformGraphicsInterface()
{
    //CCEAGLView *glview = (CCEAGLView*) _eaglview;
    //[glview release];
}

void PlatformGraphicsInterface::Initialize() {
    mLastTime = gOpenGLView.displayLink.timestamp;
}

float PlatformGraphicsInterface::GetScale() {
    return mScale;
}

bool PlatformGraphicsInterface::IsReady() {
    if (gOpenGLEngine != NULL) {
        return gOpenGLEngine->IsReady();
    }
    return false;
}


void PlatformGraphicsInterface::Kill() {
    //[CCDirectorCaller destroy];
    // destroy EAGLView
    //CCEAGLView *eaglview = (CCEAGLView*) _eaglview;
    //[eaglview removeFromSuperview];
    //[eaglview release];
    //release();
}

void PlatformGraphicsInterface::Prerender() {
    if (gOpenGLEngine) {
        gOpenGLEngine->Prerender();
    }
    //[gMetalEngine prerender];
}


void PlatformGraphicsInterface::Postrender() {
    if (gOpenGLEngine) {
        gOpenGLEngine->Postrender();
    }
}

bool PlatformGraphicsInterface::IsVSyncReady() {
    
    return true;
    
    /*
    //usleep(90000);
    
    double aTimeStamp = CACurrentMediaTime();
    double aFrameTime = (aTimeStamp - mLastTime) * 1000.0f;
    
    
    static int aOutOut = 0;
    
    aOutOut++;
    if (aOutOut >= 60) {
        aOutOut = 0;
        printf("aFrameTime = %f\n", aFrameTime);
    }
    
    if (aFrameTime > 16.7) {
        //printf("VSync is redy\n");
        mLastTime = gMetalView.displayLink.timestamp;
        return true;
    } else {
        //printf("VSync is NOT redy\n");
    }

    
    return false;
    */
}

void PlatformGraphicsInterface::SetContext() {
    [gOpenGLView setContext];
    
}


void PlatformGraphicsInterface::Commit() {
    
    [gOpenGLView commit];
    
    //[gMetalEngine commit];
}

