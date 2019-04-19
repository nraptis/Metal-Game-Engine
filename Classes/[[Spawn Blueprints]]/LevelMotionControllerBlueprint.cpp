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
    //FreeList(LevelMotionControllerNodeBlueprint, mNodeList);
    //FreeList(LevelMotionControllerNodeBlueprint, mKillList);
    
}

void LevelMotionControllerBlueprint::Update() {
    
    
    /*
    EnumList(LevelMotionControllerNodeBlueprint, aNode, mKillList) {
        aNode->mKillTimer--;
        if (aNode->mKillTimer <= 0) { mDeleteList.Add(aNode); }
    }
    EnumList(LevelMotionControllerNodeBlueprint, aNode, mDeleteList) {
        mKillList.Remove(aNode);
        delete aNode;
    }
    mDeleteList.RemoveAll();
    */
}

void LevelMotionControllerBlueprint::Reset() {
    
    /*
    EnumList(LevelMotionControllerNodeBlueprint, aNode, mNodeList) {
        mKillList.Add(aNode);
    }
    mNodeList.RemoveAll();
    */
    
    
}

void LevelMotionControllerBlueprint::Draw() {
    
}


void LevelMotionControllerBlueprint::Build(LevelMotionController *pMotionController) {
    
    if (pMotionController == NULL) { return; }
    
    pMotionController->Reset();
    
    
    
}

FJSONNode *LevelMotionControllerBlueprint::Save() {
    
    FJSONNode *aExport = new FJSONNode();
    aExport->mNodeType = JSON_NODE_TYPE_DICTIONARY;
    
    /*
    if (mSmooth == true) {
        aExport->AddDictionaryBool("smooth", mSmooth);
    }
    
    if (mSpeedClass != SPEED_CLASS_MEDIUM) {
        aExport->AddDictionaryInt("speed_class", mSpeedClass);
    }
    
    
    FJSONNode *aNodeListNode = new FJSONNode();
    aNodeListNode->mNodeType = JSON_NODE_TYPE_ARRAY;
    
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelMotionControllerNodeBlueprint *aNode = (LevelMotionControllerNodeBlueprint *)mNodeList.mData[i];
        aNodeListNode->AddArray(aNode->Save());
    }
    aExport->AddDictionary("node_list", aNodeListNode);
    */
    
    return aExport;
}

void LevelMotionControllerBlueprint::Load(FJSONNode *pNode) {
    Reset();
    if (pNode == NULL) { return; }
    
    /*
    mSmooth = pNode->GetBool("smooth", false);
    mSpeedClass = pNode->GetInt("speed_class", SPEED_CLASS_MEDIUM);
    
    FJSONNode *aNodeListNode = pNode->GetArray("node_list");
    
    if (aNodeListNode != NULL) {
        EnumJSONArray(aNodeListNode, aPathLoadNode) {
            LevelMotionControllerNodeBlueprint *aPathNode = new LevelMotionControllerNodeBlueprint();
            aPathNode->Load(aPathLoadNode);
            mNodeList.Add(aPathNode);
        }
    }
    */
    
}
