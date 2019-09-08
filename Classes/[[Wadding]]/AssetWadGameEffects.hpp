//
//  AssetWadGameEffects.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 8/26/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef AssetWadGameEffects_hpp
#define AssetWadGameEffects_hpp

#include "AssetWad.hpp"

class AssetWadGameEffects : public AssetWad {
public:
    AssetWadGameEffects();
    ~AssetWadGameEffects();
    
    virtual void                                    Load();
    virtual void                                    Unload();
    
    FSprite                                         mAdditiveTwinkleWhiteLarge;
    FSprite                                         mAdditiveTwinkleWhiteSmall;
    
    
    FSprite                                         mBalloonPopMark;
    FSprite                                         mBalloonPopMarkSmall;
    
    FSprite                                         mWhiteStar;
    FSprite                                         mWhiteStarSmall;
    
    
    
    
    FSpriteSequence                                 mSequenceBlast1;
    FSpriteSequence                                 mSequenceBlast2;
    FSpriteSequence                                 mSequenceBlast3;
    
    
    
    FSpriteSequence                                 mSequenceCoin[5];
    
    
    //balloon_blast_01_00_scale_1.png
    //balloon_blast_01_30_scale_1.png
    //balloon_blast_02_00_scale_1.png
    //balloon_blast_02_31_scale_1.png
    //balloon_blast_03_00_scale_1.png
    //balloon_blast_03_31_scale_1.png
    
    
};

#endif /* AssetWadGameEffects_hpp */
