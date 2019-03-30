//
//  LevelWaveSpawnBlueprint.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/29/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelWaveSpawnBlueprint.hpp"
#include "core_includes.h"

LevelWaveSpawnBlueprint::LevelWaveSpawnBlueprint() {
    
    mSpawnSpacingOffset = gRand.Get(-5, 5);
    
    
}

LevelWaveSpawnBlueprint::~LevelWaveSpawnBlueprint() {
    
}

void LevelWaveSpawnBlueprint::Reset() {
    
    
}


FJSONNode *LevelWaveSpawnBlueprint::Save() {
    FJSONNode *aExport = new FJSONNode();
    aExport->AddDictionaryInt("spacing_offset", mSpawnSpacingOffset);
    
    
    return aExport;
}

void LevelWaveSpawnBlueprint::Load(FJSONNode *pNode) {
    Reset();
    if (pNode == NULL) { return; }
    
    mSpawnSpacingOffset = pNode->GetInt("speed_class", mSpawnSpacingOffset);
    
    
}
