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
    
    mModel = &gApp->mBrickhead;
    mSprite = &gApp->mBrickheadMap;
    
    mAccessoryModel = &gApp->mBrickheadCage;
    mAccessorySprite = &gApp->mBrickheadCageMap;
    
    //mTransform.mScaleZ = 0.5f;
    //mTransform.mOffsetY = 33.0f;
    
    mUniform = &(gGame->mRenderer->mUniformPhongBalloon);
    
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
    
    if (mAccessoryModel != NULL && mAccessorySprite != NULL) {
        
        if (mUniform != NULL) {
            /*
            gGame->Convert2DTransformTo3D(&mTransform, &mTransform3D);
            
            mModelView.Reset();
            
            //We start by translation...?
            
            mModelView.Translate(mTransform3D.mX, mTransform3D.mY, mTransform3D.mZ);
            
            //All of our models are exported with X 90 degrees wrong...
            mModelView.RotateX(90.0f);
            
            if (mTransform3D.mRotationX != 0.0f) {
                mModelView.RotateX(mTransform3D.mRotationX);
            }
            
            if (mTransform3D.mRotationZ != 0.0f) {
                mModelView.RotateZ(mTransform3D.mRotationZ);
            }
            
            //Now we do a 2-D rotation...
            if (mTransform3D.mRotation2D != 0.0f) {
                mModelView.RotateY(mTransform3D.mRotation2D);
            }
            
            //Now we spin around the Y axis...
            if (mTransform3D.mSpin != 0.0f) {
                mModelView.RotateZ(mTransform3D.mSpin);
            }
            
            //Now we scale down...
            mModelView.Scale(mTransform3D.mScaleX * mTransform3D.mScale, mTransform3D.mScaleY * mTransform3D.mScale, mTransform3D.mScaleZ * mTransform3D.mScale);
            
            mNormal.SetNormalMatrix(mModelView);
            */
            
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
            
            
            //aNormal.SetNormalMatrix(aModelView);
            
            
            mUniform->mColor.mRed = mColor.mRed;
            mUniform->mColor.mGreen = mColor.mGreen;
            mUniform->mColor.mBlue = mColor.mBlue;
            mUniform->mColor.mAlpha = mColor.mAlpha;
            
            //Then bind the uniform...
            Graphics::UniformBind(mUniform);
        }
        
        Graphics::DrawTrianglesIndexedWithPackedBuffers(mAccessoryModel->mBuffer, 0, mAccessoryModel->mIndex, mAccessoryModel->mIndexCount, mAccessorySprite->mTexture);
        
    }
    
}


