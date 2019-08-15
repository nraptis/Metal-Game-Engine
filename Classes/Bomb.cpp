//
//  Bomb.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 8/13/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "Bomb.hpp"
#include "Game.hpp"

Bomb::Bomb() {
    
    
    mGameObjectType = GAME_OBJECT_TYPE_BOMB;
    
    mSpinSpeed = gRand.GetFloat(0.25f, 0.45f);
    if (gRand.GetBool()) mSpinSpeed = -mSpinSpeed;
    
    //mModel = &gApp->mBomb;
    //mSprite = &gApp->mBombMap;
    
    //mAccessoryModel = &gApp->mBombCage;
    //mAccessorySprite = &gApp->mBombMap;
    
    mUniform = &(gGame->mRenderer->mUniformPhongBalloon);
    
    mVelX = 0.0f;
    mVelY = 0.0f;
}

Bomb::~Bomb() {
    
}

void Bomb::Update() {
    mTransform3D.mSpin += mSpinSpeed;
    
    mTransform.mX += mVelX;
    mTransform.mY += mVelY;
    
}

void Bomb::Draw() {
    
    GameObject::Draw();
    
}

void Bomb::Draw3D() {
    
    GameObject::Draw3D();
    
    if (mAccessoryModel != NULL && mAccessorySprite != NULL) {
        
        if (mUniform != NULL) {
            
            //Assign the model view to the uniform...
            mUniform->mModelView.Set(mModelView);
            
            if (mUniform->GetType() == UNIFORM_TYPE_LIGHT_DIFFUSE) {
                FUniformsLightDiffuse *aUniform = (FUniformsLightDiffuse *)(mUniform);
                aUniform->mNormal.Set(mNormal);
            }
            
            if (mUniform->GetType() == UNIFORM_TYPE_LIGHT_PHONG) {
                FUniformsLightPhong *aUniform = (FUniformsLightPhong *)(mUniform);
                aUniform->mNormal.Set(mNormal);
            }
            
            if (mUniform->GetType() == UNIFORM_TYPE_LIGHT_SIMPLE_SPOTLIGHT) {
                FUniformsLightSimpleSpotlight *aUniform = (FUniformsLightSimpleSpotlight *)(mUniform);
                aUniform->mNormal.Set(mNormal);
            }
            
            mUniform->mColor.mRed = mColor.mRed;
            mUniform->mColor.mGreen = mColor.mGreen;
            mUniform->mColor.mBlue = mColor.mBlue;
            mUniform->mColor.mAlpha = mColor.mAlpha;
            
            Graphics::UniformBind(mUniform);
        }
        
        Graphics::DrawTrianglesIndexedWithPackedBuffers(mAccessoryModel->mBuffer, 0, mAccessoryModel->mIndex, mAccessoryModel->mIndexCount, mAccessorySprite->mTexture);
        
    }
    
}


