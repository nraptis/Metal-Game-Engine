//
//  GameOverlayEffectsEffects.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 9/3/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "core_includes.h"
#include "GameContainer.hpp"
#include "GameOverlayEffects.hpp"
#include "FAnimation.hpp"
#include "Game.hpp"

GameOverlayEffects *gEffectsOverlay = NULL;

GameOverlayEffects::GameOverlayEffects() {
    gEffectsOverlay = this;
    mConsumesTouches = false;
    mName = "[~Game Overlay Effects~]";
    
    
    mSeqFrame01 = 0.0f;
    mSeqFrame02 = 0.0f;
    mSeqFrame03 = 0.0f;
    
    
}

GameOverlayEffects::~GameOverlayEffects() {
    if (gEffectsOverlay == this) { gEffectsOverlay = NULL; }
    
}

void GameOverlayEffects::Layout() {
    
}

void GameOverlayEffects::Update() {
    
    if ((gGameContainer != NULL) && (gGameContainer->mPaused == true)) {
        return;
    }
    
    mEffectListBalloonBursts.Update();
    mEffectListDartFadeStar.Update();
    
    
    
    mSeqFrame01 += 2.25f;
    if (mSeqFrame01 > gWadGameEffects.mSequenceBlast1.GetMaxFrame() * 3.0f) {
        //mSeqFrame01 -= gWadGameEffects.mSequenceBlast1.GetMaxFrame();
        mSeqFrame01 = 0.0f;
    }
    
    
    mSeqFrame02 += 2.25f;
    if (mSeqFrame02 > gWadGameEffects.mSequenceBlast2.GetMaxFrame() * 3.0f) {
        //mSeqFrame02 -= gWadGameEffects.mSequenceBlast2.GetMaxFrame();
        mSeqFrame02 = 0.0f;
        
    }
    
    mSeqFrame03 += 2.25f;
    if (mSeqFrame03 > gWadGameEffects.mSequenceBlast3.GetMaxFrame() * 3.0f) {
        //mSeqFrame03 -= gWadGameEffects.mSequenceBlast3.GetMaxFrame();
        mSeqFrame03 = 0.0f;
    }
    
}

void GameOverlayEffects::Draw() {
    
    Graphics::SetColor();
    
    //Graphics::PipelineStateSetSpritePremultipliedBlending();
    Graphics::PipelineStateSetSpriteAdditiveBlending();
    mEffectListBalloonBursts.Draw();
    
    Graphics::PipelineStateSetSpriteAdditiveBlending();
    mEffectListDartFadeStar.Draw();
    
    
    
    Graphics::PipelineStateSetSpriteAdditiveBlending();
    
    Graphics::SetColor();
    
    gWadGameEffects.mSequenceBlast1.Center(mSeqFrame01, 100.0f, 150.0f);
    gWadGameEffects.mSequenceBlast2.Center(mSeqFrame02, 180.0f, 250.0f);
    gWadGameEffects.mSequenceBlast3.Center(mSeqFrame03, 260.0f, 350.0f);
    
}
