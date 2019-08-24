//
//  GameInfoTextBubble.cpp
//  Crazy Darts 2 iOS
//
//  Created by Doombot on 8/7/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "GameInfoTextBubble.hpp"
#include "core_includes.h"
#include "FApp.hpp"

GameInfoTextBubble::GameInfoTextBubble(const char *pText) {
    mText = pText;
    mFadeOut = false;
    mX = 0.0f;
    mY = 0.0f;
    
    mAllComplete = false;
    mPermsComplete = false;
    mWavesComplete = false;
    mHasAnyObjects = false;
    
    mKill = false;
    mKillTimer = 300;
}

GameInfoTextBubble::~GameInfoTextBubble() {
    printf("Delete GameInfoTextBubble(%s)\n", mText.c());
}

void GameInfoTextBubble::Update() {
    
}

void GameInfoTextBubble::Draw() {
    FFont *aFont = &(gAppBase->mSysFont);
    Graphics::PipelineStateSetSpritePremultipliedBlending();
    Graphics::SetColor();
    
    FString aText = mText;
    
    aText += " WC: ";
    if (mWavesComplete) {
        aText += "true";
    } else {
        aText += "false";
    }
    
    aText += " PC: ";
    if (mPermsComplete) {
        aText += "true";
    } else {
        aText += "false";
    }
    
    aText += " AC: ";
    if (mAllComplete) {
        aText += "true";
    } else {
        aText += "false";
    }
    
    aText += " OB: ";
    if (mHasAnyObjects) {
        aText += "true";
    } else {
        aText += "false";
    }
    
    aFont->Draw(aText.c(), mX, mY, 1.0f);
}

