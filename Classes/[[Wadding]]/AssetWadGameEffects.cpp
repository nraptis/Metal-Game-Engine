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
    
    mSequenceBlast1.Load("balloon_blast_01_");
    mSequenceBlast2.Load("balloon_blast_02_");
    mSequenceBlast3.Load("balloon_blast_03_");
    
    
    printf("SEQ LOAD CNT: %d\n", mSequenceBlast1.mList.mCount);
    
    
    
    
    //FSpriteSequence mSequenceBlast1;
    //FSpriteSequence mSequenceBlast2;
    //FSpriteSequence mSequenceBlast3;
    
    
    //balloon_blast_01_00_scale_1.png
    //balloon_blast_01_30_scale_1.png
    //balloon_blast_02_00_scale_1.png
    //balloon_blast_02_31_scale_1.png
    //balloon_blast_03_00_scale_1.png
    //balloon_blast_03_31_scale_1.png
    
    
}

void AssetWadGameEffects::Unload() {
    mAdditiveTwinkleWhiteLarge.Kill();
    mAdditiveTwinkleWhiteSmall.Kill();
    
    
}


