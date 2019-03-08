//
//  GameObject.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 2/28/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "GameObject.hpp"

GameObject::GameObject() {
    
    mUniform = NULL;
    mModel = NULL;
    mSprite = NULL;
    
    mX = 0.0f;
    mY = 0.0f;
    mZ = 0.0f;
    
    mOffsetX = 0.0f;
    mOffsetY = 0.0f;
    mOffsetZ = 0.0f;
    
    mRotation2D = 0.0f;
    
    mOffsetRotation2D = 0.0f;
    
    mOffsetRotationX = 0.0f;
    mOffsetRotationZ = 0.0f;
    
    mSpin = 0.0f;
    
    mScale = 1.0f;
    
    mOffsetScale = 1.0f;
    
    mScaleX = 1.0f;
    mScaleY = 1.0f;
    mScaleZ = 1.0f;
    
}

GameObject::~GameObject() {
    
}

void GameObject::Update() {
    
    
}

void GameObject::Draw() {
    
}

void GameObject::Draw3D() {
    
    if (mModel != NULL && mSprite != NULL) {
        
        if (mUniform != NULL) {
            
            mModelView.Reset();
            
            //We start by translation...?
            mModelView.Translate(mX + mOffsetX, mY + mOffsetY, mZ + mOffsetZ);
            
            //All of our models are exported with X 90 degrees wrong...
            mModelView.RotateX(90.0f);
            
            if (mOffsetRotationX != 0.0f) {
                mModelView.RotateX(mOffsetRotationX);
            }
            
            if (mOffsetRotationZ != 0.0f) {
                mModelView.RotateZ(mOffsetRotationZ);
            }
            
            //Now we do a 2-D rotation...
            if (mRotation2D != 0.0f || mOffsetRotation2D != 0.0f) {
                mModelView.RotateY(mRotation2D + mOffsetRotation2D);
            }
            
            //Now we spin around the Y axis...
            if (mSpin != 0.0f) {
                mModelView.RotateZ(mSpin);
            }
            
            //Now we scale down...
            mModelView.Scale(mScaleX * mScale * mOffsetScale,
                             mScaleY * mScale * mOffsetScale,
                             mScaleZ * mScale * mOffsetScale);
            
            //Assign the model view to the uniform...
            mUniform->mModelView.Set(mModelView);
            mUniform->mColor.mRed = mColor.mRed;
            mUniform->mColor.mGreen = mColor.mGreen;
            mUniform->mColor.mBlue = mColor.mBlue;
            mUniform->mColor.mAlpha = mColor.mAlpha;
            
            //Then bind the uniform...
            Graphics::UniformBind(mUniform);
        }
        Graphics::DrawTrianglesIndexedFromPackedBuffers(mModel->mBufferVertex,
                                                        mModel->mBufferVertexOffset,
                                                        mModel->mBufferIndex,
                                                        mModel->mBufferIndexOffset,
                                                        mModel->mIndexCount,
                                                        mSprite->mTexture);
    }
}

void GameObject::Kill() {
    FObject::Kill();
}

FVec2 GameObject::GetScreenPos() {
    FVec2 aResult;
    printf("WARNING: Not Implemented... SCREEN POS...\n");
    aResult.mX = mX;
    aResult.mY = mY;
    return aResult;
}






