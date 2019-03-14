//
//  GFXApp.cpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/29/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

//#include "MetalEngine.h"

#include "GFXApp.hpp"
#include "core_app_shell.h"
#include "LevelSelectorScreen.hpp"
#include "LightConfigurationScene.hpp"
#include "Balloon.hpp"
#include "Util_ScreenFrame.h"
#include "Game.hpp"
#include "GameContainer.hpp"
#include "CameraMenu.hpp"

GFXApp *gApp = 0;
GFXApp::GFXApp() {
    gApp = this;
    
    mGameContainer = NULL;
    mLevelSelect = NULL;
    mLightScene = NULL;
    mScreenTool = NULL;
    mCameraMenu = NULL;
    
    /*
    mCamera.mFOV = 0.987429;
    mCamera.mTarget = FVec3(0.0f, 0.0f, 0.0f);
    mCamera.mDirection = FVec3(0.000000, 0.000000, 1.000000);
    mCamera.mDistance = 6.337314;
    mCamera.mRotationPrimary = 0.0f;
    mCamera.mRotationSecondary = 0.0f;
    */
    
    mLayoutGame = true;
    
}

GFXApp::~GFXApp() {
    
}

void GFXApp::Load() {
    
    mSound1.Load("land.caf");
    mSound2.Load("match.caf");
    
    mGameAreaMarker.Load("game_area_marker");
    
    
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
    
    mDart.LoadOBJ("dart.obj");
    mDartMap.Load("dart_color");
    
    
    mBalloon.LoadOBJ("balloon.obj");
    mBalloonMap[0].Load("balloon_skin_01");
    mBalloonMap[1].Load("balloon_skin_02");
    mBalloonMap[2].Load("balloon_skin_03");
    mBalloonMap[3].Load("balloon_skin_04");
    mBalloonMap[4].Load("balloon_skin_05");
    //
    //
    //
    Log("mBalloon[%d][%d]\n", mBalloon.mDataCount, mBalloon.mIndexCount);
    //
    //
    //
    //We need to have differently named files OR clean
    //out the texture cache when we CHANGE resolution.
    //As long as we START with the RIGHT resolution,
    //then we will be fine...
    
    
     
    AppShellSetImageFileScale(1);
    mChaosEgg1X.Load("gi_chaos_egg_mockup_1");
    mRay[0].Load("effect_ray_wide_1_0");
    
    
    AppShellSetImageFileScale(2);
    mChaosEgg2X.Load("gi_chaos_egg_mockup_2");
    mRay[1].Load("effect_ray_wide_2_0");
    
    
    AppShellSetImageFileScale(3);
    mChaosEgg3X.Load("gi_chaos_egg_mockup_3");
    mRay[2].Load("effect_ray_wide_3_0");
    
    
    AppShellSetImageFileScale(4);
    mChaosEgg4X.Load("gi_chaos_egg_mockup_4");
    mRay[3].Load("effect_ray_wide_4_0");
    
}

void GFXApp::LoadComplete() {
    //
    //
    //
    
    
    /*
    core_sound_musicPlay("song1.m4a", true);
    
    //
    
    
    
    if (mCameraMenu == NULL) {
        mCameraMenu = new CameraMenu(&mCamera);
        mWindowTools.AddChild(mCameraMenu);
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
    //
    //
    //
    
    if (mGameContainer == NULL) {
        mGameContainer = new GameContainer();
        mWindowMain.AddChild(mGameContainer);
    }
    
    if (mScreenTool == NULL) {
        mScreenTool = new Util_ScreenFrame();
        mScreenTool->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
        mWindowTools.AddChild(mScreenTool);
    }
    
    
    //
    /*
    if (mLightScene == NULL) {
        mLightScene = new LightConfigurationScene();
        mWindowMain.AddChild(mLightScene);
    }
    */
    
    /*
    float aAngle = 0.0f;
    for (float aX=0; aX < gDeviceWidth;aX += 40.0f){
        for (float aY=0; aY < gDeviceHeight;aY += 40.0f){
            SpamDart *aDart = new SpamDart();
            aDart->mX = aX;
            aDart->mY = aY;
            aDart->mScale = 10.0f;
            mDartList.Add(aDart);
        }
    }
    */
    mLayoutGame = true;
    
}

void GFXApp::Update() {
    
    mCamera.mRotationPrimary += 1.0f;
    if (mCamera.mRotationPrimary >= 360.0f) {
        mCamera.mRotationPrimary -= 360.0f;
    }
    
    /*
    if (mLayoutGame) {
        if (mGameContainer) {
            mLayoutGame = false;
            //mGameContainer->SetFrame(0.0f, 0.0f, gVirtualDevWidth, gVirtualDevHeight);
            
            mWindowMain.RegisterFrameDidUpdate(mGameContainer);
            mWindowMain.RegisterFrameDidUpdate(mGameContainer->mContainer);
            mWindowMain.RegisterFrameDidUpdate(mGameContainer->mGame);
            
        }
    }
    */
    
    
}

void GFXApp::Draw3D() {
    /*
    Graphics::PipelineStateSetShape3DAlphaBlending();
    
    FMatrix aProjection = mCamera.GetProjection();
    Graphics::MatrixProjectionSet(aProjection);
    //Graphics::MatrixProjectionResetOrtho();
    Graphics::MatrixModelViewReset();
    Graphics::SetColor(1.0f, 0.5f, 0.75f, 0.75f);
    
    Graphics::DrawBox(0.0f, 0.0f, 0.0f, 4.0f, 2.0f, -1.0f, 2.0f);
    
    
    Graphics::MatrixModelViewReset();
    */
}

void GFXApp::Draw2D() {
    
    Graphics::SetColor();
    Graphics::MatrixProjectionResetOrtho();
    Graphics::MatrixModelViewReset();
    Graphics::PipelineStateSetSpriteAlphaBlending();
    
    Graphics::SetColor(0.125f);
    mBalloonMap[4].DrawQuad(0.0f, 0.0f, gDeviceWidth - 10.0f, gDeviceHeight - 10.0f);
    
    
    Graphics::SetColor(0.25f, 0.25f, 0.45f);
    Graphics::PipelineStateSetShape2DNoBlending();
    
    Graphics::DrawLine(0.0f, 0.0f, gDeviceWidth, gDeviceHeight, 3.0f);
    Graphics::DrawLine(gDeviceWidth, 0.0f, 0.0f, gDeviceHeight, 3.0f);
    
    
    Graphics::SetColor();
    Graphics::PipelineStateSetSpriteNoBlending();
    
    
    
    Graphics::SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    
    
    
    
    Graphics::SetColor(1.0f, 0.25f, 0.25f, 0.75f);
    
    mChaosEgg1X.Draw(10, 70, 1.0f, 60.0f);
    
    
    Graphics::PipelineStateSetSpriteAlphaBlending();
    mChaosEgg2X.Draw(150.0f, 100.0f, 1.0f, 20.0f);
    
    Graphics::SetColor();
    
    Graphics::PipelineStateSetSpriteAdditiveBlending();
    mChaosEgg3X.Draw(300.0f, 100.0f, 1.0f, 20.0f);
    
    
    mRay[0].Draw(40, 300);
    
    Graphics::PipelineStateSetSpriteWhiteBlending();
    
    mRay[1].Draw(50, 300);
    
    mRay[2].Draw(100, 300);
    
    Graphics::PipelineStateSetSpriteAdditiveBlending();
    
    mRay[3].Draw(150, 300);
    
    Graphics::SetColor(0.0f, 0.5f, 1.0f, 0.75f);
    
    
    
}


void GFXApp::Draw() {
    
    Graphics::Clear(0.025f, 0.022f, 0.045f, 1.0f);

    if (mIsLoadingComplete) {
        Graphics::RenderPassBegin(GFX_RENDER_PASS_3D_MAIN,
                                  true, //Clear Color
                                  true); //Clear Depth
        
        //if (mGameContainer) mGameContainer->Draw3D();
        //if (mLevelSelect) mLevelSelect->mPage1->Draw3D();
        
        
        //Draw3D();
        
        
        
        
        
        
        
        
        
        
        
        Graphics::RenderPassBegin(GFX_RENDER_PASS_2D_MAIN,
                                  false, //Clear Color
                                  false); //Clear Depth
        
        Draw2D();
        
        Graphics::PipelineStateSetSpriteAlphaBlending();
        
    }
}

void GFXApp::SetVirtualFrame(int pX, int pY, int pWidth, int pHeight) {
    if (mGameContainer) {
        mGameContainer->SetFrame(0.0f, 0.0f, gVirtualDevWidth, gVirtualDevHeight);
    }
    if (mLevelSelect) {
        mLevelSelect->SetFrame(0.0f, 0.0f, gVirtualDevWidth, gVirtualDevHeight);
        mLevelSelect->mPage1->SetFrame(0.0f, 0.0f, gVirtualDevWidth, gVirtualDevHeight);
        mLevelSelect->mPage2->SetFrame(gVirtualDevWidth, 0.0f, gVirtualDevWidth, gVirtualDevHeight);
        mLevelSelect->mPage3->SetFrame(gVirtualDevWidth + gVirtualDevWidth, 0.0f, gVirtualDevHeight, gVirtualDevHeight);
        
    }
    
    mLayoutGame = true;
}

void GFXApp::TouchDown(float pX, float pY, void *pData) {
    
    //core_sound_musicCrossFade("song2.mp3", 200, true);
    //core_sound_musicFadeOut(40);
    
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
    
    float aPercentY = pY / gDeviceHeight;
    
    aPercentY = (0.5 - aPercentY);
    
    float aPercentX = pX / gDeviceWidth;
    aPercentX = (0.5 - aPercentX);
    
    //mCamera.mCameraVertical = aPercentY * 10.0f;
    //mCamera.mCameraRotation = aPercentX * 360.0f + 180.0f;
    
    
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
    
    if (mGameContainer) {
        mGameContainer->SetFrame(0.0f, 0.0f, gVirtualDevWidth, gVirtualDevHeight);
    }
    
    mLayoutGame = true;
}
