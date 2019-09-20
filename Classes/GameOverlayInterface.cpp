//
//  GameOverlayInterfaceInterface.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 9/3/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "core_includes.h"
#include "GameContainer.hpp"
#include "GameOverlayInterface.hpp"
#include "FAnimation.hpp"
#include "Game.hpp"

GameOverlayInterface *gInterfaceOverlay = NULL;

GameOverlayInterface::GameOverlayInterface() {
    
    gInterfaceOverlay = this;
    
    mPauseButton = NULL;
    mConsumesTouches = false;
    mName = "GameOverlayInterface";
    
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
    
    mCoinFrame[0] = 0.0f;
    mCoinFrame[1] = 0.0f;
    mCoinFrame[2] = 0.0f;
    mCoinFrame[3] = 0.0f;
    mCoinFrame[4] = 0.0f;
    
    BuildTextBubbleExploreGrid();
}

GameOverlayInterface::~GameOverlayInterface() {
    if (gInterfaceOverlay == this) { gInterfaceOverlay = NULL; }
    
    
    mPauseButton = NULL;
    //if (mPauseButton != NULL) {
    //    mPauseButton->Kill();
    //    mPauseButton = NULL;
    //}
    
    for (int i=0;i<mLifeIndicatorCount;i++) {
        mLifeIndicator[i] = NULL;
        
        
        //if (mLifeIndicator[i] != NULL) {
        //    mLifeIndicator[i]->Kill();
        //    mLifeIndicator[i] = NULL;
        //}
    }
}

void GameOverlayInterface::Layout() {
    if (mPauseButton != NULL) {
        float aWidth = gWadGameInterface.mPauseButtonUp.mWidth + 6.0f * gSpriteDrawScale;
        float aHeight = gWadGameInterface.mPauseButtonUp.mHeight + 6.0f * gSpriteDrawScale;
        float aPaddingLeft = 2.0f * gSpriteDrawScale + gSafeAreaInsetLeft;
        float aPaddingTop = 2.0f * gSpriteDrawScale + gSafeAreaInsetBottom;
        
        float aY = (mHeight - aHeight) - aPaddingTop;
        
        mPauseButton->SetFrame(aPaddingLeft, aY, aWidth, aHeight);
    }
    
    RefreshLifeIndicatorFrames();
}

void GameOverlayInterface::Update() {
    
    if ((gGameContainer != NULL) && (gGameContainer->mPaused == true)) {
        return;
    }
    
    if (gGame->mLivesMax != mLifeIndicatorCount) {
        RefreshLifeIndicators();
    }
    
    
    
    float aMaxFrame = gWadGameEffects.mSequenceCoin[0].GetMaxFrame();
    
    if (aMaxFrame >= 1.0f) {
        
        mCoinFrame[0] += 0.25f;
        if (mCoinFrame[0] >= aMaxFrame) { mCoinFrame[0] -= aMaxFrame; }
        
        mCoinFrame[1] += 0.28f;
        if (mCoinFrame[1] >= aMaxFrame) { mCoinFrame[1] -= aMaxFrame; }
        
        mCoinFrame[2] += 0.31f;
        if (mCoinFrame[2] >= aMaxFrame) { mCoinFrame[2] -= aMaxFrame; }
        
        mCoinFrame[3] += 0.33f;
        if (mCoinFrame[3] >= aMaxFrame) { mCoinFrame[3] -= aMaxFrame; }
        
        mCoinFrame[4] += 0.35f;
        if (mCoinFrame[4] >= aMaxFrame) { mCoinFrame[4] -= aMaxFrame; }
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
    
    gWadGameInterface.mFontScoreLarge.Draw(FString("Score:") + FString(gGame->mScore), 2.0f * gSpriteDrawScale + gSafeAreaInsetLeft, -2.0 * gSpriteDrawScale + gSafeAreaInsetTop);
    gWadGameInterface.mFontScoreLarge.Draw(FString("Streak:") + FString(gGame->mScore), 2.0f * gSpriteDrawScale + gSafeAreaInsetLeft, 20.0 * gSpriteDrawScale + gSafeAreaInsetTop);
    
    
    gWadGameInterface.mFontScoreLarge.Center(FString("BL:") + FString(gGame->mRecentFloatingAwayTick), mWidth2, 12.0 * gSpriteDrawScale + gSafeAreaInsetTop);
    
    
    
    
    
    
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    
    float aWindBarCenter = mWidth2;
    float aWindBarLength = mWidth * 0.9f;
    if (aWindBarLength > 300.0f) { aWindBarLength = 300.0f; }
    
    Graphics::SetColor(0.35f, 0.35f, 0.35f, 0.75f);
    Graphics::DrawRect(aWindBarCenter - aWindBarLength / 2.0f, mHeight - 30.0f, aWindBarLength, 25.0f);
    
    float aWindPower = gGame->mWind.mPower;
    float aWindBarWidth = aWindBarLength * aWindPower * 0.5f;
    
    if (aWindPower >= 0.0f) {
        Graphics::SetColor(1.0f, 0.125f, 0.125f, 0.75f);
        Graphics::DrawRect(aWindBarCenter, mHeight - 30.0f, aWindBarWidth, 25.0f);
    } else {
        Graphics::SetColor(1.0f, 0.125f, 0.125f, 0.75f);
        Graphics::DrawRect(aWindBarCenter + aWindBarWidth, mHeight - 30.0f, -aWindBarWidth, 25.0f);
    }
    
    //Graphics::PipelineStateSetSpriteAlphaBlending();
    //Graphics::SetColor(0.25f);
    //gWadGameInterface.mGameMenuBack.Center(mWidth2, mHeight2);
    //Graphics::SetColor();
    
    
    if (mPauseButton != NULL) {
        Graphics::SetColor();
        Graphics::PipelineStateSetSpriteAlphaBlending();
        mPauseButton->DrawManual();
        Graphics::SetColor();
    }
    
    
    
    DrawTransform();
    Graphics::PipelineStateSetShape2DAlphaBlending();
    
    Graphics::SetColor(0.125f, 0.125f, 0.125f, 1.0f);
    Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
    
    for (int i=0;i<mTextBubbleExploreList.mCount;i++) {
        
        float aPercent = ((float)i) / ((float)mTextBubbleExploreList.mCount);
        
        float aX = mTextBubbleExploreList.mX[i];
        float aY = mTextBubbleExploreList.mY[i];
        
        aX += mWidth2;
        aY += mHeight2;
        
        Graphics::SetColor(aPercent, 0.5f, 0.5f, 0.85f);
        Graphics::DrawPoint(aX, aY, 6.0f);
        
    }
    
    
    /*
    DrawTransform();
    Graphics::PipelineStateSetSpritePremultipliedBlending();
    Graphics::SetColor();
    
    float aY = 40.0f * gSpriteDrawScale + gSafeAreaInsetTop;
    float aX = 4.0f * gSpriteDrawScale;
    for (int i=0;i<5;i++) {
        
        float aX = 4.0f * gSpriteDrawScale;
        for (int k=0;k<5;k++) {
            
            gWadGameEffects.mSequenceCoin[(i + k) % 5].Draw(mCoinFrame[i], aX, aY);
            
            aX += gWadGameEffects.mSequenceCoin[i].mWidth * 0.6f + 2.0f * gSpriteDrawScale;
        }
        
        aY += gWadGameEffects.mSequenceCoin[i].mWidth * 0.6f + 2.0f * gSpriteDrawScale;
    }
     
    */
    
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
        
        if (gGameContainer != NULL) {
            if (gGameContainer->mGameMenu == NULL) {
                gGameContainer->PauseAndShowGameMenu();
            }
        }
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
    
    float aX = (mWidth - 6.0f * gSpriteDrawScale) - gSafeAreaInsetRight;
    float aY = 0.0f * gSpriteDrawScale + gSafeAreaInsetTop;
    
    for (int i=0;i<MAX_LIFE_INDICATOR_COUNT;i++) {
        if (mLifeIndicator[i] != NULL) {
            aX -= aStride;
            mLifeIndicator[i]->SetFrame(aX, aY, aWidth, aHeight);
        }
    }
}

void GameOverlayInterface::BuildTextBubbleExploreGrid() {
    
    //TEXT_BUBBLE_EXPLORE_GRID_RADIUS
    //TEXT_BUBBLE_EXPLORE_GRID_STEP_SIZE
    
    int aGridSize = ((TEXT_BUBBLE_EXPLORE_GRID_RADIUS - 1) + (TEXT_BUBBLE_EXPLORE_GRID_RADIUS - 1) + 1);
    
    float aExploreGridX[aGridSize][aGridSize];
    float aExploreGridY[aGridSize][aGridSize];
    float aExploreEuropeanDistance[aGridSize][aGridSize];
    
    int aGridOffset = (TEXT_BUBBLE_EXPLORE_GRID_RADIUS - 1);
    
    float aX = 0.0f;
    float aY = 0.0f;
    float aDist = 0.0f;
    int aListCount = 0;
    
    float aHopSize = TEXT_BUBBLE_EXPLORE_GRID_STEP_SIZE;
    for (int i=(-(TEXT_BUBBLE_EXPLORE_GRID_RADIUS - 1));i<TEXT_BUBBLE_EXPLORE_GRID_RADIUS;i++) {
        aX = ((float)i) * aHopSize;
        for (int n=(-(TEXT_BUBBLE_EXPLORE_GRID_RADIUS - 1));n<TEXT_BUBBLE_EXPLORE_GRID_RADIUS;n++) {
            aY = ((float)n) * aHopSize;
            aExploreGridX[i + aGridOffset][n + aGridOffset] = aX;
            aExploreGridY[i + aGridOffset][n + aGridOffset] = aY;
            aDist = aX * aX + aY * aY;
            aExploreEuropeanDistance[i + aGridOffset][n + aGridOffset] = aDist;
            
            aListCount += 1;
        }
    }
    
    float aListX[aListCount];
    float aListY[aListCount];
    float aListDist[aListCount];
    int aIndex = 0;
    
    for (int i=0;i<aGridSize;i++) {
        for (int n=0;n<aGridSize;n++) {
            aListX[aIndex] = aExploreGridX[i][n];
            aListY[aIndex] = aExploreGridY[i][n];
            aListDist[aIndex] = aExploreEuropeanDistance[i][n];
            
            aIndex++;
        }
    }
    
    float aHoldX = 0.0f;
    float aHoldY = 0.0f;
    float aHoldDist = 0.0f;
    
    int i = 0;
    int j = 0;
    
    for (i=1;i<aListCount;i++) {
        aHoldDist = aListDist[i];
        aHoldX = aListX[i];
        aHoldY = aListY[i];
        
        j = i;
        while ((j>0) && ((aListDist[j-1]<aHoldDist))) {
            aListDist[j] = aListDist[j - 1];
            aListX[j] = aListX[j - 1];
            aListY[j] = aListY[j - 1];
            
            j--;
        }
        aListDist[j] = aHoldDist;
        aListX[j] = aHoldX;
        aListY[j] = aHoldY;
    }
    
    mTextBubbleExploreList.RemoveAll();
    for (int i=0;i<aListCount;i++) {
        mTextBubbleExploreList.Add(aListX[i], aListY[i]);
    }
    
    printf("Explore Point Count: %d\n", mTextBubbleExploreList.mCount);
    
}


