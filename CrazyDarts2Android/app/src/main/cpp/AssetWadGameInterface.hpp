//
//  AssetWadGameInterface.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 8/24/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef AssetWadGameInterface_hpp
#define AssetWadGameInterface_hpp

#include "AssetWad.hpp"

class AssetWadGameInterface : public AssetWad {
public:
    AssetWadGameInterface();
    ~AssetWadGameInterface();
    
    virtual void                                    Load();
    virtual void                                    Unload();
    
    FSprite                                         mSpriteTest;
    
    
    FSprite                                         mMenuButton;
    FSprite                                         mMenuButtonDown;
    
    //FFont                                           mFontLarge;
    //FFont                                           mFontSmall;
    
    FFont                                           mFontScoreLarge;
    FFont                                           mFontScoreSmall;
    
    
    //FFont                                           mFontSystem;
    
    
    //candy_beans_256_font.kern
    //fnt_cb_256_font.kern
    //fnt_mh_256_font.kern
    //fnt_osb_256_font.kern
    //mont_heavy_256_font.kern
    //old_sans_black_256_font.kern
    
    /*
    fnt_cb_64
    fnt_cb_128
    fnt_mh_64
    fnt_mh_128
    fnt_osb_64
    fnt_osb_128
    
    candy_beans_64
    candy_beans_128
    mont_heavy_64
    mont_heavy_128
    old_sans_black_64
    old_sans_black_128
    */
    
    
    
};


#endif /* AssetWadGameInterface_hpp */
