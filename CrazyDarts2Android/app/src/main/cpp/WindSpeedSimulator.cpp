//
//  WindSpeedSimulator.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 8/28/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "WindSpeedSimulator.hpp"

WindSpeedSimulator::WindSpeedSimulator() {
    mPower = 0.0f;
    mPowerTarget = 0.0f;
    
    mChannelBaseline.AddAvailableMode(WIND_MODE_SLEEPING_LIGHT);
    mChannelBaseline.AddAvailableMode(WIND_MODE_SLEEPING_HARD);
    mChannelBaseline.AddAvailableMode(WIND_MODE_SLEEPING_HARD);
    mChannelBaseline.AddAvailableMode(WIND_MODE_WANDER);
    mChannelBaseline.AddAvailableMode(WIND_MODE_WANDER);
    mChannelBaseline.AddAvailableMode(WIND_MODE_GUSTING_HARD);
    mChannelBaseline.AddAvailableMode(WIND_MODE_GUSTING_LIGHT);
    mChannelBaseline.AddAvailableMode(WIND_MODE_GUSTING_LIGHT);
    mChannelBaseline.mModeTimerMin = 380;
    mChannelBaseline.mModeTimerMax = 700;
    mChannelBaseline.Realize();
    
    mChannelFlanger.AddAvailableMode(WIND_MODE_GUSTING_HARD);
    mChannelFlanger.AddAvailableMode(WIND_MODE_GUSTING_HARD);
    mChannelFlanger.AddAvailableMode(WIND_MODE_GUSTING_LIGHT);
    mChannelFlanger.mModeTimerMin = 200;
    mChannelFlanger.mModeTimerMax = 400;
    mChannelFlanger.Realize();
    
    mChannelNoise.AddAvailableMode(WIND_MODE_GUSTING_HARD);
    mChannelNoise.AddAvailableMode(WIND_MODE_GUSTING_HARD);
    mChannelNoise.AddAvailableMode(WIND_MODE_GUSTING_LIGHT);
    mChannelNoise.AddAvailableMode(WIND_MODE_OSCILLATING);
    mChannelNoise.AddAvailableMode(WIND_MODE_OSCILLATING);
    mChannelNoise.mModeTimerMin = 100;
    mChannelNoise.mModeTimerMax = 140;
    mChannelNoise.Realize();
    
    Update();
}

WindSpeedSimulator::~WindSpeedSimulator() {
    
}

void WindSpeedSimulator::Update() {
    
    mChannelBaseline.Update();
    mChannelFlanger.Update();
    mChannelNoise.Update();
    
    float aPowerBaseline = mChannelBaseline.mForce;
    float aPowerFlanger = mChannelFlanger.mForce * 0.25f;
    float aPowerNoise = mChannelNoise.mForce * 0.125f;
    
    mPowerTarget = (aPowerBaseline + aPowerFlanger + aPowerNoise) / 135.0f;
    if (mPowerTarget > 1.0f) { mPowerTarget = 1.0f; }
    if (mPowerTarget < -1.0f) { mPowerTarget = -1.0f; }
    
    mPower += (mPowerTarget - mPower) * 0.125f;
    
}

