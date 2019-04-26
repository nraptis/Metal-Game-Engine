//
//  LevelMotionControllerSliceBlueprint.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/20/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelMotionControllerSliceBlueprint.hpp"
#include "LevelWave.hpp"
#include "GameEditor.hpp"

LevelMotionControllerSliceBlueprint::LevelMotionControllerSliceBlueprint() {
    mType = LEVEL_MOTION_SLICE_TYPE_NONE;
    mSpeedClass = SPEED_CLASS_MEDIUM;
    mSpeedNegateAlways = false;
    mSpeedNegateRandomly = false;
    mKillTimer = 8;
}

LevelMotionControllerSliceBlueprint::~LevelMotionControllerSliceBlueprint() {
    
}

void LevelMotionControllerSliceBlueprint::Build(LevelMotionControllerSlice *pSlice) {
    
    if (pSlice == NULL) { return; }
    
    pSlice->mSpeedClass = mSpeedClass;
    pSlice->mSpeedNegateAlways = mSpeedNegateAlways;
    pSlice->mSpeedNegateRandomly = mSpeedNegateRandomly;
    
}

FJSONNode *LevelMotionControllerSliceBlueprint::Save() {
    FJSONNode *aExport = new FJSONNode();
    
    
    if (mType != LEVEL_MOTION_SLICE_TYPE_NONE) { aExport->AddDictionaryInt("type", mType); }
    
    if (mSpeedClass != SPEED_CLASS_MEDIUM) { aExport->AddDictionaryInt("speed_class", mSpeedClass); }
    if (mSpeedNegateAlways == true) { aExport->AddDictionaryBool("negate", mSpeedNegateAlways); }
    if (mSpeedNegateRandomly == true) { aExport->AddDictionaryBool("negate_rand", mSpeedNegateRandomly); }
    
    return aExport;
}

void LevelMotionControllerSliceBlueprint::Load(FJSONNode *pNode) {
    
    if (pNode == NULL) { return; }
    
    mSpeedClass = pNode->GetInt("speed_class", SPEED_CLASS_MEDIUM);
    mSpeedNegateAlways = pNode->GetBool("negate", false);
    mSpeedNegateRandomly = pNode->GetBool("negate_rand", false);
}




LevelMotionControllerSliceRotateBlueprint::LevelMotionControllerSliceRotateBlueprint() {
    mType = LEVEL_MOTION_SLICE_TYPE_ROTATE;
    mPivotOffsetX = 0;
    mPivotOffsetY = 0;
}

LevelMotionControllerSliceRotateBlueprint::~LevelMotionControllerSliceRotateBlueprint() {
    
}

void LevelMotionControllerSliceRotateBlueprint::Build(LevelMotionControllerSliceRotate *pSlice) {
    
    if (pSlice == NULL) { return; }
    
    LevelMotionControllerSliceBlueprint::Build(pSlice);
    
}

FJSONNode *LevelMotionControllerSliceRotateBlueprint::Save() {
    
    FJSONNode *aExport = LevelMotionControllerSliceBlueprint::Save();
    
    if (mPivotOffsetX != 0) { aExport->AddDictionaryInt("pivot_offset_x", mPivotOffsetX); }
    if (mPivotOffsetY != 0) { aExport->AddDictionaryInt("pivot_offset_y", mPivotOffsetY); }
    
    return aExport;
}

void LevelMotionControllerSliceRotateBlueprint::Load(FJSONNode *pNode) {
    
    if (pNode == NULL) { return; }
    LevelMotionControllerSliceBlueprint::Load(pNode);
    
    mPivotOffsetX = pNode->GetInt("pivot_offset_x", 0);
    mPivotOffsetY = pNode->GetInt("pivot_offset_y", 0);
}

void LevelMotionControllerSliceRotateBlueprint::ResetPivot() {
    mPivotOffsetX = 0;
    mPivotOffsetY = 0;
    
    if (gEditor != NULL) {
        gEditor->RefreshPlayback();
    }
}
