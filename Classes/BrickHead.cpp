//
//  BrickHead.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/4/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "BrickHead.hpp"
#include "Game.hpp"

BrickHead::BrickHead() {
    
    
    mGameObjectType = GAME_OBJECT_TYPE_BRICKHEAD;
    
    mSpinSpeed = gRand.GetFloat(0.25f, 0.45f);
    if (gRand.GetBool()) mSpinSpeed = -mSpinSpeed;
    
    mModel = &gApp->mMonolith;
    mSprite = &gApp->mMonolithMap;
    
    mTransform.mScaleZ = 0.5f;
    mTransform.mOffsetY = 33.0f;
    
    mUniform = &(gGame->mRenderer->mUniformPhong);
    
    mVelX = 0.0f;
    mVelY = 0.0f;
}

BrickHead::~BrickHead() {
    //Log("BrickHead has died [%LX]\n", this);
}

void BrickHead::Update() {
    mTransform3D.mSpin += mSpinSpeed;
    
    mTransform.mX += mVelX;
    mTransform.mY += mVelY;
    
}

void BrickHead::Draw() {
    
    GameObject::Draw();
    
    //Graphics::PipelineStateSetShape2DNoBlending();
    //Graphics::SetColor(1.0f, 0.25f, 0.25f, 0.35f);
    //Graphics::DrawPoint(mTransform.mX, mTransform.mY);
}

void BrickHead::Draw3D() {
    
    
    //aNormal.SetNormalMatrix(aModelView);
    //((FUniformsLightPhong *)mUniform)->mLight.mShininess = 58.0f;
    //((FUniformsLightPhong *)mUniform)->mLight.mSpecularIntensity = 1.0f;
    
    GameObject::Draw3D();
}


