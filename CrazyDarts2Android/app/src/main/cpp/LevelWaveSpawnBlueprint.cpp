//
//  LevelWaveSpawnBlueprint.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/29/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelWaveSpawnBlueprint.hpp"
#include "GameObject.hpp"
#include "core_includes.h"

LevelWaveSpawnBlueprint::LevelWaveSpawnBlueprint() {
    mSpawnSpacingOffset = 0;
    
    
    mFormationID = "";
    
    mObjectType = GAME_OBJECT_TYPE_BALLOON;
}

LevelWaveSpawnBlueprint::~LevelWaveSpawnBlueprint() {
    
}

void LevelWaveSpawnBlueprint::Reset() {
    mMotionController.Reset();
}

FJSONNode *LevelWaveSpawnBlueprint::Save() {
    FJSONNode *aExport = new FJSONNode();
    aExport->mNodeType = JSON_NODE_TYPE_DICTIONARY;
    
    if (mSpawnSpacingOffset != 0) {
        aExport->AddDictionaryInt("spacing_offset", mSpawnSpacingOffset);
    }
    
    if (mFormationID.mLength > 0) {
        //Possibility 1.) We have a formation...
        aExport->AddDictionaryString("formation", mFormationID.c());
    } else {
        //Possibility 2.) We have an object...
        if (mObjectType != GAME_OBJECT_TYPE_BALLOON) {
            aExport->AddDictionaryInt("type", mObjectType);
        }
    }
    
    if (mMotionController.IsEmpty() == false) {
        aExport->AddDictionary("motion", mMotionController.Save());
    }
    
    return aExport;
}

void LevelWaveSpawnBlueprint::Load(FJSONNode *pNode) {
    Reset();
    if (pNode == NULL) { return; }
    
    mSpawnSpacingOffset = pNode->GetInt("spacing_offset", 0);
    mFormationID = pNode->GetString("formation", mFormationID);
    
    if (mFormationID.mLength > 0) {
        //Possibility 1.) We have a formation...
    } else {
        //Possibility 2.) We have an object...
        mObjectType = pNode->GetInt("type", mObjectType);
    }

    
    FJSONNode *aMotionNode = pNode->GetDictionary("motion");
    mMotionController.Load(aMotionNode);
    
}
