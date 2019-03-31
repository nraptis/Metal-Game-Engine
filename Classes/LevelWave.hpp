//
//  LevelWave.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/14/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelWave_hpp
#define LevelWave_hpp

#define WAVE_CREATION_TYPE_PREV_WAVE_START 0
#define WAVE_CREATION_TYPE_PREV_WAVE_END 1
#define WAVE_CREATION_TYPE_PREV_WAVE_CLEAR 2
#define WAVE_CREATION_TYPE_SCREEN_CLEAR 3

#include "GameObject.hpp"
#include "LevelWavePath.hpp"
#include "LevelWaveSpawn.hpp"

class LevelWave {
public:
    LevelWave();
    ~LevelWave();
    
    void                                Reset();
    void                                Restart();
    
    
    void                                Prepare();
    
    void                                Update();
    void                                Draw();
    
    void                                DisposeObject(GameObject *pObject);
    
    bool                                mIsComplete;
    
    LevelWavePath                       mPath;
    
    //Decides how the wave is "created" relative to the
    //previous wave. E.G. 200 ticks after prev wave starts...
    int                                 mCreationType;
    int                                 mCreationDelay;
    
    
    FList                               mSpawnList;
    int                                 mSpawnIndex;
    
    float                               mSpawnSeparationDistance;
    
    int                                 mKillTimer;
    
    FList                               mSpawnKillList;
    FList                               mSpawnDeleteList;
};


#endif /* LevelWave_hpp */
