//
//  LevelWaveFormation.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/15/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelWaveFormation_hpp
#define LevelWaveFormation_hpp


#include "FList.hpp"
#include "LevelWaveSpawnFormationTracer.hpp"
#include "LevelWaveSpawnFormationNode.hpp"

class LevelWaveSpawnFormationTracer;
class LevelWaveSpawnFormation {
public:
    LevelWaveSpawnFormation();
    ~LevelWaveSpawnFormation();
    
    void                                        Reset();
    void                                        Spawn();
    void                                        Update();
    void                                        Draw();
    
    FString                                     mID;
    
    FList                                       mNodeList;
    FList                                       mTracerList;
    
    
    ///////////////////
    //
    //   Copy Vars...
    //
    float                                       mX;
    float                                       mY;
    //
    //
    //////////////////
    
    
    float                                       mRotation;
    
    void                                        GetExtremeties(float &pTop, float &pRight, float &pLeft, float &pBottom);
    
    LevelWaveSpawnFormation                     *Clone();
    
    
    //For Editor
    void                                        EditorKillAllObjects();
    
private:
    
    FList                                       mNodeKillList;
    FList                                       mNodeDeleteList;
    
    FList                                       mTracerKillList;
    FList                                       mTracerDeleteList;
    
};

#endif /* LevelWaveFormation_hpp */
