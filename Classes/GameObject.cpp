//
//  GameObject.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 2/28/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "GameObject.hpp"
#include "Game.hpp"

GameObject::GameObject() {
    
    mUniform = NULL;
    mModel = NULL;
    mSprite = NULL;
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





