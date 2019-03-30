//
//  LevelWaveBlueprint.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelWaveBlueprint_hpp
#define LevelWaveBlueprint_hpp

#include "LevelWavePathBlueprint.hpp"
#include "LevelWaveSpawnBlueprint.hpp"

#define MAX_SPAWN_COUNT 64

class LevelWave;
class LevelWaveBlueprint {
public:
    LevelWaveBlueprint();
    ~LevelWaveBlueprint();
    
    void                                        Clear();
    
    void                                        Update();
    void                                        Draw(bool pSelected);
    LevelWavePathBlueprint                      mPath;
    
    LevelWaveSpawnBlueprint                     mSpawn[MAX_SPAWN_COUNT + 4];
    int                                         mSpawnCount;
    
    int                                         mSpawnSpacing;
    
    void                                        ApplyEditorConstraints();
    
    void                                        Build();
    void                                        Build(LevelWave *pWave);
    
    FJSONNode                                   *Save();
    void                                        Load(FJSONNode *pNode);
    
    int                                         mKillTimer;
};

#endif
