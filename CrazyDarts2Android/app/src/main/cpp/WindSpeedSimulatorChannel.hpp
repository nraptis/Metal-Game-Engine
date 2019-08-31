//
//  WindSpeedSimulatorChannel.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 8/29/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef WindSpeedSimulatorChannel_hpp
#define WindSpeedSimulatorChannel_hpp

#define WIND_AVAILABLE_MODE_COUNT 8


//We essentially just slowly move in the range [-7, 7]
#define WIND_MODE_SLEEPING_LIGHT 0

//We essentially just slowly move in the range [-14, 14]
#define WIND_MODE_SLEEPING_HARD 1

//Wander is very simply, the force just randomly creeps in range [-60, 60]
#define WIND_MODE_WANDER 2

//Gusting picks a direction and oscillates hard in this particular direction. [70, 100]
#define WIND_MODE_GUSTING_HARD 3

//Gusting picks a direction and oscillates slowly in this particular direction. [30, 60]
#define WIND_MODE_GUSTING_LIGHT 4

//Oscillate from at changing pace. [-30, 30]
#define WIND_MODE_OSCILLATING 5



class WindSpeedSimulatorChannel {
public:
    WindSpeedSimulatorChannel();
    ~WindSpeedSimulatorChannel();
    
    //We call this once after we are fully configured.
    void                            Realize();
    
    void                            SetMode(int pMode);
    
    void                            Update();
    
    void                            UpdateWander();
    void                            UpdateGust();
    void                            UpdateOscillate();
    
    
    void                            AddAvailableMode(int pMode);
    int                             mAvailableModeList[WIND_AVAILABLE_MODE_COUNT];
    int                             mAvailableModeListCount;
    
    int                             mMode;
    int                             mModeTimer;
    
    int                             mModeTimerMin;
    int                             mModeTimerMax;
    
    //Control for the factor of wind speed in range [-100, 100]
    float                           mForce;
    float                           mTargetForce;
    
    bool                            mWanderBiasDirection;
    float                           mWanderMin;
    float                           mWanderMax;
    float                           mWanderSpeedMin;
    float                           mWanderSpeedMax;
    
    bool                            mGustingBiasDirection;
    float                           mGustingMin;
    float                           mGustingMax;
    float                           mGustingSpeedMin;
    float                           mGustingSpeedMax;
    
    float                           mOscillatingMin;
    float                           mOscillatingMax;
    float                           mOscillatingSin;
    float                           mOscillatingSinSpeed;
    float                           mOscillatingSinTargetSpeed;
    
    float                           mOscillatingSinSpeedMin;
    float                           mOscillatingSinSpeedMax;
};



#endif /* WindSpeedSimulatorChannel_hpp */
