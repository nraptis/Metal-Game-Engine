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
#define WAVE_CREATION_TYPE_SCREEN_CLEAR_IGNORE_PERMS 3
#define WAVE_CREATION_TYPE_SCREEN_CLEAR_AND_PERMS 3



#define WAVE_EXIT_TYPE_DISPERSE 0
#define WAVE_EXIT_TYPE_INSTANT 1
//??
#define WAVE_EXIT_TYPE_STAGGER 2


#include "GameObject.hpp"
#include "LevelPath.hpp"
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
    
    int                                 mExitType;
    
    
    LevelPath                           mPath;
    
    //Decides how the wave is "created" relative to the
    //previous wave. E.G. 200 ticks after prev wave starts...
    int                                 mCreationType;
    int                                 mCreationDelay;
    
    FList                               mSpawnList;
    int                                 mSpawnIndex;
    
    float                               mSpawnSeparationDistance;
    
    int                                 mKillTimer;
    
private:
    FList                               mSpawnKillList;
    FList                               mSpawnDeleteList;
    
    // Only used duting update cycle.
    FList                               mRecentlyCompletedList;
    
    void                                HandleSpawnComplete(LevelWaveSpawn *pSpawn);
    
};


#endif /* LevelWave_hpp */
