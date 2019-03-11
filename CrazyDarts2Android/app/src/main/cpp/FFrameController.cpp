//
//  FFrameController.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/9/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "FFrameController.hpp"
#include "core_includes.h"

FFrameController::FFrameController() {
    mFrameCount = 0;
    mUpdatesPerSecond = 100;
    
    mStartTime = os_system_time();
    
    mMiliseconds = 0;
    mSeconds = 0;
    mFPS = 0;
    mUPS = 0;
    
    mConsecutiveBadReads = 0;
    
}

FFrameController::~FFrameController() {
    
}
//Call this when the OS decides to render a frame...
int FFrameController::Frame() {
    
    int aTime = os_system_time() & 0x7FFFFFFF;
    int aSlot = 0;
    
    if (mFrameCount < FRAME_CONTROLLER_HISTORY_COUNT) {
        aSlot = mFrameCount;
        ++mFrameCount;
    } else {
        
        for (int i=1;i<FRAME_CONTROLLER_HISTORY_COUNT;i++) {
            mFrameTime[i-1] = mFrameTime[i];
        }
        for (int i=1;i<FRAME_CONTROLLER_HISTORY_COUNT;i++) {
            mUpdateCount[i-1] = mUpdateCount[i];
        }
        
        aSlot = FRAME_CONTROLLER_HISTORY_COUNT - 1;
    }
    
    mFrameTime[aSlot] = aTime;
    mUpdateCount[aSlot] = 1; //Since the default is 1, we can assume we do 1 update...
    
    bool aReset = false;
    if (mFrameCount > 1) {
        int aTimeDiff = (int)(mFrameTime[mFrameCount - 1] - mFrameTime[mFrameCount - 2]);
        if (aTimeDiff > 100000 || aTimeDiff < 0) {
            Log("Something is whack with the time...\n");
            aReset = true;
        } else {
            mMiliseconds = aTime;
            mSeconds = (int)(mFrameTime[mFrameCount - 1] - mStartTime) / 1000;
        }
    }
    
    int aResult = 1;
    
    if (aReset) {
        Flush();
        mStartTime = aTime;
        aSlot = 0;
        mFrameCount = 1;
        
    } else {
        
        if (mFrameCount == 1) {
            mStartTime = aTime;
            Log("Frame Controller Start: %d\n", mStartTime);
        }
        
        if (mFrameCount > 8) {
            
            int aTimeDiff = (int)(mFrameTime[mFrameCount - 1] - mFrameTime[0]);
            int aTotalUpdates = 0;
            for (int i=0;i<mFrameCount;i++) {
                aTotalUpdates += mUpdateCount[i];
            }
            
            if (aTotalUpdates >= mFrameCount && aTotalUpdates < 1000 * 255 && aTimeDiff > 0 && aTimeDiff < 1000 * 1000) {
                
                // aTimeDiff / 1000 seconds have gone by...
                // We have performed aTotalUpdates updates in this time...
                
                float aSecondsEllapsed = ((float)aTimeDiff) / 1000.0f;
                float aExpectedUpdates = aSecondsEllapsed * ((float)mUpdatesPerSecond);
                
                float aUpdatesDelta = aExpectedUpdates - ((float)aTotalUpdates);
                
                if (aUpdatesDelta > 25.0f) {
                    Log("Too Many? %f\n", aUpdatesDelta);
                    aUpdatesDelta = 25.0f;
                    ++mConsecutiveBadReads;
                } else {
                    mConsecutiveBadReads = 0;
                }
                if (mConsecutiveBadReads > 5) {
                    Log("mConsecutiveBadReads = %d...\n", mConsecutiveBadReads);
                }
                
                if (aUpdatesDelta >= 1.0f) {
                    aResult = (int)aUpdatesDelta;
                    //Log("Recommend Updates: %d\n", aResult);
                    
                }
                
                mUPS = (int)(((float)aTotalUpdates) / aSecondsEllapsed);
                
            } else {
                Log("Bounds Error?? We have whacky numbers..? [%d] [%d]\n", aTimeDiff, aTotalUpdates);
                Flush();
            }
        }
    }
    
    if (aResult > 1) {
        aResult = 2;
    }
    
    mFrameTime[aSlot] = aTime;
    mUpdateCount[aSlot] = aResult;
    
    return aResult;
}

//The app has come alive from the background...
void FFrameController::Active() {
    Log("FFrameController::Active()\n");
    Flush();
}

//The app has gone into the backgrond;
void FFrameController::Inactive() {
    Log("FFrameController::Inactive()\n");
    Flush();
}

void FFrameController::Flush() {
    Log("FFrameController::Flush()\n");
    
    mConsecutiveBadReads = 0;
    mFrameCount = 0;
    mSeconds = 0;
    mMiliseconds = 0;
    mFPS = 0;
    mUPS = 0;
    
}
