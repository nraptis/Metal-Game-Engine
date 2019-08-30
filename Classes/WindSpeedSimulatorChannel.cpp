//
//  WindSpeedSimulatorChannel.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 8/29/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "WindSpeedSimulatorChannel.hpp"
#include "core_includes.h"

WindSpeedSimulatorChannel::WindSpeedSimulatorChannel() {
    mMode = -1;
    mModeTimer = 0;
    mModeTimerMin = 380;
    mModeTimerMax = 700;
    mForce = 0.0f;
    mTargetForce = mForce;
    for (int i=0;i<WIND_AVAILABLE_MODE_COUNT;i++) { mAvailableModeList[i] = 0; }
    mAvailableModeListCount = 0;
}

WindSpeedSimulatorChannel::~WindSpeedSimulatorChannel() {
    
}

void WindSpeedSimulatorChannel::Realize() {
    SetMode(mAvailableModeList[gRand.Get(mAvailableModeListCount)]);
}

void WindSpeedSimulatorChannel::SetMode(int pMode) {
    mMode = pMode;
    mModeTimer = gRand.Get(mModeTimerMin, mModeTimerMax);
    if (mMode == WIND_MODE_SLEEPING_LIGHT) {
        //We essentially just slowly move in the range [-7, 7]
        mWanderMin = -7.0f;
        mWanderMax = 7.0f;
        mWanderSpeedMin = 0.045f;
        mWanderSpeedMax = 0.0875;
        mWanderBiasDirection = gRand.GetBool();
        if (mTargetForce < mWanderMin) { mTargetForce = mWanderMin; }
        if (mTargetForce > mWanderMax) { mTargetForce = mWanderMax; }
    } else if (mMode == WIND_MODE_SLEEPING_HARD) {
        //We essentially just slowly move in the range [-14, 14]
        mWanderMin = -14.0f;
        mWanderMax = 14.0f;
        mWanderSpeedMin = 0.075f;
        mWanderSpeedMax = 0.1465f;
        mWanderBiasDirection = gRand.GetBool();
        if (mTargetForce < mWanderMin) { mTargetForce = mWanderMin; }
        if (mTargetForce > mWanderMax) { mTargetForce = mWanderMax; }
    } else if (mMode == WIND_MODE_WANDER) {
        //Wander is very simply, the force just randomly creeps in range [-60, 60]
        mGustingBiasDirection = gRand.GetBool();
        mWanderMin = -60.0f;
        mWanderMax = 60.0f;
        mWanderSpeedMin = 0.125;
        mWanderSpeedMax = 0.215;
        mWanderBiasDirection = gRand.GetBool();
        if (mTargetForce < mWanderMin) { mTargetForce = mWanderMin; }
        if (mTargetForce > mWanderMax) { mTargetForce = mWanderMax; }
    } else if (mMode == WIND_MODE_GUSTING_HARD) {
        //Gusting picks a direction and oscillates hard in this particular direction. [70, 100]
        mGustingBiasDirection = gRand.GetBool();
        mGustingMin = 70.0f;
        mGustingMax = 100.0f;
        mGustingSpeedMin = 0.125;
        mGustingSpeedMax = 0.215;
        if (gRand.GetBool()) {
            mGustingMin = -100.0f;
            mGustingMax = -70.0f;
        }
    } else if (mMode == WIND_MODE_GUSTING_LIGHT) {
        //Gusting picks a direction and oscillates slowly in this particular direction. [30, 60]
        mGustingBiasDirection = gRand.GetBool();
        mGustingMin = 30.0f;
        mGustingMax = 60.0f;
        mGustingSpeedMin = 0.125;
        mGustingSpeedMax = 0.215;
        if (gRand.GetBool()) {
            mGustingMin = -60.0f;
            mGustingMax = -30.0f;
        }
    } else if (mMode == WIND_MODE_OSCILLATING) {
        //Oscillate from at changing pace. [-30, 30]
        mOscillatingMin = -30.0f;
        mOscillatingMax = 30.0f;
        mOscillatingSin = gRand.GetRotation();
        mOscillatingSinSpeedMin = 1.25f;
        mOscillatingSinSpeedMax = 2.5f;
        mOscillatingSinSpeed = gRand.GetFloat(mOscillatingSinSpeedMin, mOscillatingSinSpeedMax);
        mOscillatingSinTargetSpeed = mOscillatingSinSpeed;
    }
}

void WindSpeedSimulatorChannel::Update() {
    mModeTimer--;
    if (mModeTimer <= 0) { SetMode(mAvailableModeList[gRand.Get(mAvailableModeListCount)]); }
    if (mMode == WIND_MODE_SLEEPING_LIGHT) {
        UpdateWander();
    } else if (mMode == WIND_MODE_SLEEPING_HARD) {
        UpdateWander();
    } else if (mMode == WIND_MODE_WANDER) {
        UpdateWander();
    } else if (mMode == WIND_MODE_GUSTING_HARD) {
        UpdateGust();
    } else if (mMode == WIND_MODE_GUSTING_LIGHT) {
        UpdateGust();
    } else if (mMode == WIND_MODE_OSCILLATING) {
        UpdateOscillate();
    }
    mForce += (mTargetForce - mForce) * 0.025f;
}

void WindSpeedSimulatorChannel::UpdateWander() {
    if (gRand.Get(120) == 20) { mWanderBiasDirection = gRand.GetBool(); }
    float aSpeed = gRand.GetFloat(mWanderSpeedMin, mWanderSpeedMax);
    if (mWanderBiasDirection == true) {
        if (gRand.Get(3) == 1) { aSpeed = -aSpeed; }
    } else {
        if (gRand.Get(3) != 1) { aSpeed = -aSpeed; }
    }
    mTargetForce += aSpeed;
    if (mTargetForce < mWanderMin) { mTargetForce += (mWanderMin - mTargetForce) * 0.045f; }
    if (mTargetForce > mWanderMax) { mTargetForce -= (mTargetForce - mWanderMin) * 0.045f; }
}

void WindSpeedSimulatorChannel::UpdateGust() {
    if (gRand.Get(60) == 20) { mGustingBiasDirection = gRand.GetBool(); }
    float aSpeed = gRand.GetFloat(mGustingSpeedMin, mGustingSpeedMax);
    if (mGustingBiasDirection == true) {
        if (gRand.Get(3) == 1) { aSpeed = -aSpeed; }
    } else {
        if (gRand.Get(3) != 1) { aSpeed = -aSpeed; }
    }
    mTargetForce += aSpeed;
    if (mTargetForce < mGustingMin) { mTargetForce += (mGustingMin - mTargetForce) * 0.045f; }
    if (mTargetForce > mGustingMax) { mTargetForce -= (mTargetForce - mGustingMax) * 0.045f; }
}

void WindSpeedSimulatorChannel::UpdateOscillate() {
    
    if (gRand.Get(180) == 40) { mOscillatingSinTargetSpeed = gRand.GetFloat(mOscillatingSinSpeedMin, mOscillatingSinSpeedMax); }
    mOscillatingSinSpeed += (mOscillatingSinTargetSpeed - mOscillatingSinSpeed) * 0.0075f;
    mOscillatingSin += mOscillatingSinSpeed;
    if (mOscillatingSin >= 360.0f) { mOscillatingSin -= 360.0f; }
    float aForce = (1.0f + Sin(mOscillatingSin)) * 0.5f;
    aForce = mOscillatingMin + (mOscillatingMax - mOscillatingMin) * aForce;
    if (mTargetForce < aForce) { mTargetForce += (aForce - mTargetForce) * 0.075f; }
    if (mTargetForce > aForce) { mTargetForce -= (mTargetForce - aForce) * 0.075f; }
}

void WindSpeedSimulatorChannel::AddAvailableMode(int pMode) {
    if (mAvailableModeListCount < WIND_AVAILABLE_MODE_COUNT) {
        mAvailableModeList[mAvailableModeListCount++] = pMode;
    }
}




