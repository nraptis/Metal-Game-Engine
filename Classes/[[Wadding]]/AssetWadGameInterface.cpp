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
    
    
    
    
    gImageBundler.StartBundle("bndl_game_text_1");
    gImageBundler.mKeepAllAlpha = true;
    
    mPauseButtonUp.Load("pause_button_up");
    mPauseButtonDown.Load("pause_button_down");
    
    mLivesIndicatorShadow.Load("lives_indicator_shadow");
    mLivesIndicatorFull.Load("lives_indicator_full");
    mLivesIndicatorEmpty.Load("lives_indicator_empty");
    
    mComboTextOrangeAdd5.Load("combo_text_add_orange_5");
    mComboTextOrangeAdd10.Load("combo_text_add_orange_10");
    mComboTextOrangeAdd25.Load("combo_text_add_orange_25");
    mComboTextOrangeAdd50.Load("combo_text_add_orange_50");
    mComboTextOrangeAdd75.Load("combo_text_add_orange_75");
    mComboTextOrangeAdd100.Load("combo_text_add_orange_100");
    mComboTextOrangeAdd200.Load("combo_text_add_orange_200");
    mComboTextOrangeAdd300.Load("combo_text_add_orange_300");
    mComboTextOrangeAdd400.Load("combo_text_add_orange_400");
    mComboTextOrangeAdd500.Load("combo_text_add_orange_500");
    mComboTextOrangeAdd750.Load("combo_text_add_orange_750");
    mComboTextOrangeAdd1000.Load("combo_text_add_orange_1000");
    mComboTextOrangeMult2.Load("combo_text_mult_orange_2");
    mComboTextOrangeMult3.Load("combo_text_mult_orange_3");
    mComboTextOrangeMult4.Load("combo_text_mult_orange_4");
    mComboTextOrangeMult5.Load("combo_text_mult_orange_5");
    mComboTextOrangeMult6.Load("combo_text_mult_orange_6");
    mComboTextOrangeMult7.Load("combo_text_mult_orange_7");
    mComboTextOrangeMult8.Load("combo_text_mult_orange_8");
    mComboTextOrangeMult9.Load("combo_text_mult_orange_9");
    mComboTextOrangeMult10.Load("combo_text_mult_orange_10");
    mComboTextBlueAdd5.Load("combo_text_add_blue_5");
    mComboTextBlueAdd10.Load("combo_text_add_blue_10");
    mComboTextBlueAdd25.Load("combo_text_add_blue_25");
    mComboTextBlueAdd50.Load("combo_text_add_blue_50");
    mComboTextBlueAdd75.Load("combo_text_add_blue_75");
    mComboTextBlueAdd100.Load("combo_text_add_blue_100");
    mComboTextBlueAdd200.Load("combo_text_add_blue_200");
    mComboTextBlueAdd300.Load("combo_text_add_blue_300");
    mComboTextBlueAdd400.Load("combo_text_add_blue_400");
    mComboTextBlueAdd500.Load("combo_text_add_blue_500");
    mComboTextBlueAdd750.Load("combo_text_add_blue_750");
    mComboTextBlueAdd1000.Load("combo_text_add_blue_1000");
    mComboTextBlueMult2.Load("combo_text_mult_blue_2");
    mComboTextBlueMult3.Load("combo_text_mult_blue_3");
    mComboTextBlueMult4.Load("combo_text_mult_blue_4");
    mComboTextBlueMult5.Load("combo_text_mult_blue_5");
    mComboTextBlueMult6.Load("combo_text_mult_blue_6");
    mComboTextBlueMult7.Load("combo_text_mult_blue_7");
    mComboTextBlueMult8.Load("combo_text_mult_blue_8");
    mComboTextBlueMult9.Load("combo_text_mult_blue_9");
    mComboTextBlueMult10.Load("combo_text_mult_blue_10");
    gImageBundler.mKeepAllAlpha = false;
    
    gImageBundler.EndBundle();
    
    
    
    
    gImageBundler.StartBundle("bndl_temp_menus");
    
    mGameMenuBack.Load("game_menu_back");
    
    mGameMenuButtonTextMainMenu.Load("menu_button_text_main_menu");
    mGameMenuButtonTextLevelSelect.Load("menu_button_text_level_select");
    mGameMenuButtonTextOkay.Load("menu_button_text_okay");
    mGameMenuButtonTextCancel.Load("menu_button_text_cancel");
    mGameMenuButtonTextOptions.Load("menu_button_text_options");
    mGameMenuButtonTextResume.Load("menu_button_text_resume");
    
    gImageBundler.EndBundle();
    gImageBundler.mAutoBundle = false;
    
    
    
    //Un-Bundled...
    mGameMenuGenericButtonUp.Load("game_menu_button_up");
    mGameMenuGenericButtonDown.Load("game_menu_button_down");
    
    
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
    
    
    //mFontLarge.LoadNew("fnt_osb_256_font.kern", "old_sans_black_128_", "0123456789AaBbCcDdEeFfXxYyZz ");
    //mFontSmall.LoadNew("fnt_osb_256_font.kern", "old_sans_black_64_", "0123456789AaBbCcDdEeFfXxYyZz ");
    
    //mFontLarge.LoadNew("fnt_osb_256_font.kern", "fnt_osb_128_", "0123456789AaBbCcDdEeFfXxYyZz ");
    //mFontSmall.LoadNew("fnt_osb_256_font.kern", "fnt_osb_64_", "0123456789AaBbCcDdEeFfXxYyZz ");
    
    
    
    
    //mont_heavy_64_33_scale_1.png
    //mont_heavy_128_33_scale_1.png
    //mont_heavy_256_font.kern
    
    
    //float aImageScale = 1.0f / ((float)gSpriteScale);
    
    mFontScoreLarge.mDataScale = 0.125f * gSpriteDrawScale;
    mFontScoreLarge.ApplyExpand(14.0f);
    mFontScoreLarge.SetSpaceWidth(64.0f);
    
    mFontScoreSmall.mDataScale = 0.0625f * gSpriteDrawScale;
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
    

    
    mGameMenuBack.Kill();
    
    mGameMenuGenericButtonUp.Kill();
    mGameMenuGenericButtonDown.Kill();
    
    mGameMenuButtonTextMainMenu.Kill();
    mGameMenuButtonTextLevelSelect.Kill();
    mGameMenuButtonTextOkay.Kill();
    mGameMenuButtonTextCancel.Kill();
    mGameMenuButtonTextOptions.Kill();
    mGameMenuButtonTextResume.Kill();
    
    
    
    mPauseButtonUp.Kill();
    mPauseButtonDown.Kill();
    
    mLivesIndicatorShadow.Kill();
    mLivesIndicatorFull.Kill();
    mLivesIndicatorEmpty.Kill();
    
    
    
    
    mComboTextOrangeAdd5.Kill();
    mComboTextOrangeAdd10.Kill();
    mComboTextOrangeAdd25.Kill();
    mComboTextOrangeAdd50.Kill();
    mComboTextOrangeAdd75.Kill();
    mComboTextOrangeAdd100.Kill();
    mComboTextOrangeAdd200.Kill();
    mComboTextOrangeAdd300.Kill();
    mComboTextOrangeAdd400.Kill();
    mComboTextOrangeAdd500.Kill();
    mComboTextOrangeAdd750.Kill();
    mComboTextOrangeAdd1000.Kill();
    
    mComboTextOrangeMult2.Kill();
    mComboTextOrangeMult3.Kill();
    mComboTextOrangeMult4.Kill();
    mComboTextOrangeMult5.Kill();
    mComboTextOrangeMult6.Kill();
    mComboTextOrangeMult7.Kill();
    mComboTextOrangeMult8.Kill();
    mComboTextOrangeMult9.Kill();
    mComboTextOrangeMult10.Kill();
    
    
    mComboTextBlueAdd5.Kill();
    mComboTextBlueAdd10.Kill();
    mComboTextBlueAdd25.Kill();
    mComboTextBlueAdd50.Kill();
    mComboTextBlueAdd75.Kill();
    mComboTextBlueAdd100.Kill();
    mComboTextBlueAdd200.Kill();
    mComboTextBlueAdd300.Kill();
    mComboTextBlueAdd400.Kill();
    mComboTextBlueAdd500.Kill();
    mComboTextBlueAdd750.Kill();
    mComboTextBlueAdd1000.Kill();
    
    mComboTextBlueMult2.Kill();
    mComboTextBlueMult3.Kill();
    mComboTextBlueMult4.Kill();
    mComboTextBlueMult5.Kill();
    mComboTextBlueMult6.Kill();
    mComboTextBlueMult7.Kill();
    mComboTextBlueMult8.Kill();
    mComboTextBlueMult9.Kill();
    mComboTextBlueMult10.Kill();
    
    
}

