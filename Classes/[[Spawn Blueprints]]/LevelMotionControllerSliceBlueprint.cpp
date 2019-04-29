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
    pSlice->mPivotOffsetX = ((float)mPivotOffsetX);
    pSlice->mPivotOffsetY = ((float)mPivotOffsetY);
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





LevelMotionControllerSliceOscillateRotationBlueprint::LevelMotionControllerSliceOscillateRotationBlueprint() {
    mType = LEVEL_MOTION_SLICE_TYPE_OSCILLATE_ROTATION;
}

LevelMotionControllerSliceOscillateRotationBlueprint::~LevelMotionControllerSliceOscillateRotationBlueprint() {
    
}

void LevelMotionControllerSliceOscillateRotationBlueprint::Build(LevelMotionControllerSliceOscillateRotation *pSlice) {
    if (pSlice == NULL) { return; }
    LevelMotionControllerSliceBlueprint::Build(pSlice);
    
    //pSlice->mPivotOffsetX = ((float)mPivotOffsetX);
    //pSlice->mPivotOffsetY = ((float)mPivotOffsetY);
    
}

FJSONNode *LevelMotionControllerSliceOscillateRotationBlueprint::Save() {
    FJSONNode *aExport = LevelMotionControllerSliceBlueprint::Save();
    //if (mPivotOffsetX != 0) { aExport->AddDictionaryInt("pivot_offset_x", mPivotOffsetX); }
    //if (mPivotOffsetY != 0) { aExport->AddDictionaryInt("pivot_offset_y", mPivotOffsetY); }
    
    return aExport;
}

void LevelMotionControllerSliceOscillateRotationBlueprint::Load(FJSONNode *pNode) {
    if (pNode == NULL) { return; }
    LevelMotionControllerSliceBlueprint::Load(pNode);
    //mPivotOffsetX = pNode->GetInt("pivot_offset_x", 0);
    //mPivotOffsetY = pNode->GetInt("pivot_offset_y", 0);
    
}




LevelMotionControllerSliceOscillateVerticalBlueprint::LevelMotionControllerSliceOscillateVerticalBlueprint() {
    mType = LEVEL_MOTION_SLICE_TYPE_OSCILLATE_VERTICAL;
    mRadius = 32;
    mLinear = false;
    mLinearTimer = 90;
    mLinearTime = 180;
    mPause1 = 0;
    mPause2 = 0;
}

LevelMotionControllerSliceOscillateVerticalBlueprint::~LevelMotionControllerSliceOscillateVerticalBlueprint() {
    
}

void LevelMotionControllerSliceOscillateVerticalBlueprint::Build(LevelMotionControllerSliceOscillateVertical *pSlice) {
    if (pSlice == NULL) { return; }
    LevelMotionControllerSliceBlueprint::Build(pSlice);
    pSlice->mLinear = mLinear;
    pSlice->mLinearTimer = mLinearTimer;
    pSlice->mLinearTime = mLinearTime;
    pSlice->mRadius = ((float)mRadius);
    pSlice->mPause1 = mPause1;
    pSlice->mPause2 = mPause2;
}

FJSONNode *LevelMotionControllerSliceOscillateVerticalBlueprint::Save() {
    FJSONNode *aExport = LevelMotionControllerSliceBlueprint::Save();
    if (mLinear == true) { aExport->AddDictionaryBool("linear", mLinear); }
    if (mLinearTimer != 90) { aExport->AddDictionaryInt("linear_tick", mLinearTimer); }
    if (mLinearTime != 180) { aExport->AddDictionaryInt("linear_time", mLinearTime); }
    if (mRadius != 32) { aExport->AddDictionaryInt("radius", mRadius); }
    if (mPause1 != 0) { aExport->AddDictionaryInt("pause_1", mPause1); }
    if (mPause2 != 0) { aExport->AddDictionaryInt("pause_2", mPause2); }
    return aExport;
}

void LevelMotionControllerSliceOscillateVerticalBlueprint::Load(FJSONNode *pNode) {
    if (pNode == NULL) { return; }
    LevelMotionControllerSliceBlueprint::Load(pNode);
    mLinear = pNode->GetBool("linear", false);
    mLinearTimer = pNode->GetInt("linear_tick", 90);
    mLinearTime  = pNode->GetInt("linear_time", 180);
    mRadius = pNode->GetInt("radius", 32);
    mPause1 = pNode->GetInt("pause_1", 0);
    mPause2 = pNode->GetInt("pause_2", 0);
}


