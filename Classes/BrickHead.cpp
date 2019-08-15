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
    
    mSpinSpeed = 0.0f;
    
    mSwivel = gRand.GetFloat(360.0f);
    mSwivelSpeed = gRand.GetFloat(0.25, 0.65, true);
    
    mModel = &gApp->mBrickhead;
    mSprite = &gApp->mBrickheadMap;
    
    mAccessoryModel = &gApp->mBrickheadCage;
    mAccessorySprite = &gApp->mBrickheadMap;
    
    //mTransform.mScaleZ = 0.5f;
    //mTransform.mOffsetY = 33.0f;
    
    mUniform = &(gGame->mRenderer->mUniformPhongBalloon);
    
    mStuck = false;
    mStuckDart = NULL;
    
    mStuckDartStartDartRotation = 0.0f;
    mStuckDartStartBrickHeadRotation = 0.0f;
    mStuckDartStartXDiff = 0.0f;
    mStuckDartStartYDiff = 0.0f;
    
    mHitDelay = 200;
    
    mVelX = 0.0f;
    mVelY = 0.0f;
    
    mCornerPoint1 = FVec2(-12.0f,  12.0f);
    mCornerPoint2 = FVec2(12.0f , -12.0f);
    mCornerPoint3 = FVec2(12.0f ,  12.0f);
    mCornerPoint4 = FVec2(-12.0f,  12.0f);
    
    mHitOscSin = 0.0f;
    mHitOscSpinRot = 0.0f;
    
}

BrickHead::~BrickHead() {
    //Log("BrickHead has died [%LX]\n", this);
}

void BrickHead::Update() {
    mTransform3D.mSpin += mSpinSpeed;
    
    if (mStuck == false) {
        mSwivel += mSwivelSpeed;
        if (mSwivel >= 360.0f) { mSwivel -= 360.0f; }
        if (mSwivel <= 360.0f) { mSwivel += 360.0f; }
    } else {
        
        if (mHitDelay > 0) {
            mHitDelay--;
        } else {
            mSwivel -= mSwivelSpeed / 2.0;
            if (mSwivel >= 360.0f) { mSwivel -= 360.0f; }
            if (mSwivel <= 360.0f) { mSwivel += 360.0f; }
            
            mHitOscSin += 0.75f;
            if (mHitOscSin >= 360.0f) { mHitOscSin -= 360.0f; }
            
            mHitOscSpinRot += 0.25f;
            if (mHitOscSpinRot >= 360.0f) { mHitOscSpinRot -= 360.0f; }
            
            float aOscAmount = Sin(mHitOscSin) * 36.0f;
            
            FVec2 aOscDir = AngleToVector(mHitOscSpinRot);
            
            mTransform.mX = mHitStartX + aOscDir.mX * aOscAmount;
            mTransform.mY = mHitStartY + aOscDir.mY * aOscAmount;
        }
    }
        
    mTransform.mRotation = mSwivel;
    
    if (mStuck == false) {
        mTransform.mX += mVelX;
        mTransform.mY += mVelY;
    }
    
    float aSize = 1.4f;
    
    gGame->Convert2DTransformTo3D(&mTransform, &mTransform3D);
    
    mCornerPoint1 = FVec2(-aSize, -aSize);
    mCornerPoint2 = FVec2(aSize, -aSize);
    mCornerPoint3 = FVec2(aSize, aSize);
    mCornerPoint4 = FVec2(-aSize, aSize);
    
    mCornerPoint1 = PivotPoint(mCornerPoint1, mTransform.mRotation + mTransform.mOffsetRotation);
    mCornerPoint2 = PivotPoint(mCornerPoint2, mTransform.mRotation + mTransform.mOffsetRotation);
    mCornerPoint3 = PivotPoint(mCornerPoint3, mTransform.mRotation + mTransform.mOffsetRotation);
    mCornerPoint4 = PivotPoint(mCornerPoint4, mTransform.mRotation + mTransform.mOffsetRotation);
    
    mCornerPoint1.mX += mTransform3D.mX;
    mCornerPoint1.mY += mTransform3D.mY;
    
    mCornerPoint2.mX += mTransform3D.mX;
    mCornerPoint2.mY += mTransform3D.mY;
    
    mCornerPoint3.mX += mTransform3D.mX;
    mCornerPoint3.mY += mTransform3D.mY;
    
    mCornerPoint4.mX += mTransform3D.mX;
    mCornerPoint4.mY += mTransform3D.mY;
    
    mCornerPoint1 = gGame->Convert3DCoordsTo2D(mCornerPoint1.mX, mCornerPoint1.mY);
    mCornerPoint2 = gGame->Convert3DCoordsTo2D(mCornerPoint2.mX, mCornerPoint2.mY);
    mCornerPoint3 = gGame->Convert3DCoordsTo2D(mCornerPoint3.mX, mCornerPoint3.mY);
    mCornerPoint4 = gGame->Convert3DCoordsTo2D(mCornerPoint4.mX, mCornerPoint4.mY);
    
    if (mStuckDart != NULL) {
        
        float aRotationDiff = mTransform.mRotation - mStuckDartStartBrickHeadRotation;
        mStuckDart->mTransform.mRotation = mStuckDartStartDartRotation + aRotationDiff;
        
        FVec2 aDartOffset = FVec2(mStuckDartStartXDiff, mStuckDartStartYDiff);
        aDartOffset = PivotPoint(aDartOffset, aRotationDiff);
        
        mStuckDart->mTransform.mX = mTransform.mX + aDartOffset.mX;
        mStuckDart->mTransform.mY = mTransform.mY + aDartOffset.mY;
    }
    
}

void BrickHead::Draw() {
    
    GameObject::Draw();
    
    Graphics::SetColor(1.0f, 0.15f, 0.15f, 0.75f);
    Graphics::PipelineStateSetShape2DAlphaBlending();
    
    Graphics::DrawLine(mCornerPoint1.mX, mCornerPoint1.mY, mCornerPoint2.mX, mCornerPoint2.mY);
    Graphics::DrawLine(mCornerPoint2.mX, mCornerPoint2.mY, mCornerPoint3.mX, mCornerPoint3.mY);
    Graphics::DrawLine(mCornerPoint3.mX, mCornerPoint3.mY, mCornerPoint4.mX, mCornerPoint4.mY);
    Graphics::DrawLine(mCornerPoint4.mX, mCornerPoint4.mY, mCornerPoint1.mX, mCornerPoint1.mY);
    
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
            
            mUniform->mColor.mRed = mColor.mRed;
            mUniform->mColor.mGreen = mColor.mGreen;
            mUniform->mColor.mBlue = mColor.mBlue;
            mUniform->mColor.mAlpha = mColor.mAlpha;
            
            //Then bind the uniform...
            Graphics::UniformBind(mUniform);
            Graphics::DrawTrianglesIndexedWithPackedBuffers(mAccessoryModel->mBuffer, 0, mAccessoryModel->mIndex, mAccessoryModel->mIndexCount, mAccessorySprite->mTexture);
            
        }
    }
}


bool BrickHead::WillCollide(float pStartX, float pStartY, float pEndX, float pEndY) {
    
    if (QuadContainsPoint(pStartX, pStartY, mCornerPoint1.mX, mCornerPoint1.mY, mCornerPoint2.mX, mCornerPoint2.mY, mCornerPoint3.mX, mCornerPoint3.mY, mCornerPoint4.mX, mCornerPoint4.mY)) {
        return true;
    }
    
    if (QuadContainsPoint(pEndX, pEndY, mCornerPoint1.mX, mCornerPoint1.mY, mCornerPoint2.mX, mCornerPoint2.mY, mCornerPoint3.mX, mCornerPoint3.mY, mCornerPoint4.mX, mCornerPoint4.mY)) {
        return true;
    }
    
    if (SegmentsIntersect(mCornerPoint1, mCornerPoint2, FVec2(pStartX, pStartY), FVec2(pEndX, pEndY))) {
        return true;
    }
    if (SegmentsIntersect(mCornerPoint2, mCornerPoint3, FVec2(pStartX, pStartY), FVec2(pEndX, pEndY))) {
        return true;
    }
    
    if (SegmentsIntersect(mCornerPoint3, mCornerPoint4, FVec2(pStartX, pStartY), FVec2(pEndX, pEndY))) {
        return true;
    }
    
    if (SegmentsIntersect(mCornerPoint4, mCornerPoint1, FVec2(pStartX, pStartY), FVec2(pEndX, pEndY))) {
        return true;
    }
    
    return false;
}

