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
    
    LevelWaveSpawnFormation             *mFormation;
    GameObject                          *mObject;
    
    float                               mBaseX;
    float                               mBaseY;
    
    int                                 mKillTimer;
};


#endif /* LevelWaveSpawnFormationNodeFormationNode_hpp */
