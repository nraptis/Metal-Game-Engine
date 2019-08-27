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
    QuickLoad("effect_twinkle_additive_white_large", &mAdditiveTwinkleWhiteLarge);
    QuickLoad("effect_twinkle_additive_white_small", &mAdditiveTwinkleWhiteSmall);
    
}

void AssetWadGameEffects::Unload() {
    mAdditiveTwinkleWhiteLarge.Kill();
    mAdditiveTwinkleWhiteSmall.Kill();
    
}


