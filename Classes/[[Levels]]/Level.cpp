//
//  Level.cpp
//  Crazy Darts 2 Mac
//
//  Created by Doombot on 8/6/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "Level.hpp"

Level::Level() {
    ResetAll();
    
}

Level::~Level() {
    FreeList(LevelGroup, mGroupList);
}

void Level::AddSection(const char *pSectionName) {
    
    LevelNode *aNode = new LevelNode(pSectionName);
    
    aNode->mAliveTimer = mAliveTimer;
    aNode->mKillTimer = mKillTimer;
    
    LevelGroup *aCurrentGroup = GetCurrentGroup();
    aCurrentGroup->AddNode(aNode);
}

LevelData *Level::Build() {
    LevelData *aData = new LevelData();
    
    FList aList;
    EnumList(LevelGroup, aGroup, mGroupList) {
        aGroup->Build(&mTempList);
        aList.Add(mTempList);
        mTempList.RemoveAll();
    }
    
    //Now we have a flat list of LevelNode.
    
    EnumList(LevelNode, aNode, aList) {
        Log("Flat Section: %s\n", aNode->mSectionName.c());
    }
    
    EnumList(LevelNode, aNode, aList) {
        
        LevelSection *aSection = new LevelSection();
        aSection->Load(aNode->mSectionName.c());
        aSection->mAliveTimer = aNode->mAliveTimer;
        aSection->mKillTimer = aNode->mKillTimer;
        
        if (aSection->mLoadError) {
            Log("** Failed To Load Section: [%s]\n", aNode->mSectionName.c());
            delete aSection;
            continue;
        } else {
            Log("** Loaded Section: %s\n", aNode->mSectionName.c());
        }
        
        aData->AddSection(aSection);
    }
    
    
    
    return aData;
}

LevelGroup *Level::GetCurrentGroup() {
    LevelGroup *aResult = NULL;
    if (mGroupList.mCount > 0) {
        aResult = ((LevelGroup *)mGroupList.Last());
    } else {
        aResult = new LevelGroup();
        mGroupList.Add(aResult);
    }
    return aResult;
}

void Level::GroupBegin() {
    LevelGroup *aCurrentGroup = GetCurrentGroup();
    if (aCurrentGroup->mNodeList.mCount == 0) {
        return;
    }
    
    LevelGroup *aNewGroup = new LevelGroup();
    mGroupList.Add(aNewGroup);
}

void Level::GroupSetCount(int pCount) {
    LevelGroup *aCurrentGroup = GetCurrentGroup();
    aCurrentGroup->mCount = pCount;
}

void Level::SetAliveTimer(int pTicks) {
    mAliveTimer = pTicks;
    if (mAliveTimer != 0) { mKillTimer = 0; }
}

void Level::SetKillTimer(int pTicks) {
    mKillTimer = pTicks;
    if (mKillTimer != 0) { mAliveTimer = 0; }
}

void Level::ResetAll() {
    SetAliveTimer(0);
    SetKillTimer(0);
}
