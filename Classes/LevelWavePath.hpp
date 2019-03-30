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

#define WAVE_SPEED_EXTRA_SLOW -300
#define WAVE_SPEED_SLOW -200
#define WAVE_SPEED_MEDIUM_SLOW -100
#define WAVE_SPEED_MEDIUM 0
#define WAVE_SPEED_MEDIUM_FAST 100
#define WAVE_SPEED_FAST 200
#define WAVE_SPEED_EXTRA_FAST 300
#define WAVE_SPEED_INSANE 700

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
    
    int                         mKillTimer;
};

class LevelWavePath {
public:
    
    LevelWavePath();
    ~LevelWavePath();
    
    void                                Reset();
    
    void                                AddMove(float pX, float pY, int pWait = 0);
    
    bool                                mDidFinalize;
    bool                                mDidFailFinalize;
    
    void                                AddSegmentBacktrackingFrom(int pIndex);
    
    void                                Update();
    void                                Draw();
    void                                Finalize();
    
    bool                                mSmooth;
    
    void                                SetSpeedClass(int pSpeedClass);
    float                               mSpeed;
    
    FList                               mNodeList;
    
    FPointList                          mPath;
    FFloatList                          mDist;
    
    float                               mTestPer;
    
    float                               mTempX;
    float                               mTempY;
    float                               mTempDist;
    
    int                                 mDemoIndex;
    
private:
    void                                Add(int pType, float pX, float pY, int pWait);
    
    FList                               mKillList;
    FList                               mDeleteList;
};

#endif /* LevelWavePath_hpp */
