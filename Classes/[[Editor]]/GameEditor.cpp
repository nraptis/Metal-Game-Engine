//
//  GameEditorEditor.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/17/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "core_includes.h"
#include "GameEditor.hpp"
#include "GameContainer.hpp"
#include "FAnimation.hpp"

GameEditor *gEditor = NULL;

GameEditor::GameEditor(Game *pGame) {
    
    mIsRefreshingPlayback = false;
    
    mEditorShowReferenced = false;
    mEditorWaveLoop = true;
    mEditorSectionLoop = true;
    mEditorPlaybackFromCurrentWave = true;
    mEditorPlaybackEnabled = true;
    
    
    
    mRandomSeed = os_system_time() ^ gRand.Get(999999);
    
    mSpeedClassIndex = SPEED_CLASS_MEDIUM;
    mSpawnRotationSpeedClassIndex = SPEED_CLASS_MEDIUM;
    
    
    
    
    mMenuSpeed = NULL;
    mMenuAttachment = NULL;
    mMenuSpawnPicker = NULL;
    mMenuWavesPicker = NULL;
    mMenuSpawn = NULL;
    
    mMenuObjectClearing = NULL;
    mMenuMotion = NULL;
    
    mMenuStyle = NULL;
    
    
    mTestIndex = 0;
    mTestMode = false;
    
    mPickFormationReason = 0;
    
    mEnqueueInitialLoad = 3;
    mAutosaveTimer = 0;
    
    gEditor = this;
    mGame = pGame;
    
    mName = "[GameEditor]";
    gEditor = this;
    
    SetWidth(gDeviceWidth);
    SetHeight(gDeviceHeight);
    
    mOverlay = NULL;
    
    
    
    mPathEditor = NULL;
    mFormationEditor = NULL;
    mPermEditor = NULL;
    
    
    mToolContainer = new FCanvas();
    mToolContainer->mConsumesTouches = false;
    mToolContainer->mName = "Tool Container";
    AddChild(mToolContainer);
    mToolContainer->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    
    
    mMenuSections = new EditorMenuSections(this);
    mToolContainer->AddChild(mMenuSections);
    mMenuSections->SetFrame(gSafeAreaInsetLeft + 16.0f, gSafeAreaInsetTop + 10.0f, 400.0f, mHeight - (gSafeAreaInsetBottom + gSafeAreaInsetTop + 20.0f));
    
    
    
    float aSpeedMenuWidth = 510.0f;
    if (aSpeedMenuWidth > gDeviceWidth) { aSpeedMenuWidth = gDeviceWidth; }
    
    mMenuSpeed = new SpeedControlMenu();
    mToolContainer->AddChild(mMenuSpeed);
    mMenuSpeed->SetFrame(gDeviceWidth2 - aSpeedMenuWidth / 2.0f, 38.0f, aSpeedMenuWidth, 150.0f);
    
    
    
    mExportIndex = 0;
    
    SetOverlay(mToolContainer);
    
    
    
    //WaveAdd();
    //OpenPathEditorForWave();
    
    mFreeze = false;
    mFreezeFrame = 400;
    mPreviousFreezeFrame = -1;
    mFreezeFrameRecapTimer = 0;
    
    
    
    LoadConfig();
    //
    OpenSpawnMenu();
    OpenWavePickerMenu();
    OpenSpawnPickerMenu();
    OpenAttachmentMenu();
    
}

GameEditor::~GameEditor() {
    if (gEditor == this) {
        gEditor = NULL;
    }
}

void GameEditor::Layout() {
    
    mToolContainer->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    if (mPathEditor) mPathEditor->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    
    FVec2 aSpawnZone1 = FVec2(gGame->mSpawnZoneLeft, gGame->mSpawnZoneTop);
    aSpawnZone1 = FCanvas::Convert(aSpawnZone1, gGame, this);
    FVec2 aSpawnZone2 = FVec2(gGame->mSpawnZoneRight, gGame->mSpawnZoneBottom);
    aSpawnZone2 = FCanvas::Convert(aSpawnZone2, gGame, this);
    mSpawnZoneTop = aSpawnZone1.mY;
    mSpawnZoneRight = aSpawnZone2.mX;
    mSpawnZoneLeft = aSpawnZone1.mX;
    mSpawnZoneBottom = aSpawnZone2.mY;
    
    
    FVec2 aPeekZone1 = FVec2(gGame->mPeekZoneLeft, gGame->mPeekZoneTop);
    aPeekZone1 = FCanvas::Convert(aPeekZone1, gGame, this);
    FVec2 aPeekZone2 = FVec2(gGame->mPeekZoneRight, 0.0f);
    aPeekZone2 = FCanvas::Convert(aPeekZone2, gGame, this);
    mPeekZoneTop = aPeekZone1.mY;
    mPeekZoneRight = aPeekZone2.mX;
    mPeekZoneLeft = aPeekZone1.mX;
    
    FVec2 aQuarterZone1 = FVec2(gGame->mQuarterZoneLeft, gGame->mQuarterZoneTop);
    aQuarterZone1 = FCanvas::Convert(aQuarterZone1, gGame, this);
    FVec2 aQuarterZone2 = FVec2(gGame->mQuarterZoneRight, gGame->mQuarterZoneBottom);
    aQuarterZone2 = FCanvas::Convert(aQuarterZone2, gGame, this);
    mQuarterZoneTop = aQuarterZone1.mY;
    mQuarterZoneRight = aQuarterZone2.mX;
    mQuarterZoneLeft = aQuarterZone1.mX;
    mQuarterZoneBottom = aQuarterZone2.mY;
    
    
    FVec2 aExitZone1 = FVec2(gGame->mExitZoneLeft, gGame->mExitZoneTop);
    aExitZone1 = FCanvas::Convert(aExitZone1, gGame, this);
    FVec2 aExitZone2 = FVec2(gGame->mExitZoneRight, 0.0f);
    aExitZone2 = FCanvas::Convert(aExitZone2, gGame, this);
    mExitZoneTop = aExitZone1.mY;
    mExitZoneRight = aExitZone2.mX;
    mExitZoneLeft = aExitZone1.mX;
    
    
    FVec2 aPlayZone1 = FVec2(0.0f, gGame->mPlayAreaBottom);
    aPlayZone1 = FCanvas::Convert(aPlayZone1, gGame, this);
    mPlayZoneBottom = aPlayZone1.mY;
    
    
    FVec2 aGameArea1 = FVec2(gGame->mGameAreaLeft, gGame->mGameAreaTop);
    aGameArea1 = FCanvas::Convert(aGameArea1, gGame, this);
    FVec2 aGameArea2 = FVec2(gGame->mGameAreaRight, gGame->mGameAreaBottom);
    aGameArea2 = FCanvas::Convert(aGameArea2, gGame, this);
    mGameAreaTop = aGameArea1.mY;
    mGameAreaRight = aGameArea2.mX;
    mGameAreaLeft = aGameArea1.mX;
    mGameAreaBottom = aGameArea2.mY;
    
    FVec2 aCenter = FVec2((gGame->mPlayAreaLeft + gGame->mPlayAreaRight) / 2.0f,
                            (gGame->mPlayAreaTop + gGame->mPlayAreaBottom) / 2.0f);
    aCenter = FCanvas::Convert(aCenter, gGame, this);
    mCenterH = aCenter.mX;
    mCenterV = aCenter.mY;
    
}

void GameEditor::Update() {
    
    bool aIsOnMainTools = (mOverlay == mToolContainer);
    bool aIsOnPathTools = (mOverlay == mPathEditor);
    bool aIsOnPermTools = (mOverlay == mPermEditor);
    bool aIsOnFormationTools = (mOverlay == mFormationEditor);
    
    
    
    
    
    
    bool aFreeze = mFreeze;
    if (aIsOnPathTools || aIsOnPermTools || aIsOnFormationTools) { aFreeze = false; }
    
    if (aFreeze == false) {
        
        mFreezeFrameRecapTimer = 0;
        mPreviousFreezeFrame = -1;
        for (int i=0;i<gGameContainer->mPlaybackUpdateCount;i++) {
            mEditorSection.Update();
            mSection.Update();
        }
    } else {
        
        mFreezeFrameRecapTimer--;
        if (mFreezeFrameRecapTimer <= 0) {
            mFreezeFrameRecapTimer = 20;
            
            RefreshPlayback();
            for (int i=0;i<mFreezeFrame;i++) {
                mSection.Update();
                mEditorSection.Update();
            }
        }
        
        
        
    }
    
    if (mSection.mCurrentWave) {
        mSpeedClassIndex = SpeedConvertTypeToSegment(mSection.mCurrentWave->mPath.mSpeedClass);
    }
    
    mAutosaveTimer += 1;
    if (mAutosaveTimer >= 150) {
        Autosave();
        mAutosaveTimer = 0;
    }
    
    if (mEnqueueInitialLoad > 0) {
        mEnqueueInitialLoad--;
        if (mEnqueueInitialLoad <= 0) {
            Autoload();
            
            //HOOK: We want to jump right to a particular toolset?
            
            //Load("section_learning_start");
            
            Load("section_medhard_4_perms_2_double_turtle_4linev_2_2_turtle_2_brick_rect_5_wave_trap5_line6_tect8_circ6_circ6_brick");
            
            //Load("section_medium_2_perms_2_bricks_2_turtles_4_waves_staggered_mixed_turtles_bricks_medium_circle_2_singles_1_turtle_brick");
            //Load("editor_test_section");
            
            //Load("section_medium_5_waves_1_4_spaced_turtles_2_sym_circles6_brick_center_1_marquee6_1_tri3");

            //Load("section_easymed_2_perms_2_bricks_blocking_1_turtle_both_sides_3_waves_med_tri_2_singles_med_square");
            //Load("section_medium_2_perms_2_bricks_2_turtles_4_waves_staggered_mixed_turtles_bricks_medium_circle_2_singles_1_turtle_brick");
            //Load("section_medium_3_waves_simultaneous_large_hexahon_two_ring_tracer_with_bricks_2_small_osc_circles_brick_in_center");
            //Load("section_medium_2_perms_circle_8_4_bricks_rot_oscillations_1_wave_circle_8_4_bricks_rotating");
            
            //OpenFormationEditor(NULL);
            
            
            //PickFormationForFormationEditor();
            
            //OpenPermanentEditor();
            
        }
    }
    
    
    
    if (true) {
        LevelWave *aWave = ((LevelWave *)gEditor->mEditorSection.mWaveList.Fetch(gEditor->WaveIndex()));
        if (aWave != NULL) {
            
            int aRequiredTestObjectCount = aWave->mPath.mNodeList.mCount;
            
            while (mEditorObjectList.mCount > aRequiredTestObjectCount) {
                mEditorObjectQueue.Add(mEditorObjectList.PopLast());
            }
            
            while (mEditorObjectList.mCount < aRequiredTestObjectCount && mEditorObjectQueue.mCount > 0) {
                mEditorObjectList.Add(mEditorObjectQueue.PopLast());
            }
            
            while (mEditorObjectList.mCount < aRequiredTestObjectCount) {
                Balloon *aBalloon = new Balloon();
                mEditorObjectList.Add(aBalloon);
            }
            
            for (int i=0;i<aWave->mPath.mNodeList.mCount;i++) {
                
                GameObject *aObject = (GameObject *)mEditorObjectList.Fetch(i);
                LevelPathNode *aPathNode = (LevelPathNode *)aWave->mPath.mNodeList.Fetch(i);
                
                if (aObject != NULL && aPathNode != NULL) {
                    aObject->mTransform.mX = aPathNode->mX;
                    aObject->mTransform.mY = aPathNode->mY;
                    aObject->Update();
                }
            }
        }
    }
    
    
    
    
    
    /*
    if (aIsOnMainTools || aIsOnPathTools || aIsOnPermTools) {
        if (mEditorPlaybackEnabled) {
            if (mEditorPlaybackWaveOnly) {
                mEditorWave.Update();
                if (mEditorWave.mIsComplete) {
                    if (mEditorWaveLoop) {
                        //mEditorWave.Restart();
                        //RefreshPlayback();
                    }
                }
                
                //We do this to prevent crash when
                //we mass delete objects and have switched
                //modes back and forth too many times...
                mEditorSection.Update();
                mEditorSection.Reset();
            } else {
                mEditorSection.Update();
                if (mEditorSection.mIsComplete) {
                    if (mEditorSectionLoop) {
                        //mEditorSection.Restart();
                        //RefreshPlayback();
                        
                    }
                }
                
                //We do this to prevent crash when
                //we mass delete objects and have switched
                //modes back and forth too many times...
                mEditorWave.Update();
                mEditorWave.Reset();
            }
        }
    } else {
        mEditorWave.Reset();
        mEditorSection.Reset();
    }
    */
    
}

void GameEditor::Draw() {
    
    if (gGame == NULL) { return; }
    
    bool aIsOnMainTools = (mOverlay == mToolContainer);
    bool aIsOnPathTools = (mOverlay == mPathEditor);
    bool aIsOnPermTools = (mOverlay == mPermEditor);
    
    
    
    gGame->DrawTransform();
    
    Graphics::PipelineStateSetShape2DNoBlending();
    Graphics::SetColor();
    if (true) {
        LevelWave *aWave = ((LevelWave *)mEditorSection.mWaveList.Fetch(WaveIndex()));
        if (aWave != NULL) {
            aWave->mPath.Draw();
        }
    }
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    Graphics::SetColor(0.35f, 0.65f, 0.35f, 0.45f);
    
    Graphics::OutlineRectInside(mEditorSection.mX, mEditorSection.mY, gGame->mGameAreaRight - gGame->mGameAreaLeft, gGame->mGameAreaBottom - gGame->mGameAreaTop, 6.0f);
    
    
    DrawTransform();
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    
    if (aIsOnMainTools || aIsOnPathTools || aIsOnPermTools) {
        Graphics::SetColor(0.0125f, 0.0125f, 0.0125f, 0.40f);
        Graphics::DrawRect(0.0f, 0.0f, mGameAreaLeft, gDeviceHeight);
        Graphics::DrawRect(mGameAreaLeft, 0.0f, mGameAreaRight - mGameAreaLeft, mGameAreaTop);
        Graphics::DrawRect(mGameAreaLeft, mGameAreaBottom, mGameAreaRight - mGameAreaLeft, gDeviceHeight - mGameAreaBottom);
        Graphics::DrawRect(mGameAreaLeft + (mGameAreaRight - mGameAreaLeft), 0.0f, gDeviceWidth - (mGameAreaLeft + (mGameAreaRight - mGameAreaLeft)), gDeviceHeight);
        
        float aMarkerMult = 0.6f;
        float aMarkerOpacity = 0.35f;
        
        Graphics::SetColor(0.125f * aMarkerMult, 1.0f * aMarkerMult, 0.056f * aMarkerMult, aMarkerOpacity);
        Graphics::DrawLine(mSpawnZoneLeft, mSpawnZoneTop, mSpawnZoneRight, mSpawnZoneTop);
        Graphics::DrawLine(mSpawnZoneLeft, mSpawnZoneTop, mSpawnZoneLeft, mSpawnZoneBottom);
        Graphics::DrawLine(mSpawnZoneRight, mSpawnZoneTop, mSpawnZoneRight, mSpawnZoneBottom);
        
        Graphics::SetColor(0.65f * aMarkerMult, 0.65f * aMarkerMult, 0.105f * aMarkerMult, aMarkerOpacity);
        Graphics::DrawLine(mPeekZoneLeft, mPeekZoneTop, mPeekZoneRight, mPeekZoneTop);
        Graphics::DrawLine(mPeekZoneLeft, mPeekZoneTop, mPeekZoneLeft, mPlayZoneBottom);
        Graphics::DrawLine(mPeekZoneRight, mPeekZoneTop, mPeekZoneRight, mPlayZoneBottom);
        
        Graphics::SetColor(0.125f * aMarkerMult, 0.125f * aMarkerMult, 0.85f * aMarkerMult, aMarkerOpacity);
        Graphics::DrawLine(mCenterH, mSpawnZoneTop, mCenterH, mSpawnZoneBottom);
        Graphics::DrawLine(mSpawnZoneLeft, mCenterV, mSpawnZoneRight, mCenterV);
        
        Graphics::SetColor(0.125f * aMarkerMult, 0.125f * aMarkerMult, 0.65f * aMarkerMult, aMarkerOpacity);
        Graphics::DrawLine(mQuarterZoneLeft, mQuarterZoneTop, mQuarterZoneRight, mQuarterZoneTop);
        Graphics::DrawLine(mQuarterZoneLeft, mQuarterZoneBottom, mQuarterZoneRight, mQuarterZoneBottom);
        Graphics::DrawLine(mQuarterZoneLeft, mQuarterZoneTop, mQuarterZoneLeft, mQuarterZoneBottom);
        Graphics::DrawLine(mQuarterZoneRight, mQuarterZoneTop, mQuarterZoneRight, mQuarterZoneBottom);
        
        Graphics::SetColor(0.55f * aMarkerMult, 0.05f * aMarkerMult, 0.05f * aMarkerMult, aMarkerOpacity);
        Graphics::DrawLine(mExitZoneLeft, mExitZoneTop, mExitZoneRight, mExitZoneTop);
        Graphics::DrawLine(mExitZoneLeft, mExitZoneTop, mExitZoneLeft, mPlayZoneBottom);
        Graphics::DrawLine(mExitZoneRight, mExitZoneTop, mExitZoneRight, mPlayZoneBottom);
        
        Graphics::SetColor(0.15f * aMarkerMult, 0.15f * aMarkerMult, 0.15f * aMarkerMult, aMarkerOpacity);
        Graphics::DrawLine(mGameAreaLeft, mGameAreaTop, mGameAreaRight, mGameAreaTop);
        Graphics::DrawLine(mGameAreaLeft, mGameAreaBottom, mGameAreaRight, mGameAreaBottom);
        Graphics::DrawLine(mGameAreaLeft, mGameAreaTop, mGameAreaLeft, mGameAreaBottom);
        Graphics::DrawLine(mGameAreaRight, mGameAreaTop, mGameAreaRight, mGameAreaBottom);
        
        Graphics::SetColor();
        mSection.Draw();
    }
    
    Graphics::PipelineStateSetSpritePremultipliedBlending();
    Graphics::SetColor();
    FString aExportString = FString("Export: ") + FString(mExportIndex);
    gApp->mSysFontBold.Center(aExportString.c(), gDeviceWidth2, gSafeAreaInsetTop + 20.0f, 0.5f);
    
    
    
    //
    LevelWave *aWave = ((LevelWave *)mEditorSection.mWaveList.Fetch(WaveIndex()));
    if (aWave != NULL && (mFreeze == true)) {
        
        EnumList(LevelWaveSpawn, aSpawn, aWave->mSpawnList) {
            
            if (aSpawn->mCurrentWaitTime > 0) {
                
                FString aWaitString = FString("W: ") + FString(aSpawn->mCurrentWaitTick) + FString(" / ") + FString(aSpawn->mCurrentWaitTime);
                float aTextWidth = gApp->mSysFontBold.Width(aWaitString.c(), 0.5f);
                
                Graphics::PipelineStateSetShape2DAlphaBlending();
                Graphics::SetColor(0.25f, 0.125f, 0.685f, 0.75f);
                
                FVec2 aPoint = FVec2(aSpawn->mBaseX, aSpawn->mBaseY);
                aPoint = FCanvas::Convert(aPoint, gGame, this);
                Graphics::DrawRect(aPoint.mX - aTextWidth / 2.0f, aPoint.mY - 16.0f, aTextWidth, 32.0f);
                Graphics::PipelineStateSetSpritePremultipliedBlending();
                Graphics::SetColor();
                
                gApp->mSysFontBold.Center(aWaitString.c(), aPoint.mX, aPoint.mY, 0.5f);
                
            }
        }
        
        /*
        if (mCurrentWaitTime > 0) {
            if (mCurrentWaitTick < mCurrentWaitTime) {
                mCurrentWaitTick++;
            }
        }
        */
        
        
    }
    
    
}

void GameEditor::TouchDown(float pX, float pY, void *pData) {
    SelectClosestObject(pX, pY);
}

void GameEditor::TouchMove(float pX, float pY, void *pData) {
    
}

void GameEditor::TouchUp(float pX, float pY, void *pData) {
    
}

void GameEditor::TouchFlush() {
    
}

void GameEditor::KeyDown(int pKey) {
    
    if (gGame == NULL) {
        Log("Game doesn't exist?\n");
        return;
    }
    if (mPathEditor != NULL && mOverlay == mPathEditor) {
        return;
    }
    if (mFormationEditor != NULL && mOverlay == mFormationEditor) {
        return;
    }
    if (mPermEditor != NULL && mOverlay == mPermEditor) {
        return;
    }
    
    bool aShift = gKeyDownShift;
    bool aCtrl = gKeyDownCtrl;
    bool aAlt = gKeyDownAlt;
    
    if (mFreeze == true) {
        if (pKey == __KEY__LEFT) {
            
            if (aCtrl == true && aShift == true) {
                mFreezeFrame -= 500;
            } else if (aCtrl == true) {
                mFreezeFrame -= 50;
            } else if (aShift == true) {
                mFreezeFrame -= 10;
            } else {
                mFreezeFrame -= 1;
            }
        }
        
        if (pKey == __KEY__RIGHT) {
            if (aCtrl == true && aShift == true) {
                mFreezeFrame += 500;
            } else if (aCtrl == true) {
                mFreezeFrame += 50;
            } else if (aShift == true) {
                mFreezeFrame += 10;
            } else {
                mFreezeFrame += 1;
            }
        }
        
    }
    
    if (aCtrl) {
        if (pKey == __KEY__0) { mTestIndex = 0; LoadTest(); return; }
        if (pKey == __KEY__1) { mTestIndex = 1; LoadTest(); return; }
        if (pKey == __KEY__2) { mTestIndex = 2; LoadTest(); return; }
        if (pKey == __KEY__3) { mTestIndex = 3; LoadTest(); return; }
        if (pKey == __KEY__4) { mTestIndex = 4; LoadTest(); return; }
        if (pKey == __KEY__5) { mTestIndex = 5; LoadTest(); return; }
        if (pKey == __KEY__6) { mTestIndex = 6; LoadTest(); return; }
        if (pKey == __KEY__7) { mTestIndex = 7; LoadTest(); return; }
        if (pKey == __KEY__8) { mTestIndex = 8; LoadTest(); return; }
        if (pKey == __KEY__9) { mTestIndex = 9; LoadTest(); return; }
    } else {
        if (pKey == __KEY__0) { mExportIndex = 0; SaveConfig(); }
        if (pKey == __KEY__1) { mExportIndex = 1; SaveConfig(); }
        if (pKey == __KEY__2) { mExportIndex = 2; SaveConfig(); }
        if (pKey == __KEY__3) { mExportIndex = 3; SaveConfig(); }
        if (pKey == __KEY__4) { mExportIndex = 4; SaveConfig(); }
        if (pKey == __KEY__5) { mExportIndex = 5; SaveConfig(); }
        if (pKey == __KEY__6) { mExportIndex = 6; SaveConfig(); }
        if (pKey == __KEY__7) { mExportIndex = 7; SaveConfig(); }
        if (pKey == __KEY__8) { mExportIndex = 8; SaveConfig(); }
        if (pKey == __KEY__9) { mExportIndex = 9; SaveConfig(); }
    }
    
    if (pKey == __KEY__Z) {
        if (aShift == false && aCtrl == false && aAlt == false) {
            mFreeze = !mFreeze;
        }
    }
    
    if (pKey == __KEY__Q) {
        if (aShift == false && aCtrl == true && aAlt == false) {
            Clear();
        }
    }
    
    if (pKey == __KEY__ENTER) {
        if (aShift == false && aCtrl == true && aAlt == false) {
            Test();
        }
    }
    
    if (pKey == __KEY__E) {
        if (aShift == false && aCtrl == false && aAlt == false) {
            if (mSection.mCurrentWave) {
                OpenPathEditorForWave();
            }
        }
    }
    
    if (pKey == __KEY__K) {
        if (aShift == false && aCtrl == false && aAlt == false) {
            //KillAll();
            //DisposeAllObjects();
            gGame->DisposeAllObjects();
        }
        if (aShift == false && aCtrl == true && aAlt == false) {
            KillAllBalloons();
        }
    }
    
    if (pKey == __KEY__F) {
        if (aShift == false && aCtrl == false && aAlt == false) {
            OpenFormationEditor(NULL);
        }
        
        if (aShift == false && aCtrl == true && aAlt == false) {
            PickFormationForFormationEditor();
        }
    }
    
    if (pKey == __KEY__M) {
        if (aShift == false && aCtrl == false && aAlt == false) {
            OpenMotionMenu();
        }
        
        if (aShift == false && aCtrl == true && aAlt == false) {
            
        }
    }
    
    if (pKey == __KEY__T) {
        if (aShift == false && aCtrl == false && aAlt == false) {
            OpenAttachmentMenu();
        }
    }
    
    if (pKey == __KEY__Y) {
        if (aShift == false && aCtrl == false && aAlt == false) {
            OpenStyleMenu();
        }
    }
    
    if (pKey == __KEY__A) {
        if (aShift == false && aCtrl == true && aAlt == false) {
            WaveAdd();
        }
    }
    
    if (pKey == __KEY__O) {
        LevelWaveSpawnBlueprint *aSpawn = SpawnGet();
            Log("Formation Selected for WAVE SPAWN [%llx]\n", aSpawn);
            if (aSpawn != NULL) {
                PickFormationForSpawnNode();
            }
        
    }
    
    if (pKey == __KEY__DELETE) {
        WaveRemove();
    }
    
    if (pKey == __KEY__S) {
        Log("Hit S Shift[%d] Ctrl[%d] Alt[%d]\n", aShift, aCtrl, aAlt);
        if (aShift == false && aCtrl == true && aAlt == false) {
            SaveAt(mExportIndex);
        }
    }
    
    if (pKey == __KEY__L) {
        if (aShift == false && aCtrl == true && aAlt == false) { LoadAt(mExportIndex); }
    }
    
    if (pKey == __KEY__P) {
        if (aShift == false && aCtrl == false && aAlt == false) {
            OpenPermanentEditor();
        }
        if (aShift == false && aCtrl == true && aAlt == false) {
            mSection.WaveSelectPrev();
        }
    }
    
    if (pKey == __KEY__R) {
        if (aShift == false && aCtrl == false && aAlt == false) {
#ifdef EDITOR_MODE
            //Not need?
            //mEditorShowReferenced = !mEditorShowReferenced;
            
            RefreshPlayback();
#endif
        }
    }
    
    if (pKey == __KEY__N) {
        if (aShift == false && aCtrl == false && aAlt == false) {
            
        }
        if (aShift == false && aCtrl == true && aAlt == false) {
            mSection.WaveSelectNext();
        }
    }
}

void GameEditor::KeyUp(int pKey) {
    
}

void GameEditor::Notify(void *pSender, const char *pNotification) {
    if (FString("slider_update") == pNotification) {
        
    }
    if (FString("button_click") == pNotification) {
        
        
    }
    
    if (FString("formation_selected") == pNotification) {
        if (gSelectedFormation != NULL) {
            Log("SELECTED[%s]\n", gSelectedFormation->mID.c());
        }
        if (mPickFormationReason == 0) {
            Log("Formation Selected for Formation Editor...\n");
            OpenFormationEditor(gSelectedFormation);
        }
        if (mPickFormationReason == 1) {
            LevelWaveSpawnBlueprint *aSpawn = SpawnGet();
            Log("Formation Selected for WAVE SPAWN [%llx]\n", aSpawn);
            if (aSpawn != NULL) {
                aSpawn->mFormationID = gSelectedFormation->mID.c();
                RefreshPlayback();
            }
        }
        if (mPickFormationReason == 2) {
            LevelPermSpawnBlueprint *aSpawn = PermSpawnGet();
            Log("Formation Selected for PERM SPAWN [%llx]\n", aSpawn);
            if (aSpawn != NULL) {
                aSpawn->mFormationID = gSelectedFormation->mID.c();
                RefreshPlayback();
            }
            if (mPermEditor != NULL) {
                SetOverlay(mPermEditor);
            }
        }
        
        if (mPickFormationReason == 3) {
            LevelSectionPermBlueprint *aPerm = PermGet();
            Log("Formation Selected for PERM [%llx]\n", aPerm);
            if (aPerm != NULL) {
                aPerm->mFormationID = gSelectedFormation->mID.c();
                RefreshPlayback();
            }
            if (mPermEditor != NULL) {
                SetOverlay(mPermEditor);
            }
        }
        
        
        
        
        
    }
}

void GameEditor::DisposeObjectFromLevelData(GameObject *pObject) {
    
    
    
}

bool GameEditor::XConstraintInvertAllowed(int pConstraint) {
    
    if (pConstraint == X_CONSTRAINT_LEFT_EXIT) { return true; }
    if (pConstraint == X_CONSTRAINT_LEFT_SPAWN) { return true; }
    if (pConstraint == X_CONSTRAINT_LEFT_PEEK) { return true; }
    if (pConstraint == X_CONSTRAINT_LEFT_QUARTER) { return true; }
    if (pConstraint == X_CONSTRAINT_CENTER) { return true; }
    if (pConstraint == X_CONSTRAINT_RIGHT_QUARTER) { return true; }
    if (pConstraint == X_CONSTRAINT_RIGHT_PEEK) { return true; }
    if (pConstraint == X_CONSTRAINT_RIGHT_SPAWN) { return true; }
    if (pConstraint == X_CONSTRAINT_RIGHT_EXIT) { return true; }
    
    return false;
}

int GameEditor::XConstraintInvert(int pConstraint) {
    if (pConstraint == X_CONSTRAINT_LEFT_EXIT) { return X_CONSTRAINT_RIGHT_EXIT; }
    if (pConstraint == X_CONSTRAINT_LEFT_SPAWN) { return X_CONSTRAINT_RIGHT_SPAWN; }
    if (pConstraint == X_CONSTRAINT_LEFT_PEEK) { return X_CONSTRAINT_RIGHT_PEEK; }
    if (pConstraint == X_CONSTRAINT_LEFT_QUARTER) { return X_CONSTRAINT_RIGHT_QUARTER; }
    if (pConstraint == X_CONSTRAINT_CENTER) { return X_CONSTRAINT_CENTER; }
    if (pConstraint == X_CONSTRAINT_RIGHT_QUARTER) { return X_CONSTRAINT_LEFT_QUARTER; }
    if (pConstraint == X_CONSTRAINT_RIGHT_PEEK) { return X_CONSTRAINT_LEFT_PEEK; }
    if (pConstraint == X_CONSTRAINT_RIGHT_SPAWN) { return X_CONSTRAINT_LEFT_SPAWN; }
    if (pConstraint == X_CONSTRAINT_RIGHT_EXIT) { return X_CONSTRAINT_LEFT_EXIT; }
    
    return X_CONSTRAINT_NONE;
}

int GameEditor::ClosestXConstraint(float pX) {
    int aResult = X_CONSTRAINT_LEFT_EXIT;
    float aBestDist = fabsf(mExitZoneLeft - pX);
    float aDist = fabsf(mSpawnZoneLeft - pX);
    if (aDist < aBestDist) { aBestDist = aDist; aResult = X_CONSTRAINT_LEFT_SPAWN; }
    aDist = fabsf(mPeekZoneLeft - pX);
    if (aDist < aBestDist) { aBestDist = aDist; aResult = X_CONSTRAINT_LEFT_PEEK; }
    aDist = fabsf(mQuarterZoneLeft - pX);
    if (aDist < aBestDist) { aBestDist = aDist; aResult = X_CONSTRAINT_LEFT_QUARTER; }
    aDist = fabsf(mCenterH - pX);
    if (aDist < aBestDist) { aBestDist = aDist; aResult = X_CONSTRAINT_CENTER; }
    aDist = fabsf(mQuarterZoneRight - pX);
    if (aDist < aBestDist) { aBestDist = aDist; aResult = X_CONSTRAINT_RIGHT_QUARTER; }
    aDist = fabsf(mPeekZoneRight - pX);
    if (aDist < aBestDist) { aBestDist = aDist; aResult = X_CONSTRAINT_RIGHT_PEEK; }
    aDist = fabsf(mSpawnZoneRight - pX);
    if (aDist < aBestDist) { aBestDist = aDist; aResult = X_CONSTRAINT_RIGHT_SPAWN; }
    aDist = fabsf(mExitZoneRight - pX);
    if (aDist < aBestDist) { aBestDist = aDist; aResult = X_CONSTRAINT_RIGHT_EXIT; }
    return aResult;
}

int GameEditor::ClosestYConstraint(float pY) {
    int aResult = Y_CONSTRAINT_TOP_EXIT;
    float aBestDist = fabsf(mExitZoneTop - pY);
    float aDist = fabsf(mSpawnZoneTop - pY);
    if (aDist < aBestDist) { aBestDist = aDist; aResult = Y_CONSTRAINT_TOP_SPAWN; }
    aDist = fabsf(mPeekZoneTop - pY);
    if (aDist < aBestDist) { aBestDist = aDist; aResult = Y_CONSTRAINT_TOP_PEEK; }
    aDist = fabsf(mQuarterZoneTop - pY);
    if (aDist < aBestDist) { aBestDist = aDist; aResult = Y_CONSTRAINT_TOP_QUARTER; }
    aDist = fabsf(mCenterV - pY);
    if (aDist < aBestDist) { aBestDist = aDist; aResult = Y_CONSTRAINT_CENTER; }
    aDist = fabsf(mQuarterZoneBottom - pY);
    if (aDist < aBestDist) { aBestDist = aDist; aResult = Y_CONSTRAINT_BOTTOM_QUARTER; }
    aDist = fabsf(mPlayZoneBottom - pY);
    if (aDist < aBestDist) { aBestDist = aDist; aResult = Y_CONSTRAINT_BOTTOM; }
    return aResult;
}

int GameEditor::NextXConstraintf(float pX) {
    return NextXConstraint(ClosestXConstraint(pX));
}

int GameEditor::PrevXConstraintf(float pX) {
    return PrevXConstraint(ClosestXConstraint(pX));
}

int GameEditor::NextYConstraintf(float pY) {
    return NextYConstraint(ClosestYConstraint(pY));
}

int GameEditor::PrevYConstraintf(float pY) {
    return PrevYConstraint(ClosestYConstraint(pY));
}

int GameEditor::NextXConstraint(int pConstraint) {
    if (pConstraint == X_CONSTRAINT_RIGHT_EXIT || pConstraint == X_CONSTRAINT_RIGHT_SPAWN) { return X_CONSTRAINT_RIGHT_EXIT; }
    if (pConstraint == X_CONSTRAINT_RIGHT_PEEK) { return X_CONSTRAINT_RIGHT_SPAWN; }
    if (pConstraint == X_CONSTRAINT_RIGHT_QUARTER) { return X_CONSTRAINT_RIGHT_PEEK; }
    if (pConstraint == X_CONSTRAINT_CENTER) { return X_CONSTRAINT_RIGHT_QUARTER; }
    if (pConstraint == X_CONSTRAINT_LEFT_QUARTER) { return X_CONSTRAINT_CENTER; }
    if (pConstraint == X_CONSTRAINT_LEFT_PEEK) { return X_CONSTRAINT_LEFT_QUARTER; }
    if (pConstraint == X_CONSTRAINT_LEFT_SPAWN) { return X_CONSTRAINT_LEFT_PEEK; }
    if (pConstraint == X_CONSTRAINT_LEFT_EXIT) { return X_CONSTRAINT_LEFT_SPAWN; }
    return X_CONSTRAINT_LEFT_EXIT;
}

int GameEditor::PrevXConstraint(int pConstraint) {
    if (pConstraint == X_CONSTRAINT_LEFT_EXIT || pConstraint == X_CONSTRAINT_LEFT_SPAWN) { return X_CONSTRAINT_LEFT_EXIT; }
    if (pConstraint == X_CONSTRAINT_LEFT_PEEK) { return X_CONSTRAINT_LEFT_SPAWN; }
    if (pConstraint == X_CONSTRAINT_LEFT_QUARTER) { return X_CONSTRAINT_LEFT_PEEK; }
    if (pConstraint == X_CONSTRAINT_CENTER) { return X_CONSTRAINT_LEFT_QUARTER; }
    if (pConstraint == X_CONSTRAINT_RIGHT_QUARTER) { return X_CONSTRAINT_CENTER; }
    if (pConstraint == X_CONSTRAINT_RIGHT_PEEK) { return X_CONSTRAINT_RIGHT_QUARTER; }
    if (pConstraint == X_CONSTRAINT_RIGHT_SPAWN) { return X_CONSTRAINT_RIGHT_PEEK; }
    if (pConstraint == X_CONSTRAINT_RIGHT_EXIT) { return X_CONSTRAINT_RIGHT_SPAWN; }
    return X_CONSTRAINT_RIGHT_EXIT;
}

int GameEditor::NextYConstraint(int pConstraint) {
    if (pConstraint == Y_CONSTRAINT_BOTTOM || pConstraint == Y_CONSTRAINT_BOTTOM_QUARTER) { return Y_CONSTRAINT_BOTTOM; }
    if (pConstraint == Y_CONSTRAINT_BOTTOM_QUARTER) { return Y_CONSTRAINT_BOTTOM; }
    if (pConstraint == Y_CONSTRAINT_CENTER) { return Y_CONSTRAINT_BOTTOM_QUARTER; }
    if (pConstraint == Y_CONSTRAINT_TOP_QUARTER) { return Y_CONSTRAINT_CENTER; }
    if (pConstraint == Y_CONSTRAINT_TOP_PEEK) { return Y_CONSTRAINT_TOP_QUARTER; }
    if (pConstraint == Y_CONSTRAINT_TOP_SPAWN) { return Y_CONSTRAINT_TOP_PEEK; }
    if (pConstraint == Y_CONSTRAINT_TOP_EXIT) { return Y_CONSTRAINT_TOP_SPAWN; }
    return Y_CONSTRAINT_TOP_EXIT;
}

int GameEditor::PrevYConstraint(int pConstraint) {
    if (pConstraint == Y_CONSTRAINT_TOP_EXIT || pConstraint == Y_CONSTRAINT_TOP_SPAWN) { return Y_CONSTRAINT_TOP_EXIT; }
    if (pConstraint == Y_CONSTRAINT_TOP_PEEK) { return Y_CONSTRAINT_TOP_SPAWN; }
    if (pConstraint == Y_CONSTRAINT_TOP_QUARTER) { return Y_CONSTRAINT_TOP_PEEK; }
    if (pConstraint == Y_CONSTRAINT_CENTER) { return Y_CONSTRAINT_TOP_QUARTER; }
    if (pConstraint == Y_CONSTRAINT_BOTTOM_QUARTER) { return Y_CONSTRAINT_CENTER; }
    if (pConstraint == Y_CONSTRAINT_BOTTOM) { return Y_CONSTRAINT_BOTTOM_QUARTER; }
    return Y_CONSTRAINT_BOTTOM;
}

void GameEditor::SetOverlay(FCanvas *pCanvas) {
    if (mOverlay) {
        if (mOverlay == pCanvas) {
            return;
        }
        mOverlay->Deactivate();
        mOverlay = NULL;
    }
    if (pCanvas) {
        mOverlay = pCanvas;
        mOverlay->Activate();
    }
}

int GameEditor::SpeedConvertSegmentToType(int pSegmentIndex) {
    int aResult = SPEED_CLASS_MEDIUM_FAST;
    if (pSegmentIndex == 0) { aResult = SPEED_CLASS_DEFAULT; }
    if (pSegmentIndex == 1) { aResult = SPEED_CLASS_EXTRA_SLOW; }
    if (pSegmentIndex == 2) { aResult = SPEED_CLASS_SLOW; }
    if (pSegmentIndex == 3) { aResult = SPEED_CLASS_MEDIUM_SLOW; }
    if (pSegmentIndex == 4) { aResult = SPEED_CLASS_MEDIUM; }
    if (pSegmentIndex == 5) { aResult = SPEED_CLASS_MEDIUM_FAST; }
    if (pSegmentIndex == 6) { aResult = SPEED_CLASS_FAST; }
    if (pSegmentIndex == 7) { aResult = SPEED_CLASS_EXTRA_FAST; }
    if (pSegmentIndex == 8) { aResult = SPEED_CLASS_INSANE; }
    return aResult;
}

int GameEditor::SpeedConvertTypeToSegment(int pType) {
    int aResult = 0;
    if (pType == SPEED_CLASS_DEFAULT)      { aResult = 0; }
    if (pType == SPEED_CLASS_EXTRA_SLOW)   { aResult = 1; }
    if (pType == SPEED_CLASS_SLOW)         { aResult = 2; }
    if (pType == SPEED_CLASS_MEDIUM_SLOW)  { aResult = 3; }
    if (pType == SPEED_CLASS_MEDIUM)       { aResult = 4; }
    if (pType == SPEED_CLASS_MEDIUM_FAST)  { aResult = 5; }
    if (pType == SPEED_CLASS_FAST)         { aResult = 6; }
    if (pType == SPEED_CLASS_EXTRA_FAST)   { aResult = 7; }
    if (pType == SPEED_CLASS_INSANE)       { aResult = 8; }
    return aResult;
}

void GameEditor::RefreshPlayback() {
    
    
    if (mIsRefreshingPlayback == true) {
        Log("Niffing refreshing...\n");
        return;
    }
    
    gRand.Seed(mRandomSeed);
    
    mIsRefreshingPlayback = true;
    
    //KillAll();
    
    if (gGame != NULL) {
        gGame->DisposeAllObjects();
    }
    
    mEditorSection.Reset();
    
    if (mPermEditor != NULL && mPermEditor == mOverlay) {
        LevelSectionPermBlueprint *aPerm = PermGet();
        if (aPerm != NULL) {
            mPermEditor->mPathSpeedClassIndex = SpeedConvertTypeToSegment(aPerm->mPath.mSpeedClass);
        }
    }
    
    if (mSection.mCurrentWave != NULL) {
        mSpeedClassIndex = SpeedConvertTypeToSegment(mSection.mCurrentWave->mPath.mSpeedClass);
    }
    
    if (true) {
        int aWaveIndex = WaveIndex();
        if (mEditorPlaybackFromCurrentWave == true && aWaveIndex >= 0 && (mFreeze == false)) {
            mEditorSection.mStartWaveIndex = aWaveIndex;
        } else {
            mEditorSection.mStartWaveIndex = 0;
        }
        mSection.Build();
    }
    
    mEditorSection.Spawn();
    
    mIsRefreshingPlayback = false;
}

void GameEditor::RefreshPlaybackSpeed() {
    if (mSection.mCurrentWave != NULL) {
        mSection.mCurrentWave->mPath.mSpeedClass = SpeedConvertSegmentToType(mSpeedClassIndex);
    }
}

void GameEditor::KillAllBalloons() {
    if (gGame != NULL) {
        EnumList(GameObject, aObject, gGame->mBalloonList.mObjectList) {
            gGame->DisposeObject(aObject);
        }
    }
}

void GameEditor::KillAllNonBalloons() {
    if (gGame != NULL) {
        EnumList(GameObject, aObject, gGame->mDartList.mObjectList) {
            gGame->DisposeObject(aObject);
        }
        EnumList(GameObject, aObject, gGame->mBrickHeadList.mObjectList) {
            gGame->DisposeObject(aObject);
        }
        EnumList(GameObject, aObject, gGame->mTurtleList.mObjectList) {
            gGame->DisposeObject(aObject);
        }
        EnumList(GameObject, aObject, gGame->mBombList.mObjectList) {
            gGame->DisposeObject(aObject);
        }
    }
}

void GameEditor::KillAllPerms() {
    if (gGame != NULL) {
        EnumList(GameObject, aObject, gGame->mBalloonList.mObjectList) {
            if (aObject->mDidOriginateAsPermanent == true) {
                gGame->DisposeObject(aObject);
            }
        }
        EnumList(GameObject, aObject, gGame->mDartList.mObjectList) {
            if (aObject->mDidOriginateAsPermanent == true) {
                gGame->DisposeObject(aObject);
            }
        }
        EnumList(GameObject, aObject, gGame->mBrickHeadList.mObjectList) {
            if (aObject->mDidOriginateAsPermanent == true) {
                gGame->DisposeObject(aObject);
            }
        }
        EnumList(GameObject, aObject, gGame->mTurtleList.mObjectList) {
            if (aObject->mDidOriginateAsPermanent == true) {
                gGame->DisposeObject(aObject);
            }
        }
        EnumList(GameObject, aObject, gGame->mBombList.mObjectList) {
            if (aObject->mDidOriginateAsPermanent == true) {
                gGame->DisposeObject(aObject);
            }
        }
    }
}

void GameEditor::KillAllWaves() {
    if (gGame != NULL) {
        EnumList(GameObject, aObject, gGame->mBalloonList.mObjectList) {
            if (aObject->mDidOriginateOnWave == true) {
                gGame->DisposeObject(aObject);
            }
        }
        EnumList(FreeLife, aObject, gGame->mFreeLifeList.mObjectList) {
            if (aObject->mDidOriginateOnWave == true) {
                gGame->DisposeObject(aObject);
            }
        }
        EnumList(GameObject, aObject, gGame->mDartList.mObjectList) {
            if (aObject->mDidOriginateOnWave == true) {
                gGame->DisposeObject(aObject);
            }
        }
        EnumList(GameObject, aObject, gGame->mBrickHeadList.mObjectList) {
            if (aObject->mDidOriginateOnWave == true) {
                gGame->DisposeObject(aObject);
            }
        }
        EnumList(GameObject, aObject, gGame->mTurtleList.mObjectList) {
            if (aObject->mDidOriginateOnWave == true) {
                gGame->DisposeObject(aObject);
            }
        }
        EnumList(GameObject, aObject, gGame->mBombList.mObjectList) {
            if (aObject->mDidOriginateOnWave == true) {
                gGame->DisposeObject(aObject);
            }
        }
    }
}

void GameEditor::WaveAdd() {
    mSection.WaveAdd();
    OpenPathEditorForWave();
}

void GameEditor::WaveRemove() {
    mSection.WaveRemove();
}

void GameEditor::WaveSelectNext() {
    mSection.WaveSelectNext();
}

void GameEditor::WaveSelectPrev() {
    mSection.WaveSelectPrev();
}

void GameEditor::WaveDeselect() {
    mSection.WaveDeselect();
}

void GameEditor::WaveMoveUp() {
    mSection.WaveMoveUp();
}

void GameEditor::WaveMoveDown() {
    mSection.WaveMoveDown();
}

void GameEditor::WaveSelect(int pIndex) {
    mSection.WaveSelect(pIndex);
    if (mEditorPlaybackEnabled) {
        RefreshPlayback();
    }
}

void GameEditor::WaveFlipH() {
    if (mSection.mCurrentWave != NULL) {
        mSection.mCurrentWave->FlipH();
        RefreshPlayback();
    }
    
}

int GameEditor::WaveCount(int pIndex) {
    return mSection.WaveCount(pIndex);
}

int GameEditor::WaveIndex() {
    for (int i=0;i<mSection.mWaveList.mCount;i++) {
        LevelWaveBlueprint *aWave = (LevelWaveBlueprint *)mSection.mWaveList[i];
        if (aWave == mSection.mCurrentWave) {
            return i;
        }
    }
    return -1;
}

void GameEditor::SpawnSelect(int pIndex) {
    if (mSection.mCurrentWave != NULL) {
        mSection.mCurrentWave->mSelectedSpawnIndex = pIndex;
        
        //TODO: For some reason we weren't doing this. Do we remember why?
        //if (mEditorPlaybackEnabled == true) {
        //    RefreshPlayback();
        //}
    }
}

int GameEditor::SpawnIndex() {
    if (mSection.mCurrentWave != NULL) {
        return mSection.mCurrentWave->mSelectedSpawnIndex;
    }
    return 0;
}

LevelWaveSpawnBlueprint *GameEditor::SpawnGet() {
    
    LevelWaveSpawnBlueprint *aResult = NULL;
    
    int aIndex = SpawnIndex();
    if (mSection.mCurrentWave != NULL) {
        if (aIndex >= 0 && aIndex < mSection.mCurrentWave->mSpawnCount) {
            aResult = &(mSection.mCurrentWave->mSpawn[aIndex]);
        }
    }
    return aResult;
}

void GameEditor::SpawnClearFormation() {
    if (mOverlay == mPermEditor && mPermEditor != NULL) {
        LevelPermSpawnBlueprint *aSpawn = PermSpawnGet();
        if (aSpawn != NULL) {
            aSpawn->mFormationID.Clear();
        } else {
            LevelSectionPermBlueprint *aPerm = PermGet();
            if (aPerm != NULL) {
                aPerm->mFormationID.Clear();
            }
        }
    } else {
        LevelWaveSpawnBlueprint *aSpawn = SpawnGet();
        if (aSpawn != NULL) {
            aSpawn->mFormationID.Clear();
        }
    }
    RefreshPlayback();
}

void GameEditor::SpawnPickType(int pType) {
    
    if (mOverlay == mPermEditor && mPermEditor != NULL) {
        LevelPermSpawnBlueprint *aSpawn = PermSpawnGet();
        if (aSpawn != NULL) {
            aSpawn->mFormationID.Clear();
            aSpawn->mObjectType = pType;
        } else {
            
            LevelSectionPermBlueprint *aPerm = PermGet();
            if (aPerm != NULL) {
                aPerm->mFormationID.Clear();
                aPerm->mObjectType = pType;
            }
        }
    } else {
        LevelWaveSpawnBlueprint *aSpawn = SpawnGet();
        if (aSpawn != NULL) {
            aSpawn->mFormationID.Clear();
            aSpawn->mObjectType = pType;
        }
    }
    RefreshPlayback();
}

void GameEditor::SpawnPickBalloon() {
    SpawnPickType(GAME_OBJECT_TYPE_BALLOON);
}

void GameEditor::SpawnPickBrickHead() {
    SpawnPickType(GAME_OBJECT_TYPE_BRICKHEAD);
}

void GameEditor::SpawnPickBomb() {
    SpawnPickType(GAME_OBJECT_TYPE_BOMB);
}

void GameEditor::SpawnPickTurtle() {
    SpawnPickType(GAME_OBJECT_TYPE_TURTLE);
}

void GameEditor::PermSelect(int pIndex) {
    mSection.mCurrentPerm = (LevelSectionPermBlueprint *)mSection.mPermList.Fetch(pIndex);
}

int GameEditor::PermIndex() {
    return mSection.mPermList.Find(mSection.mCurrentPerm);
}

LevelSectionPermBlueprint *GameEditor::PermGet() {
    return mSection.mCurrentPerm;
}

void GameEditor::PermDelete() {
    mSection.PermRemove();
}

LevelPermSpawnBlueprint *GameEditor::PermSpawnGet() {
    LevelSectionPermBlueprint *aPerm = PermGet();
    if (aPerm != NULL) {
        if (aPerm->IsPathPerm() && aPerm->mSelectedSpawnIndex >= 0 && aPerm->mSelectedSpawnIndex < aPerm->mSpawnCount) {
            return &aPerm->mSpawn[aPerm->mSelectedSpawnIndex];
        }
    }
    return NULL;
}

LevelFormationConfigurationBlueprint *GameEditor::FormationConfigurationGet() {
    
    LevelFormationConfigurationBlueprint *aResult = NULL;
    
    if (mOverlay == mPermEditor && mPermEditor != NULL) {
        LevelPermSpawnBlueprint *aSpawn = PermSpawnGet();
        if (aSpawn != NULL) {
            return &(aSpawn->mFormationConfiguration);
        } else {
            
            LevelSectionPermBlueprint *aPerm = PermGet();
            if (aPerm != NULL) {
                return &(aPerm->mFormationConfiguration);
            }
        }
    } else {
        LevelWaveSpawnBlueprint *aSpawn = SpawnGet();
        if (aSpawn != NULL) {
            return &(aSpawn->mFormationConfiguration);
        }
    }
    
    return aResult;
}


void GameEditor::OpenPathEditorForWave() {
    if (mSection.mCurrentWave == NULL) { Log("Must have wave...\n"); return; }
    mPathEditor = new GamePathEditor(this);
    mPathEditor->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    mPathEditor->mName = "{Path Editor}";
    AddChild(mPathEditor);
    mPathEditor->SetUp(mSection.mCurrentWave);
    SetOverlay(mPathEditor);
}

void GameEditor::ClosePathEditor() {
    SetOverlay(mToolContainer);
    if (mPathEditor) {
        mPathEditor->Kill();
        mPathEditor = NULL;
    }
}

void GameEditor::OpenPermanentEditor() {
    
    mPermEditor = new GamePermanentEditor(this);
    mPermEditor->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    mPermEditor->mName = "{Perm Editor}";
    AddChild(mPermEditor);
    mPermEditor->SetUp();
    SetOverlay(mPermEditor);
}

void GameEditor::ClosePermanentEditor() {
    SetOverlay(mToolContainer);
    if (mPermEditor) {
        mPermEditor->Kill();
        mPermEditor = NULL;
    }
    RefreshPlayback();
}

void GameEditor::OpenFormationEditor(LevelFormation *pFormation) {
    
    mFormationEditor = new GameFormationEditor(this);
    mFormationEditor->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    mFormationEditor->mName = "{Form Editor}";
    AddChild(mFormationEditor);
    
    LevelFormationBlueprint *aFormationBlueprint = NULL;
    if (pFormation != NULL) {
        aFormationBlueprint = new LevelFormationBlueprint();
        FJSON aJSON;
        aJSON.Load(pFormation->mID.c());
        aFormationBlueprint->Load(aJSON.mRoot, pFormation->mID);
        if (aFormationBlueprint->IsValid() == false) {
            delete aFormationBlueprint;
            aFormationBlueprint = NULL;
        }
    }
    
    mFormationEditor->SetUp(aFormationBlueprint);
    SetOverlay(mFormationEditor);
}

void GameEditor::CloseFormationEditor() {
    SetOverlay(mToolContainer);
    if (mFormationEditor) {
        mFormationEditor->Kill();
        mFormationEditor = NULL;
    }
}

void GameEditor::PickFormationForFormationEditor() {
    PickFormation(0);
}

void GameEditor::PickFormationForSpawnNode() {
    LevelWaveSpawnBlueprint *aSpawn = SpawnGet();
    if (aSpawn == NULL) {
        Log("NO SPAWN IS SELECTED... CANNOT PICK...\n\n");
        return;
    }
    PickFormation(1);
}

void GameEditor::PickFormationForPerm() {
    LevelSectionPermBlueprint *aPerm = PermGet();
    if (aPerm == NULL) {
        Log("NO PERM PERM PERM IS AVAILABLE... CANNOT PICK...\n\n");
        return;
    }
    PickFormation(3);
}

void GameEditor::PickFormationForPermSpawnNode() {
    
    
    //PermGet()
    
    LevelPermSpawnBlueprint *aSpawn = PermSpawnGet();
    if (aSpawn == NULL) {
        Log("NO PERM SPAWN IS AVAILABLE... CANNOT PICK...\n\n");
        return;
    }
    PickFormation(2);
}


void GameEditor::PickFormation(int pReason) {
    
    SetOverlay(mToolContainer);
    
    mPickFormationReason = pReason;
    EditorMenuFormationPicker *aFormationPicker = new EditorMenuFormationPicker();
    mToolContainer->AddChild(aFormationPicker);
    gNotify.Register(this, aFormationPicker, "formation_selected");
    
}

void GameEditor::OpenSpawnMenu() {
    if (mMenuSpawn == NULL) {
        mMenuSpawn = new EditorMenuSpawn(this);
        mToolContainer->AddChild(mMenuSpawn);
        mMenuSpawn->SetFrame(gDeviceWidth - (gSafeAreaInsetRight + 14.0f + 400.0f),
                             gSafeAreaInsetTop, 400.0f, 520.0f);
    }
}

void GameEditor::OpenWavePickerMenu() {
    if (mMenuWavesPicker == NULL) {
        mMenuWavesPicker = new EditorMenuWavesPicker(this);
        mToolContainer->AddChild(mMenuWavesPicker);
        mMenuWavesPicker->SetFrame(gDeviceWidth - (gSafeAreaInsetRight + 14.0f + 400.0f),
                                   (gDeviceHeight - gSafeAreaInsetBottom - 2.0f) - (154.0f + 134.0f + 2.0f), 400.0f, 154.0f);
    }
}

void GameEditor::OpenSpawnPickerMenu() {
    if (mMenuSpawnPicker == NULL) {
        mMenuSpawnPicker = new EditorMenuSpawnPicker(this);
        mToolContainer->AddChild(mMenuSpawnPicker);
        mMenuSpawnPicker->SetFrame(gDeviceWidth - (gSafeAreaInsetRight + 14.0f + 400.0f),
                                   (gDeviceHeight - gSafeAreaInsetBottom - 2.0f) - 134.0f, 400.0f, 154.0f);
    }
}

void GameEditor::OpenAttachmentMenu() {
    if (mMenuAttachment == NULL) {
        mMenuAttachment = new EditorMenuAttachment(this);
        mToolContainer->AddChild(mMenuAttachment);
        mMenuAttachment->SetFrame(gDeviceWidth2 + 200.0f,
                                  (gDeviceHeight - gSafeAreaInsetBottom) - 740.0f - 2.0f, 400.0f, 740.0f);
    }
}

void GameEditor::OpenObjectClearingMenu() {
    
    if (mMenuObjectClearing == NULL) {
        mMenuObjectClearing = new EditorMenuObjectClearing(this);
        mToolContainer->AddChild(mMenuObjectClearing);
        mMenuObjectClearing->SetFrame(gDeviceWidth2 / 2.0f - 420.0f / 2.0f, 250.0f, 420.0f, 400.0f);
    }
}

void GameEditor::OpenMotionMenu() {
    
    if (mMenuMotion == NULL) {
        mMenuMotion = new EditorMenuMotion(this);
        mToolContainer->AddChild(mMenuMotion);
        mMenuMotion->SetFrame(gDeviceWidth2 / 2.0f - 420.0f / 2.0f, 130.0f, 420.0f, 600.0f);
    }
}

void GameEditor::OpenStyleMenu() {
    if (mMenuStyle == NULL) {
        mMenuStyle = new EditorMenuStyle(this);
        mToolContainer->AddChild(mMenuStyle);
        mMenuStyle->SetFrame(gDeviceWidth2 / 2.0f - 280.0f / 2.0f, 160.0f, 420.0f, 500.0f);
    }
}





void GameEditor::Test() {
    Autosave();
    
    FString aTestPath = gDirDocuments + FString("editor_test_section.json");
    Save(aTestPath.c());
    
    
#ifdef EDITOR_MODE
    gApp->EditorTestSwitchToGame();
    
#endif

    
    
}

void GameEditor::Clear() {
    FString aRecoverPath = gDirDocuments + FString("clear_backup.json");
    Save(aRecoverPath.c());
    
    ClosePathEditor();
    mSection.Reset();
    
    mEditorSection.Reset();
    
    
    //KillAll();
    gGame->DisposeAllObjects();
    
    
    RefreshPlayback();
}

void GameEditor::LoadCleared() {
    for (int i=0;i<20;i++) {
        FString aRecoverPath = gDirDocuments + FString("clear_backup.json");
        Load(aRecoverPath.c());
    }
}

void GameEditor::Autosave() {
    if (mTestMode == false) {
        FString aAutosavePath = gDirDocuments + FString("editor_autosave_") + FString(mExportIndex) + FString(".json");
        Save(aAutosavePath.c());
    }
}

void GameEditor::Autoload() {
    FString aAutosavePath = gDirDocuments + FString("editor_autosave_") + FString(mExportIndex) + FString(".json");
    Load(aAutosavePath.c());
}

void GameEditor::SelectClosestObject(float pX, float pY) {
    LevelWaveBlueprint *aClosestWave = NULL;
    float aClosestWaveDist = 80.0f * 80.0f;
    for (int i=mSection.mWaveList.mCount - 1;i>=0;i--) {
        LevelWaveBlueprint *aWave = (LevelWaveBlueprint *)mSection.mWaveList[i];
        float aDist = 80.0f * 80.0f;
        int aIndex = aWave->mPath.GetClosestIndex(pX, pY, aDist);
        if (aIndex != -1) {
            if (aDist < aClosestWaveDist) {
                aClosestWaveDist = aDist;
                aClosestWave = aWave;
            }
        }
    }
    
    for (int i=mSection.mWaveList.mCount - 1;i>=0;i--) {
        LevelWaveBlueprint *aWave = (LevelWaveBlueprint *)mSection.mWaveList[i];
        float aDist = 80.0f * 80.0f;
        aWave->mPath.GetClosestPointOnLine(pX, pY, aDist);
        if (aDist < aClosestWaveDist) {
            aClosestWaveDist = aDist;
            aClosestWave = aWave;
        }
    }
    
    
    if (aClosestWave) {
        mSection.mCurrentWave = aClosestWave;
    } else {
        mSection.mCurrentWave = NULL;
    }
    
    RefreshPlayback();
}

void GameEditor::SaveAt(int pIndex) {
    mTestMode = false;
    FString aPath = gDirDocuments + FString("export_section_") + FString(pIndex) + FString(".json");
    Save(aPath.c());
}

void GameEditor::LoadAt(int pIndex) {
    mTestMode = false;
    FString aPath = gDirDocuments + FString("export_section_") + FString(pIndex) + FString(".json");
    Load(aPath.c());
}

void GameEditor::LoadTest() {
    mTestMode = true;
    
    FString aNumberString = FString(mTestIndex);
    
    while (aNumberString.mLength < 2) {
        aNumberString = FString("0") + aNumberString;
    }
    
    FString aPath = FString("test_section_") + aNumberString;
    Log("Loading Test: %s\n", aPath.c());
    
    Load(aPath.c());
}



void GameEditor::Save(const char *pFile) {
    FJSON aJSON;
    aJSON.mRoot = mSection.Save();
    aJSON.Save(pFile);
}

void GameEditor::Load(const char *pFile) {
    
    ClosePathEditor();
    CloseFormationEditor();
    
    FJSON aJSON;
    aJSON.Load(pFile);
    mSection.Load(aJSON.mRoot);
    
    //Moved out of load procedure...
    EnumList(LevelWaveBlueprint, aWaveBlueprint, mSection.mWaveList) {
        aWaveBlueprint->ApplyEditorConstraints();
    }
    
    EnumList(LevelSectionPermBlueprint, aPerm, mSection.mPermList) {
        aPerm->ApplyEditorConstraints();
    }
    
    RefreshPlayback();
}


void GameEditor::SaveConfig() {
    FString aPath = gDirDocuments + FString("editor_config.json");
    FJSON aJSON;
    FJSONNode *aConfigNode = new FJSONNode();
    aJSON.mRoot = aConfigNode;
    aConfigNode->AddDictionaryInt("export_index", mExportIndex);
    aJSON.Save(aPath.c());
}

void GameEditor::LoadConfig() {
    FString aPath = gDirDocuments + FString("editor_config.json");
    FJSON aJSON;
    aJSON.Load(aPath.c());
    FJSONNode *aConfigNode = aJSON.mRoot;
    if (aConfigNode == NULL) return;
    mExportIndex = aConfigNode->GetInt("export_index", mExportIndex);
}




void GameEditor::EditorRestartWave() {
    
}


void GameEditor::EditorRestartSection() {
    
}


void GameEditor::CopyWave() {
    LevelWaveBlueprint *aWave = mSection.mCurrentWave;
    if (aWave == NULL) {
        printf("Cannot CopyWave()\n");
        return;
    }
    
    FString aPath = gDirDocuments + FString("editor_pasteboard_wave.json");
    FJSON aJSON;
    aJSON.mRoot = aWave->Save();
    aJSON.Save(aPath.c());
}

void GameEditor::CopyWaveSpawn() {
    LevelWaveSpawnBlueprint *aSpawn = SpawnGet();
    if (aSpawn == NULL) {
        printf("Cannot CopyWaveSpawn()\n");
        return;
    }
    
    FString aPath = gDirDocuments + FString("editor_pasteboard_wave_spawn.json");
    FJSON aJSON;
    aJSON.mRoot = aSpawn->Save();
    aJSON.Save(aPath.c());
}

void GameEditor::CopyPerm() {
    LevelSectionPermBlueprint *aPerm = PermGet();
    if (aPerm == NULL) {
        printf("Cannot CopyPerm()\n");
        return;
    }
    
    FString aPath = gDirDocuments + FString("editor_pasteboard_perm.json");
    FJSON aJSON;
    aJSON.mRoot = aPerm->Save();
    aJSON.Save(aPath.c());
    
}

void GameEditor::CopyPermSpawn() {
    LevelPermSpawnBlueprint *aSpawn = PermSpawnGet();
    if (aSpawn == NULL) {
        printf("Cannot CopyPermSpawn()\n");
        return;
    }
    
    FString aPath = gDirDocuments + FString("editor_pasteboard_perm_spawn.json");
    FJSON aJSON;
    aJSON.mRoot = aSpawn->Save();
    aJSON.Save(aPath.c());
}

void GameEditor::CopyMotion(LevelMotionControllerBlueprint *pMotion) {
    if (pMotion == NULL) {
        printf("Cannot Copy Motion... Motion Doesn't Exist..\n");
        return;
    }
    FString aPath = gDirDocuments + FString("editor_pasteboard_motion.json");
    FJSON aJSON;
    aJSON.mRoot = pMotion->Save();
    aJSON.Save(aPath.c());
}

void GameEditor::PasteWave(LevelWaveBlueprint *pWave) {
    if (pWave == NULL) {
        printf("Cannot Post Wave... Wave Doesn't Exist..\n");
        return;
    }
    FString aPath = gDirDocuments + FString("editor_pasteboard_wave.json");
    FJSON aJSON;
    aJSON.Load(aPath);
    pWave->Load(aJSON.mRoot);
    RefreshPlayback();
}

void GameEditor::PasteWaveSpawn(LevelWaveSpawnBlueprint *pSpawn) {
    if (pSpawn == NULL) {
        printf("Cannot Post Wave... Wave Doesn't Exist..\n");
        return;
    }
    FString aPath = gDirDocuments + FString("editor_pasteboard_wave_spawn.json");
    FJSON aJSON;
    aJSON.Load(aPath);
    pSpawn->Load(aJSON.mRoot);
    RefreshPlayback();
}

void GameEditor::PastePerm(LevelSectionPermBlueprint *pPerm) {
    if (pPerm == NULL) {
        printf("Cannot Post Wave... Wave Doesn't Exist..\n");
        return;
    }
    FString aPath = gDirDocuments + FString("editor_pasteboard_perm.json");
    FJSON aJSON;
    aJSON.Load(aPath);
    pPerm->Load(aJSON.mRoot);
    RefreshPlayback();
    
}

void GameEditor::PastePermSpawn(LevelPermSpawnBlueprint *pSpawn) {
    if (pSpawn == NULL) {
        printf("Cannot Post Wave... Wave Doesn't Exist..\n");
        return;
    }
    FString aPath = gDirDocuments + FString("editor_pasteboard_perm_spawn.json");
    FJSON aJSON;
    aJSON.Load(aPath);
    pSpawn->Load(aJSON.mRoot);
    RefreshPlayback();
}

void GameEditor::PasteMotion(LevelMotionControllerBlueprint *pMotion) {
    if (pMotion == NULL) {
        printf("Cannot Paste Motion... Motion Doesn't Exist..\n");
        return;
    }
    FString aPath = gDirDocuments + FString("editor_pasteboard_motion.json");
    FJSON aJSON;
    aJSON.Load(aPath);
    pMotion->Load(aJSON.mRoot);
    RefreshPlayback();
}

void GameEditor::PasteWaveAtEndOfList() {
    mSection.WaveAdd();
    PasteWave(mSection.mCurrentWave);
}

void GameEditor::PasteWaveAfterCurrent() {
    mSection.WaveInsert();
    PasteWave(mSection.mCurrentWave);
}

void GameEditor::PasteWaveSpawnEndOfList() {
    LevelWaveBlueprint *aWave = mSection.mCurrentWave;
    if (aWave == NULL) { return; }
    if (aWave->mSpawnCount >= WAVE_MAX_SPAWN_COUNT) { return; }
    int aPasteIndex = aWave->mSpawnCount;
    aWave->mSpawnCount++;
    aWave->mSelectedSpawnIndex = aPasteIndex;
    PasteWaveSpawn(&(aWave->mSpawn[aPasteIndex]));
}

void GameEditor::PasteWaveSpawnAfterCurrent() {
    LevelWaveBlueprint *aWave = mSection.mCurrentWave;
    if (aWave == NULL) { return; }
    if (aWave->mSpawnCount >= WAVE_MAX_SPAWN_COUNT) { return; }
    if ((aWave->mSelectedSpawnIndex < 0) || (aWave->mSelectedSpawnIndex >= aWave->mSpawnCount)) { return; }
    int aPasteIndex = aWave->mSelectedSpawnIndex;
    aWave->ShiftSpawnFromIndex(aPasteIndex);
    aWave->mSelectedSpawnIndex = (aPasteIndex + 1);
    PasteWaveSpawn(&(aWave->mSpawn[aPasteIndex + 1]));
}
