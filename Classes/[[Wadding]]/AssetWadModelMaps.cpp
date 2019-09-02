//
//  AssetWadModelMaps.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nick Raptis on 9/1/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "AssetWadModelMaps.hpp"
#include "core_includes.h"

AssetWadModelMaps::AssetWadModelMaps() {
    
}

AssetWadModelMaps::~AssetWadModelMaps() {
    
}

void AssetWadModelMaps::Load() {
    
    
    int aBorder = gImageBundler.mBorder;
    int aEdgeBorder = gImageBundler.mEdgeBorder;
    int aInset = gImageBundler.mInset;
    
    
    gImageBundler.mBorder = 0;
    gImageBundler.mEdgeBorder = 0;
    gImageBundler.mInset = 0;
    
    //gImageBundler.mAutoBundle = true;
    
    
    gImageBundler.StartBundle("bndl_model_maps_01");
    mDartRegular[0].Load("dart_color_1_map");
    mDartRegular[1].Load("dart_color_2_map");
    mDartRegular[2].Load("dart_color_3_map");
    mDartRegular[3].Load("dart_color_4_map");
    
    gImageBundler.StartBundle("bndl_model_maps_02");
    mDartRegular[4].Load("dart_color_5_map");
    mDartRegular[5].Load("dart_color_6_map");
    mDartMini[0].Load("minidart_color_1_map");
    mDartMini[1].Load("minidart_color_2_map");
    
    gImageBundler.StartBundle("bndl_model_maps_03");
    mDartMini[2].Load("minidart_color_3_map");
    mDartMini[3].Load("minidart_color_4_map");
    mDartMini[4].Load("minidart_color_5_map");
    mDartMini[5].Load("minidart_color_6_map");
    
    gImageBundler.StartBundle("bndl_model_maps_04");
    mDartBat[0].Load("batdart_color_1_map");
    mDartBat[1].Load("batdart_color_2_map");
    mDartBat[2].Load("batdart_color_3_map");
    mDartBat[3].Load("batdart_color_4_map");
    
    gImageBundler.StartBundle("bndl_model_maps_05");
    mDartBat[4].Load("batdart_color_5_map");
    mDartBat[5].Load("batdart_color_6_map");
    mExtraLife.Load("extra_life_map");
    
    
    gImageBundler.StartBundle("bndl_model_maps_06");
    
    mTurtle.Load("turtle_map");
    mTurtleDamaged.Load("turtle_damaged_map");
    mTurtlePropeller.Load("turtle_propeller_map");
    mPrizeStar.Load("prize_star_map");
    
    
    gImageBundler.EndBundle();
    //gImageBundler.mAutoBundle = false;
    
    //
    //
    //
    //
    //
    //
    //
    //
    
    
    
    //batdart_color_6_map
    //dart_color_4_map
    //minidart_color_6_map
    //extra_life_map
    //turtle_map
    //turtle_damaged_map
    //turtle_propeller_map
    //prize_star_map
    
    
    //gImageBundler.mA
    gImageBundler.StartBundle("bndl_score_font");
    //mFontScoreLarge.LoadNew("fnt_mh_256_font.kern", "mont_heavy_128_", "0123456789+-.,");
    //mFontScoreSmall.LoadNew("fnt_mh_256_font.kern", "mont_heavy_64_", "0123456789+-.,");
    gImageBundler.EndBundle();
    
    
    
    gImageBundler.mBorder = aBorder;
    gImageBundler.mEdgeBorder = aEdgeBorder;
    gImageBundler.mInset = aInset;
    
    
    
    
    
    mDartRegularModel[0].LoadData("dart.3dp", &mDartRegular[0]);
    mDartRegularModel[1].LoadData("dart.3dp", &mDartRegular[1]);
    mDartRegularModel[2].LoadData("dart.3dp", &mDartRegular[2]);
    mDartRegularModel[3].LoadData("dart.3dp", &mDartRegular[3]);
    mDartRegularModel[4].LoadData("dart.3dp", &mDartRegular[4]);
    mDartRegularModel[5].LoadData("dart.3dp", &mDartRegular[5]);
}

void AssetWadModelMaps::Unload() {
    
    mDartRegular[0].Kill();
    mDartRegular[1].Kill();
    mDartRegular[2].Kill();
    mDartRegular[3].Kill();
    mDartRegular[4].Kill();
    mDartRegular[5].Kill();
    
    
    mDartMini[0].Kill();
    mDartMini[1].Kill();
    mDartMini[2].Kill();
    mDartMini[3].Kill();
    mDartMini[4].Kill();
    mDartMini[5].Kill();

    mDartBat[0].Kill();
    mDartBat[1].Kill();
    mDartBat[2].Kill();
    mDartBat[3].Kill();
    mDartBat[4].Kill();
    mDartBat[5].Kill();
    
    
    mExtraLife.Kill();
    
    mTurtle.Kill();
    mTurtleDamaged.Kill();
    mTurtlePropeller.Kill();
    
    mPrizeStar.Kill();
    
    //batdart_color_6_map
    //dart_color_4_map
    //minidart_color_6_map
    //extra_life_map
    //turtle_map
    //turtle_damaged_map
    //turtle_propeller_map
    //prize_star_map
    
    
}

