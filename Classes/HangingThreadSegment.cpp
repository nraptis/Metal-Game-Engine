//
//  HangingThreadSegment.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nick Raptis on 8/22/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "HangingThreadSegment.hpp"

HangingThreadSegment::HangingThreadSegment() {
    
    mX = 0.0f;
    mY = 0.0f;
    mZ = 0.0f;
    
    mNormX = 0.0f;
    mNormY = -1.0f;
    mNormZ = 0.0f;
    
    for (int i=0;i<HANGING_THREAD_SEGMENT_RING_POINT_COUNT;i++) {
        mRingX[i] = 0.0f;
        mRingY[i] = 0.0f;
        mRingZ[i] = 0.0f;
    }
}

HangingThreadSegment::~HangingThreadSegment() {
    
}
