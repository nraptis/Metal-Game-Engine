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
    
    mSpinSpeed = gRand.GetFloat(1.25f, 1.45f);
    if (gRand.GetBool()) mSpinSpeed = -mSpinSpeed;
    
    //While we are "idle" we have not yet been released
    //and are sitting at the lower center of the screen...
    mIdle = true;
    
    mDeathTimer = 5000;
    mTimer = 0;
    
    //mModel = &gApp->mDart;
    //mSprite = &gApp->mDartMap;
    mUniform = &(gGame->mRenderer->mUniformPhong);
    
    mVelX = 0.0f;
    mVelY = 0.0f;
    
    mSpawnAnimation = false;
    mSpawnAnimationTime = 38;
    mSpawnAnimationTimer = 0;
    mSpawnAnimationDelay = 0;
}

Dart::~Dart() {
    //Log("Dart has died [%LX]\n", this);
}

void Dart::Update() {
    mSpin += mSpinSpeed;
    if (mSpawnAnimation) {
        
        float aSpawnAnimationPercent = ((float)mSpawnAnimationTimer) / ((float)mSpawnAnimationTime);
        
        float aPercent = FAnimation::EaseInCurve(aSpawnAnimationPercent);
        float aPercentInv = (1.0f - aPercent);
        
        mOffsetZ = -aPercentInv * gGame->mCamera->mDistance * 0.125f;
        mOffsetY = aPercentInv * gGame->mCamera->mDistance * 0.1f;
        
        mOffsetRotationX = -aPercentInv * 220.0f;
        mOffsetScale = 0.25f + aPercent * 0.75f;
        
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
        mX += mVelX;
        mY += mVelY;
        mVelY += gGame->mGravity;
        //
        if (fabsf(mVelX) > 0.001f || fabsf(mVelY) > 0.001f) {
            mTargetRotation = FaceTarget(-mVelX, -mVelY);
        }
        //
        float aAngleDiff = DistanceBetweenAngles(mRotation2D, mTargetRotation);
        if (aAngleDiff > 2.0f) { mRotation2D += 1.0f; }
        if (aAngleDiff < -2.0f) { mRotation2D -= 1.0f; }
        aAngleDiff = DistanceBetweenAngles(mRotation2D, mTargetRotation);
        mRotation2D += aAngleDiff * 0.035f;
        //
        --mDeathTimer;
        if (mDeathTimer <= 0) { Kill(); }
        
        if (gGame->IsGameObjectOutsideKillZone(this)) {
            Kill();
        }
    }
}

void Dart::Draw() {
    
    Graphics::PipelineStateSetShape2DNoBlending();
    Graphics::SetColor(0.5f, 0.8f, 0.25f, 0.5f);
    
    FVec2 aConverted = gGame->ConvertSceneCoordsToScreen(mX, mY);
    Graphics::DrawPoint(aConverted.mX, aConverted.mY);
    
    FVec2 aTipPoint = GetTipPoint();
    aTipPoint = gGame->ConvertSceneCoordsToScreen(aTipPoint.mX, aTipPoint.mY);
    
    Graphics::SetColor(1.0f, 0.25f, 0.25f, 0.5f);
    
    
    //FVec2 aConverted = gGame->ConvertSceneCoordsToScreen(mX, mY);
    Graphics::DrawPoint(aTipPoint.mX, aTipPoint.mY);
    
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
        
        mOffsetX = 0.0f;
        mOffsetY = 0.0f;
        mOffsetZ = 0.0f;
        
        mOffsetRotation2D = 0.0f;
        
        mOffsetRotationX = 0.0f;
        mOffsetRotationZ = 0.0f;
        
        mOffsetScale = 1.0f;
        
        mColor.mRed = 1.0f;
        mColor.mGreen = 1.0f;
        mColor.mBlue = 1.0f;
        mColor.mAlpha = 1.0f;
    }
}

FVec2 Dart::GetTipPoint() {
    float aDistFromCenter = 2.125f * (mScale * mOffsetScale);
    FVec2 aDir = AngleToVector(mRotation2D + mOffsetRotation2D);
    FVec2 aResult;
    aResult.mX = mX + aDir.mX * aDistFromCenter * mScaleX;
    aResult.mY = mY + aDir.mY * aDistFromCenter * mScaleY;
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
}
