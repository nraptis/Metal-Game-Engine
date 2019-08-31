//
//  AssetWadGameEffects.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 8/26/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "AssetWadGameEffects.hpp"

AssetWadGameEffects::AssetWadGameEffects() {
    
}

AssetWadGameEffects::~AssetWadGameEffects() {
    
}

void AssetWadGameEffects::Load() {
    
    mAdditiveTwinkleWhiteLarge.Load("effect_twinkle_additive_white_large");
    mAdditiveTwinkleWhiteSmall.Load("effect_twinkle_additive_white_small");
    
}

void AssetWadGameEffects::Unload() {
    mAdditiveTwinkleWhiteLarge.Kill();
    mAdditiveTwinkleWhiteSmall.Kill();
    
}


