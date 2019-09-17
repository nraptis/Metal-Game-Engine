//
//  LevelWaveBlueprint.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelWaveBlueprint_hpp
#define LevelWaveBlueprint_hpp

#include "LevelPathBlueprint.hpp"
#include "LevelWaveSpawnBlueprint.hpp"

#define WAVE_MAX_SPAWN_COUNT 32

class LevelWave;
class LevelWaveBlueprint {
public:
    LevelWaveBlueprint();
    ~LevelWaveBlueprint();
    
    void                                        Reset();
    
    void                                        Update();
    void                                        Draw(bool pSelected);
    
    LevelPathBlueprint                          mPath;
    LevelWaveSpawnBlueprint                     mSpawn[WAVE_MAX_SPAWN_COUNT + 1];
    
    int                                         mSpawnCount;
    int                                         mSelectedSpawnIndex;
    
    int                                         mSpawnSpacing;
    
    
    //int                                         mCreationType;
    
    bool                                        mCreationRequiresPrevWaveStart;
    bool                                        mCreationRequiresPrevWaveComplete;
    bool                                        mCreationRequiresScreenWavesClear;
    bool                                        mCreationRequiresScreenPermsClear;
    
    int                                         mCreationDelay;
    
    void                                        ApplyEditorConstraints();
    
    void                                        FindLargestSpawnSize();
    int                                         mMaxSpawnSize;
    
    void                                        ShiftSpawnFromIndex(int pIndex);
    
    void                                        FlipH();
    void                                        FlipV();
    
    
    
    //Note: BUILD should have NO TIE-IN TO EDITOR...
    //This HAS to work WITHOUT EDITOR for GAME......
    void                                        Build();
    void                                        Build(LevelWave *pWave);
    
    FJSONNode                                   *Save();
    void                                        Load(FJSONNode *pNode);
    
    int                                         mKillTimer;
};

#endif
