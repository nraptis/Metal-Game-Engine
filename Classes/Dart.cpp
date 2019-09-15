//
//  Dart.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 2/28/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "Dart.hpp"
#include "Game.hpp"

Dart::Dart() {
    
    mGameObjectType = GAME_OBJECT_TYPE_DART;
    
    mSpinSpeed = gRand.GetFloat(1.25f, 1.45f);
    if (gRand.GetBool()) mSpinSpeed = -mSpinSpeed;
    
    //While we are "idle" we have not yet been released
    //and are sitting at the lower center of the screen...
    mIdle = true;
    mStuck = false;
    mKnockedDown = false;
    
    mKnockedDownColorSin = 0.0f;
    
    mDeathTimer = 5000;
    mTimer = 0;
    
    mHitCount = 0;
    
    mStyleIndex = gRand.Get(6);
    
    //mModel = &gWadModels.mDartRegular[mStyleIndex];
    //mSprite = &gWadModels.mDartRegularMap[mStyleIndex];
    
    //mModel = &gWadModels.mDartMini[mStyleIndex];
    //mSprite = &gWadModels.mDartMiniMap[mStyleIndex];
    
    mModel = &gWadModels.mDartBat[mStyleIndex];
    mSprite = &gWadModels.mDartBatMap[mStyleIndex];
    
    //mModel = &gWadModels.mExtraLife;
    //mSprite = &gWadModels.mExtraLifeMap;
    
    //mModel = &gWadModels.mTurtle;
    //mSprite = &gWadModels.mTurtleMap;
    
    //mModel = &gWadModels.mTurtlePropeller;
    //mSprite = &gWadModels.mTurtlePropellerMap;
    
    //mModel = &gWadModels.mPrizeStar;
    //mSprite = &gWadModels.mPrizeStarMap;
    
    
    mUniform = &(gGame->mRenderer->mUniformPhong);
    //mUniform = &(gGame->mRenderer->mUniformPhongBalloon);
    
    mVelX = 0.0f;
    mVelY = 0.0f;
    
    mSpawnAnimation = false;
    mSpawnAnimationTime = 38;
    mSpawnAnimationTimer = 0;
    mSpawnAnimationDelay = 0;
    
    mPrevTipX = 0.0f;
    mPrevTipY = 0.0f;
    
    mTipX = 0.0f;
    mTipY = 0.0f;
    
    mEllipseRadiusH = 0.0f;
    mEllipseRadiusV = 0.0f;
    
    mUpdateInterpStartX = 0.0f;
    mUpdateInterpStartY = 0.0f;
    mUpdateInterpStartRotation = 0.0f;
    
    mUpdateInterpEndX = 0.0f;
    mUpdateInterpEndY = 0.0f;
    mUpdateInterpEndRotation = 0.0f;
}

Dart::~Dart() {
    //Log("Dart has died [%LX]\n", this);
}

void Dart::Update() {
    
    if (mStuck) {
        //Once we are stuck, we can NEVER SPIN, EVER AGAIN!!!
        mSpinSpeed = 0;
    } else {
        mTransform3D.mSpin += mSpinSpeed;
    }
    
    mPrevTipX = mTipX;
    mPrevTipY = mTipY;
    
    if (mSpawnAnimation) {
        
        float aSpawnAnimationPercent = ((float)mSpawnAnimationTimer) / ((float)mSpawnAnimationTime);
        
        float aPercent = FAnimation::EaseInCurve(aSpawnAnimationPercent);
        float aPercentInv = (1.0f - aPercent);
        
        //mOffsetZ = -aPercentInv * gGame->mCamera->mDistance * 0.125f;
        mTransform.mOffsetY = aPercentInv * 70.0f;
        mTransform3D.mRotationX = -aPercentInv * 220.0f;
        mTransform.mOffsetScale = 0.25f + aPercent * 0.75f;
        
        mColor.mRed = aPercent;
        mColor.mGreen = aPercent;
        mColor.mBlue = aPercent;
        mColor.mAlpha = 1.0f;
        
        if (mSpawnAnimationDelay > 0) {
            --mSpawnAnimationDelay;
        } else {
            if (++mSpawnAnimationTimer >= mSpawnAnimationTime) {
                SpawnAnimationForceComplete();
            }
        }
    }
    
    if ((mIdle == false) && (mStuck == false) && (mKnockedDown == false)) {
        mTimer++;
        
        mUpdateInterpStartX = mTransform.mX;
        mUpdateInterpStartY = mTransform.mY;
        mUpdateInterpStartRotation = mTransform.mRotation;
        
        mVelY += gGame->mGravity;
        
        if (fabsf(mVelX) > 0.001f || fabsf(mVelY) > 0.001f) {
            mTargetRotation = FaceTarget(-mVelX, -mVelY);
        }
        
        float aAngleDiff = DistanceBetweenAngles(mTransform.mRotation, mTargetRotation);
        if (aAngleDiff > 2.0f) { mTransform.mRotation += 1.0f; }
        if (aAngleDiff < -2.0f) { mTransform.mRotation -= 1.0f; }
        aAngleDiff = DistanceBetweenAngles(mTransform.mRotation, mTargetRotation);
        //mTransform.mRotation += aAngleDiff * 0.035f;
        
        mUpdateInterpEndX = mTransform.mX + mVelX;
        mUpdateInterpEndY = mTransform.mY + mVelY;
        mUpdateInterpEndRotation = mTransform.mRotation + aAngleDiff * 0.035f;
        
        --mDeathTimer;
        if (mDeathTimer <= 0) {
            gGame->DisposeObject(this);
        } else if (gGame->IsGameObjectOutsideKillZone(this)) {
            gGame->DisposeObject(this);
        }
    }
    
    if (mKnockedDown == true) {
        
        mKnockedDownColorSin += 14.0f;
        if (mKnockedDownColorSin >= 360.0f) { mKnockedDownColorSin -= 360.0f; }
        
        if (mTransform.mScale > 0.6f) {
            mTransform.mScale *= 0.985f;
            if (mTransform.mScale <= 0.6f) { mTransform.mScale = 0.6f; }
        }
        
        mTransform.mRotation += DistanceBetweenAngles(mTransform.mRotation, 180.0f) * 0.02125f;
        mTransform.mY += mVelY;
        mVelY += gGame->mGravity;
        
        float aColorSin = Sin(mKnockedDownColorSin);
        float aColorPercent = (aColorSin + 1.0f) * 0.5f; //Goes from 0 to 1...
        
        mColor.mRed = 1.0f - (aColorPercent * 0.8f);
        mColor.mGreen = 1.0f - (aColorPercent * 0.8f);
        mColor.mBlue = 1.0f - (aColorPercent * 0.8f);
        
        if (gGame->IsGameObjectOutsideKillZone(this)) {
            gGame->DisposeObject(this);
        }
    }
    
    
    GetTipPoint(mTipX, mTipY);
}

void Dart::Draw() {
    GameObject::Draw();
    
    /*
    Graphics::PipelineStateSetShape2DNoBlending();
    Graphics::SetColor(1.0f, 0.2f, 0.18f, 1.0f);
    Graphics::DrawPoint(mTipX, mTipY, 8.0f);
    */
}

void Dart::Draw3D() {
    GameObject::Draw3D();
}

void Dart::SpawnAnimation() {
    
    mSpawnAnimation = true;
    mSpawnAnimationTimer = 0;
    
    mSpawnAnimationDelay = 15;
    
    //Does one update to snap into position...
    Update();
}

void Dart::SpawnAnimationForceComplete() {
    
    if (mSpawnAnimation) {
        mSpawnAnimation = false;
        mSpawnAnimationTimer = 0;
        
        mTransform.mOffsetX = 0.0f;
        mTransform.mOffsetY = 0.0f;
        mTransform.mOffsetZ = 0.0f;
        
        mTransform.mOffsetRotation = 0.0f;
        mTransform3D.mRotationX = 0.0f;
        mTransform3D.mRotationZ = 0.0f;
        mTransform.mOffsetScale = 1.0f;
        
        mColor.mRed = 1.0f;
        mColor.mGreen = 1.0f;
        mColor.mBlue = 1.0f;
        mColor.mAlpha = 1.0f;
    }
}

void Dart::GetTipPoint(float &pTipX, float &pTipY) {
    float aScale = mTransform.mScale * mTransform.mOffsetScale;
    float aRotation = mTransform.mRotation + mTransform.mOffsetRotation;
    GetTipPoint(mTransform.mX, mTransform.mY, aScale, aRotation, pTipX, pTipY);
}

void Dart::GetTipPoint(float pCenterX, float pCenterY, float pScale, float pRotation, float &pTipX, float &pTipY) {
    float aDistFromCenter = 48.0f * pScale;
    float aDirX = Sin(pRotation);
    float aDirY = -Cos(pRotation);
    pTipX = pCenterX + aDirX * aDistFromCenter;
    pTipY = pCenterY + aDirY * aDistFromCenter;
}

void Dart::Fling(float pVelocityX, float pVelocityY) {
    if (mSpawnAnimation) {
        Log("Forcing spawn animation to complete...\n");
        SpawnAnimationForceComplete();
    }
    mIdle = false;
    mVelX = pVelocityX;
    mVelY = pVelocityY;
    
    mTargetRotation = FaceTarget(-mVelX, -mVelY);
    mTransform.mRotation = mTargetRotation;
    
    
    GetTipPoint(mTipX, mTipY);
    mPrevTipX = mTipX;
    mPrevTipY = mTipY;
}

void Dart::KnockDown() {
    mKnockedDown = true;
    mKnockedDownColorSin = 0.0f;
    
    mVelX = 0.0f;
    mVelY = 0.0f;
}


