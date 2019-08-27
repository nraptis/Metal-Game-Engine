//
//  EffectDartFadeStar.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 8/26/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EffectDartFadeStar.hpp"
#include "GFXApp.hpp"

EffectDartFadeStar::EffectDartFadeStar() {
    
    
    SetSprite(&gWadGameEffects.mAdditiveTwinkleWhiteLarge);
    SetDelayAlphaSpeed(200, -0.01f);
    
}

EffectDartFadeStar::~EffectDartFadeStar() {
    
    
}

