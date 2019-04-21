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

class LevelWaveSpawnBlueprint {
public:
    LevelWaveSpawnBlueprint();
    ~LevelWaveSpawnBlueprint();
    
    void                                        Reset();
    
    FJSONNode                                   *Save();
    void                                        Load(FJSONNode *pNode);
    
    int                                         mSpawnSpacingOffset;
    
    //Possibility 1.) We have a formation...
    FString                                     mFormationID;
    
    //Possibility 2.) We have an object...
    int                                         mObjectType;
    
};


#endif /* LevelWaveSpawnBlueprint_hpp */
