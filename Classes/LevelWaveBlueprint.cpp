//
//  LevelWaveBlueprint.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelWaveBlueprint.hpp"
#include "GameEditor.hpp"

LevelWaveBlueprint::LevelWaveBlueprint() {
    
}

LevelWaveBlueprint::~LevelWaveBlueprint() {
    
}


void LevelWaveBlueprint::Draw(bool pSelected) {
    mPath.Draw(pSelected);
}

