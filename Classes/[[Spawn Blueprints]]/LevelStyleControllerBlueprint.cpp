//
//  LevelStyleControllerBlueprint.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nick Raptis on 9/19/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelStyleControllerBlueprint.hpp"
#include "os_core_graphics.h"
#include "core_includes.h"
#include "GameEditor.hpp"

LevelStyleControllerBlueprint::LevelStyleControllerBlueprint() {
    Reset();
}

LevelStyleControllerBlueprint::~LevelStyleControllerBlueprint() {
    
}

void LevelStyleControllerBlueprint::Update() {
    
}

void LevelStyleControllerBlueprint::Reset() {
    mDisableThreads = false;
    mEnableBobbleMode = false;
    mRandomizeSpin = false;
}

bool LevelStyleControllerBlueprint::ShouldSave() {
    
    if (mDisableThreads == true) { return true; }
    if (mEnableBobbleMode == true) { return true; }
    if (mEnableBobbleMode == true) { return true; }
    
    return false;
}

void LevelStyleControllerBlueprint::Build(LevelStyleController *pStyleController) {
    
    if (pStyleController == NULL) { return; }
    
    pStyleController->Reset();
    
    pStyleController->mDisableThreads = mDisableThreads;
    pStyleController->mEnableBobbleMode = mEnableBobbleMode;
    pStyleController->mRandomizeSpin = mRandomizeSpin;
}

FJSONNode *LevelStyleControllerBlueprint::Save() {
    
    FJSONNode *aExport = new FJSONNode();
    aExport->mNodeType = JSON_NODE_TYPE_DICTIONARY;
    
    if (mDisableThreads != false) { aExport->AddDictionaryBool("disable_threads", mDisableThreads); }
    if (mEnableBobbleMode != false) { aExport->AddDictionaryBool("enable_bobble", mEnableBobbleMode); }
    if (mRandomizeSpin != false) { aExport->AddDictionaryBool("randomize_spin", mRandomizeSpin); }
    
    return aExport;
}

void LevelStyleControllerBlueprint::Load(FJSONNode *pNode) {
    Reset();
    if (pNode == NULL) { return; }
    
    mDisableThreads = pNode->GetBool("disable_threads", false);
    mEnableBobbleMode = pNode->GetBool("enable_bobble", false);
    mRandomizeSpin = pNode->GetBool("randomize_spin", false);
    
}
