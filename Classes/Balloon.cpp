//
//  Balloon.cpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/14/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#include "Balloon.hpp"
#include "Game.hpp"

Balloon::Balloon() {
    
    mGameObjectType = GAME_OBJECT_TYPE_BALLOON;
    
    mSpinSpeed = gRand.GetFloat(0.25f, 0.45f, true);
    mSpinSpeed = gRand.GetFloat(0.65f, 1.5f, true);
    
    //if (gRand.GetBool()) mSpinSpeed = -mSpinSpeed;
    
    
    mModel = &gApp->mBalloon;
    mSprite = &gApp->mBalloonMap[gRand.Get(5)];
    mUniform = &(gGame->mRenderer->mUniformPhongBalloon);
    
    mVelX = 0.0f;
    mVelY = 0.0f;
    
    mTagged = false;
    
    mTilt = 0.0f;
    
    mThread.Setup();
    mIsThreadVisible = true;
    
    mBounceFactor = 0.0f;
    mBounceFactorSin = 0.0f;
    
    
    mThread.Setup();
}

Balloon::~Balloon() {
    //Log("Balloon has died [%LX]\n", this);
}

void Balloon::Update() {
    
    GameObject::Update();
    
    mTransform3D.mSpin += mSpinSpeed;
    mTransform3D.mRotationX = mTilt;
    
    if (mFloatAway == false) {
        mTransform.mX += mVelX;
        mTransform.mY += mVelY;
    }
    
    
    mBounceFactorSin -= 1.5f;
    if (mBounceFactorSin < 0.0f) { mBounceFactorSin += 360.0f; }
    
    mBounceFactor = Sin(mBounceFactorSin);
}

void Balloon::Draw() {
    GameObject::Draw();
}

void Balloon::Draw3D() {
    
    
    if (mTagged) {
        mTransform.mOffsetRotation = 90.0f;
    }
    
    //aNormal.SetNormalMatrix(aModelView);
    //((FUniformsLightPhong *)mUniform)->mLight.mShininess = 58.0f;
    //((FUniformsLightPhong *)mUniform)->mLight.mSpecularIntensity = 1.0f;
    
    GameObject::Draw3D();
}

void Balloon::Draw3DThread() {
    
    
    
    gGame->Convert2DTransformTo3D(&mTransform, &mTransform3D);
    
    FVec3 aCenter = FVec3(mTransform3D.mX, mTransform3D.mY, mTransform3D.mZ);
    FVec3 aPos = aCenter;
    aPos.mY += 2.15f;
    
    aPos = PivotPoint(aPos, mTransform.mRotation, aCenter);
    
    mThread.mOffsetX = aPos.mX;
    mThread.mOffsetY = aPos.mY;
    mThread.mOffsetZ = 0.0f;
    
    mThread.Generate(gGame->mWind.mPower, 0.0f);
    mThread.Draw3D();
}
