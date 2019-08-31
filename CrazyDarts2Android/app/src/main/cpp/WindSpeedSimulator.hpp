//
//  WindSpeedSimulator.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 8/28/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef WindSpeedSimulator_hpp
#define WindSpeedSimulator_hpp

#include "WindSpeedSimulatorChannel.hpp"

class WindSpeedSimulator {
public:
    WindSpeedSimulator();
    ~WindSpeedSimulator();
    
    void                            Update();
    
    //This will be a magnitude in the range [-1, 1]
    float                           mPower;
    float                           mPowerTarget;
    
    
    WindSpeedSimulatorChannel       mChannelBaseline;
    WindSpeedSimulatorChannel       mChannelFlanger;
    WindSpeedSimulatorChannel       mChannelNoise;
    
};

#endif
