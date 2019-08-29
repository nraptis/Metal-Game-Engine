//
//  WindSpeedSimulator.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 8/28/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef WindSpeedSimulator_hpp
#define WindSpeedSimulator_hpp

#define WIND_BASELINE_MODE_WANDER 0
#define WIND_BASELINE_MODE_GUSTING 1

class WindSpeedSimulator {
public:
    WindSpeedSimulator();
    ~WindSpeedSimulator();
    
    void                            Update();
    
    //This will be a magnitude in the range [-1, 1]
    float                           mPower;
    
    
    int                             mBaselineMode;
    int                             mBaselineModeTick;
    
    //Control for the "Baseline" wind speed in range [-100, 100]
    float                           mBaseline;
    float                           mTargetBaseline;
    
    
    
};

#endif
