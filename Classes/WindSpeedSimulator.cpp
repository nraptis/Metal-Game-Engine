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
    
    mBaselineMode = WIND_BASELINE_MODE_WANDER;
    mBaselineModeTick = 1000;
    mBaseline = 0;
    mTargetBaseline = 30;
}


WindSpeedSimulator::~WindSpeedSimulator() {
    
}

void WindSpeedSimulator::Update() {
    
    
}

