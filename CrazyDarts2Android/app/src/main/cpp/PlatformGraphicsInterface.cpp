//
//  PlatformGraphicsInterface.cpp
//  Apex
//
//  Created by Nicholas Raptis on 12/14/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#include "PlatformGraphicsInterface.hpp"
#include "FApp.hpp"

PlatformGraphicsInterface::PlatformGraphicsInterface() {
    mLastTime = 0.0f;
}

PlatformGraphicsInterface::~PlatformGraphicsInterface()
{
    //CCEAGLView *glview = (CCEAGLView*) _eaglview;
    //[glview release];
}

void PlatformGraphicsInterface::Initialize() {
    //mLastTime = gOpenGLView.displayLink.timestamp;
    
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
}


void PlatformGraphicsInterface::Postrender() {
    if (gOpenGLEngine) {
        gOpenGLEngine->Postrender();
    }
}

bool PlatformGraphicsInterface::IsVSyncReady() {
    
    return true;
    //usleep(90000);
    /*
    double aTime = CACurrentMediaTime() * 60.0f;
    double aLinkTime = mLastTime * 60.0f;
    double aDiff = (aTime - aLinkTime);
    //printf("---Time[%f] LinkTime[%f]  (%f)\n", aTime, aLinkTime, aDiff);
    
    int aFudge = 0;
    while (aDiff < 1.0f && aFudge < 2000) {
        usleep(200);
        aTime = CACurrentMediaTime() * 60.0f;
        aDiff = (aTime - aLinkTime);
        //printf(">Time[%f] LinkTime[%f]  (%f)\n", aTime, aLinkTime, aDiff);
        aFudge++;
    }
    if (aFudge > 1) {
        //printf("Sleeps[%d]\n", aFudge);
    }
    */
    
}

void PlatformGraphicsInterface::SetContext() {
    //[gOpenGLView setContext];
    
}

void PlatformGraphicsInterface::Commit() {
    
    //[gOpenGLView commit];
    //[gMetalEngine commit];

    os_commitRender();
}

