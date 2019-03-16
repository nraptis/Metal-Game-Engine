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


//We slow down to "stop" points
#define PATH_NODE_STOP 0

//Then we "wait" for some time
#define PATH_NODE_WAIT 1

//We move right through these points.
#define PATH_NODE_MOVE 2

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
    
    void                        Add(int pType, float pX, float pY);
    void                        AddMove(float pX, float pY);
    void                        AddStop(float pX, float pY);
    void                        AddWait(int pTime);
    
    bool                        mDidFinalize;
    
    void                        AddSegmentBacktrackingFrom(int pIndex);
    
    void                        Dump(bool pDecel);
    
    void                        Draw();
    void                        Finalize();
    
    float                       mSpeed;
    
    
    FList                       mNodeList;
    
    
    FPointList                  mRendumList;
    
    
    
};

#endif /* LevelWavePath_hpp */
