//
//  LevelPath.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/15/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelPath_hpp
#define LevelPath_hpp

#include "FFloatList.hpp"
#include "FIntList.hpp"
#include "FPointList.hpp"
#include "Constraint.hpp"
#include "FList.hpp"

#define SPEED_CLASS_EXTRA_SLOW -300
#define SPEED_CLASS_SLOW -200
#define SPEED_CLASS_MEDIUM_SLOW -100
#define SPEED_CLASS_MEDIUM 0
#define SPEED_CLASS_MEDIUM_FAST 100
#define SPEED_CLASS_FAST 200
#define SPEED_CLASS_EXTRA_FAST 300
#define SPEED_CLASS_INSANE 700

//We move right through these points.
#define PATH_NODE_NORMAL 0

//We haven't decided anything.
#define PATH_NODE_INVALID -1


class LevelPathNode {
public:
    LevelPathNode();
    ~LevelPathNode();
    float                               mX;
    float                               mY;
    int                                 mType;
    int                                 mWaitTimer;
    
    int                                 mKillTimer;
};

class LevelPath {
public:
    
    LevelPath();
    ~LevelPath();
    
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
    
    
    int                                 mStartConstraintTypeX;
    int                                 mStartConstraintTypeY;
    
    int                                 mEndConstraintTypeX;
    int                                 mEndConstraintTypeY;
    
    
    
private:
    void                                Add(int pType, float pX, float pY, int pWait);
    
    float                               mTempX;
    float                               mTempY;
    float                               mTempDist;
    
    FList                               mKillList;
    FList                               mDeleteList;
};

#endif /* LevelPath_hpp */
