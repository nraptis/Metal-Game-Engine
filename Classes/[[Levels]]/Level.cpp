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
    
    aNode->mKeepAliveTimer = mKeepAliveTimer;
    aNode->mForceKillTimer = mForceKillTimer;
    
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
        
        if (aNode->mKeepAliveTimer != 0) {
            aSection->mKeepAliveTimer = aNode->mKeepAliveTimer;
        }
        
        if (aNode->mForceKillTimer != 0) {
            aSection->mForceKillTimer = aNode->mForceKillTimer;
        }
        
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
    mKeepAliveTimer = pTicks;
}

void Level::SetKillTimer(int pTicks) {
    mForceKillTimer = pTicks;
}

void Level::ResetAll() {
    SetAliveTimer(0);
    SetKillTimer(0);
}
