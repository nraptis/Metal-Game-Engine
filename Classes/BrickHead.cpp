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
    
    mModel = &gApp->mBrickhead;
    mSprite = &gApp->mBrickheadMap;
    
    mAccessoryModel = &gApp->mBrickheadCage;
    mAccessorySprite = &gApp->mBrickheadMap;
    
    //mTransform.mScaleZ = 0.5f;
    //mTransform.mOffsetY = 33.0f;
    
    mUniform = &(gGame->mRenderer->mUniformPhongBalloon);
    
    //mStuck = false;
    //mStuckDart = NULL;
    //mStuckDartStartDartRotation = 0.0f;
    //mStuckDartStartBrickHeadRotation = 0.0f;
    //mStuckDartStartXDiff = 0.0f;
    //mStuckDartStartYDiff = 0.0f;
    
    
    mVelX = 0.0f;
    mVelY = 0.0f;
    
    mCornerPoint1 = FVec2(-12.0f,  12.0f);
    mCornerPoint2 = FVec2(12.0f , -12.0f);
    mCornerPoint3 = FVec2(12.0f ,  12.0f);
    mCornerPoint4 = FVec2(-12.0f,  12.0f);
    
    
    mWanderingSinX = gRand.GetFloat(360.0f);
    mWanderingSinY = gRand.GetFloat(360.0f);
    mWanderingOsc = gRand.GetFloat(360.0f);
    
    mWanderingMagX = gRand.GetFloat(3.0f, 40.0f, true);
    mWanderingMagY = gRand.GetFloat(3.0f, 40.0f, true);
    
    
    mIsRumbling = false;
    mRumbleTime = 200;
    mRumbleDampenTime = mRumbleTime - 100;
    
    mRumbleTimer = 0;
    
    mRumbleColorSin = 0.0f;
    
    mRumbleDirX = 0.0f;
    mRumbleDirY = -1.0f;
    
    mRumbleBounceMagnitude = 5.0f;
    mRumbleBounceSin = 0.0f;
    
    
    
}

BrickHead::~BrickHead() {
    FreeList(StuckDart, mStuckDartList);
}

void BrickHead::Update() {
    mTransform3D.mSpin += mSpinSpeed;
    
    mTransform.mX += mVelX;
    mTransform.mY += mVelY;
    
    
    //
    
    
    
    if (mIsRumbling) {
        
        
        
        mRumbleTimer++;
        if (mRumbleTimer >= mRumbleTime) {
            mIsRumbling = false;
            
        }
        
        float aDampenPercent = 0.0f;
        if (mRumbleTimer > mRumbleDampenTime) {
            
            int aAdjustedTimer = mRumbleTimer - mRumbleDampenTime;
            int aDampenSpan = mRumbleTime - mRumbleDampenTime;
            
            aDampenPercent = ((float)aAdjustedTimer) / ((float)aDampenSpan);
        }
        
        mRumbleColorSin += 11.0f;
        if (mRumbleColorSin >= 360.0f) {
            mRumbleColorSin -= 360.0f;
        }
        
        mRumbleBounceSin += 9.0f;
        if (mRumbleBounceSin >= 360.0f) {
            mRumbleBounceSin -= 360.0f;
        }
        
        float aColorSin = Sin(mRumbleColorSin);
        float aColorPercent = (aColorSin + 1.0f) * 0.5f; //Goes from 0 to 1...
        
        //aDampenPercent
        mColor.mRed = 1.0f - (aColorPercent * 0.55f) * (1.0f - aDampenPercent);
        mColor.mGreen = 1.0f - (aColorPercent * 0.8f) * (1.0f - aDampenPercent);
        mColor.mBlue = 1.0f - (aColorPercent * 0.8f) * (1.0f - aDampenPercent);
        
        
        mRumbleBounceMagnitude = 7.0f * (1.0f - aDampenPercent);
        
        float aMag = Cos(mRumbleBounceSin) * mRumbleBounceMagnitude;
        
        mTransform.mOffsetX = mRumbleDirX * aMag;
        mTransform.mOffsetY = mRumbleDirY * aMag;
        
        
    } else {
        mColor.mRed = 1.0f;
        mColor.mGreen = 1.0f;
        mColor.mBlue = 1.0f;
        
        mTransform.mOffsetX = 0.0f;
        mTransform.mOffsetY = 0.0f;
    }
    
    
    
    
    /*
    float aMultiplier = 0.5f;
    
    
    mWanderingSinX += 3.0f * aMultiplier;
    if (mWanderingSinX >= 360.0f) { mWanderingSinX -= 360.0f; }
    
    mWanderingSinY -= 0.75f * aMultiplier;
    if (mWanderingSinY <= 0.0f) { mWanderingSinY += 360.0f; }
    
    mWanderingOsc += 1.5f * aMultiplier;
    if (mWanderingOsc >= 360.0f) { mWanderingOsc -= 360.0f; }
    
    
    float aSin1 = Sin(mWanderingSinX);
    float aSin2 = Sin(mWanderingSinY);
    
    float aSinOsc = Sin(mWanderingOsc);
    
    float aShiftX = aSin1 * mWanderingMagX;
    float aShiftY = aSin1 * mWanderingMagY;
    
    float aRot = aSinOsc;
    
    mTransform.mOffsetX = aShiftX;
    mTransform.mOffsetY = aShiftY;
    
    mTransform.mOffsetRotation = aRot * 30.0f;
    
    */
    
    
    
    float aSize = 1.42f;
    
    gGame->Convert2DTransformTo3D(&mTransform, &mTransform3D);
    
    mCornerPoint1 = FVec2(-aSize, -aSize);
    mCornerPoint2 = FVec2( aSize, -aSize);
    mCornerPoint3 = FVec2( aSize,  aSize);
    mCornerPoint4 = FVec2(-aSize,  aSize);
    
    mCornerPoint1 = PivotPoint(mCornerPoint1, mTransform.mRotation + mTransform.mOffsetRotation);
    mCornerPoint2 = PivotPoint(mCornerPoint2, mTransform.mRotation + mTransform.mOffsetRotation);
    mCornerPoint3 = PivotPoint(mCornerPoint3, mTransform.mRotation + mTransform.mOffsetRotation);
    mCornerPoint4 = PivotPoint(mCornerPoint4, mTransform.mRotation + mTransform.mOffsetRotation);
    
    mCornerPoint1.mX += mTransform3D.mX; mCornerPoint1.mY += mTransform3D.mY;
    mCornerPoint2.mX += mTransform3D.mX; mCornerPoint2.mY += mTransform3D.mY;
    mCornerPoint3.mX += mTransform3D.mX; mCornerPoint3.mY += mTransform3D.mY;
    mCornerPoint4.mX += mTransform3D.mX; mCornerPoint4.mY += mTransform3D.mY;
    
    mCornerPoint1 = gGame->Convert3DCoordsTo2D(mCornerPoint1.mX, mCornerPoint1.mY);
    mCornerPoint2 = gGame->Convert3DCoordsTo2D(mCornerPoint2.mX, mCornerPoint2.mY);
    mCornerPoint3 = gGame->Convert3DCoordsTo2D(mCornerPoint3.mX, mCornerPoint3.mY);
    mCornerPoint4 = gGame->Convert3DCoordsTo2D(mCornerPoint4.mX, mCornerPoint4.mY);
    
    
    EnumList(StuckDart, aStuck, mStuckDartList) {
        aStuck->Update();
        if (aStuck->mDelete) {
            mStuckDartDeleteList.Add(aStuck);
        }
        
        Dart *aDart = aStuck->mDart;
        if (aDart != NULL) {
            float aRotationDiff = (mTransform.mRotation + mTransform.mOffsetRotation) - aStuck->mStartReferenceRotation;
            
            aDart->mTransform.mRotation = aStuck->mStartDartRotation + aRotationDiff;
            
            FVec2 aDartOffset = FVec2(aStuck->mStartXDiff, aStuck->mStartYDiff);
            aDartOffset = PivotPoint(aDartOffset, aRotationDiff);
            
            aDart->mTransform.mX = (mTransform.mX + mTransform.mOffsetX) + aDartOffset.mX;
            aDart->mTransform.mY = (mTransform.mY + mTransform.mOffsetY) + aDartOffset.mY;
        }
    }
    
    EnumList(StuckDart, aStuck, mStuckDartDeleteList) {
        mStuckDartList.Remove(aStuck);
        delete aStuck;
    }
    mStuckDartDeleteList.RemoveAll();
    
}

void BrickHead::Draw() {
    
    
    GameObject::Draw();
    
    /*
    
    Graphics::SetColor(1.0f, 0.15f, 0.15f, 0.75f);
    Graphics::PipelineStateSetShape2DAlphaBlending();
    
    Graphics::DrawLine(mCornerPoint1.mX, mCornerPoint1.mY, mCornerPoint2.mX, mCornerPoint2.mY);
    Graphics::DrawLine(mCornerPoint2.mX, mCornerPoint2.mY, mCornerPoint3.mX, mCornerPoint3.mY);
    Graphics::DrawLine(mCornerPoint3.mX, mCornerPoint3.mY, mCornerPoint4.mX, mCornerPoint4.mY);
    Graphics::DrawLine(mCornerPoint4.mX, mCornerPoint4.mY, mCornerPoint1.mX, mCornerPoint1.mY);
    
    */
    
    
    
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

void BrickHead::Rumble(float pRotation) {
    
    mIsRumbling = true;
    
    mRumbleTimer = 0;
    
    mRumbleColorSin = 0.0f;
    
    
    mRumbleDirX = Sin(pRotation);
    mRumbleDirY = -Cos(pRotation);
    
    mRumbleBounceMagnitude = 12.0f;
    mRumbleBounceSin = 0.0f;
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

