//
//  HangingThread.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 8/20/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef HangingThread_hpp
#define HangingThread_hpp

#include "HangingThreadKnot.hpp"
#include "HangingThreadSegment.hpp"
#include "FSpline.hpp"
#include "FList.hpp"
#include "FPrimitive.hpp"

#define MIN_KNOT_COUNT 6
#define MAX_KNOT_COUNT 7

//So, here is our plan after toying for some time with the thing.

//1.) We build the "base" / default thread positions.
//2.) We will have 2 factors, "vertical compression" and "wind"
//3.) We rebuild the spline and chunked quads on each update...? (We have to test this, might be too laggy)

class HangingThread {
public:
    HangingThread();
    ~HangingThread();
    
    void                                Update();
    void                                Draw3D();
    
    void                                Setup();
    void                                Generate(float pWind, float pBounce);
    
    
    void                                ApplyEnvironmentals(float pWind, float pBounce);
    
    
    
    FDrawNodeList                       mNodeList;
    
    HangingThreadKnot                   *mKnot[MAX_KNOT_COUNT];
    int                                 mKnotCount;
    
    FSpline3D                           mSpline;
    
    FList                               mSegmentList;
    FList                               mSegmentQueue; //Segments which may be used...
    
    float                               mSegmentColorRed[HANGING_THREAD_SEGMENT_RING_POINT_COUNT];
    float                               mSegmentColorGreen[HANGING_THREAD_SEGMENT_RING_POINT_COUNT];
    float                               mSegmentColorBlue[HANGING_THREAD_SEGMENT_RING_POINT_COUNT];
    
    float                               mOffsetX;
    float                               mOffsetY;
    float                               mOffsetZ;
};

#endif
