//
//  GameTestRunningOverlay.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 8/12/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "GameTestRunningOverlay.hpp"

//
//  GameTestRunningOverlay.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 5/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "core_includes.h"
#include "GameTestRunningOverlay.hpp"
#include "FAnimation.hpp"
#include "Game.hpp"

GameTestRunningOverlay *gGameTestRunningOverlay = NULL;

GameTestRunningOverlay::GameTestRunningOverlay() {
    
    gGameTestRunningOverlay = this;
    mConsumesTouches = false;
    
    mTestRunningMenu = NULL;
    mCameraMenu = NULL;
    mHangingThreadMenu = NULL;
    
    mName = "{{Game Running Test Overlay}}";
    
    
    //mTestRunningMenu = new GameTestRunningMainMenu(gGame);
    //mTestRunningMenu->SetFrame(14.0f, 80.0f, 220.0f, 130.0f);
    //gApp->mWindowTools.AddChild(mTestRunningMenu);
    
    
    /*
    mCameraMenu = new CameraMenu(gGame->mRenderer->mCamera);
    
    if (gDeviceWidth > 800.0f) {
        mCameraMenu->SetFrame(1090.0f, 150.0f, 340.0f, 360.0f);
    } else {
        mCameraMenu->SetFrame(60.0f, 150.0f, 340.0f, 360.0f);
    }
    
    gApp->mWindowTools.AddChild(mCameraMenu);
    
    
    mHangingThreadMenu = new HangingThreadTestMenu(gGame);
    mHangingThreadMenu->SetFrame(60.0f, 150.0f, 340.0f, 360.0f);
    gApp->mWindowTools.AddChild(mHangingThreadMenu);
    
    */
    
}

GameTestRunningOverlay::~GameTestRunningOverlay() {
    if (mTestRunningMenu != NULL) {
        mTestRunningMenu->Kill();
        mTestRunningMenu = NULL;
    }
    
    if (mCameraMenu != NULL) {
        mCameraMenu->Kill();
        mCameraMenu = NULL;
    }
}

void GameTestRunningOverlay::Layout() {
    
    
    if (mParent != NULL) {
        SetFrame(0.0f, 0.0f, mParent->mWidth, mParent->mHeight);
    }
    
    
    /*
     if (mGame != NULL && mContainer != NULL) {
     
     float aScale = 1.0f;
     float aGameAreaWidth = mWidth - (mInterfaceLeftWidth + mInterfaceRightWidth);
     float aGameAreaHeight = mHeight - (mInterfaceTopHeight + mInterfaceBottomHeight);
     
     FRect aFrame = FRect(0.0f, 0.0f, aGameAreaWidth, aGameAreaHeight);
     FRect aFit = FRect::FitAspectFit(aFrame, mGame->mWidth, mGame->mHeight, 0.0f, aScale);
     float aContainerWidth = round(aGameAreaWidth / aScale);
     float aContainerHeight = round(aGameAreaHeight / aScale);
     mContainer->SetTransformScale(aScale);
     mContainer->SetFrame(round(-(aContainerWidth / (2.0f))), - round((aContainerHeight / (2.0f))), aContainerWidth, aContainerHeight);
     //mContainer->SetTransformTranslate(mWidth2 + mInterfaceLeftWidth * aScale, mHeight2 + mInterfaceTopHeight * aScale);
     
     //mContainer->SetTransformTranslate(mWidth2, mHeight2);
     
     mContainer->SetTransformTranslate(mWidth2 - (mInterfaceRightWidth - mInterfaceLeftWidth) / 2.0f, mHeight2 - (mInterfaceBottomHeight - mInterfaceTopHeight) / 2.0f);
     
     mGame->mRenderShiftX = -((mInterfaceRightWidth - mInterfaceLeftWidth) / 2.0f) / aScale;
     mGame->mRenderShiftY = -((mInterfaceBottomHeight - mInterfaceTopHeight) / 2.0f) / aScale;
     
     
     float aGameX = round(mContainer->mWidth2 - mGame->mWidth2);
     float aGameY = round(mContainer->mHeight2 - mGame->mHeight2);
     mGame->SetX(aGameX);
     mGame->SetY(aGameY);
     }
     */
    
}

void GameTestRunningOverlay::Update() {
    
}

void GameTestRunningOverlay::Draw() {
    
    //Graphics::PipelineStateSetShape2DNoBlending();
    //Graphics::SetColor(0.6f, 0.25f, 0.125f, 0.35f);
    //Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
    
    //Graphics::PipelineStateSetShape2DAlphaBlending();
    
    //Graphics::SetColor(1.0f, 1.0f, 0.25f, 0.25f);
    //Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
    
    
    /*
     Graphics::SetColor(1.0f, 0.0f, 0.25f, 0.25f);
     Graphics::DrawRect(0.0f, 0.0f, mInterfaceLeftWidth, mHeight);
     
     Graphics::SetColor(0.0f, 0.125f, 1.0f, 0.25f);
     Graphics::DrawRect(mWidth - mInterfaceRightWidth, 0.0f, mInterfaceRightWidth, mHeight);
     
     
     
     Graphics::SetColor(0.5f, 0.75f, 0.5f, 0.25f);
     Graphics::DrawRect(0.0f, 0.0f, mWidth, mInterfaceTopHeight);
     
     Graphics::SetColor(1.0f, 0.5f, 0.0f, 0.25f);
     Graphics::DrawRect(0.0f, mHeight - mInterfaceBottomHeight, mWidth, mInterfaceBottomHeight);
     */
    
    
    
    
    /*
    FFont *aFont = &(gAppBase->mSysFont);
    
    Graphics::PipelineStateSetSpritePremultipliedBlending();
    Graphics::SetColor();
    
    float aX = mWidth - 20;
    float aY = mHeight - 60;
    
    FString aString1 = FString("Lives: ") + FString(gGame->mLives) + FString(" / ") + FString(gGame->mLivesMax);
    aFont->Right(aString1.c(), aX, aY);
    aY -= 40.0f;
    
    FString aString2 = FString("Popped: ") + FString(gGame->mPoppedCount);
    aFont->Right(aString2.c(), aX, aY);
    aY -= 40.0f;
    
    FString aString3 = FString("Thrown: ") + FString(gGame->mThrownCount);
    aFont->Right(aString3.c(), aX, aY);
    aY -= 40.0f;
    
    FString aString4 = FString("Missed: ") + FString(gGame->mThrownMissedCount);
    aFont->Right(aString4.c(), aX, aY);
    aY -= 40.0f;
    
    FString aString5 = FString("Hit: ") + FString(gGame->mThrownHitCount);
    aFont->Right(aString5.c(), aX, aY);
    aY -= 40.0f;
    
    Graphics::PipelineStateSetShape2DNoBlending();
    */
     
}

void GameTestRunningOverlay::TouchDown(float pX, float pY, void *pData) {
    
}

void GameTestRunningOverlay::TouchMove(float pX, float pY, void *pData) {
    
}

void GameTestRunningOverlay::TouchUp(float pX, float pY, void *pData) {
    
}

void GameTestRunningOverlay::TouchFlush() {
    
}

void GameTestRunningOverlay::KeyDown(int pKey) {
    
    bool aShift = gKeyDownShift;
    bool aCtrl = gKeyDownCtrl;
    bool aAlt = gKeyDownAlt;
    
    if (pKey == __KEY__E) {
        if (aShift == false && aCtrl == true && aAlt == false) {
            
        }
    }
    
}

void GameTestRunningOverlay::KeyUp(int pKey) {
    
}

void GameTestRunningOverlay::Notify(void *pSender, const char *pNotification) {
    
}

