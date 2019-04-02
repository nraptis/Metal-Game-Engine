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

class LevelWaveSpawnFormationTracer {
public:
    LevelWaveSpawnFormationTracer();
    ~LevelWaveSpawnFormationTracer();
    
    void                                        Reset();
    void                                        Spawn();
    void                                        Update();
    
    FList                                       mNodeList;
    
    //Note: Path is NOT transformed...
    FPointList                                  mPath;
    FFloatList                                  mDist;
    
    int                                         mKillTimer;
    
    void                                        SetSpeedClass(int pSpeedClass);
    float                                       mSpeed;
    
private:
    
    FList                                       mNodeKillList;
    FList                                       mNodeDeleteList;
    
};
    
#endif /* LevelWaveSpawnFormationTracerTracer_hpp */
