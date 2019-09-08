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
    
    gImageBundler.StartBundle("bndl_effect_bling");
    
    mSequenceCoin[0].Load("coin_spin_01_", 0, 15);
    mSequenceCoin[1].Load("coin_spin_02_", 0, 15);
    mSequenceCoin[2].Load("coin_spin_03_", 0, 15);
    mSequenceCoin[3].Load("coin_spin_04_", 0, 15);
    mSequenceCoin[4].Load("coin_spin_05_", 0, 15);
    
    mBalloonPopMark.Load("effect_balloon_pop");
    mBalloonPopMarkSmall.Load("effect_balloon_pop_small");
    
    mWhiteStar.Load("effect_white_star");
    mWhiteStarSmall.Load("effect_white_star_small");
    
    
    gImageBundler.EndBundle();
    
    
    
    
    
    
    mAdditiveTwinkleWhiteLarge.Load("effect_twinkle_additive_white_large");
    mAdditiveTwinkleWhiteSmall.Load("effect_twinkle_additive_white_small");
    
    
    //gImageBundler.mAutoBundle = true;
    //gImageBundler.StartBundle("bndl_bblast_1");
    //mSequenceBlast1.Load("balloon_blast_01_");
    //gImageBundler.EndBundle();
    
    
    //gImageBundler.StartBundle("bndl_bblast_2");
    //mSequenceBlast2.Load("balloon_blast_02_");
    //gImageBundler.EndBundle();
    
    //gImageBundler.StartBundle("bndl_bblast_3");
    //mSequenceBlast3.Load("balloon_blast_03_");
    //gImageBundler.EndBundle();
    
    //exit(0);
    
    //printf("SEQ LOAD CNT: %d\n", mSequenceBlast1.mList.mCount);
    
    
    
    
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
    
    mSequenceCoin[0].Kill();
    mSequenceCoin[1].Kill();
    mSequenceCoin[2].Kill();
    mSequenceCoin[3].Kill();
    mSequenceCoin[4].Kill();
    
    mBalloonPopMark.Kill();
    mBalloonPopMarkSmall.Kill();
    
    mWhiteStar.Kill();
    mWhiteStarSmall.Kill();
    
}


