//
//  HangingThreadSegment.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nick Raptis on 8/22/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef HangingThreadSegment_hpp
#define HangingThreadSegment_hpp

#define HANGING_THREAD_SEGMENT_RING_POINT_COUNT 8

class HangingThreadSegment {
public:
    HangingThreadSegment();
    ~HangingThreadSegment();
    
    float                   mX;
    float                   mY;
    float                   mZ;
    
    float                   mNormX;
    float                   mNormY;
    float                   mNormZ;
    
    float                   mRingX[HANGING_THREAD_SEGMENT_RING_POINT_COUNT];
    float                   mRingY[HANGING_THREAD_SEGMENT_RING_POINT_COUNT];
    float                   mRingZ[HANGING_THREAD_SEGMENT_RING_POINT_COUNT];
    
};

#endif /* HangingThreadSegment_hpp */
