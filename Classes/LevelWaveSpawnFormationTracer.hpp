//
//  LevelWaveSpawnFormationTracerTracer.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/31/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelWaveSpawnFormationTracerTracer_hpp
#define LevelWaveSpawnFormationTracerTracer_hpp

#include "LevelWaveSpawnFormationTracerNode.hpp"
#include "FList.hpp"
#include "FPointList.h"

class LevelWaveSpawnFormation;
class LevelWaveSpawnFormationTracer {
public:
    LevelWaveSpawnFormationTracer(LevelWaveSpawnFormation *pFormation);
    ~LevelWaveSpawnFormationTracer();
    
    void                                        Reset();
    void                                        Spawn();
    void                                        Update();
    
    
    FList                                       mSpawnNodeList;
    
    FList                                       mTracerNodeList;
    
    LevelWaveSpawnFormation                     *mFormation;
    
    //Note: Path is NOT transformed...
    FPointList                                  mPath;
    FFloatList                                  mDist;
    
    int                                         mKillTimer;
    
    int                                         mCount;
    
    int                                         mPathIndex;
    
    
    void                                        SetSpeedClass(int pSpeedClass);
    float                                       mSpeed;
    
private:
    
    FList                                       mTracerNodeKillList;
    FList                                       mTracerNodeDeleteList;
    
    
    
    FList                                       mSpawnNodeKillList;
    FList                                       mSpawnNodeDeleteList;
    
    
    
    
};
    
#endif /* LevelWaveSpawnFormationTracerTracer_hpp */
