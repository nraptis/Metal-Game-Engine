//
//  LevelFormationConfigurationBlueprint.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nick Raptis on 9/8/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelFormationConfigurationBlueprint.hpp"
#include "core_includes.h"
#include "LevelPath.hpp"
#include "LevelFormationConfiguration.hpp"

LevelFormationConfigurationBlueprint::LevelFormationConfigurationBlueprint() {
    mTracerSpeedGlobal = SPEED_CLASS_DEFAULT;
    mTracerSpeed1 = SPEED_CLASS_DEFAULT;
    mTracerSpeed2 = SPEED_CLASS_DEFAULT;
    mTracerSpeed3 = SPEED_CLASS_DEFAULT;
    mTracerSpeed4 = SPEED_CLASS_DEFAULT;
    mTracerSpeed5 = SPEED_CLASS_DEFAULT;
    mTracerSpeed6 = SPEED_CLASS_DEFAULT;
    mTracerSpeed7 = SPEED_CLASS_DEFAULT;
    mTracerSpeed8 = SPEED_CLASS_DEFAULT;
}

LevelFormationConfigurationBlueprint::~LevelFormationConfigurationBlueprint() {
    
}

void LevelFormationConfigurationBlueprint::Reset() {
    
}

FJSONNode *LevelFormationConfigurationBlueprint::Save() {
    FJSONNode *aExport = new FJSONNode();
    aExport->mNodeType = JSON_NODE_TYPE_DICTIONARY;
    
    if (mTracerSpeedGlobal != SPEED_CLASS_DEFAULT) {
        aExport->AddDictionaryInt("tracer_speed_class_global", mTracerSpeedGlobal);
    } else {
        if (mTracerSpeed1 != SPEED_CLASS_DEFAULT) {
            aExport->AddDictionaryInt("tracer_speed_class_1", mTracerSpeed1);
        }
        if (mTracerSpeed2 != SPEED_CLASS_DEFAULT) {
            aExport->AddDictionaryInt("tracer_speed_class_2", mTracerSpeed2);
        }
        if (mTracerSpeed3 != SPEED_CLASS_DEFAULT) {
            aExport->AddDictionaryInt("tracer_speed_class_3", mTracerSpeed3);
        }
        if (mTracerSpeed4 != SPEED_CLASS_DEFAULT) {
            aExport->AddDictionaryInt("tracer_speed_class_4", mTracerSpeed4);
        }
        if (mTracerSpeed5 != SPEED_CLASS_DEFAULT) {
            aExport->AddDictionaryInt("tracer_speed_class_5", mTracerSpeed5);
        }
        if (mTracerSpeed6 != SPEED_CLASS_DEFAULT) {
            aExport->AddDictionaryInt("tracer_speed_class_6", mTracerSpeed6);
        }
        if (mTracerSpeed7 != SPEED_CLASS_DEFAULT) {
            aExport->AddDictionaryInt("tracer_speed_class_7", mTracerSpeed7);
        }
        if (mTracerSpeed8 != SPEED_CLASS_DEFAULT) {
            aExport->AddDictionaryInt("tracer_speed_class_8", mTracerSpeed8);
        }
    }
    
    return aExport;
}

void LevelFormationConfigurationBlueprint::Load(FJSONNode *pNode) {
    Reset();
    if (pNode == NULL) { return; }
    
    
    mTracerSpeedGlobal = pNode->GetInt("tracer_speed_class_global", SPEED_CLASS_DEFAULT);
    
    if (mTracerSpeedGlobal == SPEED_CLASS_DEFAULT) {
        mTracerSpeed1 = pNode->GetInt("tracer_speed_class_1", SPEED_CLASS_DEFAULT);
        mTracerSpeed2 = pNode->GetInt("tracer_speed_class_2", SPEED_CLASS_DEFAULT);
        mTracerSpeed3 = pNode->GetInt("tracer_speed_class_3", SPEED_CLASS_DEFAULT);
        mTracerSpeed4 = pNode->GetInt("tracer_speed_class_4", SPEED_CLASS_DEFAULT);
        mTracerSpeed5 = pNode->GetInt("tracer_speed_class_5", SPEED_CLASS_DEFAULT);
        mTracerSpeed6 = pNode->GetInt("tracer_speed_class_6", SPEED_CLASS_DEFAULT);
        mTracerSpeed7 = pNode->GetInt("tracer_speed_class_7", SPEED_CLASS_DEFAULT);
        mTracerSpeed8 = pNode->GetInt("tracer_speed_class_8", SPEED_CLASS_DEFAULT);
        
    }
    
    /*
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
    */
    
}

void LevelFormationConfigurationBlueprint::Build(LevelFormationConfiguration *pConfiguration) {
    
    if (pConfiguration == NULL) { return; }
    
    pConfiguration->mTracerSpeedGlobal = mTracerSpeedGlobal;
    pConfiguration->mTracerSpeed1 = mTracerSpeed1;
    pConfiguration->mTracerSpeed2 = mTracerSpeed2;
    pConfiguration->mTracerSpeed3 = mTracerSpeed3;
    pConfiguration->mTracerSpeed4 = mTracerSpeed4;
    pConfiguration->mTracerSpeed5 = mTracerSpeed5;
    pConfiguration->mTracerSpeed6 = mTracerSpeed6;
    pConfiguration->mTracerSpeed7 = mTracerSpeed7;
    pConfiguration->mTracerSpeed8 = mTracerSpeed8;
    
    
}
