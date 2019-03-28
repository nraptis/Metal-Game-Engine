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

#include "SoundConfigMenu.hpp"







#ifdef EDITOR_MODE
class GameEditor;
#include "GameEditor.hpp"
#endif

GFXApp *gApp = 0;
GFXApp::GFXApp() {
    
    /*
    FString aString1;
    FString aString2 = "bag";
    FString aString3 = "a";
    FString aString4 = "brains";
    FString aString5 = "abcdefghijklmnopqrt";
    
    FString aTemp1 = aString1;
    FString aTemp2 = aString2;
    FString aTemp3 = aString3;
    FString aTemp4 = aString4;
    FString aTemp5 = aString5;
    
    for (int aCount=0;aCount<5;aCount++) {
        
        for (int aIndex=-2;aIndex<8;aIndex++) {
            aTemp1 = aString1;
            aTemp2 = aString2;
            aTemp3 = aString3;
            aTemp4 = aString4;
            aTemp5 = aString5;
            
            aTemp1.Insert('*', aCount, aIndex);
            aTemp2.Insert('*', aCount, aIndex);
            aTemp3.Insert('*', aCount, aIndex);
            aTemp4.Insert('*', aCount, aIndex);
            aTemp5.Insert('*', aCount, aIndex);
            
            printf("[%d|%d] Temp1 = {%s}\n", aCount, aIndex, aTemp1.c());
            printf("[%d|%d] Temp2 = {%s}\n", aCount, aIndex, aTemp2.c());
            printf("[%d|%d] Temp3 = {%s}\n", aCount, aIndex, aTemp3.c());
            printf("[%d|%d] Temp4 = {%s}\n", aCount, aIndex, aTemp4.c());
            printf("[%d|%d] Temp5 = {%s}\n", aCount, aIndex, aTemp5.c());
        }
    }
    exit(0);
    */
    
    gApp = this;
    
#ifdef EDITOR_MODE
    mEditor = NULL;
#endif
    mGameContainer = NULL;
    mLevelSelect = NULL;
    mLightScene = NULL;
    mScreenTool = NULL;
    mCameraMenu = NULL;
    mSoundMenu = NULL;
    
    

    
    
    mTestTouch1 = NULL;
    mTestTouch2 = NULL;
    
    mTestX1 = 300.0f;
    mTestY1 = 300.0f;
    
    mTestX2 = 50.0f;
    mTestY2 = 360.0f;
    
    mTestSin1 = 0.0f;
    mTestSin2 = 180.0f;
    
    
    mAmbientRoll1 = 0.0f;
    mAmbientRoll2 = 0.0f;
    
    
    /*
    mCamera.mFOV = 0.987429;
    mCamera.mTarget = FVec3(0.0f, 0.0f, 0.0f);
    mCamera.mDirection = FVec3(0.000000, 0.000000, 1.000000);
    mCamera.mDistance = 6.337314;
    mCamera.mRotationPrimary = 0.0f;
    mCamera.mRotationSecondary = 0.0f;
    */
    
    mLoadGame = 20;
}

GFXApp::~GFXApp() {
    
}

void GFXApp::Load() {
    
    mRocket.mUseNormals = false;
    mRocket.LoadOBJ("rocket.obj");
    mRocketMap.Load("rocket_uvw");
    
    mSnail.LoadOBJ("snail.obj");
    mSnailMap.Load("snail_uvw");
    
    
    
    
    
    
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
    
    
    
    
    
    mSoundOne[0].Load("burn_stinger.caf", 1);
    mSoundOne[1].Load("drilling.caf", 1);
    mSoundOne[2].Load("magic_woosh.caf", 1);
    mSoundOne[3].Load("powerup_shuffle.caf", 1);
    mSoundOne[4].Load("rock_thud_1.caf", 1);
    mSoundOne[5].Load("relic_discover.caf", 1);
    
    
    mSoundMulti[0].Load("charge_up_laser_flanger.caf", 5);
    mSoundMulti[1].Load("charge_up_laser_cancel.caf", 5);
    mSoundMulti[2].Load("rock_break_1.caf", 5);
    mSoundMulti[3].Load("burn_stinger.caf", 5);
    mSoundMulti[4].Load("timer_tick.caf", 5);
    mSoundMulti[5].Load("timer_tock.caf", 5);
    
    
    //demo_song_1.mp3
    //demo_song_2.mp3
    
    
}

void GFXApp::LoadComplete() {
    //
    //
    //
    
    mTestRR.SetRect(gDeviceWidth - 200, gDeviceHeight - 300.0f, 150.0f, 200.0f);
    mTestRR.SetColorTop(1.0f, 0.25f, 0.25f, 0.66f);
    mTestRR.SetColorBottom(0.0f, 1.0f, 0.5f, 1.0f);
    
    
    //music_play("song2.mp3", true);
    
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
        mGameContainer = new GameContainer();
        mWindowMain.AddChild(mGameContainer);
        
#ifdef EDITOR_MODE
        mEditor = new GameEditor(mGameContainer->mGame);
        mWindowTools.AddChild(mEditor);
#endif
        
    }
    
    
    if (mSoundMenu == NULL) {
        mSoundMenu = new SoundConfigMenu();
        mSoundMenu->SetFrame(gSafeAreaInsetLeft + 20.0f, gSafeAreaInsetTop + 20.0f, 450.0f, gDeviceHeight * 0.8f);
        mWindowTools.AddChild(mSoundMenu);
    }
    
    /*
    if (mScreenTool == NULL) {
        mScreenTool = new Util_ScreenFrame();
        mScreenTool->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
        mWindowTools.AddChild(mScreenTool);
    }
    */
    
    
    //
    /*
    if (mLightScene == NULL) {
        mLightScene = new LightConfigurationScene();
        mWindowTools.AddChild(mLightScene);
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
}

void GFXApp::Update() {
    if (mIsLoadingComplete) {
        if (mLoadGame > 0) {
            --mLoadGame;
            if (mLoadGame == 0 && mGameContainer != NULL) {
                Log("Loading Game...\n");
                //mGameContainer->mGame->Load();
                
            }
        }
    }
    
    
    mCamera.mRotationPrimary += 0.05f;
    if (mCamera.mRotationPrimary >= 360.0f) {
        mCamera.mRotationPrimary -= 360.0f;
    }
    
    
    
    mTestSin1 += 3.0f;
    if (mTestSin1 >= 360.0f) mTestSin1 -= 360.0f;
    
    mTestSin2 -= 0.35f;
    if (mTestSin2 <= 0.0f) mTestSin2 += 360.0f;
    
    
    
    mAmbientRoll1 += gRand.GetFloat(0.5f) + 1.0f;
    if (mAmbientRoll1 >= 360.0f) mAmbientRoll1 -= 360.0f;
    
    mAmbientRoll2 += gRand.GetFloat(0.65f) + 2.0f;
    if (mAmbientRoll2 >= 360.0f) mAmbientRoll2 -= 360.0f;
    
    
    
}

void GFXApp::Draw3D() {
    
    FMatrix aProjection = mCamera.GetProjection();
    
    
    mUniAmb.mProjection = aProjection;
    mUniAmb.mModelView.Reset();
    mUniAmb.mModelView.Scale(0.35f);
    mUniAmb.mModelView.Translate(2.0f, -1.5f);
    mUniAmb.mModelView.RotateX(40.0f);
    mUniAmb.mLight.mAmbientIntensity = (Sin(mAmbientRoll1) + 1.0f) / 2.0f;
    
    
    mUniDiff.mProjection = aProjection;
    mUniDiff.mModelView.Reset();
    mUniDiff.mModelView.Scale(0.66f);
    mUniDiff.mModelView.Translate(-2.0f, 2.0f);
    mUniDiff.mModelView.RotateY(-60.0f);
    
    mUniDiff.mLight.mGreen = 0.5f;
    mUniDiff.mLight.mAmbientIntensity = 0.125f;
    mUniDiff.mLight.mDiffuseIntensity = 3.0f;
    mUniDiff.mLight.mDirZ = (Sin(mAmbientRoll1) + 1.0f) / 2.0f;
    
    
    mUniPhong.mProjection = aProjection;
    mUniPhong.mModelView.Reset();
    mUniPhong.mModelView.Scale(2.0f);
    mUniPhong.mModelView.Translate(-1.0f, -1.0f, 1.25f);
    mUniPhong.mModelView.RotateZ(60.0f);
    
    mUniPhong.mLight.mAmbientIntensity = 0.0f;
    mUniPhong.mLight.mDiffuseIntensity = (Sin(mAmbientRoll1) + 1.0f) / 4.0f + 0.25f;
    mUniPhong.mLight.mSpecularIntensity = 10.0f;
    mUniPhong.mLight.mDirZ = (Sin(mAmbientRoll2) + 1.0f) / 2.0f;
    
    //FUniformsLightAmbient                   mUniAmb;
    //FUniformsLightDiffuse            mUniDiff;
    //FUniformsLightPhong                     mUniPhong;
    
    
    Graphics::PipelineStateSetShape3DAlphaBlending();
    Graphics::CullFacesSetDisabled();
    Graphics::DepthEnable();
    
    
    Graphics::MatrixProjectionSet(aProjection);
    //Graphics::MatrixProjectionResetOrtho();
    Graphics::MatrixModelViewReset();
    Graphics::SetColor(1.0f, 0.5f, 0.75f, 0.75f);
    
    Graphics::DrawBox(0.0f, 0.0f, 0.0f, 1.0f, 2.0f, -1.0f, 0.125f);
    Graphics::MatrixModelViewReset();
    
    
    
    Graphics::PipelineStateSetSimpleModelNoBlending();
    
    Graphics::SetColor();
    
    Graphics::UniformBind();
    
    //.LoadOBJ("snail.obj");
    //.Load("snail_uvw");
    
    Graphics::DrawModel(mSnail.mXYZ, mSnail.mUVW, NULL, mSnail.mUVWCount, mSnailMap.mTexture);
    
    
    FMatrix aModelView = Graphics::MatrixModelViewGet();
    aModelView.Translate(5.0f, 0.0f);
    Graphics::MatrixModelViewSet(aModelView);
    
    Graphics::UniformBind();
    Graphics::DrawModel(mSnail.mXYZ, mSnail.mUVW, NULL, mSnail.mUVWCount, mSnailMap.mTexture);
    
    aModelView = Graphics::MatrixModelViewGet();
    aModelView.Reset();
    aModelView.Translate(-2.0f, 0.0f);
    
    aModelView.RotateY(-20.0f);
    Graphics::MatrixModelViewSet(aModelView);
    
    
    Graphics::PipelineStateSetSimpleModelIndexedNoBlending();
    
    if (mRocket.mBuffer != NULL && mRocket.mBuffer->mBindIndex != -1) {
    Graphics::ArrayBufferData(mRocket.mBuffer, 0);
    Graphics::ArrayBufferPositions(NULL, 0);
    Graphics::ArrayBufferTextureCoords(NULL, sizeof(float) * 3);
    Graphics::TextureBind(mRocketMap.mTexture);
    Graphics::UniformBind();
    Graphics::DrawTrianglesIndexed(mRocket.mIndex, mRocket.mIndexCount);
    }
    
    //Graphics::DrawModelIndexed(mRocket.mXYZ, mRocket.mXYZCount, mRocket.mUVW, mRocket.mUVWCount, 0, 0, mRocket.mIndex, mRocket.mIndexCount, mRocketMap.mTexture);
    
    aModelView = Graphics::MatrixModelViewGet();
    aModelView.Reset();
    aModelView.Translate(1.0f, -2.0f, 1.0f);
    Graphics::MatrixModelViewSet(aModelView);
    
    
    
    /*
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRocket.mBufferIndex);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mRocket.mIndexCount * sizeof(GFX_MODEL_INDEX_GL_TYPE), &(mRocket.mIndex), GL_STATIC_DRAW);
    
    Graphics::ArrayBufferData(mRocket.mBufferVertex, mRocket.mBufferVertexOffset);
    Graphics::ArrayBufferPositions(-1, 0);
    Graphics::ArrayBufferTextureCoords(-1, sizeof(float) * 3);
    Graphics::TextureBind(mRocketMap.mTexture);
    Graphics::UniformBind();
    
    
    glDrawElements(GL_TRIANGLES, 00, GFX_MODEL_INDEX_GL_TYPE, 0);
     
    */
    
    //mBufferSlotIndex
    
    //Graphics::DrawTrianglesIndexed(0, mRocket.mIndexCount);
    
    
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRocket.mBufferIndex);
    
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, mRocket.mIndexCount * sizeof(GFX_MODEL_INDEX_GL_TYPE), &(mRocket.mIndex), GL_STATIC_DRAW);
    
    //glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,
    //                mRocket.mBufferIndexOffset, mRocket.mIndexCount * sizeof(GFX_MODEL_INDEX_GL_TYPE), mRocket.mIndex);
    
    
    //glDrawElements(GL_TRIANGLES, 30, GFX_MODEL_INDEX_GL_TYPE, 0);
    
    
    
    
    
    
    //Graphics::DrawModelIndexed(mRocket.mXYZ, mRocket.mXYZCount, mRocket.mUVW, mRocket.mUVWCount, 0, 0, mRocket.mIndex, mRocket.mIndexCount, mRocketMap.mTexture);
    
    
    Graphics::PipelineStateSetModelIndexedNoBlending();
    aModelView = Graphics::MatrixModelViewGet();
    aModelView.Reset();
    aModelView.Translate(0.25f, 2.0f, -1.0f);
    Graphics::MatrixModelViewSet(aModelView);
    
    if (mPalmTrunk.mBuffer != NULL && mPalmTrunk.mBuffer->mBindIndex != -1) {
    Graphics::ArrayBufferData(mPalmTrunk.mBuffer, 0);
    Graphics::ArrayBufferPositions(NULL, 0);
    Graphics::ArrayBufferTextureCoords(NULL, sizeof(float) * 3);
    Graphics::TextureBind(mPalmTrunkMap.mTexture);
    Graphics::UniformBind();
    Graphics::DrawTrianglesIndexed(mPalmTrunk.mIndex, mPalmTrunk.mIndexCount);
    }
    
    
    
    
    Graphics::PipelineStateSetModelIndexedLightedAmbientNoBlending();
    //Graphics::PipelineStateSetModelIndexedAlphaBlending();
        
        if (mMonolith.mBuffer != NULL && mMonolith.mBuffer->mBindIndex != -1) {
    Graphics::ArrayBufferData(mMonolith.mBuffer, 0);
    Graphics::ArrayBufferPositions(NULL, 0);
    Graphics::ArrayBufferTextureCoords(NULL, sizeof(float) * 3);
    Graphics::ArrayBufferNormals(NULL, sizeof(float) * 6);
    Graphics::TextureBind(mMonolithMap.mTexture);
    Graphics::UniformBind(&mUniAmb);
    Graphics::DrawTrianglesIndexed(mMonolith.mIndex, mMonolith.mIndexCount);
        }
    
    

    if (mMonolith.mBuffer != NULL && mMonolith.mBuffer->mBindIndex != -1) {
    Graphics::PipelineStateSetModelIndexedLightedDiffuseAlphaBlending();
    Graphics::ArrayBufferData(mMonolith.mBuffer, 0);
    Graphics::ArrayBufferPositions(NULL, 0);
    Graphics::ArrayBufferTextureCoords(NULL, sizeof(float) * 3);
    Graphics::ArrayBufferNormals(NULL, sizeof(float) * 6);
    Graphics::TextureBind(mMonolithMap.mTexture);
    Graphics::UniformBind(&mUniDiff);
    Graphics::DrawTrianglesIndexed(mMonolith.mIndex, mMonolith.mIndexCount);
    }
    
    
    
    if (mMonolith.mBuffer != NULL && mMonolith.mBuffer->mBindIndex != -1) {
    Graphics::PipelineStateSetModelIndexedLightedPhongAlphaBlending();
    Graphics::ArrayBufferData(mMonolith.mBuffer, 0);
    Graphics::ArrayBufferPositions(NULL, 0);
    Graphics::ArrayBufferTextureCoords(NULL, sizeof(float) * 3);
    Graphics::ArrayBufferNormals(NULL, sizeof(float) * 6);
    Graphics::TextureBind(mMonolithMap.mTexture);
    Graphics::UniformBind(&mUniPhong);
    Graphics::DrawTrianglesIndexed(mMonolith.mIndex, mMonolith.mIndexCount);
    }
    
    
    
    
    Graphics::DepthDisable();
}

void GFXApp::Draw2D() {
    
    //return;
    
    Graphics::SetColor();
    Graphics::MatrixProjectionResetOrtho();
    Graphics::MatrixModelViewReset();
    Graphics::PipelineStateSetSpriteAlphaBlending();
    
    //Graphics::SetColor(0.125f);
    //mBalloonMap[4].DrawQuad(0.0f, 0.0f, gDeviceWidth - 10.0f, gDeviceHeight - 10.0f);
    
    //mBalloonMap[4].Draw(gDeviceWidth2, gDeviceHeight2);
    //mRay[2].Draw(gDeviceWidth2, gDeviceHeight2);
    
    
    mSpiralPineTreeMap.DrawQuadRect(200.0f, 200.0f, 300.0f, 150.0f);
    
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
    
    
    mSnailMap.DrawAngleRange(500.0f, 650.0f, 0.45f, -20.0f, mAmbientRoll1 - 40.0f, mAmbientRoll1 + (Sin(mAmbientRoll2) + 1.0f) * 50.0f + 40.0f);
    
    Graphics::SetColor();
    
    Graphics::PipelineStateSetSpriteAdditiveBlending();
    mChaosEgg3X.Draw(300.0f, 100.0f, 1.0f, 20.0f);
    
    
    mChaosEgg3X.Draw(400.0f, 400.0f, 1.0f, 60.0f);
    mChaosEgg3X.DrawFlippedH(500.0f, 400.0f, 1.0f, 60.0f);
    
    
    
    
    mRay[0].Draw(40, 300);
    
    Graphics::PipelineStateSetSpriteWhiteBlending();
    
    mRay[1].Draw(50, 300);
    
    mRay[2].Draw(100, 300);
    
    Graphics::PipelineStateSetSpriteAdditiveBlending();
    
    mRay[3].Draw(150, 300);
    
    Graphics::SetColor();
    
    mMonolithMap.Draw(mTestX1, mTestY1, 0.125f, Sin(mTestSin1) * 40.0f, -1);
    mChaosEgg2X.Draw(mTestX2, mTestY2, 0.5f, mTestSin2, -1);
    
    
    
    //Graphics::PipelineStateSetShapeNodeNoBlending();
    //mTestRR.Draw();
    
    
    
    //mPackedBuffer = Graphics::BufferArrayGenerate(100 * sizeof(float));
    //mPackedBuffer =
    
    
    
}


void GFXApp::Draw() {
    

    if (mIsLoadingComplete) {
        Graphics::RenderPassBegin(GFX_RENDER_PASS_3D_MAIN,
                                  true, //Clear Color
                                  true); //Clear Depth
        
        if (mGameContainer) mGameContainer->Draw3D();
        //if (mLevelSelect) mLevelSelect->mPage1->Draw3D();
        if (mLightScene) { mLightScene->Draw3D(); }
        
        
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
        
    }
}

void GFXApp::SetVirtualFrame(int pX, int pY, int pWidth, int pHeight) {
    if (mGameContainer) {
        mGameContainer->SetFrame(0.0f, 0.0f, gVirtualDevWidth, gVirtualDevHeight);
        
#ifdef EDITOR_MODE
        mEditor->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
#endif
        
        
    }
    if (mLevelSelect) {
        mLevelSelect->SetFrame(0.0f, 0.0f, gVirtualDevWidth, gVirtualDevHeight);
        mLevelSelect->mPage1->SetFrame(0.0f, 0.0f, gVirtualDevWidth, gVirtualDevHeight);
        mLevelSelect->mPage2->SetFrame(gVirtualDevWidth, 0.0f, gVirtualDevWidth, gVirtualDevHeight);
        mLevelSelect->mPage3->SetFrame(gVirtualDevWidth + gVirtualDevWidth, 0.0f, gVirtualDevHeight, gVirtualDevHeight);
    }
    
    if (mLightScene) {
        mLightScene->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    }
    
}

void GFXApp::TouchDown(float pX, float pY, void *pData) {
    
    if (mTestTouch1 == NULL) {
        mTestTouch1 = pData;
        mTestX1 = pX;
        mTestY1 = pY;
    } else if (mTestTouch2 == NULL) {
        mTestTouch2 = pData;
        mTestX2 = pX;
        mTestY2 = pY;
    }
    
    
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
    
    
    if (mTestTouch1 == pData) {
        mTestX1 = pX;
        mTestY1 = pY;
    } else if (mTestTouch2 == pData) {
        mTestX2 = pX;
        mTestY2 = pY;
    }
    
    
    float aPercentY = pY / gDeviceHeight;
    
    aPercentY = (0.5 - aPercentY);
    
    float aPercentX = pX / gDeviceWidth;
    aPercentX = (0.5 - aPercentX);
    
    //mCamera.mCameraVertical = aPercentY * 10.0f;
    //mCamera.mCameraRotation = aPercentX * 360.0f + 180.0f;
    
    
}

void GFXApp::TouchUp(float pX, float pY, void *pData) {
    if (mTestTouch1 == pData) {
        mTestTouch1 = NULL;
    } else if (mTestTouch2 == pData) {
        mTestTouch2 = NULL;
    }
}

void GFXApp::TouchFlush() {
    mTestTouch1 = NULL;
    mTestTouch2 = NULL;
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
#ifdef EDITOR_MODE
        mEditor->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
#endif
    }
    
    if (mLightScene) {
        mLightScene->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    }
    
}
