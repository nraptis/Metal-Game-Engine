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
    
    mDeathTimer = 5000;
    mTimer = 0;
    
    mHitCount = 0;
    
    mStyleIndex = gRand.Get(5);
    mModel = &gWadModelMaps.mDartRegularModel[mStyleIndex];
    mSprite = &gWadModelMaps.mDartRegular[mStyleIndex];
    
    
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
    
    mTransform3D.mSpin += mSpinSpeed;
    //mTransform3D.mSpin = 0.0f;
    
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
    
    if (!mIdle) {
        mTimer++;
        
        //We are flying through space...
        
        mUpdateInterpStartX = mTransform.mX;
        mUpdateInterpStartY = mTransform.mY;
        mUpdateInterpStartRotation = mTransform.mRotation;
        
        //mTransform.mX += mVelX;
        //mTransform.mY += mVelY;
        
        if (mStuck == false && mKill == 0 && mIdle == false) {
            mVelY += gGame->mGravity;
        }
        
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
            gGame->DartFlyOffScreen(this);
        }
        
        if (gGame->IsGameObjectOutsideKillZone(this)) {
            printf("Kill Dart[ %f %f ]\n\n", mTransform.mX, mTransform.mY);
            gGame->DartFlyOffScreen(this);
        }
    }
    
    FVec2 aTip = GetTipPoint();
    mTipX = aTip.mX;
    mTipY = aTip.mY;
}

void Dart::Draw() {
    GameObject::Draw();
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

FVec2 Dart::GetTipPoint() {
    float aScale = mTransform.mScale * mTransform.mOffsetScale;
    float aDistFromCenter = 48.0f * (aScale);
    FVec2 aDir = AngleToVector(mTransform.mRotation + mTransform.mOffsetRotation);
    FVec2 aResult;
    aResult.mX = mTransform.mX + aDir.mX * aDistFromCenter * mTransform.mScaleX;
    aResult.mY = mTransform.mY + aDir.mY * aDistFromCenter * mTransform.mScaleY;
    return aResult;
}

void Dart::Fling(float pVelocityX, float pVelocityY) {
    if (mSpawnAnimation) {
        Log("Forcing spawn animation to complete...\n");
        SpawnAnimationForceComplete();
    }
    mIdle = false;
    mVelX = pVelocityX;
    mVelY = pVelocityY;
    
    FVec2 aTip = GetTipPoint();
    mTipX = aTip.mX;
    mTipY = aTip.mY;
    mPrevTipX = aTip.mX;
    mPrevTipY = aTip.mY;
}
