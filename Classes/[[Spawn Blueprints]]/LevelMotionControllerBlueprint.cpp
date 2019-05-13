//
//  LevelMotionControllerBlueprint.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/13/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

\
#include "LevelMotionControllerBlueprint.hpp"
#include "os_core_graphics.h"
#include "core_includes.h"
#include "GameEditor.hpp"

LevelMotionControllerBlueprint::LevelMotionControllerBlueprint() {

}

LevelMotionControllerBlueprint::~LevelMotionControllerBlueprint() {
    FreeList(LevelMotionControllerSliceBlueprint, mSliceList);
    FreeList(LevelMotionControllerSliceBlueprint, mKillList);
    
}

void LevelMotionControllerBlueprint::Update() {
    
    EnumList(LevelMotionControllerSliceBlueprint, aSlice, mSliceList) {
        
    }
    
    EnumList(LevelMotionControllerSliceBlueprint, aSlice, mKillList) {
        aSlice->mKillTimer--;
        if (aSlice->mKillTimer <= 0) { mDeleteList.Add(aSlice); }
    }
    EnumList(LevelMotionControllerSliceBlueprint, aSlice, mDeleteList) {
        mKillList.Remove(aSlice);
        delete aSlice;
    }
    mDeleteList.RemoveAll();
    
}

void LevelMotionControllerBlueprint::Reset() {
    RemoveAllSlices();
}

void LevelMotionControllerBlueprint::Draw() {
    
}

bool LevelMotionControllerBlueprint::IsEmpty() {
    if (mSliceList.mCount <= 0) { return true; }
    return false;
}

void LevelMotionControllerBlueprint::RemoveAllSlices() {
    EnumList(LevelMotionControllerSliceBlueprint, aSlice, mSliceList) {
        mKillList.Add(aSlice);
    }
    mSliceList.RemoveAll();
}

void LevelMotionControllerBlueprint::RemoveFirstSlice() {
    if (mSliceList.mCount > 0) {
        LevelMotionControllerSliceBlueprint *aSlice = (LevelMotionControllerSliceBlueprint *)mSliceList.PopFirst();
        mKillList.Add(aSlice);
    }
}

void LevelMotionControllerBlueprint::RemoveLastSlice() {
    if (mSliceList.mCount > 0) {
        LevelMotionControllerSliceBlueprint *aSlice = (LevelMotionControllerSliceBlueprint *)mSliceList.PopLast();
        mKillList.Add(aSlice);
    }
}

void LevelMotionControllerBlueprint::AddSliceNegate() {
    LevelMotionControllerSliceNegateBlueprint *aSlice = new LevelMotionControllerSliceNegateBlueprint();
    mSliceList.Add(aSlice);
}

void LevelMotionControllerBlueprint::AddSliceRotate() {
    LevelMotionControllerSliceRotateBlueprint *aSlice = new LevelMotionControllerSliceRotateBlueprint();
    mSliceList.Add(aSlice);
}

void LevelMotionControllerBlueprint::AddSliceOscillateRotation() {
    LevelMotionControllerSliceOscillateRotationBlueprint *aSlice = new LevelMotionControllerSliceOscillateRotationBlueprint();
    mSliceList.Add(aSlice);
}

void LevelMotionControllerBlueprint::AddSliceOscillateV() {
    LevelMotionControllerSliceOscillateVerticalBlueprint *aSlice = new LevelMotionControllerSliceOscillateVerticalBlueprint();
    mSliceList.Add(aSlice);
}

void LevelMotionControllerBlueprint::AddSliceOscillateH() {
    LevelMotionControllerSliceOscillateHorizontalBlueprint *aSlice = new LevelMotionControllerSliceOscillateHorizontalBlueprint();
    mSliceList.Add(aSlice);
}

void LevelMotionControllerBlueprint::Build(LevelMotionController *pMotionController) {
    
    if (pMotionController == NULL) { return; }
    
    pMotionController->Reset();
    
    EnumList(LevelMotionControllerSliceBlueprint, aSliceBlueprint, mSliceList) {
    
        if (aSliceBlueprint->mType == LEVEL_MOTION_SLICE_TYPE_NONE) {
            LevelMotionControllerSlice *aSlice = new LevelMotionControllerSlice();
            aSliceBlueprint->Build(aSlice);
            pMotionController->mSliceList.Add(aSlice);
        }
        
        if (aSliceBlueprint->mType == LEVEL_MOTION_SLICE_TYPE_NEGATE) {
            LevelMotionControllerSliceNegateBlueprint *aBlueprint = (LevelMotionControllerSliceNegateBlueprint *)aSliceBlueprint;
            LevelMotionControllerSliceNegate *aSlice = new LevelMotionControllerSliceNegate();
            aBlueprint->Build(aSlice);
            pMotionController->mSliceList.Add(aSlice);
        }
        
        if (aSliceBlueprint->mType == LEVEL_MOTION_SLICE_TYPE_ROTATE) {
            LevelMotionControllerSliceRotateBlueprint *aBlueprint = (LevelMotionControllerSliceRotateBlueprint *)aSliceBlueprint;
            LevelMotionControllerSliceRotate *aSlice = new LevelMotionControllerSliceRotate();
            aBlueprint->Build(aSlice);
            pMotionController->mSliceList.Add(aSlice);
        }
        
        if (aSliceBlueprint->mType == LEVEL_MOTION_SLICE_TYPE_OSCILLATE_ROTATION) {
            LevelMotionControllerSliceOscillateRotationBlueprint *aBlueprint = (LevelMotionControllerSliceOscillateRotationBlueprint *)aSliceBlueprint;
            LevelMotionControllerSliceOscillateRotation *aSlice = new LevelMotionControllerSliceOscillateRotation();
            aBlueprint->Build(aSlice);
            pMotionController->mSliceList.Add(aSlice);
        }
        
        if (aSliceBlueprint->mType == LEVEL_MOTION_SLICE_TYPE_OSCILLATE_VERTICAL) {
            LevelMotionControllerSliceOscillateVerticalBlueprint *aBlueprint = (LevelMotionControllerSliceOscillateVerticalBlueprint *)aSliceBlueprint;
            LevelMotionControllerSliceOscillateVertical *aSlice = new LevelMotionControllerSliceOscillateVertical();
            aBlueprint->Build(aSlice);
            pMotionController->mSliceList.Add(aSlice);
        }
        
        if (aSliceBlueprint->mType == LEVEL_MOTION_SLICE_TYPE_OSCILLATE_HORIZONTAL) {
            LevelMotionControllerSliceOscillateHorizontalBlueprint *aBlueprint = (LevelMotionControllerSliceOscillateHorizontalBlueprint *)aSliceBlueprint;
            LevelMotionControllerSliceOscillateHorizontal *aSlice = new LevelMotionControllerSliceOscillateHorizontal();
            aBlueprint->Build(aSlice);
            pMotionController->mSliceList.Add(aSlice);
        }
    }
}

FJSONNode *LevelMotionControllerBlueprint::Save() {
    
    FJSONNode *aExport = new FJSONNode();
    aExport->mNodeType = JSON_NODE_TYPE_DICTIONARY;
    

    FJSONNode *aSliceListNode = new FJSONNode();
    aSliceListNode->mNodeType = JSON_NODE_TYPE_ARRAY;
    
    EnumList(LevelMotionControllerSliceBlueprint, aSlice, mSliceList) {
        aSliceListNode->AddArray(aSlice->Save());
    }
    aExport->AddDictionary("slice_list", aSliceListNode);
    
    
    return aExport;
}

void LevelMotionControllerBlueprint::Load(FJSONNode *pNode) {
    Reset();
    if (pNode == NULL) { return; }
    
    
    FJSONNode *aSliceListNode = pNode->GetArray("slice_list");
    
    if (aSliceListNode != NULL) {
        EnumJSONArray(aSliceListNode, aSliceLoadNode) {
            
            int aType = aSliceLoadNode->GetInt("type", LEVEL_MOTION_SLICE_TYPE_NONE);
            
            LevelMotionControllerSliceBlueprint *aSlice = NULL;
            
            if (aType == LEVEL_MOTION_SLICE_TYPE_NONE) { aSlice = new LevelMotionControllerSliceBlueprint(); }
            if (aType == LEVEL_MOTION_SLICE_TYPE_NEGATE) { aSlice = new LevelMotionControllerSliceNegateBlueprint(); }
            if (aType == LEVEL_MOTION_SLICE_TYPE_ROTATE) { aSlice = new LevelMotionControllerSliceRotateBlueprint(); }
            if (aType == LEVEL_MOTION_SLICE_TYPE_OSCILLATE_ROTATION) { aSlice = new LevelMotionControllerSliceOscillateRotationBlueprint(); }
            if (aType == LEVEL_MOTION_SLICE_TYPE_OSCILLATE_VERTICAL) { aSlice = new LevelMotionControllerSliceOscillateVerticalBlueprint(); }
            if (aType == LEVEL_MOTION_SLICE_TYPE_OSCILLATE_HORIZONTAL) { aSlice = new LevelMotionControllerSliceOscillateHorizontalBlueprint(); }
            
            if (aSlice != NULL) {
                aSlice->Load(aSliceLoadNode);
                mSliceList.Add(aSlice);
            }
        }
    }
}
