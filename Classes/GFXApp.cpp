//
//  GFXApp.cpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/29/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

//#include "MetalEngine.h"

#include "core_app_shell.hpp"
#include "GFXApp.hpp"
#include "FormationCollection.hpp"

#include "LevelSelectorScreen.hpp"
#include "LightConfigurationScene.hpp"
#include "WorldConfigScene.hpp"

#include "Balloon.hpp"
#include "Util_ScreenFrame.h"
#include "Game.hpp"
#include "GameContainer.hpp"
#include "CameraMenu.hpp"

#include "SoundConfigMenu.hpp"
#include "AssetConfigMenu.hpp"

#ifdef EDITOR_MODE
class GameEditor;
#include "GameEditor.hpp"
#endif

AssetWadGameInterface gWadGameInterface;
AssetWadGameEffects gWadGameEffects;
AssetWadModels gWadModels;

GFXApp *gApp = 0;
GFXApp::GFXApp() {
    
    gApp = this;
    
//#ifndef EDITOR_MODE
    
    mDarkMode = true;
    
//#endif
    
#ifdef EDITOR_MODE
    mEditor = NULL;
    
    mEditorSwitchType = 0;
    mEditorSwitchTimer = 0;
    
#endif
    
    mGameContainer = NULL;
    mLevelSelect = NULL;
    mLightScene = NULL;
    mWorldScene = NULL;
    
    mScreenTool = NULL;
    mCameraMenu = NULL;
    mSoundMenu = NULL;
    mAssetMenu = NULL;
    
    mLoadGame = 12;
    
    mWadReloadIsEnqueued = false;
    mWadReloadOnNextDraw = false;
    mWadReloadTimer = 0;
    
}

GFXApp::~GFXApp() {
    
}

void GFXApp::Load() {
    
    gWadConfiguration.NotifyVirtualFrameChange();
    
    
    /*
    
    FModelDataPacked aExportModel;
    aExportModel.LoadOBJ("bardart.obj");
    aExportModel.Save(gDirExport + FString("bardart.3dp"));
    
    aExportModel.LoadOBJ("minidart.obj");
    aExportModel.Save(gDirExport + FString("minidart.3dp"));
    
    exit(0);
    
    */
    
    //mDart.LoadOBJ("dart.obj");
    
    //mDart.LoadData("dart.3dp");
    
    
    //mDart.Save(gDirExport + FString("dart.3dp"));
    
    
    
    ///
    ///  TODO: Temp Font Load Stuff...
    
    //   TODO: Need fnt data exported as XML, not flat file...
    
    /*
    
    FFontImportData *aData1 = FFont::BitmapDataImport("candy_beans_256.fnt", "candy_beans_256_0.png", 0, 16, 48);
    FFont::BitmapDataExportTestStrips(aData1, "fnt_cb_256_");
    FFont::BitmapDataExportGlyphs(aData1, "fnt_cb_256_");
    FFont::BitmapDataExportData(aData1, "fnt_cb_256_");
     
    FFontImportData *aData2 = FFont::BitmapDataImport("mont_heavy_256.fnt", "mont_heavy_256_0.png", 0, 16, 48);
    FFont::BitmapDataExportTestStrips(aData2, "fnt_mh_256_");
    FFont::BitmapDataExportGlyphs(aData2, "fnt_mh_256_");
    FFont::BitmapDataExportData(aData2, "fnt_mh_256_");
    
    FFontImportData *aData3 = FFont::BitmapDataImport("old_sans_black_256.fnt", "old_sans_black_256_0.png", 0, 16, 48);
    FFont::BitmapDataExportTestStrips(aData3, "fnt_osb_256_");
    FFont::BitmapDataExportGlyphs(aData3, "fnt_osb_256_");
    FFont::BitmapDataExportData(aData3, "fnt_osb_256_");
    
    */
    
    /*
    FFontImportData *aData4 = FFont::BitmapDataImport("roboto_260.fnt", "roboto_260_0.png", 0, 16, 0);
    FFont::BitmapDataExportGlyphs(aData4, "roboto_260_");
    FFont::BitmapDataExportData(aData4, "roboto_260_");
    
    
    FFontImportData *aData5 = FFont::BitmapDataImport("roboto_bold_260.fnt", "roboto_bold_260_0.png", 0, 16, 0);
    FFont::BitmapDataExportGlyphs(aData5, "roboto_bold_260_");
    FFont::BitmapDataExportData(aData5, "roboto_bold_260_");
    
    
    
    
    
    FFontImportData *aData6 = FFont::BitmapDataImport("roboto_300.fnt", "roboto_300_0.png", 0, 16, 0);
    FFont::BitmapDataExportGlyphs(aData6, "roboto_300_");
    FFont::BitmapDataExportData(aData6, "roboto_300_");
    
    
    FFontImportData *aData7 = FFont::BitmapDataImport("roboto_bold_300.fnt", "roboto_bold_300_0.png", 0, 16, 0);
    FFont::BitmapDataExportGlyphs(aData7, "roboto_bold_300_");
    FFont::BitmapDataExportData(aData7, "roboto_bold_300_");
    
    
    exit(0);
    */
    
    mPalmTrunk.LoadOBJ("palm_tree_trunk_01.obj");
    mPalmTrunkMap.Load("palm_tree_trunk_01_map_1024");
    
    mPalmLeaves.LoadOBJ("palm_tree_leaves_01.obj");
    mPalmLeavesMap.Load("palm_tree_leaves_01_map_1024");
    
    mGround.LoadOBJ("ground.obj");
    mGroundMixedMap.Load("ground_mixed_map");
    mGroundGreenMap.Load("ground_green_map");
    
    mSpiralPineStump.LoadOBJ("tree_stump_wide_01.obj");
    mSpiralPineStumpMap.Load("tree_stump_wide_01_map");
    
    mSpiralPineTree.LoadOBJ("tree_pine_spiral_01.obj");
    mSpiralPineTreeMap.Load("tree_pine_spiral_01_map");
    
    mMonolith.LoadOBJ("monolith.obj");
    mMonolithMap.Load("monolith_map");
    
    //mDart.LoadOBJ("dart.obj");
    
    //mDart.LoadData("dart.3dp");
    
    
    //mDart.Save(gDirExport + FString("dart.3dp"));

    
    mBalloon.LoadOBJ("balloon.obj");
    mBalloonMap[0].Load("balloon_skin_01");
    mBalloonMap[1].Load("balloon_skin_02");
    mBalloonMap[2].Load("balloon_skin_03");
    mBalloonMap[3].Load("balloon_skin_04");
    mBalloonMap[4].Load("balloon_skin_05");
    
    mBrickhead.LoadOBJ("brickhead.obj");
    mBrickheadMap.Load("brickhead_uvw");
    
    mBrickheadCage.LoadOBJ("brickhead_cage.obj");
    mBrickheadCageMap.Load("brickhead_cage_uvw");
    
    
    ExecuteWadReload();
    
    
    mSoundBalloonPop.Load("balloon_pop_1", 3);
    //balloon_pop_1
    //balloon_pop_2
    //balloon_pop_3
    //balloon_pop_4
    //balloon_pop_5
    
    mSoundDartPullback.Load("pullback");
    mSoundDartRelease.Load("release_dart_01", 3);
    //release_dart_01
    //release_dart_02
    //release_dart_03
    //release_dart_04
    //release_dart_05
    //release_dart_06
    
    
    mSoundHitBrickhead.Load("hit_brickhead");
    mSoundHitTurtle.Load("hit_turtle");
    
    mSoundFreeLife.Load("free_life");
    
    mSoundSparkle1.Load("sparkle_1");
    mSoundSparkle2.Load("sparkle_2");
    
    mSoundXylophone.Load("xylophone");
    
    gFormationCollection.Load();
    
}

void GFXApp::LoadComplete() {
    //
    //
    //
    
    //music_play("song2.mp3", true);
    
    /*
     if (mWorldScene == NULL) {
     mWorldScene = new WorldConfigScene();
     mWindowTools.AddChild(mWorldScene);
     mWorldScene->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
     }
     */
    
    
    /*
     if (mCameraMenu == NULL) {
     mCameraMenu = new CameraMenu(&mCamera);
     mWindowTools.AddChild(mCameraMenu);
     mCameraMenu->SetFrame(30.0f, gDeviceHeight - 90.0f, 260.0f, 240.0f);
     mCameraMenu->Collapse();
     }
     */
    
    
    
    /*
     if (mLevelSelect == NULL) {
     mLevelSelect = new LevelSelectorScreen();
     mLevelSelect->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
     mWindowMain.AddChild(mLevelSelect);
     }
     */
    
    //
    //
    //
    
    
    if (mGameContainer == NULL) {
        
#ifdef EDITOR_MODE
        EditorTestSwitchToEditor();
#else
        mGameContainer = new GameContainer();
        mWindowMain.AddChild(mGameContainer);
#endif
    }
    
    /*
     if (mSoundMenu == NULL) {
     mSoundMenu = new SoundConfigMenu();
     mSoundMenu->SetFrame(gSafeAreaInsetLeft + 20.0f, gSafeAreaInsetTop + 20.0f, 450.0f, gDeviceHeight * 0.8f);
     mWindowTools.AddChild(mSoundMenu);
     }
    */
    
    /*
    if (mAssetMenu == NULL) {
        mAssetMenu = new AssetConfigMenu();
        mWindowTools.AddChild(mAssetMenu);
        
        if (gDeviceWidth > 600.0f) {
            mAssetMenu->SetFrame(gSafeAreaInsetLeft + 20.0f, gSafeAreaInsetTop + 20.0f, 450.0f, gDeviceHeight * 0.4f);
        } else {
            mAssetMenu->SetFrame(gSafeAreaInsetLeft + 20.0f, gSafeAreaInsetTop + 20.0f, 300.0f, gDeviceHeight * 0.4f);
            mAssetMenu->Collapse();
        }
    }
    */
    
#ifndef EDITOR_MODE
    
    if (gDeviceWidth > 300) {
        if (mScreenTool == NULL) {
            mScreenTool = new Util_ScreenFrame();
            mScreenTool->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
            mScreenTool->RefreshVirtualFrame();
            mWindowTools.AddChild(mScreenTool);
        }
    }
    
#endif
    
    
    
}

void GFXApp::Update() {
    if (mIsLoadingComplete) {
        if (mLoadGame > 0) {
            --mLoadGame;
            if (mLoadGame == 0 && mGameContainer != NULL) {
                
#ifdef EDITOR_MODE
                
                
                //mEditorSwitchType = 0;
                //mEditorSwitchTimer = 0;
                
                if (mEditorSwitchType == 0) {
                    mEditor = new GameEditor(mGameContainer->mGame);
                    mWindowTools.AddChild(mEditor);
                    mEditor->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
                } else {
                    mGameContainer->mGame->LoadEditorTest();
                    
                    mGameContainer->OpenEditorTestMenus();
                    
                }
                
                Log("Preventing Load, Editor Mode...\n");
                
#else
                Log("Loading Game...\n");
                mGameContainer->mGame->Load();
#endif
                
                mGameContainer->Realize();
            }
        }
    }
    
    mCamera.mRotationPrimary += 0.05f;
    if (mCamera.mRotationPrimary >= 360.0f) {
        mCamera.mRotationPrimary -= 360.0f;
    }
}

void GFXApp::Draw() {
    
    
    if (mIsLoadingComplete) {
        Graphics::RenderPassBegin(GFX_RENDER_PASS_3D_MAIN,
                                  true, //Clear Color
                                  true); //Clear Depth
        
        if (mGameContainer != NULL) { mGameContainer->Draw3D(); }
        
        if (mLightScene != NULL) { mLightScene->Draw3D(); }
        
        if (mWorldScene != NULL) { mWorldScene->Draw3D(); }
        
        /*
         Draw3D();
         if (gRand.Get(14) == 10) {
         for (int i=0;i<60;i++) {
         Draw3D();
         }
         }
         */
        
        
        Graphics::RenderPassBegin(GFX_RENDER_PASS_2D_MAIN,
                                  false, //Clear Color
                                  false); //Clear Depth
        
        /*
         
         Draw2D();
         if (gRand.Get(14) == 10) {
         for (int i=0;i<60;i++) {
         Draw2D();
         }
         }
         
         */
        
        
        Graphics::PipelineStateSetSpriteAlphaBlending();
        
        
        
        if (mWadReloadIsEnqueued) {
            
            if (mWadReloadOnNextDraw) {
                
                
                Log("WAD RELOAD - Triggered!!!\n");
                
                
                mWadReloadIsEnqueued = false;
                mWadReloadOnNextDraw = false;
                mWadReloadTimer = 0;
                
                ExecuteWadReload();
                
                gApp->mWindowMain.RefreshAll();
                gApp->mWindowModal.RefreshAll();
                gApp->mWindowTools.RefreshAll();
                
            } else {
                mWadReloadTimer--;
                if (mWadReloadTimer <= 0) {
                    mWadReloadOnNextDraw = true;
                }
            }
        }
        
        /*
        Graphics::MatrixProjectionResetOrtho();
        Graphics::MatrixModelViewReset();
        Graphics::PipelineStateSetSpriteAlphaBlending();
        Graphics::SetColor();
        gWadGameInterface.mSpriteScreenSize.Draw(gVirtualDevX + gVirtualDevWidth / 2.0f, gVirtualDevY + gVirtualDevHeight / 2.0f, 1.0f);
        */
        
    }
}

void GFXApp::SetVirtualFrame(int pX, int pY, int pWidth, int pHeight) {
    if (mGameContainer) {
        mGameContainer->SetFrame(0.0f, 0.0f, gVirtualDevWidth, gVirtualDevHeight);
        
#ifdef EDITOR_MODE
        if (mEditor != NULL) {
            mEditor->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
        }
#endif
    }
    if (mLevelSelect != NULL) {
        mLevelSelect->SetFrame(0.0f, 0.0f, gVirtualDevWidth, gVirtualDevHeight);
        mLevelSelect->mPage1->SetFrame(0.0f, 0.0f, gVirtualDevWidth, gVirtualDevHeight);
        mLevelSelect->mPage2->SetFrame(gVirtualDevWidth, 0.0f, gVirtualDevWidth, gVirtualDevHeight);
        mLevelSelect->mPage3->SetFrame(gVirtualDevWidth + gVirtualDevWidth, 0.0f, gVirtualDevHeight, gVirtualDevHeight);
    }
    
    if (mLightScene != NULL) {
        mLightScene->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    }
    
    if (mWorldScene != NULL) {
        mWorldScene->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    }
    
    
    ReevaluateScreenResolution();
}

void GFXApp::TouchDown(float pX, float pY, void *pData) {
    
    //music_crossfade("song2.mp3", 200, true);
    //music_fadeout(40);
    
    TouchMove(pX, pY, pData);
    //
    //
    // Graphics::FlushUniforms();
    //
    //
    /*
     for (float aAngle = 0.0f;aAngle<359.0f;aAngle += 24.0f) {
     FVec2 aDir = AngleToVector(aAngle);
     FVec2 aCenter = FVec2(pX, pY);
     FVec2 aPos = aCenter + aDir * 30.0f;
     
     SpamDart *aDart = new SpamDart();
     
     
     aDart->mX = aPos.mX;
     aDart->mY = aPos.mY;
     //aSpark->mScale *= aScaleFactor;
     //aSpark->mIndex = 0;
     //
     mDartList.Add(aDart);
     }
     */
    
    //
    //
    //SpamDart
    //
    //FList mDartList;
    //
    //
    
}

void GFXApp::TouchMove(float pX, float pY, void *pData) {
    
    
}

void GFXApp::TouchUp(float pX, float pY, void *pData) {
    
}

void GFXApp::TouchFlush() {
    
}

void GFXApp::MouseWheel(int pDirection) {
    
}

void GFXApp::KeyDown(int pKey) {
    
}

void GFXApp::KeyUp(int pKey) {
    
}

void GFXApp::SetDeviceSize(int pWidth, int pHeight) {
    if (mGameContainer != NULL) {
        mGameContainer->SetFrame(0.0f, 0.0f, gVirtualDevWidth, gVirtualDevHeight);
#ifdef EDITOR_MODE
        if (mEditor != NULL) {
            mEditor->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
        }
#endif
    }
    
    if (mLightScene != NULL) {
        mLightScene->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    }
    
    if (mWorldScene != NULL) {
        mWorldScene->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    }
    
    ReevaluateScreenResolution();
}

void GFXApp::EnqueueWadReload(int pTime) {
    mWadReloadIsEnqueued = true;
    mWadReloadOnNextDraw = false;
    mWadReloadTimer = pTime;
}

void GFXApp::DequeueWadReload() {
    mWadReloadIsEnqueued = false;
    mWadReloadOnNextDraw = false;
    mWadReloadTimer = 0;
}

void GFXApp::ExecuteWadReload() {
    
    Log("*** BEGIN:: GFXApp::ExecuteWadReload()\n");
    
    DequeueWadReload();
    if (gWadConfiguration.ShouldReload() == false) {
        Log("BLOCKING RELOAD, NO NEED...\n");
        return;
    }
    
    Log("NOTIFYING RELOAD, NO NEED...\n");
    
    gWadConfiguration.NotifyReload();
    
    AppShellSetImageFileScale(gWadConfiguration.mAssetScale);
    AppShellSetSpriteDrawScale(gWadConfiguration.mSpriteScale);
    
    gWadGameInterface.Unload();
    gWadGameInterface.Load();
    
    gWadGameEffects.Unload();
    gWadGameEffects.Load();
    
    gWadModels.Unload();
    gWadModels.Load();
    
    
    Log("*** End:: GFXApp::ExecuteWadReload()\n");
    
}

void GFXApp::ReevaluateScreenResolution() {
    if (mIsLoadingComplete) {
        gWadConfiguration.NotifyVirtualFrameChange();
        EnqueueWadReload(1);
    }
}

#ifdef EDITOR_MODE

void GFXApp::EditorTestSwitchToGame() {
    
    float aAspectRatio = 768.0f / 1024.0f;
    float aPadding = 5.0f;
    float aVirtualHeight = round(gDeviceHeight - (aPadding * 2.0f));
    float aVirtualWidth = round(gDeviceHeight * aAspectRatio);
    float aVirtualX = round(gDeviceWidth / 2.0f - (aVirtualWidth / 2.0f));
    float aVirtualY = aPadding;
    
    //TODO:
    AppShellSetVirtualFrame(aVirtualX, aVirtualY, aVirtualWidth, aVirtualHeight);
    
    
    mEditorSwitchType = 1;
    
    if (mEditor != NULL) {
        mEditor->Kill();
        mEditor = NULL;
    }
    if (mGameContainer != NULL) {
        mGameContainer->Kill();
        mGameContainer = NULL;
    }
    
    
    mGameContainer = new GameContainer();
    mGameContainer->SetFrame(0.0f, 0.0f, gVirtualDevWidth, gVirtualDevHeight);
    mWindowMain.AddChild(mGameContainer);
    
    mLoadGame = 4;
}

void GFXApp::EditorTestSwitchToEditor() {
    
    
    float aAspectRatio = 768.0f / 1024.0f;
    float aVirtualHeight = round(gDeviceHeight * 0.75f);
    float aVirtualWidth = round(aVirtualHeight * aAspectRatio);
    float aVirtualX = round(gDeviceWidth / 2.0f - (aVirtualWidth / 2.0f));
    float aVirtualY = gDeviceHeight - (5.0f + aVirtualHeight);
    
    //TODO:
    AppShellSetVirtualFrame(aVirtualX, aVirtualY, aVirtualWidth, aVirtualHeight);
    
    
    mEditorSwitchType = 0;
    
    if (mEditor != NULL) {
        mEditor->Kill();
        mEditor = NULL;
    }
    if (mGameContainer != NULL) {
        mGameContainer->Kill();
        mGameContainer = NULL;
    }
    
    mGameContainer = new GameContainer();
    mGameContainer->SetFrame(0.0f, 0.0f, gVirtualDevWidth, gVirtualDevHeight);
    mWindowMain.AddChild(mGameContainer);
    
    mLoadGame = 4;
}

#endif

