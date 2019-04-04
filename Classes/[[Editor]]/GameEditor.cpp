//
//  GameEditorEditor.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/17/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "core_includes.h"
#include "GameEditor.hpp"
#include "FAnimation.h"

GameEditor *gEditor = NULL;

GameEditor::GameEditor(Game *pGame) {
    
    mEditorShowReferenced = false;
    mEditorWaveLoop = true;
    mEditorSectionLoop = true;
    mEditorPlaybackWaveOnly = false;
    mEditorPlaybackFromCurrentWave = true;
    mEditorPlaybackEnabled = true;
    
    mSpeedClassIndex = WAVE_SPEED_MEDIUM;
    mSpawnRotationSpeedClassIndex = WAVE_SPEED_MEDIUM;
    
    mMenuAttachment = NULL;
    mMenuSpawnPicker = NULL;
    mMenuWavesPicker = NULL;
    mMenuSpawn = NULL;
    
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
    
    
    mToolContainer = new FCanvas();
    mToolContainer->mConsumesTouches = false;
    mToolContainer->mName = "Tool Container";
    AddChild(mToolContainer);
    mToolContainer->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    
    
    
    mMenuSections = new EditorMenuSections(this);
    mToolContainer->AddChild(mMenuSections);
    mMenuSections->SetFrame(gSafeAreaInsetLeft + 16.0f, gSafeAreaInsetTop + 20.0f, 400.0f, 640.0f);
    
    mExportIndex = 0;
    
    SetOverlay(mToolContainer);
    
    
    
    //WaveAdd();
    //OpenPathEditor();
    
    
    
    
    LoadConfig();
    //
    OpenSpawnMenu();
    OpenWavePickerMenu();
    OpenSpawnPickerMenu();
    //OpenAttachmentMenu();
    
    
    
    
}

GameEditor::~GameEditor() {
    if (gEditor == this) {
        gEditor = NULL;
    }
}

void GameEditor::Layout() {
    
    mToolContainer->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    if (mPathEditor) mPathEditor->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    
    FPoint aSpawnZone1 = FPoint(gGame->mSpawnZoneLeft, gGame->mSpawnZoneTop);
    aSpawnZone1 = FCanvas::Convert(aSpawnZone1, gGame, this);
    FPoint aSpawnZone2 = FPoint(gGame->mSpawnZoneRight, gGame->mSpawnZoneBottom);
    aSpawnZone2 = FCanvas::Convert(aSpawnZone2, gGame, this);
    mSpawnZoneTop = aSpawnZone1.mY;
    mSpawnZoneRight = aSpawnZone2.mX;
    mSpawnZoneLeft = aSpawnZone1.mX;
    mSpawnZoneBottom = aSpawnZone2.mY;
    
    
    FPoint aPeekZone1 = FPoint(gGame->mPeekZoneLeft, gGame->mPeekZoneTop);
    aPeekZone1 = FCanvas::Convert(aPeekZone1, gGame, this);
    FPoint aPeekZone2 = FPoint(gGame->mPeekZoneRight, 0.0f);
    aPeekZone2 = FCanvas::Convert(aPeekZone2, gGame, this);
    mPeekZoneTop = aPeekZone1.mY;
    mPeekZoneRight = aPeekZone2.mX;
    mPeekZoneLeft = aPeekZone1.mX;
    
    FPoint aQuarterZone1 = FPoint(gGame->mQuarterZoneLeft, gGame->mQuarterZoneTop);
    aQuarterZone1 = FCanvas::Convert(aQuarterZone1, gGame, this);
    FPoint aQuarterZone2 = FPoint(gGame->mQuarterZoneRight, gGame->mQuarterZoneBottom);
    aQuarterZone2 = FCanvas::Convert(aQuarterZone2, gGame, this);
    mQuarterZoneTop = aQuarterZone1.mY;
    mQuarterZoneRight = aQuarterZone2.mX;
    mQuarterZoneLeft = aQuarterZone1.mX;
    mQuarterZoneBottom = aQuarterZone2.mY;
    
    
    FPoint aExitZone1 = FPoint(gGame->mExitZoneLeft, gGame->mExitZoneTop);
    aExitZone1 = FCanvas::Convert(aExitZone1, gGame, this);
    FPoint aExitZone2 = FPoint(gGame->mExitZoneRight, 0.0f);
    aExitZone2 = FCanvas::Convert(aExitZone2, gGame, this);
    mExitZoneTop = aExitZone1.mY;
    mExitZoneRight = aExitZone2.mX;
    mExitZoneLeft = aExitZone1.mX;
    
    
    FPoint aPlayZone1 = FPoint(0.0f, gGame->mPlayAreaBottom);
    aPlayZone1 = FCanvas::Convert(aPlayZone1, gGame, this);
    mPlayZoneBottom = aPlayZone1.mY;
    
    
    FPoint aGameArea1 = FPoint(gGame->mGameAreaLeft, gGame->mGameAreaTop);
    aGameArea1 = FCanvas::Convert(aGameArea1, gGame, this);
    FPoint aGameArea2 = FPoint(gGame->mGameAreaRight, gGame->mGameAreaBottom);
    aGameArea2 = FCanvas::Convert(aGameArea2, gGame, this);
    mGameAreaTop = aGameArea1.mY;
    mGameAreaRight = aGameArea2.mX;
    mGameAreaLeft = aGameArea1.mX;
    mGameAreaBottom = aGameArea2.mY;
    
    
    
    FPoint aCenter = FPoint((gGame->mPlayAreaLeft + gGame->mPlayAreaRight) / 2.0f,
                            (gGame->mPlayAreaTop + gGame->mPlayAreaBottom) / 2.0f);
    aCenter = FCanvas::Convert(aCenter, gGame, this);
    mCenterH = aCenter.mX;
    mCenterV = aCenter.mY;
    
}

void GameEditor::Update() {
    
    mSection.Update();
    
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
            //OpenFormationEditor();
            //PickFormationForFormationEditor();
            
        }
    }
    
    
    
    
    
    int aRequiredTestObjectCount = mEditorWave.mPath.mNodeList.mCount;
    
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
    
    for (int i=0;i<mEditorWave.mPath.mNodeList.mCount;i++) {
        
        GameObject *aObject = (GameObject *)mEditorObjectList.Fetch(i);
        LevelWavePathNode *aPathNode = (LevelWavePathNode *)mEditorWave.mPath.mNodeList.Fetch(i);
        
        if (aObject != NULL && aPathNode != NULL) {
            aObject->mTransform.mX = aPathNode->mX;
            aObject->mTransform.mY = aPathNode->mY;
            aObject->Update();
        }
    }
    
    
    bool aIsOnMainTools = (mOverlay == mToolContainer);
    bool aIsOnPathTools = (mOverlay == mPathEditor);
    
    if (aIsOnMainTools || aIsOnPathTools) {
        if (mEditorPlaybackEnabled) {
            if (mEditorPlaybackWaveOnly) {
                mEditorWave.Update();
                if (mEditorWave.mIsComplete) {
                    if (mEditorWaveLoop) {
                        mEditorWave.Restart();
                    }
                }
            } else {
                mEditorSection.Update();
                if (mEditorSection.mIsComplete) {
                    if (mEditorSectionLoop) {
                        mEditorSection.Restart();
                    }
                }
            }
        }
    } else {
        mEditorWave.Reset();
        mEditorSection.Reset();
    }
    
}

void GameEditor::Draw() {
    
    if (gGame == NULL) { return; }
    
    bool aIsOnMainTools = (mOverlay == mToolContainer);
    bool aIsOnPathTools = (mOverlay == mPathEditor);
    
    gGame->DrawTransform();
    
    Graphics::PipelineStateSetShape2DNoBlending();
    Graphics::SetColor();
    mEditorWave.mPath.Draw();
    mEditorWave.Draw();
    
    DrawTransform();
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    
    if (aIsOnMainTools || aIsOnPathTools) {
        Graphics::SetColor(0.0125f, 0.0125f, 0.0125f, 0.65f);
        Graphics::DrawRect(0.0f, 0.0f, mGameAreaLeft, gDeviceHeight);
        Graphics::DrawRect(mGameAreaLeft, 0.0f, mGameAreaRight - mGameAreaLeft, mGameAreaTop);
        Graphics::DrawRect(mGameAreaLeft, mGameAreaBottom, mGameAreaRight - mGameAreaLeft, gDeviceHeight - mGameAreaBottom);
        Graphics::DrawRect(mGameAreaLeft + (mGameAreaRight - mGameAreaLeft), 0.0f, gDeviceWidth - (mGameAreaLeft + (mGameAreaRight - mGameAreaLeft)), gDeviceHeight);
        
        float aMarkerMult = 1.0f;
        float aMarkerOpacity = 0.75f;
        
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
        printf("Game doesn't exist?\n");
        return;
    }
    if (mPathEditor != NULL && mOverlay == mPathEditor) {
        return;
    }
    if (mFormationEditor != NULL && mOverlay == mFormationEditor) {
        return;
    }
    
    bool aShift = gKeyDownShift;
    bool aCtrl = gKeyDownCtrl;
    bool aAlt = gKeyDownAlt;
    
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
    
    if (pKey == __KEY__E) {
        if (aShift == false && aCtrl == false && aAlt == false) {
            if (mSection.mCurrentWave) {
                OpenPathEditor();
            }
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
    
    if (pKey == __KEY__A) {
        if (aShift == false && aCtrl == true && aAlt == false) {
            WaveAdd();
        }
    }
    
    if (pKey == __KEY__DELETE) {
        WaveRemove();
    }
    
    if (pKey == __KEY__S) {
        if (aShift == false && aCtrl == true && aAlt == false) { SaveAt(mExportIndex); }
    }
    
    if (pKey == __KEY__L) {
        if (aShift == false && aCtrl == true && aAlt == false) { LoadAt(mExportIndex); }
    }
    
    if (pKey == __KEY__P) {
        if (aShift == false && aCtrl == false && aAlt == false) {
            mSection.WaveSelectPrev();
        }
    }
    
    if (pKey == __KEY__R) {
        if (aShift == false && aCtrl == false && aAlt == false) {
#ifdef EDITOR_MODE
            mEditorShowReferenced = !mEditorShowReferenced;
            RefreshPlayback();
#endif
        }
    }
    
    if (pKey == __KEY__N) {
        if (aShift == false && aCtrl == false && aAlt == false) {
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
        OpenFormationEditor(gSelectedFormation);
    }
    
    
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
    int aResult = WAVE_SPEED_MEDIUM_FAST;
    if (pSegmentIndex == 0) { aResult = WAVE_SPEED_EXTRA_SLOW; }
    if (pSegmentIndex == 1) { aResult = WAVE_SPEED_SLOW; }
    if (pSegmentIndex == 2) { aResult = WAVE_SPEED_MEDIUM_SLOW; }
    if (pSegmentIndex == 3) { aResult = WAVE_SPEED_MEDIUM; }
    if (pSegmentIndex == 4) { aResult = WAVE_SPEED_MEDIUM_FAST; }
    if (pSegmentIndex == 5) { aResult = WAVE_SPEED_FAST; }
    if (pSegmentIndex == 6) { aResult = WAVE_SPEED_EXTRA_FAST; }
    if (pSegmentIndex == 7) { aResult = WAVE_SPEED_INSANE; }
    return aResult;
}

int GameEditor::SpeedConvertTypeToSegment(int pType) {
    int aResult = 0;
    if (pType == WAVE_SPEED_EXTRA_SLOW)   { aResult = 0; }
    if (pType == WAVE_SPEED_SLOW)         { aResult = 1; }
    if (pType == WAVE_SPEED_MEDIUM_SLOW)  { aResult = 2; }
    if (pType == WAVE_SPEED_MEDIUM)       { aResult = 3; }
    if (pType == WAVE_SPEED_MEDIUM_FAST)  { aResult = 4; }
    if (pType == WAVE_SPEED_FAST)         { aResult = 5; }
    if (pType == WAVE_SPEED_EXTRA_FAST)   { aResult = 6; }
    if (pType == WAVE_SPEED_INSANE)       { aResult = 7; }
    return aResult;
}

void GameEditor::RefreshPlayback() {
    
    if (mSection.mCurrentWave != NULL) {
        mSpeedClassIndex = SpeedConvertTypeToSegment(mSection.mCurrentWave->mPath.mSpeedClass);
    }
    
    
    if (mSection.mCurrentWave != NULL) {
        mSection.mCurrentWave->Build();
    }
    
    if (mEditorPlaybackWaveOnly) {
        
    } else {
        
        int aWaveIndex = WaveIndex();
        //mSection.mCurrentWave
        if (mEditorPlaybackFromCurrentWave == true && aWaveIndex >= 0) {
            mEditorSection.mStartWaveIndex = aWaveIndex;
        } else {
            mEditorSection.mStartWaveIndex = 0;
        }
        
        //Section Build...
        mSection.Build();
    }
}

void GameEditor::RefreshPlaybackSpeed() {
    if (mSection.mCurrentWave != NULL) {
        
        mSection.mCurrentWave->mPath.mSpeedClass = SpeedConvertSegmentToType(mSpeedClassIndex);
    }
}

void GameEditor::RefreshSpawn() {
    
}

void GameEditor::RefreshSpawnRotationSpeed() {
    
    
    //mSpawnRotationSpeedClassIndex
    
    
}


void GameEditor::RefreshSection() {
    
}


void GameEditor::WaveAdd() {
    
    mSection.WaveAdd();
    OpenPathEditor();
}

void GameEditor::WaveRemove() {
    mSection.WaveRemove();
    if (mSection.mCurrentWave == NULL) {
        mEditorWave.Reset();
    }
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

void GameEditor::OpenPathEditor() {
    if (mSection.mCurrentWave == NULL) { printf("Must have wave...\n"); return; }
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




void GameEditor::OpenFormationEditor(LevelWaveSpawnFormation *pFormation) {
    
    mFormationEditor = new GameFormationEditor(this);
    mFormationEditor->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    mFormationEditor->mName = "{Form Editor}";
    AddChild(mFormationEditor);
    
    

    
    
    LevelWaveSpawnFormationBlueprint *aBBB = NULL;
    if (pFormation != NULL) {
        
        aBBB = new LevelWaveSpawnFormationBlueprint();
        
        FJSON aJSON;
        aJSON.Load(pFormation->mID.c());
        aBBB->Load(aJSON.mRoot);
        if (aBBB->IsValid()) {
            
        } else {
            delete aBBB;
            aBBB = NULL;
        }
        
        
    }
    
    mFormationEditor->SetUp(aBBB);
    
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
    
    EditorMenuFormationPicker *aFormationPicker = new EditorMenuFormationPicker();
    mToolContainer->AddChild(aFormationPicker);
    
    gNotify.Register(this, aFormationPicker, "formation_selected");
    gNotify.Register(this, aFormationPicker, "formation_canceled");
    
    aFormationPicker->SetFrame(gDeviceWidth2 / 2.0f, gDeviceHeight2 / 2.0f, gDeviceWidth2, gDeviceHeight2);
}

void GameEditor::OpenSpawnMenu() {
    if (mMenuSpawn == NULL) {
        mMenuSpawn = new EditorMenuSpawn(this);
        mToolContainer->AddChild(mMenuSpawn);
        mMenuSpawn->SetFrame(gDeviceWidth - (gSafeAreaInsetRight + 14.0f + 400.0f),
                             gSafeAreaInsetTop + 20.0f, 400.0f, 420.0f);
    }
}

void GameEditor::OpenWavePickerMenu() {
    if (mMenuWavesPicker == NULL) {
        mMenuWavesPicker = new EditorMenuWavesPicker(this);
        mToolContainer->AddChild(mMenuWavesPicker);
        mMenuWavesPicker->SetFrame(gDeviceWidth - (gSafeAreaInsetRight + 14.0f + 400.0f),
                                   (gDeviceHeight - gSafeAreaInsetBottom - 2.0f) - (154.0f + 154.0f + 2.0f), 400.0f, 154.0f);
    }
}

void GameEditor::OpenSpawnPickerMenu() {
    if (mMenuSpawnPicker == NULL) {
        mMenuSpawnPicker = new EditorMenuSpawnPicker(this);
        mToolContainer->AddChild(mMenuSpawnPicker);
        mMenuSpawnPicker->SetFrame(gDeviceWidth - (gSafeAreaInsetRight + 14.0f + 400.0f),
                                   (gDeviceHeight - gSafeAreaInsetBottom - 2.0f) - 154.0f, 400.0f, 154.0f);
    }
}

void GameEditor::OpenAttachmentMenu() {
    if (mMenuAttachment == NULL) {
        mMenuAttachment = new EditorMenuAttachment(this);
        mToolContainer->AddChild(mMenuAttachment);
        mMenuAttachment->SetFrame(gDeviceWidth2 - 200.0f,
                                  (gDeviceHeight - gSafeAreaInsetBottom) - 490.0f - 2.0f, 400.0f, 490.0f);
    }
}

void GameEditor::Clear() {
    FString aRecoverPath = gDirDocuments + FString("clear_backup.json");
    Save(aRecoverPath.c());
    
    ClosePathEditor();
    mSection.Clear();
    
    mEditorWave.Reset();
    mEditorSection.Reset();
}

void GameEditor::LoadCleared() {
    for (int i=0;i<200;i++) {
        FString aRecoverPath = gDirDocuments + FString("clear_backup.json");
        Load(aRecoverPath.c());
    }
}

void GameEditor::Autosave() {
    FString aAutosavePath = gDirDocuments + FString("editor_autosave_") + FString(mExportIndex) + FString(".json");
    Save(aAutosavePath.c());
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
        mEditorWave.mPath.Reset();
    }
    
    RefreshPlayback();
}

void GameEditor::SaveAt(int pIndex) {
    FString aPath = gDirExport + FString("export_section_") + FString(pIndex) + FString(".json");
    Save(aPath.c());
}

void GameEditor::LoadAt(int pIndex) {
    FString aPath = gDirExport + FString("export_section_") + FString(pIndex) + FString(".json");
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
    
    mEditorWave.mPath.Reset();
    
    FJSON aJSON;
    aJSON.Load(pFile);
    mSection.Load(aJSON.mRoot);
    
    //Moved out of load procedure...
    EnumList(LevelWaveBlueprint, aWaveBlueprint, mSection.mWaveList) {
        aWaveBlueprint->ApplyEditorConstraints();
    }
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
