//
//  LevelWaveSpawnBlueprint.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/29/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelWaveSpawnBlueprint_hpp
#define LevelWaveSpawnBlueprint_hpp

#include "FJSON.hpp"
#include "LevelMotionControllerBlueprint.hpp"
#include "LevelStyleControllerBlueprint.hpp"
#include "LevelFormationConfigurationBlueprint.hpp"

class LevelWaveSpawnBlueprint {
public:
    LevelWaveSpawnBlueprint();
    ~LevelWaveSpawnBlueprint();
    
    void                                        Reset();
    
    int                                         CountProgressObjects();
    
    FJSONNode                                   *Save();
    void                                        Load(FJSONNode *pNode);
    
    int                                         mSpawnSpacingOffset;
    
    
    LevelMotionControllerBlueprint              mMotionController;
    
    LevelStyleControllerBlueprint               mStyleController;
    
    //Possibility 1.) We have a formation...
    FString                                     mFormationID;
    LevelFormationConfigurationBlueprint        mFormationConfiguration;
    
    //Possibility 2.) We have an object...
    int                                         mObjectType;
};

#endif /* LevelWaveSpawnBlueprint_hpp */
