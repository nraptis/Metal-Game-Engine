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
    
    void                                Reset();
    void                                Update();
    
    FList                               mNodeList;
    FList                               mTracerList;
    
    
private:
    
    FList                               mNodeKillList;
    FList                               mNodeDeleteList;
    
    FList                               mTracerKillList;
    FList                               mTracerDeleteList;
    
};

#endif /* LevelWaveFormation_hpp */
