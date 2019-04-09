//
//  LevelSectionPermanent.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/5/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelSectionPermanent_hpp
#define LevelSectionPermanent_hpp

#include "GameObject.hpp"
#include "LevelFormation.hpp"
#include "LevelPath.hpp"
#include "LevelWaveSpawn.hpp"

class LevelSection;
class LevelSectionPermanent {
public:
    LevelSectionPermanent(LevelSection *pSection);
    ~LevelSectionPermanent();
    
    void                                Reset();
    void                                Restart();
    
    void                                Prepare();
    void                                Spawn();
    
    void                                Update();
    void                                Draw();
    
    void                                PositionObject();
    
    void                                DisposeObject(GameObject *pObject);
    
    int                                 mObjectType;
    
    //Since the permanents will be positioned relative
    //to the "section" we need a base position and real
    float                               mBaseX;
    float                               mBaseY;
    
    float                               mX;
    float                               mY;
    
    GameObject                          *mObject;
    
    //TODO: Remember to assign this when we BUILD...
    LevelSection                        *mSection;
    
    LevelPath                           mPath;
    
    int                                 mKillTimer;

};


#endif /* LevelSectionPermanent_hpp */
