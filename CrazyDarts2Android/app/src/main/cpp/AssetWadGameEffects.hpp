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
    
};

#endif /* AssetWadGameEffects_hpp */
