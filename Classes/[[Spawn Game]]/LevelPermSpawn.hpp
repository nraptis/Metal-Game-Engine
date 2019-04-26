//
//  LevelPermSpawn.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/21/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelPermSpawn_hpp
#define LevelPermSpawn_hpp

#include "GameObject.hpp"
#include "LevelFormation.hpp"

class LevelSectionPermanent;
class LevelPath;
class LevelPermSpawn {
public:
    
    LevelPermSpawn(LevelSectionPermanent *pPerm, LevelPath *pPath);
    virtual ~LevelPermSpawn();
    
    void                                Spawn();
    
    void                                Reset();
    
    void                                Update();
    void                                Draw();
    
    void                                DisposeObject(GameObject *pObject);
    
    bool                                IsClear(); //all of the objects are either null or "un-killable" types
    
    void                                RefreshPathPosition();
    void                                SetObjectPosition();
    
    
    LevelSectionPermanent               *mPerm;
    LevelPath                           *mPath;
    GameObject                          *mObject;
    LevelFormation                      *mFormation;
    
    int                                 mPathIndex;
    
    float                               mSpacingOffset;
    
    bool                                mDidSpawn;
    bool                                mDidUpdateAfterSpawn;
    
    float                               mPathX;
    float                               mPathY;
    
    //Possibility 1.) We have a formation...
    FString                             mFormationID;
    
    //Possibility 2.) We have an object...
    int                                 mObjectType;
    
    int                                 mKillTimer;
};



#endif /* LevelPermSpawn_hpp */
