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
#include "LevelFormation.hpp"

class LevelWave;
class LevelPath;
class LevelWaveSpawn {
public:
    LevelWaveSpawn(LevelWave *pWave, LevelPath *pPath);
    virtual ~LevelWaveSpawn();
    
    void                                Spawn();
    
    void                                Reset();
    void                                Restart();
    
    void                                Update();
    void                                Draw();
    
    void                                DisposeObject(GameObject *pObject);
    
    LevelWave                           *mWave;
    LevelPath                           *mPath;
    GameObject                          *mObject;
    LevelFormation                      *mFormation;
    
    int                                 mPathIndex;
    bool                                mIsComplete;
    
    float                               mBaseX;
    float                               mBaseY;
    float                               mDistanceTraveled;
    
    
    //Possibility 1.) We have a formation...
    FString                             mFormationID;
    
    //Possibility 2.) We have an object...
    int                                 mObjectType;
    
    void                                HandOffAllGameObjects(FList *pList);
    
    float                               mOffsetSpawnDistance;
    
    int                                 mKillTimer;
};


#endif /* LevelWaveSpawnSpawn_hpp */
