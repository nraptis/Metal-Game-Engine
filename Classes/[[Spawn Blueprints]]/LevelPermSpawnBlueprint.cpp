//
//  LevelPermSpawnBlueprint.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/21/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelPermSpawnBlueprint.hpp"
#include "LevelFormationBlueprint.hpp"
#include "GameObject.hpp"
#include "Game.hpp"
#include "core_includes.h"

LevelPermSpawnBlueprint::LevelPermSpawnBlueprint() {
    
    mSpawnSpacingOffset = 0;
    
    
    
    mFormationID = "";
    
    mObjectType = GAME_OBJECT_TYPE_BALLOON;
}

LevelPermSpawnBlueprint::~LevelPermSpawnBlueprint() {
    
}

void LevelPermSpawnBlueprint::Reset() {
    mMotionController.Reset();
    mFormationConfiguration.Reset();
}

int LevelPermSpawnBlueprint::CountProgressObjects() {
    int aResult = 0;
    if (mFormationID.mLength > 0) {
        aResult += LevelFormationBlueprint::CountProgressObjects(mFormationID.c());
    } else {
        if (gGame->DoesObjectTypeCountTowardsProgressCount(mObjectType)) {
            aResult += 1;
        }
    }
    return aResult;
}

FJSONNode *LevelPermSpawnBlueprint::Save() {
    FJSONNode *aExport = new FJSONNode();
    aExport->mNodeType = JSON_NODE_TYPE_DICTIONARY;
    
    if (mSpawnSpacingOffset != 0) {
        aExport->AddDictionaryInt("spacing_offset", mSpawnSpacingOffset);
    }
    
    if (mFormationID.mLength > 0) {
        //Possibility 1.) We have a formation...
        aExport->AddDictionaryString("formation", mFormationID.c());
        aExport->AddDictionary("formation_config", mFormationConfiguration.Save());
        
    } else {
        //Possibility 2.) We have an object...
        if (mObjectType != GAME_OBJECT_TYPE_BALLOON) {
            aExport->AddDictionaryInt("type", mObjectType);
        }
    }
    
    if (mMotionController.IsEmpty() == false) {
        aExport->AddDictionary("motion", mMotionController.Save());
    }
    
    if (mStyleController.ShouldSave() == true) {
        aExport->AddDictionary("style", mStyleController.Save());
    }
    
    return aExport;
}

void LevelPermSpawnBlueprint::Load(FJSONNode *pNode) {
    Reset();
    if (pNode == NULL) { return; }
    
    mSpawnSpacingOffset = pNode->GetInt("spacing_offset", 0);
    
    mFormationID = pNode->GetString("formation", mFormationID);
    
    
    if (mFormationID.mLength > 0) {
        //Possibility 1.) We have a formation...
        
        FJSONNode *aFormationConfigurationNode = pNode->GetDictionary("formation_config");
        mFormationConfiguration.Load(aFormationConfigurationNode);
        
    } else {
        //Possibility 2.) We have an object...
        mObjectType = pNode->GetInt("type", mObjectType);
    }

    FJSONNode *aMotionNode = pNode->GetDictionary("motion");
    mMotionController.Load(aMotionNode);
    
    FJSONNode *aStyleNode = pNode->GetDictionary("style");
    mStyleController.Load(aStyleNode);
    
}
