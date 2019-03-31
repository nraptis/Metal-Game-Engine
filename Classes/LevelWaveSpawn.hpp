//
//  LevelWaveSpawnSpawn.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/23/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelWaveSpawnSpawn_hpp
#define LevelWaveSpawnSpawn_hpp

//We are a "spawn" and we can either control
//a single balloon, or a cluster of ANYTHING (Space Lords? Maybe?)

#include "GameObject.hpp"

class LevelWave;
class LevelWavePath;
class LevelWaveSpawn {
public:
    LevelWaveSpawn(LevelWave *pWave, LevelWavePath *pPath);
    virtual ~LevelWaveSpawn();
    
    void                                Spawn();
    
    void                                Reset();
    void                                Restart();
    
    void                                Update();
    void                                Draw();
    
    void                                Dispose();
    void                                DisposeObject(GameObject *pObject);
    
    LevelWave                           *mWave;
    LevelWavePath                       *mPath;
    GameObject                          *mObject;
    
    int                                 mPathIndex;
    bool                                mIsComplete;
    
    float                               mBaseX;
    float                               mBaseY;
    float                               mDistanceTraveled;
    
    
    float                               mOffsetSpawnDistance;
    
    int                                 mKillTimer;
};


#endif /* LevelWaveSpawnSpawn_hpp */
