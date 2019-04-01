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
    
    
    
};


#endif /* LevelWaveSpawnBlueprint_hpp */
