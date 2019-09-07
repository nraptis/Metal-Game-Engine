//
//  GameOverlayInterfaceInterface.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 9/3/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "core_includes.h"
#include "GameOverlayInterface.hpp"
#include "FAnimation.hpp"
#include "Game.hpp"

GameOverlayInterface *gInterfaceOverlay = NULL;

GameOverlayInterface::GameOverlayInterface() {
    
    gInterfaceOverlay = this;
    
    mPauseButton = NULL;
    mConsumesTouches = false;
    mName = "[Game Overlay Interface]";
    
    mLifeIndicatorCount = 0;
    for (int i=0;i<MAX_LIFE_INDICATOR_COUNT;i++) {
        mLifeIndicator[i] = NULL;
    }
    RefreshLifeIndicators();
    
    
    mPauseButton = new FButton();
    AddChild(mPauseButton);
    mPauseButton->SetUp(&gWadGameInterface.mPauseButtonUp, &gWadGameInterface.mPauseButtonUp, &gWadGameInterface.mPauseButtonDown);
    mPauseButton->mRecievesConsumedTouches = true;
    mPauseButton->mDrawManual = true;
    mPauseButton->mDrawSetsSpriteAlphaPipelineState = false;
    gNotify.Register(this, mPauseButton, "button_click");
    
}

GameOverlayInterface::~GameOverlayInterface() {
    if (gInterfaceOverlay == this) { gInterfaceOverlay = NULL; }
    for (int i=0;i<mLifeIndicatorCount;i++) {
        if (mLifeIndicator[i] != NULL) {
            mLifeIndicator[i]->Kill();
            mLifeIndicator[i] = NULL;
        }
    }
}

void GameOverlayInterface::Layout() {
    if (mPauseButton != NULL) {
        float aWidth = gWadGameInterface.mPauseButtonUp.mWidth + 6.0f * gSpriteDrawScale;
        float aHeight = gWadGameInterface.mPauseButtonUp.mHeight + 6.0f * gSpriteDrawScale;
        float aPaddingLeft = 2.0f * gSpriteDrawScale;
        float aPaddingTop = 2.0f * gSpriteDrawScale;
        
        float aY = (mHeight - aHeight) - aPaddingTop;
        
        mPauseButton->SetFrame(aPaddingLeft, aY, aWidth, aHeight);
    }
    
    RefreshLifeIndicatorFrames();
}

void GameOverlayInterface::Update() {
    
    if (gGame->mLivesMax != mLifeIndicatorCount) {
        RefreshLifeIndicators();
    }
    
}

void GameOverlayInterface::Draw() {
    
    Graphics::PipelineStateSetSpritePremultipliedBlending();
    
    /*
     gWadGameInterface.mFontScoreLarge.Draw("Xa aX0123456789yYzZZzzYaY", 20.0f, 100.0f);
     gWadGameInterface.mFontScoreLarge.Draw("aa 2345BB", 20.0f, 150.0f);
     gWadGameInterface.mFontScoreLarge.Draw("987 65bacaBCACAeE", 20.0f, 200.0f);
     
     gWadGameInterface.mFontScoreSmall.Draw("Xaa X0123456789yYzZZzzYaY", 20.0f, 250.0f);
     gWadGameInterface.mFontScoreSmall.Draw("aa 2345BB", 20.0f, 300.0f);
     gWadGameInterface.mFontScoreSmall.Draw("987 65bacaBCACAeE", 20.0f, 400.0f);
     */
    
    gWadGameInterface.mFontScoreLarge.Draw(FString("Score:") + FString(gGame->mScore), 2.0f * gSpriteDrawScale, -2.0 * gSpriteDrawScale);
    gWadGameInterface.mFontScoreLarge.Draw(FString("Streak:") + FString(gGame->mScore), 2.0f * gSpriteDrawScale, 20.0 * gSpriteDrawScale);
    
    
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    
    float aWindBarCenter = mWidth2;
    float aWindBarLength = mWidth * 0.9f;
    
    Graphics::SetColor(0.35f, 0.35f, 0.35f, 0.75f);
    Graphics::DrawRect(aWindBarCenter - aWindBarLength / 2.0f, mHeight - 100.0f, aWindBarLength, 50.0f);
    
    float aWindPower = gGame->mWind.mPower;
    float aWindBarWidth = aWindBarLength * aWindPower * 0.5f;
    
    if (aWindPower >= 0.0f) {
        Graphics::SetColor(1.0f, 0.125f, 0.125f, 0.75f);
        Graphics::DrawRect(aWindBarCenter, mHeight - 100.0f, aWindBarWidth, 50.0f);
    } else {
        Graphics::SetColor(1.0f, 0.125f, 0.125f, 0.9f);
        Graphics::DrawRect(aWindBarCenter + aWindBarWidth, mHeight - 100.0f, -aWindBarWidth, 50.0f);
    }
    
    Graphics::PipelineStateSetSpriteAlphaBlending();
    Graphics::SetColor();
    
    //gWadGameInterface.mGameMenuBack.Center(mWidth2, mHeight2);
    
    /*
     
     gWadGameInterface.mPauseButtonUp.Draw(20.0f, 20.0f);
     
     float aPauseWidth = gWadGameInterface.mPauseButtonUp.mWidth;
     float aPauseHeight = gWadGameInterface.mPauseButtonUp.mHeight;
     
     
     gWadGameInterface.mPauseButtonDown.Draw(20.0f + aPauseWidth * 0.75f, 20.0f);
     
     
     
     float aLIWidth = gWadGameInterface.mLivesIndicatorShadow.mWidth;
     gWadGameInterface.mLivesIndicatorShadow.Draw(20.0f + aPauseWidth, 120.0f);
     
     gWadGameInterface.mLivesIndicatorFull.Draw(20.0f + aLIWidth * 0.7f, 20.0f + aPauseHeight);
     gWadGameInterface.mLivesIndicatorFull.Draw(20.0f + aLIWidth * 0.7f * 2, 20.0f + aPauseHeight);
     gWadGameInterface.mLivesIndicatorEmpty.Draw(20.0f + aLIWidth * 0.7f * 3, 20.0f + aPauseHeight);
     gWadGameInterface.mLivesIndicatorEmpty.Draw(20.0f + aLIWidth * 0.7f * 4, 20.0f + aPauseHeight);
     
     */
    
    
    if (mPauseButton != NULL) {
        Graphics::SetColor();
        Graphics::PipelineStateSetSpriteAlphaBlending();
        mPauseButton->DrawManual();
        Graphics::SetColor();
    }
    
}

void GameOverlayInterface::TouchDown(float pX, float pY, void *pData) {
    
}

void GameOverlayInterface::TouchMove(float pX, float pY, void *pData) {
    
}

void GameOverlayInterface::TouchUp(float pX, float pY, void *pData) {
    
}

void GameOverlayInterface::TouchFlush() {
    
}

void GameOverlayInterface::Notify(void *pSender, const char *pNotification) {
    if (pSender == mPauseButton && mPauseButton != NULL) {
        printf("WE CLICKED PAUSE... LOL!!!\n");
    }
}

void GameOverlayInterface::NotifyLivesChanged() {
    
    printf("Lives: %d\n", gGame->mLives);
    
    for (int i=0;i<mLifeIndicatorCount;i++) {
        if (mLifeIndicator[i] != NULL) {
            if (i >= (mLifeIndicatorCount - gGame->mLives)) {
                if (mLifeIndicator[i]->mFull == false) {
                    mLifeIndicator[i]->BecomeFull();
                }
            } else {
                if (mLifeIndicator[i]->mFull == true) {
                    mLifeIndicator[i]->BecomeEmpty();
                }
            }
        }
    }
}

void GameOverlayInterface::RefreshLifeIndicators() {
    mLifeIndicatorCount = gGame->mLivesMax;
    if (mLifeIndicatorCount < 0) { mLifeIndicatorCount = 0; }
    if (mLifeIndicatorCount > MAX_LIFE_INDICATOR_COUNT) { mLifeIndicatorCount = MAX_LIFE_INDICATOR_COUNT; }
    
    for (int i=0;i<mLifeIndicatorCount;i++) {
        if (mLifeIndicator[i] == NULL) {
            mLifeIndicator[i] = new LifeIndicator();
            AddChild(mLifeIndicator[i]);
        }
        mLifeIndicator[i]->mFull = (i >= (mLifeIndicatorCount - gGame->mLives));
        mLifeIndicator[i]->mHidden = false;
    }
    
    for (int i=mLifeIndicatorCount;i<MAX_LIFE_INDICATOR_COUNT;i++) {
        if (mLifeIndicator[i] != NULL) {
            mLifeIndicator[i]->mHidden = true;
        }
    }
    
    RefreshLifeIndicatorFrames();
    
}

void GameOverlayInterface::RefreshLifeIndicatorFrames() {
    
    float aWidth = gWadGameInterface.mLivesIndicatorFull.mWidth;
    float aHeight = gWadGameInterface.mLivesIndicatorFull.mHeight;
    
    float aStride = (float)((int)((aWidth * 0.78f)));
    
    float aX = mWidth - 6.0f * gSpriteDrawScale;
    float aY = 0.0f * gSpriteDrawScale;
    
    for (int i=0;i<MAX_LIFE_INDICATOR_COUNT;i++) {
        if (mLifeIndicator[i] != NULL) {
            aX -= aStride;
            mLifeIndicator[i]->SetFrame(aX, aY, aWidth, aHeight);
        }
    }
}
