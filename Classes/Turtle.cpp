//
//  Turtle.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 8/13/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "Turtle.hpp"
#include "Game.hpp"

Turtle::Turtle() {
    
    mGameObjectType = GAME_OBJECT_TYPE_TURTLE;
    
    mModel = &(gWadModels.mTurtle);
    mSprite = &(gWadModels.mTurtleMap);
    
    //mModel = &(gWadModels.mTurtlePropeller);
    //mSprite = &(gWadModels.mTurtlePropellerMap);
    
    
    mPropellerModel = &(gWadModels.mTurtlePropeller);
    mPropellerSprite = &(gWadModels.mTurtlePropellerMap);
    mPropellerSpin = gRand.Rot();
    mPropellerSpeed = gRand.GetFloat(7.0f, 9.0f);
    
    
    mPropellerBillboardSequence = &(gWadModels.mTurtlePropellerBillboardSequence);
    mPropellerBillboardSequenceMap = &(gWadModels.mTurtlePropellerBillboardMapSequence);
    
    mPropellerBillboardFrame1 = gRand.GetFloat(gWadModels.mTurtlePropellerBillboardSequence.GetMaxFrame());
    mPropellerBillboardFrame2 = gRand.GetFloat(gWadModels.mTurtlePropellerBillboardSequence.GetMaxFrame());
    mPropellerBillboardFrame3 = gRand.GetFloat(gWadModels.mTurtlePropellerBillboardSequence.GetMaxFrame());
    
    mPropellerBillboardSpin1 = gRand.Rot();
    mPropellerBillboardSpin2 = gRand.Rot();
    mPropellerBillboardSpin3 = gRand.Rot();
    
    
    
    
    
    //mPropellerBillboardSequence = gWadModels.mTurtle;
    //mPropellerBillboardSequenceMap;
    //mPropellerBillboardFrame = ;
    
    
    
    
    //FModelDataPacked                        *mPropellerModel;
    //FSprite                                 *mPropellerSprite;
    
    
    
    //mAccessoryModel = &gApp->mTurtleCage;
    //mAccessorySprite = &gApp->mTurtleMap;
    
    mUniform = &(gGame->mRenderer->mUniformPhongBalloon);
    
    mVelX = 0.0f;
    mVelY = 0.0f;
    
    mTransform.mOffsetY = 1.0f;
    mTransform.mOffsetScale = 0.65f;
    
    mBillboardFrame = 0.0f;
    
}

Turtle::~Turtle() {
    
}

void Turtle::Update() {
    
    mTransform.mX += mVelX;
    mTransform.mY += mVelY;
    
    mPropellerSpin += mPropellerSpeed + gRand.GetFloat(2.0f, 2.5f);
    if (mPropellerSpin >= 360.0f) { mPropellerSpin -= 360.0f; }
    
    if ((mPropellerBillboardSequence != NULL) && (mPropellerBillboardSequence->GetMaxFrame() > 1.0f)) {
        
        mPropellerBillboardFrame1 += 0.6f + gRand.F(0.125, 0.25);
        if (mPropellerBillboardFrame1 >= mPropellerBillboardSequence->GetMaxFrame()) {
            mPropellerBillboardFrame1 -= mPropellerBillboardSequence->GetMaxFrame();
        }
        
        mPropellerBillboardFrame2 -= 0.8f + gRand.F(0.125, 0.25);
        if (mPropellerBillboardFrame1 <= 0.0f) {
            mPropellerBillboardFrame1 += mPropellerBillboardSequence->GetMaxFrame();
        }
        
        mPropellerBillboardFrame3 += 0.9f + gRand.F(0.15, 0.325);
        if (mPropellerBillboardFrame3 >= mPropellerBillboardSequence->GetMaxFrame()) {
            mPropellerBillboardFrame3 -= mPropellerBillboardSequence->GetMaxFrame();
        }
        
        mPropellerBillboardSpin1 += 5.0f + gRand.GetFloat(3.0f);
        if (mPropellerBillboardSpin1 >= 360.0f) { mPropellerBillboardSpin1 -= 360.0f; }
        
        mPropellerBillboardSpin2 -= 5.0f + gRand.GetFloat(3.0f);
        if (mPropellerBillboardSpin2 <= 0.0f) { mPropellerBillboardSpin2 += 360.0f; }
        
        mPropellerBillboardSpin3 += 8.0f + gRand.GetFloat(4.0f);
        if (mPropellerBillboardSpin3 >= 360.0f) { mPropellerBillboardSpin3 -= 360.0f; }
        
        
        
        
        
        
    }
    
    
    
    if (gWadModels.mTurtlePropellerBillboardMapSequence.mList.mCount > 0) {
        
        mBillboardFrame += 0.5f;
        if (mBillboardFrame >= gWadModels.mTurtlePropellerBillboardMapSequence.GetMaxFrame()) {
            mBillboardFrame -= gWadModels.mTurtlePropellerBillboardMapSequence.GetMaxFrame();
        }
    }
    
}

void Turtle::Draw() {
    
    GameObject::Draw();
    
}

void Turtle::Draw3D() {
    
    //GameObject::Draw3D();
    GameObject::Draw3D();
    
    
    
    
    
    
    /*
    if (mUniform != NULL) {
        gGame->Convert2DTransformTo3D(&mTransform, &mTransform3D);
        
        mModelView.Reset();
        
        //We start by translation...?
        mModelView.Translate(mTransform3D.mX, mTransform3D.mY, mTransform3D.mZ);
        
        //All of our models are exported with X 90 degrees wrong...
        mModelView.RotateX(-90.0f);
        mModelView.RotateY(180.0f);
        
        //mModelView.RotateZ(180.0f);
        
        if (mTransform3D.mRotationX != 0.0f) {
            //mModelView.RotateX(mTransform3D.mRotationX);
        }
        
        if (mTransform3D.mRotationZ != 0.0f) {
            //mModelView.RotateZ(mTransform3D.mRotationZ);
        }
        
        //Now we do a 2-D rotation...
        if (mTransform3D.mRotation2D != 0.0f) {
            mModelView.RotateY(-mTransform3D.mRotation2D);
        }
        
        //Now we spin around the Y axis...
        if (mTransform3D.mSpin != 0.0f) {
            mModelView.RotateZ(mTransform3D.mSpin);
        }
        
        mModelView.Scale(10.0f);
        
        //Now we scale down...
        mModelView.Scale(mTransform3D.mScaleX * mTransform3D.mScale, mTransform3D.mScaleY * mTransform3D.mScale, mTransform3D.mScaleZ * mTransform3D.mScale);
        
        mNormal.SetNormalMatrix(mModelView);
        
        
        
        
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
        
        
        //Graphics::DrawTrianglesIndexedWithPackedBuffers(mPropellerModel->mBuffer, 0, mPropellerModel->mIndex, mPropellerModel->mIndexCount, mPropellerSprite->mTexture);
        
        FModelDataPacked *aModel1 = gWadModels.mTestSequence1.GetModel(mTestFrame);
        
        if (aModel1 != NULL && gWadModels.mTestSequence1.mIndexCount > 0) {
            Graphics::DrawTrianglesIndexedWithPackedBuffers(aModel1->mBuffer, 0, gWadModels.mTestSequence1.mIndex, gWadModels.mTestSequence1.mIndexCount, gWadModels.mTestSequenceMap.mTexture);
            
            
        }
        
        FModelDataPacked *aModel2 = gWadModels.mTestSequence2.GetModel(mTestFrame);
        
        if (aModel2 != NULL && gWadModels.mTestSequence1.mIndexCount > 0) {
            Graphics::DrawTrianglesIndexedWithPackedBuffers(aModel2->mBuffer, 0, gWadModels.mTestSequence1.mIndex, gWadModels.mTestSequence1.mIndexCount, gWadModels.mTestSequenceMap.mTexture);
        }
        
        
        
    }


    if (mUniform != NULL) {
        gGame->Convert2DTransformTo3D(&mTransform, &mTransform3D);
        
        mModelView.Reset();
        
        //We start by translation...?
        mModelView.Translate(mTransform3D.mX, mTransform3D.mY, mTransform3D.mZ);
        
        //All of our models are exported with X 90 degrees wrong...
        mModelView.RotateX(-90.0f);
        mModelView.RotateY(180.0f);
        
        //mModelView.RotateZ(180.0f);
        
        if (mTransform3D.mRotationX != 0.0f) {
            //mModelView.RotateX(mTransform3D.mRotationX);
        }
        
        if (mTransform3D.mRotationZ != 0.0f) {
            //mModelView.RotateZ(mTransform3D.mRotationZ);
        }
        
        //Now we do a 2-D rotation...
        if (mTransform3D.mRotation2D != 0.0f) {
            mModelView.RotateY(-mTransform3D.mRotation2D);
        }
        
        //Now we spin around the Y axis...
        if (mTransform3D.mSpin != 0.0f) {
            mModelView.RotateZ(mTransform3D.mSpin);
        }
        
        mModelView.RotateY(45.0f);
        mModelView.RotateX(45.0f);
        
        
        mModelView.Scale(10.0f);
        
        //Now we scale down...
        mModelView.Scale(mTransform3D.mScaleX * mTransform3D.mScale, mTransform3D.mScaleY * mTransform3D.mScale, mTransform3D.mScaleZ * mTransform3D.mScale);
        
        mNormal.SetNormalMatrix(mModelView);
        
        
        
        
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
        
        FModelDataPacked *aModel = gWadModels.mBillboardSequence.GetModel(mBillboardFrame);
        FSprite *aSprite = gWadModels.mBillboardMapSequence.GetSprite(mBillboardFrame);
        
        
        if (aModel != NULL && aModel->mIndexCount > 0 && aSprite != NULL) {
            Graphics::DrawTrianglesIndexedWithPackedBuffers(aModel->mBuffer, 0, aModel->mIndex, aModel->mIndexCount, aSprite->mTexture);
        }
    }
     
    */
     
}

void Turtle::Draw3DPropeller() {
    
    if (mPropellerModel != NULL && mPropellerSprite != NULL) {
        
        if (mUniform != NULL) {
            
            mPropellerMatrixModelView.Set(mModelView);
            mPropellerMatrixModelView.RotateZ(mPropellerSpin);
            
            mPropellerMatrixNormal.SetNormalMatrix(mPropellerMatrixModelView);
            
            
            //mPropellerMatrixNormal
            //mPropellerMatrixModelView
            
            //Assign the model view to the uniform...
            mUniform->mModelView.Set(mPropellerMatrixModelView);
            
            if (mUniform->GetType() == UNIFORM_TYPE_LIGHT_DIFFUSE) {
                FUniformsLightDiffuse *aUniform = (FUniformsLightDiffuse *)(mUniform);
                aUniform->mNormal.Set(mPropellerMatrixNormal);
            }
            
            if (mUniform->GetType() == UNIFORM_TYPE_LIGHT_PHONG) {
                FUniformsLightPhong *aUniform = (FUniformsLightPhong *)(mUniform);
                aUniform->mNormal.Set(mPropellerMatrixNormal);
            }
            
            if (mUniform->GetType() == UNIFORM_TYPE_LIGHT_SIMPLE_SPOTLIGHT) {
                FUniformsLightSimpleSpotlight *aUniform = (FUniformsLightSimpleSpotlight *)(mUniform);
                aUniform->mNormal.Set(mPropellerMatrixNormal);
            }
            
            mUniform->mColor.mRed = mColor.mRed;
            mUniform->mColor.mGreen = mColor.mGreen;
            mUniform->mColor.mBlue = mColor.mBlue;
            mUniform->mColor.mAlpha = mColor.mAlpha;
            
            Graphics::UniformBind(mUniform);
        }
        
        Graphics::DrawTrianglesIndexedWithPackedBuffers(mPropellerModel->mBuffer, 0, mPropellerModel->mIndex, mPropellerModel->mIndexCount, mPropellerSprite->mTexture);
    }
    
    
}

void Turtle::Draw3DBillboard() {
    
    if (mPropellerBillboardSequence != NULL && mPropellerBillboardSequenceMap != NULL) {
        FModelDataPacked *aModel = mPropellerBillboardSequence->GetModel(mPropellerBillboardFrame1);
        FSprite *aSprite = mPropellerBillboardSequenceMap->GetSprite(mPropellerBillboardFrame1);
        if ((mUniform != NULL) && (aModel != NULL) && (aSprite != NULL)) {
            mPropellerMatrixModelView.Set(mModelView);
            mPropellerMatrixModelView.RotateZ(mPropellerBillboardSpin1);
            Graphics::MatrixModelViewSet(mPropellerMatrixModelView);
            Graphics::UniformBind();
            Graphics::DrawTrianglesIndexedWithPackedBuffers(aModel->mBuffer, 0, mPropellerBillboardSequence->mIndex, mPropellerBillboardSequence->mIndexCount, aSprite->mTexture);
        }
        
        
        aModel = mPropellerBillboardSequence->GetModel(mPropellerBillboardFrame2);
        aSprite = mPropellerBillboardSequenceMap->GetSprite(mPropellerBillboardFrame2);
        if ((mUniform != NULL) && (aModel != NULL) && (aSprite != NULL)) {
            mPropellerMatrixModelView.Set(mModelView);
            mPropellerMatrixModelView.RotateX(-3.0f);
            mPropellerMatrixModelView.RotateZ(mPropellerBillboardSpin2);
            Graphics::MatrixModelViewSet(mPropellerMatrixModelView);
            Graphics::UniformBind();
            Graphics::DrawTrianglesIndexedWithPackedBuffers(aModel->mBuffer, 0, mPropellerBillboardSequence->mIndex, mPropellerBillboardSequence->mIndexCount, aSprite->mTexture);
        }
        
        aModel = mPropellerBillboardSequence->GetModel(mPropellerBillboardFrame3);
        aSprite = mPropellerBillboardSequenceMap->GetSprite(mPropellerBillboardFrame3);
        if ((mUniform != NULL) && (aModel != NULL) && (aSprite != NULL)) {
            mPropellerMatrixModelView.Set(mModelView);
            mPropellerMatrixModelView.RotateX(3.0f);
            mPropellerMatrixModelView.RotateZ(mPropellerBillboardSpin3);
            Graphics::MatrixModelViewSet(mPropellerMatrixModelView);
            Graphics::UniformBind();
            Graphics::DrawTrianglesIndexedWithPackedBuffers(aModel->mBuffer, 0, mPropellerBillboardSequence->mIndex, mPropellerBillboardSequence->mIndexCount, aSprite->mTexture);
        }
    }
}
