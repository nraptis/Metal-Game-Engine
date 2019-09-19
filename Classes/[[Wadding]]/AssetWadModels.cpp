//
//  AssetWadModels.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nick Raptis on 9/1/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "AssetWadModels.hpp"
#include "core_includes.h"

AssetWadModels::AssetWadModels() {
    
}

AssetWadModels::~AssetWadModels() {
    
}

void AssetWadModels::Load() {
    
    
    int aBorder = gImageBundler.mBorder;
    int aEdgeBorder = gImageBundler.mEdgeBorder;
    int aInset = gImageBundler.mInset;
    
    
    gImageBundler.mBorder = 0;
    gImageBundler.mEdgeBorder = 0;
    gImageBundler.mInset = 0;
    
    
    
    //gImageBundler.mAutoBundle = true;
    
    
    
    gImageBundler.mKeepAllAlpha = true;
    gImageBundler.StartBundle("bndl_turt_prop_billboard");
    mTurtlePropellerBillboardMapSequence.Load("propeller_whirl_", 0, 14);
    gImageBundler.EndBundle();
    gImageBundler.mKeepAllAlpha = false;
    
    
    gImageBundler.StartBundle("bndl_model_maps_01");
    mDartRegularMap[0].Load("dart_color_1_map");
    mDartRegularMap[1].Load("dart_color_2_map");
    mDartRegularMap[2].Load("dart_color_3_map");
    mDartRegularMap[3].Load("dart_color_4_map");
    gImageBundler.EndBundle();
    
    gImageBundler.StartBundle("bndl_model_maps_02");
    mDartRegularMap[4].Load("dart_color_5_map");
    mDartRegularMap[5].Load("dart_color_6_map");
    mDartMiniMap[0].Load("minidart_color_1_map");
    mDartMiniMap[1].Load("minidart_color_2_map");
    gImageBundler.EndBundle();
    
    gImageBundler.StartBundle("bndl_model_maps_03");
    mDartMiniMap[2].Load("minidart_color_3_map");
    mDartMiniMap[3].Load("minidart_color_4_map");
    mDartMiniMap[4].Load("minidart_color_5_map");
    mDartMiniMap[5].Load("minidart_color_6_map");
    gImageBundler.EndBundle();
    
    gImageBundler.StartBundle("bndl_model_maps_04");
    mDartBatMap[0].Load("batdart_color_1_map");
    mDartBatMap[1].Load("batdart_color_2_map");
    mDartBatMap[2].Load("batdart_color_3_map");
    mDartBatMap[3].Load("batdart_color_4_map");
    gImageBundler.EndBundle();
    
    gImageBundler.StartBundle("bndl_model_maps_05");
    mDartBatMap[4].Load("batdart_color_5_map");
    mDartBatMap[5].Load("batdart_color_6_map");
    mExtraLifeMap.Load("extra_life_map");
    gImageBundler.EndBundle();
    
    
    gImageBundler.StartBundle("bndl_model_maps_06");
    mTurtleMap.Load("turtle_map");
    mTurtleDamagedMap.Load("turtle_damaged_map");
    mTurtlePropellerMap.Load("turtle_propeller_map");
    mPrizeStarMap.Load("prize_star_map");
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
    
    

    
    
    
    gImageBundler.mBorder = aBorder;
    gImageBundler.mEdgeBorder = aEdgeBorder;
    gImageBundler.mInset = aInset;
    
    
    
    mDartRegular[0].LoadData("dart.3dp", &mDartRegularMap[0]);
    mDartRegular[1].LoadData("dart.3dp", &mDartRegularMap[1]);
    mDartRegular[2].LoadData("dart.3dp", &mDartRegularMap[2]);
    mDartRegular[3].LoadData("dart.3dp", &mDartRegularMap[3]);
    mDartRegular[4].LoadData("dart.3dp", &mDartRegularMap[4]);
    mDartRegular[5].LoadData("dart.3dp", &mDartRegularMap[5]);
    
    mDartMini[0].LoadData("minidart.3dp", &mDartMiniMap[0]);
    mDartMini[1].LoadData("minidart.3dp", &mDartMiniMap[1]);
    mDartMini[2].LoadData("minidart.3dp", &mDartMiniMap[2]);
    mDartMini[3].LoadData("minidart.3dp", &mDartMiniMap[3]);
    mDartMini[4].LoadData("minidart.3dp", &mDartMiniMap[4]);
    mDartMini[5].LoadData("minidart.3dp", &mDartMiniMap[5]);
    
    mDartBat[0].LoadData("bardart.3dp", &mDartBatMap[0]);
    mDartBat[1].LoadData("bardart.3dp", &mDartBatMap[1]);
    mDartBat[2].LoadData("bardart.3dp", &mDartBatMap[2]);
    mDartBat[3].LoadData("bardart.3dp", &mDartBatMap[3]);
    mDartBat[4].LoadData("bardart.3dp", &mDartBatMap[4]);
    mDartBat[5].LoadData("bardart.3dp", &mDartBatMap[5]);
    
    mExtraLife.LoadData("extra_life.3dp", &mExtraLifeMap);
    
    mPrizeStar.LoadData("brickhead_cage.3dp", &mPrizeStarMap);
    
    mTurtle.LoadData("turtle.3dp", &mTurtleMap);
    mTurtleDamaged.LoadData("turtle.3dp", &mTurtleDamagedMap);
    mTurtlePropeller.LoadData("turtle_propeller.3dp", &mTurtlePropellerMap);
    //mTurtlePropeller.LoadData("turtle_propeller.3dp", &mTurtlePropellerMap);
    //mTurtlePropeller.LoadOBJ("turtle_propeller.obj");
    
    
    //TODO: This is loading wrong model.
    
    
    //
    
    mTurtlePropellerBillboardSequence.LoadDataBillboardSequence("turtle_propeller_billboard.3dp", &mTurtlePropellerBillboardMapSequence);
    
    //turtle_propeller_billboard.3dp
    
    //FModelDataPacked aPropBBExpo;
    //aPropBBExpo.LoadOBJ("turtle_propeller_billboard.obj");
    //aPropBBExpo.Save(gDirExport + "turtle_propeller_billboard.3dm");
    
    //turtle_propeller_billboard.3dp
    
    //mTurtlePropellerBillboardSequence.LoadData("turtle_propeller_billboard.3ds");
    
    //mTurtlePropellerBillboardSequence.LoadOBJBillboardSequence("turtle_propeller_billboard.obj", &mTurtlePropellerBillboardMapSequence);
    //mTurtlePropellerBillboardSequence.Save(gDirExport + "turtle_propeller_billboard.3ds");
    
    
    
    
    //
    
    /*
    butterfly_body_19.obj
    butterfly_body_0.obj
    
    butterfly_wings_0.obj
    butterfly_wings_19.obj
    */
    
    
}

void AssetWadModels::Unload() {
    
    mDartRegularMap[0].Kill();
    mDartRegularMap[1].Kill();
    mDartRegularMap[2].Kill();
    mDartRegularMap[3].Kill();
    mDartRegularMap[4].Kill();
    mDartRegularMap[5].Kill();
    
    mDartMiniMap[0].Kill();
    mDartMiniMap[1].Kill();
    mDartMiniMap[2].Kill();
    mDartMiniMap[3].Kill();
    mDartMiniMap[4].Kill();
    mDartMiniMap[5].Kill();

    mDartBatMap[0].Kill();
    mDartBatMap[1].Kill();
    mDartBatMap[2].Kill();
    mDartBatMap[3].Kill();
    mDartBatMap[4].Kill();
    mDartBatMap[5].Kill();
    
    mExtraLifeMap.Kill();
    
    mTurtleMap.Kill();
    mTurtleDamagedMap.Kill();
    mTurtlePropellerMap.Kill();
    
    mPrizeStarMap.Kill();
    
    mTurtlePropellerBillboardMapSequence.Kill();
    
    /////////////////////////////
    //
    //Unload the models as well...
    //
    /////////////////////////////
    
    mDartRegular[0].Free();
    mDartRegular[1].Free();
    mDartRegular[2].Free();
    mDartRegular[3].Free();
    mDartRegular[4].Free();
    mDartRegular[5].Free();
    
    mDartBat[0].Free();
    mDartBat[1].Free();
    mDartBat[2].Free();
    mDartBat[3].Free();
    mDartBat[4].Free();
    mDartBat[5].Free();
    
    mDartMini[0].Free();
    mDartMini[1].Free();
    mDartMini[2].Free();
    mDartMini[3].Free();
    mDartMini[4].Free();
    mDartMini[5].Free();
    
    mExtraLife.Free();
    mTurtle.Free();
    mTurtleDamaged.Free();
    mTurtlePropeller.Free();
    mTurtlePropellerBillboardSequence.Free();
    mPrizeStar.Free();
    
    
}

