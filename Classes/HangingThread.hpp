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
#include "FSpline.hpp"

#define MIN_KNOT_COUNT 6
#define MAX_KNOT_COUNT 9

//So, here is our plan after toying for some time with the thing.

//1.) We build the "base" / default thread positions.
//2.) We will have 2 factors, "vertical compression" and "wind"
//3.) We rebuild the spline and chunked quads on each update...? (We have to test this, might be too laggy)

class HangingThread {
public:
    HangingThread();
    ~HangingThread();
    
    float                               mSpawnOffsetX;
    float                               mSpawnOffsetY;
    float                               mSpawnOffsetZ;
    
    void                                Update();
    void                                Draw();
    void                                Draw3D();
    
    void                                Setup();
    
    void                                Generate();
    
    
    
    HangingThreadKnot                   *mKnot[MAX_KNOT_COUNT];
    int                                 mKnotCount;
    
    FSpline3D                           mSpline;
    
};

#endif
