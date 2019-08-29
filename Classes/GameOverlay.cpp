//
//  GameOverlay.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 8/27/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "core_includes.h"
#include "GameOverlay.hpp"
#include "FAnimation.hpp"
#include "Game.hpp"

GameOverlay *gGameOverlay = NULL;

GameOverlay::GameOverlay() {
    gGameOverlay = this;
    mName = "[Game Overlay]";
    
    mConsumesTouches = false;
}

GameOverlay::~GameOverlay() {
    
}

void GameOverlay::Layout() {
    
}

void GameOverlay::Update() {
    
    mEffectListBalloonBursts.Update();
    mEffectListDartFadeStar.Update();
    
}

void GameOverlay::Draw() {
    
    //DrawTransform();
    //Graphics::MatrixModelViewReset();
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    
    Graphics::SetColor(1.0f, 0.0f, 0.0f, 0.50f);
    Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
    
    Graphics::SetColor();
    
    //Graphics::PipelineStateSetSpritePremultipliedBlending();
    Graphics::PipelineStateSetSpriteAdditiveBlending();
    mEffectListBalloonBursts.Draw();
    
    Graphics::PipelineStateSetSpriteAdditiveBlending();
    mEffectListDartFadeStar.Draw();
    
    
    
    Graphics::PipelineStateSetSpritePremultipliedBlending();
    
    gWadGameInterface.mFontLarge.Draw("Xa aX0123456789yYzZZzzYaY", 20.0f, 100.0f);
    gWadGameInterface.mFontLarge.Draw("aa 2345BB", 20.0f, 150.0f);
    gWadGameInterface.mFontLarge.Draw("987 65bacaBCACAeE", 20.0f, 200.0f);
    
    
    gWadGameInterface.mFontSmall.Draw("Xaa X0123456789yYzZZzzYaY", 20.0f, 250.0f);
    gWadGameInterface.mFontSmall.Draw("aa 2345BB", 20.0f, 300.0f);
    gWadGameInterface.mFontSmall.Draw("987 65bacaBCACAeE", 20.0f, 400.0f);
    
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
    
    gWadGameInterface.mFontLarge.Right(FString(gGame->mScore), mWidth - 40.0f, 40.0f);
    
    
}

void GameOverlay::TouchDown(float pX, float pY, void *pData) {
    
}

void GameOverlay::TouchMove(float pX, float pY, void *pData) {
    
}

void GameOverlay::TouchUp(float pX, float pY, void *pData) {
    
}

void GameOverlay::TouchFlush() {
    
}

void GameOverlay::Notify(void *pSender, const char *pNotification) {
    
}
