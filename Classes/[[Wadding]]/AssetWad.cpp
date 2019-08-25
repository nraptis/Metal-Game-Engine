//
//  AssetWad.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 8/24/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "AssetWad.hpp"
#include "core_includes.h"

AssetWad::AssetWad() {
    
}

AssetWad::~AssetWad() {
    
}

void AssetWad::Print() {
    Log("*** BEGIN AssetWad ***\n");
    
    Log("*** END AssetWad ***\n");
}

void AssetWad::Load() {
    
}

void AssetWad::Unload() {
    
}

void AssetWad::QuickLoad(const char *pKey, FSprite *pSprite) {
    
    if (pSprite == NULL) {
        return;
    }
    
    FSprite *aSprite = (FSprite *)mSpriteMap.Get(pKey);
    if (aSprite == NULL) {
        mSpriteMap.Add(pKey, pSprite);
        mSpriteList.Add(pSprite);
        aSprite = pSprite;
    }
    
    aSprite->Kill();
    aSprite->Load(pKey);
}


//FList                                           mSpriteList;
//FStringMap                                      mSpriteMap;
