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
    
    //////////////
    //   Copy
    int                                         mCount;
    float                                       mSpeed;
    //
    //////////////
    
    
    //Note: Path is NOT transformed...
    FPointList                                  mPath;
    FFloatList                                  mDist;
    
    int                                         mKillTimer;
    
    
    
    int                                         mPathIndex;
    
    
    void                                        SetSpeedClass(int pSpeedClass);
    
    
    //We must clone inside of a formation (basically, only the formation will call this)
    LevelWaveSpawnFormationTracer               *Clone(LevelWaveSpawnFormation *pFormation);
    
    
    void                                        GetExtremeties(float &pTop, float &pRight, float &pLeft, float &pBottom);
    void                                        EditorKillAllObjects();
    
private:
    
    FList                                       mTracerNodeKillList;
    FList                                       mTracerNodeDeleteList;
    
    
    
    FList                                       mSpawnNodeKillList;
    FList                                       mSpawnNodeDeleteList;
    
    
    
    
};
    
#endif /* LevelWaveSpawnFormationTracerTracer_hpp */
