//
//  LevelWave.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/14/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelWave_hpp
#define LevelWave_hpp

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
    //void                                Restart();
    
    void                                Prepare();
    
    void                                Update();
    void                                Draw();
    
    void                                DisposeObject(GameObject *pObject);
    
    bool                                mIsComplete;
    
    int                                 mExitType;
    
    
    LevelPath                           mPath;
    
    //Decides how the wave is "created" relative to the
    //previous wave. E.G. 200 ticks after prev wave starts...
    
    //TODO: We deprecate CREATION type in favor of
    //multiple flags which can be turned on and off...
    //int                                 mCreationType;
    
    bool                                mCreationRequiresPrevWaveStart;
    bool                                mCreationRequiresPrevWaveComplete;
    bool                                mCreationRequiresScreenWavesClear;
    bool                                mCreationRequiresScreenPermsClear;
    
    
    int                                 mCreationDelay;
    
    FList                               mSpawnList;
    int                                 mSpawnIndex;
    
    float                               mSpawnSpacing;
    
    int                                 mKillTimer;
    
private:
    FList                               mSpawnKillList;
    FList                               mSpawnDeleteList;
    
    FList                               mRecentlyCompletedList;
    
    void                                HandleSpawnComplete(LevelWaveSpawn *pSpawn);
    
};


#endif /* LevelWave_hpp */
