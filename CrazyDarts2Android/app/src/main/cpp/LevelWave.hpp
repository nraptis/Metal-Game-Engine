//
//  LevelWave.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/14/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelWave_hpp
#define LevelWave_hpp


#include "GameObject.hpp"
#include "LevelWavePath.hpp"
#include "LevelWaveSpawn.hpp"

class LevelWave {
public:
    LevelWave();
    virtual ~LevelWave();
    
    void                                Reset();
    void                                Restart();
    
    virtual void                        Spawn();
    virtual void                        Update();
    virtual void                        Draw();
    
    virtual void                        Dispose();
    virtual void                        DisposeObject(GameObject *pObject);
    
    bool                                mIsComplete;
    bool                                mRight;
    int                                 mAliveTimer;
    
    LevelWavePath                       mPath;
    
    FList                               mSpawnList;
    int                                 mSpawnIndex;
    
    float                               mSpawnSeparationDistance;
    
};


#endif /* LevelWave_hpp */
