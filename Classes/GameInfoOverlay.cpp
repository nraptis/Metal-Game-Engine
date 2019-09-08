//
//  GameInfoOverlay.cpp
//  Crazy Darts 2 iOS
//
//  Created by Doombot on 8/7/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "GameContainer.hpp"
#include "GameInfoOverlay.hpp"
#include "core_includes.h"
#include "GFXApp.hpp"

GameInfoOverlay::GameInfoOverlay() {
    mConsumesTouches = false;
}

GameInfoOverlay::~GameInfoOverlay() {
    
    
}

void GameInfoOverlay::Layout()  {
    
    Log("GameInfoOverlay::Layout()\n");
    
}

void GameInfoOverlay::Update() {
    
    if ((gGameContainer != NULL) && (gGameContainer->mPaused == true)) {
        return;
    }
    
    
    FList aKillList;
    
    EnumList(GameInfoTextBubble, aBubble, mBubbleList) {
        if (aBubble->mKill) {
            aBubble->mKillTimer--;
            if (aBubble->mKillTimer <= 0) {
                aKillList.Add(aBubble);
            }
        }
    }
    
    EnumList(GameInfoTextBubble, aBubble, aKillList) {
        mBubbleList.Remove(aBubble);
        mBubbleKillList.Add(aBubble);
    }
    
    
    EnumList(GameInfoTextBubble, aBubble, mBubbleList) {
        aBubble->Update();
    }
    
    
    
    
    EnumList(GameInfoTextBubble, aBubble, mBubbleKillList) {
        aBubble->mKillTimer--;
        if (aBubble->mKillTimer <= 0) { mBubbleDeleteList.Add(aBubble); }
    }
    EnumList(GameInfoTextBubble, aBubble, mBubbleDeleteList) {
        mBubbleKillList.Remove(aBubble);
        delete aBubble;
    }
    mBubbleDeleteList.RemoveAll();
    
    
    
    
    
}

void GameInfoOverlay::Draw() {
    
    
    //GameInfoTextBubble
    //mBubbleList;
    
    float aX = 20.0f;
    float aY = 20.0f;
    
    EnumList(GameInfoTextBubble, aBubble, mBubbleList) {
        
        aBubble->mX = aX;
        aBubble->mY = aY;
        
        aBubble->Draw();
        
        aY += 48.0f;
    }
    
    //Graphics::PipelineStateSetShape2DAlphaBlending();
    //Graphics::SetColor(0.6f, gRand.GetFloat() * 0.25f + 0.5f, 0.125f, 0.45f);
    
    //Graphics::DrawRect(0.0f, 0.0f, 300.0f, 300.0f);
    //Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
    
    //Graphics::PipelineStateSetShape2DAlphaBlending();
    //
    //
    //Graphics::SetColor();
    
}


void GameInfoOverlay::TouchDown(float pX, float pY, void *pData) {
    
}

void GameInfoOverlay::TouchMove(float pX, float pY, void *pData) {
    
}

void GameInfoOverlay::TouchUp(float pX, float pY, void *pData) {
    
}

void GameInfoOverlay::TouchFlush() {
    
}

void GameInfoOverlay::KeyDown(int pKey) {
    
}

void GameInfoOverlay::KeyUp(int pKey) {
    
}

void GameInfoOverlay::Notify(void *pSender, const char *pNotification)  {
    
}

void GameInfoOverlay::AddBubble(const char *pText) {
    
    GameInfoTextBubble *aBubble = new GameInfoTextBubble(pText);
    mBubbleList.Add(aBubble);
    
}

void GameInfoOverlay::RemoveBubble(const char *pText) {
    

    EnumList(GameInfoTextBubble, aBubble, mBubbleList) {
        if (aBubble->mText == pText) {
            aBubble->mKill = true;
        }
    }
}

void GameInfoOverlay::SetBubbleStatusAllComplete(const char *pName, bool pStatus) {
    EnumList(GameInfoTextBubble, aBubble, mBubbleList) {
        if (aBubble->mText == pName) {
            aBubble->mAllComplete = pStatus;
        }
    }
}

void GameInfoOverlay::SetBubbleStatusPermsComplete(const char *pName, bool pStatus) {
    EnumList(GameInfoTextBubble, aBubble, mBubbleList) {
        if (aBubble->mText == pName) {
            aBubble->mPermsComplete = pStatus;
        }
    }
}

void GameInfoOverlay::SetBubbleStatusWavesComplete(const char *pName, bool pStatus) {
    EnumList(GameInfoTextBubble, aBubble, mBubbleList) {
        if (aBubble->mText == pName) {
            aBubble->mWavesComplete = pStatus;
        }
    }
}

void GameInfoOverlay::SetBubbleStatusHasObjects(const char *pName, bool pStatus) {
    EnumList(GameInfoTextBubble, aBubble, mBubbleList) {
        if (aBubble->mText == pName) {
            aBubble->mHasAnyObjects = pStatus;
        }
    }
}


