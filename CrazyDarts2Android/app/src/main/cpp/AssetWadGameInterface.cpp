//
//  AssetWadGameInterface.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 8/24/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "AssetWadGameInterface.hpp"


AssetWadGameInterface::AssetWadGameInterface() {
    
}

AssetWadGameInterface::~AssetWadGameInterface() {
    
}

void AssetWadGameInterface::Load() {
    
    mSpriteTest.Load("demo_sprite");
    
    mMenuButton.Load("pause_button_up");
    mMenuButtonDown.Load("pause_button_up");
    
    
    //mFontLarge.LoadNew("candy_beans_256_font.kern", "fnt_cb_128_", "0123456789AaBbCcDdEeFfXxYyZz ");
    //mFontSmall.LoadNew("candy_beans_256_font.kern", "fnt_cb_64_", "0123456789AaBbCcDdEeFfXxYyZz ");
    
    //These have incorrect spacing...
    //mFontLarge.LoadNew("fnt_mh_256_font.kern", "fnt_mh_128_", "0123456789AaBbCcDdEeFfXxYyZz ");
    //mFontSmall.LoadNew("fnt_mh_256_font.kern", "fnt_mh_64_", "0123456789AaBbCcDdEeFfXxYyZz ");
    
    
    //These have approximately correct spacing...
    
    //gImageBundler.mAutoBundle = true;
    //gImageBundler.mBorder = 2;
    
    
    //gImageBundler.StartBundle("gi_fonts");
    //mFontLarge.LoadNew("fnt_mh_256_font.kern", "mont_heavy_128_", "0123456789AaBbCcDdEeFfXxYyZz ");
    //mFontSmall.LoadNew("fnt_mh_256_font.kern", "mont_heavy_64_", "0123456789AaBbCcDdEeFfXxYyZz ");
    //gImageBundler.EndBundle();
    
    gImageBundler.StartBundle("bndl_score_font");
    mFontScoreLarge.LoadNew("fnt_mh_256_font.kern", "mont_heavy_128_", "0123456789+-.,");
    mFontScoreSmall.LoadNew("fnt_mh_256_font.kern", "mont_heavy_64_", "0123456789+-.,");
    gImageBundler.EndBundle();
    
    //mFontLarge.LoadNew("fnt_mh_256_font.kern", "mont_heavy_128_", "0123456789AaBbCcDdEeFfXxYyZz ");
    //mFontSmall.LoadNew("fnt_mh_256_font.kern", "mont_heavy_64_", "0123456789AaBbCcDdEeFfXxYyZz ");
    
    //gImageBundler.mAutoBundle = true;
    //gImageBundler.StartBundle("bndl_sys_font");
    
    //mFontSystem.LoadNew("fnt_mh_256_font.kern", "sys_font_");
    
    //gImageBundler.EndBundle();
    
    //sys_font_
    
    //exit(0);
    
    //mFontLarge.LoadNew("fnt_osb_256_font.kern", "old_sans_black_128_", "0123456789AaBbCcDdEeFfXxYyZz ");
    //mFontSmall.LoadNew("fnt_osb_256_font.kern", "old_sans_black_64_", "0123456789AaBbCcDdEeFfXxYyZz ");
    
    //mFontLarge.LoadNew("fnt_osb_256_font.kern", "fnt_osb_128_", "0123456789AaBbCcDdEeFfXxYyZz ");
    //mFontSmall.LoadNew("fnt_osb_256_font.kern", "fnt_osb_64_", "0123456789AaBbCcDdEeFfXxYyZz ");
    
    
    
    
    //mont_heavy_64_33_scale_1.png
    //mont_heavy_128_33_scale_1.png
    //mont_heavy_256_font.kern
    
    
    //float aImageScale = 1.0f / ((float)gSpriteScale);
    float aImageScale = (float)gSpriteScale;
    
    
    mFontScoreLarge.mDataScale = 0.125f * aImageScale;
    mFontScoreLarge.ApplyExpand(14.0f);
    mFontScoreLarge.SetSpaceWidth(64.0f);
    
    mFontScoreSmall.mDataScale = 0.0625f * aImageScale;
    mFontScoreSmall.ApplyExpand(14.0f);
    mFontScoreSmall.SetSpaceWidth(64.0f);
    
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
    
}

void AssetWadGameInterface::Unload() {
    
    mFontScoreLarge.Kill();
    mFontScoreSmall.Kill();
    
    mSpriteTest.Kill();
    
    mMenuButton.Kill();
    mMenuButtonDown.Kill();
    
}

