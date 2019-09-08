//
//  EffectBalloonBurst.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 8/26/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EffectBalloonBurst.hpp"
#include "GFXApp.hpp"



EffectBalloonBurst::EffectBalloonBurst() {
    
    //SetSprite(&gWadGameEffects.mAdditiveTwinkleWhiteLarge);
    
    SetSprite(&gWadGameEffects.mBalloonPopMark);
    SetDelayAlphaSpeed(200, -0.01f);
}

EffectBalloonBurst::~EffectBalloonBurst() {
    
    
}

