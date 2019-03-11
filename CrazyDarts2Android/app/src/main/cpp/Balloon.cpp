//
//  Balloon.cpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/14/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#include "Balloon.hpp"
#include "Game.hpp"

Balloon::Balloon() {
    
    mSpinSpeed = gRand.GetFloat(0.25f, 0.45f);
    if (gRand.GetBool()) mSpinSpeed = -mSpinSpeed;
    
    mDeathTimer = 5000;
    mTimer = 0;
    
    mColor.mAlpha = 0.25f;
    

    mUniform = &(gGame->mRenderer->mUniformPhong);
}

Balloon::~Balloon() {
    //Log("Balloon has died [%LX]\n", this);
}

void Balloon::Update() {
    mSpin += mSpinSpeed;
}

void Balloon::Draw() {
    
    Graphics::PipelineStateSetShape2DNoBlending();
    Graphics::SetColor(1.0f, 0.25f, 0.25f, 0.35f);
    
    FVec2 aConverted = gGame->ConvertSceneCoordsToScreen(mX, mY);
    Graphics::DrawPoint(aConverted.mX, aConverted.mY);
}

void Balloon::Draw3D() {
    GameObject::Draw3D();
}
