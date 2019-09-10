//
//  EffectBalloonBurst.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 8/26/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef EffectBalloonBurst_hpp
#define EffectBalloonBurst_hpp

#include "FParticle.hpp"

#define BALLOON_BURST_SLICE_COUNT 3

class EffectBalloonBurst : public FObject {
    
public:
    EffectBalloonBurst();
    virtual ~EffectBalloonBurst();
    
    
    virtual void                                Update() override;
    virtual void                                Draw() override;
    
    float                                       mX;
    float                                       mY;
    
    int                                         mMainMode;
    int                                         mMainKill;
    float                                       mMainScale;
    float                                       mMainScaleSpeed;
    float                                       mMainScaleDownAccel;
    float                                       mMainRotation;
    float                                       mMainRotationSpeed;
    float                                       mMainRotationAccel;
    
    
    
    int                                         mSliceKill[BALLOON_BURST_SLICE_COUNT];
    
    float                                       mSliceOffsetX[BALLOON_BURST_SLICE_COUNT];
    float                                       mSliceOffsetY[BALLOON_BURST_SLICE_COUNT];
    float                                       mSliceRotation[BALLOON_BURST_SLICE_COUNT];
    float                                       mSliceScale[BALLOON_BURST_SLICE_COUNT];
    float                                       mSliceScaleSpeed[BALLOON_BURST_SLICE_COUNT];
    
    
    
    
    
    
};

#endif /* EffectBalloonBurst_hpp */
