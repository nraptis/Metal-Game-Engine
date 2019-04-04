//
//  LevelWaveSpawnFormationNodeFormationNode.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/31/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelWaveSpawnFormationNodeFormationNode_hpp
#define LevelWaveSpawnFormationNodeFormationNode_hpp

#include "GameObject.hpp"

class LevelWaveSpawnFormation;
class LevelWaveSpawnFormationTracer;
class LevelWaveSpawnFormationNode {
public:
    LevelWaveSpawnFormationNode(LevelWaveSpawnFormation *pFormation);
    virtual ~LevelWaveSpawnFormationNode();
    
    void                                Spawn();
    
    void                                Reset();
    void                                Restart();
    
    void                                Update();
    void                                Draw();
    
    void                                DisposeObject(GameObject *pObject);
    
    void                                PositionObject();
    
    LevelWaveSpawnFormation             *mFormation;
    LevelWaveSpawnFormationTracer       *mTracer;
    GameObject                          *mObject;
    
    int                                 mPathIndexOffset;
    
    float                               mBaseX;
    float                               mBaseY;
    
    
    LevelWaveSpawnFormationNode         *Clone(LevelWaveSpawnFormation *pFormation);
    
    
    
    //The positioned X and Y values...
    float                               mX;
    float                               mY;
    
    int                                 mKillTimer;
};


#endif /* LevelWaveSpawnFormationNodeFormationNode_hpp */
