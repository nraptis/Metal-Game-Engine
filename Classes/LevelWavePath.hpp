//
//  LevelWavePath.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/15/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelWavePath_hpp
#define LevelWavePath_hpp

#include "FFloatList.h"
#include "FIntList.hpp"
#include "FPointList.h"
#include "FList.hpp"

//We move right through these points.
#define PATH_NODE_NORMAL 0

//We haven't decided anything.
#define PATH_NODE_INVALID -1

class LevelWavePathNode {
public:
    LevelWavePathNode();
    ~LevelWavePathNode();
    float                       mX;
    float                       mY;
    int                         mType;
    int                         mWaitTimer;
};

class LevelWavePath {
public:
    
    LevelWavePath();
    ~LevelWavePath();
    
    void                        Reset();
    
    void                        AddMove(float pX, float pY, int pWait = 0);
    
    bool                        mDidFinalize;
    
    void                        AddSegmentBacktrackingFrom(int pIndex);
    
    void                        Dump(bool pDecel);
    
    void                        Draw();
    void                        Finalize();
    
    bool                        mSmooth;
    
    float                       mSpeed;
    
    FList                       mNodeList;
    
    FPointList                  mPath;
    
    float                       mTestPer;
    
    float                       mTempX;
    float                       mTempY;
    
    int                         mDemoIndex;
    
private:
    void                        Add(int pType, float pX, float pY, int pWait);
    
};

#endif /* LevelWavePath_hpp */
