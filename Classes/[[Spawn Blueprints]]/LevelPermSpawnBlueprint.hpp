//
//  LevelPermSpawnBlueprint.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/21/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelPermSpawnBlueprint_hpp
#define LevelPermSpawnBlueprint_hpp

#include "FJSON.hpp"

class LevelPermSpawnBlueprint {
public:
    LevelPermSpawnBlueprint();
    ~LevelPermSpawnBlueprint();
    
    void                                        Reset();
    
    FJSONNode                                   *Save();
    void                                        Load(FJSONNode *pNode);
    
    int                                         mSpawnSpacingOffset;
    
    //Possibility 1.) We have a formation...
    FString                                     mFormationID;
    
    //Possibility 2.) We have an object...
    int                                         mObjectType;
};

#endif /* LevelPermSpawnBlueprint_hpp */
