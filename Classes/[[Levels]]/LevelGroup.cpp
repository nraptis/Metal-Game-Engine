//
//  LevelGroup.cpp
//  Crazy Darts 2 Mac
//
//  Created by Doombot on 8/6/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelGroup.hpp"
#include "core_includes.h"

LevelGroup::LevelGroup() {
    mCount = 0;
    mShuffle = false;
}

LevelGroup::~LevelGroup() {
    FreeList(LevelNode, mNodeList);
}

void LevelGroup::AddNode(LevelNode *pNode) {
    mNodeList.Add(pNode);
}

void LevelGroup::Build(FList *pList) {
    if (mNodeList.mCount == 0) { Log("Missing nodes...\n"); return; }
    
    FList aList;
    aList.Add(mNodeList);
    
    if (mCount == 0) {
        if (mShuffle) { aList.Shuffle(); }
        pList->Add(aList);
        return;
    }
    
    int aDupeIndex = 0;
    while (mCount > aList.mCount) {
        aList.Add(mNodeList.Fetch(aDupeIndex));
        aDupeIndex++;
        if (aDupeIndex == mNodeList.mCount) { aDupeIndex = 0; }
    }
    
    //If we shuffle the list, just take the first "count" items...
    if (mShuffle) {
        aList.Shuffle();
        for (int i=0;i<mCount;i++) {
            pList->Add(aList.Fetch(i));
        }
        return;
    }
    
    if (mCount <= 0 || mCount == aList.mCount) {
        pList->Add(aList);
        return;
    }
    
    Log("*** NOT IMPLEMENTED **\n\n");
    Log("*** We want evenly-picked subset...? ***\n");
    
    
}
