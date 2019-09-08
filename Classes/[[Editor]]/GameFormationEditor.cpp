//
//  GameFormationEditor.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/30/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "core_includes.h"
#include "GameFormationEditor.hpp"
#include "GameEditor.hpp"
#include "FAnimation.hpp"

GameFormationEditor *gFormationEditor = NULL;

GameFormationEditor::GameFormationEditor(GameEditor *pEditor) {
    
    gFormationEditor = this;
    
    mEditor = pEditor;
    
    mGameAreaTop = pEditor->mGameAreaTop;
    mGameAreaRight = pEditor->mGameAreaRight;
    mGameAreaBottom = pEditor->mGameAreaBottom;
    mGameAreaLeft = pEditor->mGameAreaLeft;
    
    //mFormationRotationSpeedClassIndex = 3;
    //mTracerSpeedClassIndex = 3;
    
    mCenterX = (float)((int)(mGameAreaLeft + (mGameAreaRight - mGameAreaLeft) / 2.0f + 0.5f));
    mCenterY = (float)((int)(mGameAreaTop + (mGameAreaBottom - mGameAreaTop) / 2.0f + 0.5f));
    
    mGrid.mCenterX = mCenterX;
    mGrid.mCenterY = mCenterY;
    
    if (gGame) {
        mEditorFormation.mX = (float)((int)(gGame->mGameAreaLeft + (gGame->mGameAreaRight - gGame->mGameAreaLeft) / 2.0f + 0.5f));
        mEditorFormation.mY = (float)((int)(gGame->mGameAreaTop + (gGame->mGameAreaBottom - gGame->mGameAreaTop) / 2.0f + 0.5f));
    }
    
    mSelectedTouch = NULL;
    
    mSelectNodeStartX = 0.0f;
    mSelectNodeStartY = 0.0f;
    
    mSelectTouchStartX = 0.0f;
    mSelectTouchStartY = 0.0f;
    
    mTracerMode = FORMATION_MODE_ADD_POINT;
    mFormationMode = FORMATION_MODE_ADD_POINT;
    
    mTracerEnabled = false;
    
    
    mMarkersDisplay = true;
    
    
    
    //mSelectedSpawnIndex = -1;
    //mSelectedTracerSpawnIndex = -1;
    
    
    
    
    mName = "[GameFormationEditor]";
    
    SetWidth(gDeviceWidth);
    SetHeight(gDeviceHeight);
    
    mMenuFormation = new EditorMenuFormation(this);
    AddChild(mMenuFormation);
    mMenuFormation->SetFrame(gSafeAreaInsetLeft + 16.0f, gSafeAreaInsetTop + 20.0f, 400.0f, 736.0f);
    
    mMenuUtils = new EditorMenuFormationUtilities(this);
    AddChild(mMenuUtils);
    mMenuUtils->SetFrame(gDeviceWidth - (gSafeAreaInsetRight + 14.0f + 400.0f), gSafeAreaInsetTop + 20.0f, 400.0f, 736.0f);
    
    mMenuGrid = new EditorMenuFormationGrid(&mGrid);
    AddChild(mMenuGrid);
    mMenuGrid->SetFrame(gDeviceWidth - (gSafeAreaInsetRight + 14.0f + 400.0f + 60.0f), gSafeAreaInsetTop + 20.0f + 200.0f, 400.0f, 736.0f - 200.0f);
    
    
    mMenuSpawn = new EditorMenuFormationSpawnPicker(this);
    AddChild(mMenuSpawn);
    mMenuSpawn->SetFrame((gDeviceWidth2 - 500.0f / 2.0f), gSafeAreaInsetTop + 20.0f, 500.0f, 256.0f);
    
    
}

GameFormationEditor::~GameFormationEditor() {
    
    if (gFormationEditor == this) {
        gFormationEditor = NULL;
    }
    
    if (gEditor != NULL) {
        if (gEditor->mFormationEditor == this) {
            gEditor->mFormationEditor = NULL;
        }
    }
    
    mFormation.Print();
    mGrid.SaveGridState();
}

void GameFormationEditor::SetFrame(float pX, float pY, float pWidth, float pHeight) {
    FCanvas::SetFrame(pX, pY, pWidth, pHeight);
    
}

void GameFormationEditor::Layout() {
    
}

void GameFormationEditor::Update() {
    mGrid.Update();
    mFormation.Update();
    mEditorFormation.Update(NULL);
}

void GameFormationEditor::Draw() {
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    Graphics::SetColor(1.0f, 0.85f, 1.0f, 0.75f);
    Graphics::DrawRect(0.0f, 0.0f, mGameAreaLeft, gDeviceHeight);
    Graphics::DrawRect(mGameAreaLeft, 0.0f, mGameAreaRight - mGameAreaLeft, mGameAreaTop);
    Graphics::DrawRect(mGameAreaLeft, mGameAreaBottom, mGameAreaRight - mGameAreaLeft, gDeviceHeight - mGameAreaBottom);
    Graphics::DrawRect(mGameAreaLeft + (mGameAreaRight - mGameAreaLeft), 0.0f, gDeviceWidth - (mGameAreaLeft + (mGameAreaRight - mGameAreaLeft)), gDeviceHeight);
    
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    Graphics::SetColor(0.98f, 0.85f, 0.085f, 0.75f);
    Graphics::DrawPoint(mCenterX, mCenterY, 4.0f);
    
    
    if (mMarkersDisplay == true) {
        
        mFormation.Draw(true);

        mGrid.Draw();
        
        if (gGame) {
            gGame->DrawTransform();
        }
        
        
        mEditorFormation.Draw(mFormation.mCurrentTracerIndex);
        
    }
    
}

void GameFormationEditor::TouchDown(float pX, float pY, void *pData) {
    
    
    
    float aX = pX;
    float aY = pY;
    
    mGrid.GridSnap(&aX, &aY);
    
    if (mTracerEnabled == true) {
        if (mTracerMode == FORMATION_MODE_ADD_POINT) {
            LevelFormationTracerBlueprint *aTracerBlueprint = mFormation.GetTracer();
            if (aTracerBlueprint != NULL) {
                if (aTracerBlueprint->mSpecialType == TRACER_SPECIAL_TYPE_NONE) {
                    mFormation.TracerAdd(aX, aY);
                } else {
                    aTracerBlueprint->mSpecialSpecialEditorX = aX;
                    aTracerBlueprint->mSpecialSpecialEditorY = aY;
                    aTracerBlueprint->RefreshNodePositions();
                    Refresh();
                    
                }
            }
        } else if (mTracerMode == FORMATION_MODE_MOVE_POINT) {
            if (mSelectedTouch == NULL) {
                float aDist = 50.0f * 50.0f;
                
                LevelFormationTracerBlueprint *aTracerBlueprint = mFormation.GetTracer();
                
                if (aTracerBlueprint != NULL) {
                    
                    if (aTracerBlueprint->mSpecialType == TRACER_SPECIAL_TYPE_NONE) {
                        
                        int aIndex = aTracerBlueprint->GetClosestIndex(pX, pY, aDist);
                        if (aIndex != -1) {
                            
                            
                            
                            aTracerBlueprint->mSelectedTracerNodeIndex = aIndex;
                            mSelectedTouch = pData;
                            mSelectNodeStartX = mFormation.TracerGetX(aIndex);
                            mSelectNodeStartY = mFormation.TracerGetY(aIndex);
                            mSelectTouchStartX = pX;
                            mSelectTouchStartY = pY;
                        }
                        
                    } else {
                        aTracerBlueprint->mSelectedTracerNodeIndex = -1;
                        mSelectedTouch = pData;
                        mSelectNodeStartX = aTracerBlueprint->mSpecialSpecialEditorX;
                        mSelectNodeStartY = aTracerBlueprint->mSpecialSpecialEditorY;
                        mSelectTouchStartX = pX;
                        mSelectTouchStartY = pY;
                        
                    }
                    
                }
            } else {
                mSelectedTouch = NULL;
                LevelFormationTracerBlueprint *aTracerBlueprint = mFormation.GetTracer();
                if (aTracerBlueprint != NULL) {
                    aTracerBlueprint->mSelectedTracerNodeIndex = -1;
                }
                
            }
        } else if (mTracerMode == FORMATION_MODE_SELECT_POINT) {
            if (mSelectedTouch == NULL) {
                float aDist = 50.0f * 50.0f;
                
                LevelFormationTracerBlueprint *aTracerBlueprint = mFormation.GetTracer();
                
                if (aTracerBlueprint != NULL) {
                    
                    int aIndex = aTracerBlueprint->GetClosestIndex(pX, pY, aDist);
                    if (aIndex != -1) {
                        
                        mSelectedTouch = pData;
                        aTracerBlueprint->mSelectedTracerNodeIndex = aIndex;
                        mSelectNodeStartX = mFormation.GetX(aIndex);
                        mSelectNodeStartY = mFormation.GetY(aIndex);
                        mSelectTouchStartX = pX; mSelectTouchStartY = pY;
                    }
                }
            } else {
                LevelFormationTracerBlueprint *aTracerBlueprint = mFormation.GetTracer();
                if (aTracerBlueprint != NULL) {
                    aTracerBlueprint->mSelectedTracerNodeIndex = -1;
                }
                mSelectedTouch = NULL;
            }
        }
        
    } else {
        
        
        if (mFormationMode == FORMATION_MODE_ADD_POINT) {
            mFormation.Add(aX, aY);
        } else if (mFormationMode == FORMATION_MODE_MOVE_POINT) {
            if (mSelectedTouch == NULL) {
                float aDist = 50.0f * 50.0f;
                
                int aIndex = mFormation.GetClosestIndex(pX, pY, aDist);
                if (aIndex != -1) {
                    mSelectedTouch = pData;
                    mFormation.mSelectedNodeIndex = aIndex;
                    mSelectNodeStartX = mFormation.GetX(aIndex);
                    mSelectNodeStartY = mFormation.GetY(aIndex);
                    mSelectTouchStartX = pX;
                    mSelectTouchStartY = pY;
                }
            } else {
                mSelectedTouch = NULL;
                mFormation.mSelectedNodeIndex = -1;
            }
        } else if (mFormationMode == FORMATION_MODE_SELECT_POINT) {
            if (mSelectedTouch == NULL) {
                float aDist = 50.0f * 50.0f;
                int aIndex = mFormation.GetClosestIndex(pX, pY, aDist);
                if (aIndex != -1) {
                    mSelectedTouch = pData;
                    mFormation.mSelectedNodeIndex = aIndex;
                    mSelectNodeStartX = mFormation.GetX(aIndex);
                    mSelectNodeStartY = mFormation.GetY(aIndex);
                    mSelectTouchStartX = pX; mSelectTouchStartY = pY;
                }
            } else {
                mSelectedTouch = NULL;
                mFormation.mSelectedNodeIndex = -1;
            }
        }
    }
}

void GameFormationEditor::TouchMove(float pX, float pY, void *pData) {
    
    float aX = mSelectNodeStartX + (pX - mSelectTouchStartX);
    float aY = mSelectNodeStartY + (pY - mSelectTouchStartY);
    
    mGrid.GridSnap(&aX, &aY);
    
    if (mTracerEnabled == true) {
        
        if (mTracerMode == FORMATION_MODE_MOVE_POINT) {
            if (mSelectedTouch == pData) {
                LevelFormationTracerBlueprint *aTracerBlueprint = mFormation.GetTracer();
                if (aTracerBlueprint != NULL) {
                    if (aTracerBlueprint->mSpecialType == TRACER_SPECIAL_TYPE_NONE) {
                        aTracerBlueprint->Set(aTracerBlueprint->mSelectedTracerNodeIndex, aX, aY);
                        
                    } else {
                        aTracerBlueprint->mSpecialSpecialEditorX = aX;
                        aTracerBlueprint->mSpecialSpecialEditorY = aY;
                        aTracerBlueprint->RefreshNodePositions();
                        Refresh();
                    }
                }
            }
        }
    } else {
        if (mFormationMode == FORMATION_MODE_MOVE_POINT) {
            if (mSelectedTouch == pData) {
                mFormation.Set(mFormation.mSelectedNodeIndex, aX, aY);
            }
        }
    }
}

void GameFormationEditor::TouchUp(float pX, float pY, void *pData) {
    if (mSelectedTouch == pData) {
        mSelectedTouch = NULL;
    }
}

void GameFormationEditor::TouchFlush() {
    
}

void GameFormationEditor::KeyDown(int pKey) {
    
    bool aShift = gKeyDownShift;
    bool aCtrl = gKeyDownCtrl;
    bool aAlt = gKeyDownAlt;
    
    if (gEditor == NULL) { return; }
    if (gGame == NULL) { return; }
    
    if (pKey == __KEY__1) { mFormation.mCurrentTracerIndex = 0; }
    if (pKey == __KEY__2) { mFormation.mCurrentTracerIndex = 1; }
    if (pKey == __KEY__3) { mFormation.mCurrentTracerIndex = 2; }
    if (pKey == __KEY__4) { mFormation.mCurrentTracerIndex = 3; }
    if (pKey == __KEY__5) { mFormation.mCurrentTracerIndex = 4; }
    if (pKey == __KEY__6) { mFormation.mCurrentTracerIndex = 5; }
    
    
    if (pKey == __KEY__P) { Print(); }
    if (pKey == __KEY__T) { mTracerEnabled = !mTracerEnabled; }
    
    if (pKey == __KEY__A) {
        if (mTracerEnabled) {
            mTracerMode = FORMATION_MODE_ADD_POINT;
        } else {
            mFormationMode = FORMATION_MODE_ADD_POINT;
        }
    }
    
    if (pKey == __KEY__E) {
        if (mTracerEnabled) {
            mTracerMode = FORMATION_MODE_MOVE_POINT;
        } else {
            mFormationMode = FORMATION_MODE_MOVE_POINT;
        }
    }
    
    if (pKey == __KEY__S) {
        
        if (aShift == false && aCtrl == false && aAlt == false) {
            if (mTracerEnabled) {
                mTracerMode = FORMATION_MODE_SELECT_POINT;
            } else {
                mFormationMode = FORMATION_MODE_SELECT_POINT;
            }
        }
        
        if (aShift == false && aCtrl == true && aAlt == false) {
            Save();
        }
    }
    
    if (pKey == __KEY__L) {
        if (aShift == false && aCtrl == true && aAlt == false) {
            Load();
        }
    }
    
    
    if (pKey == __KEY__DELETE) {
        if (aShift == false && aCtrl == false && aAlt == false) {
            if (mTracerEnabled == true) {
                mFormation.TracerRemovePoint();
            } else {
                mFormation.Remove(mFormation.mSelectedNodeIndex);
            }
        }
        
        if (aShift == false && aCtrl == true && aAlt == false) {
            if (mTracerEnabled == true) {
                mFormation.TracerNuke();
                Refresh();
                
            } else {
                for (int i=mFormation.mNodeList.mCount - 1;i>=0;i--) {
                    mFormation.Remove(i);
                }
            }
        }
    }
    
    if (pKey == __KEY__ESCAPE) {
        if (aShift == false && aCtrl == false && aAlt == false) { Close(); }
    }
    
    
    
    if (pKey == __KEY__LEFT) {
        if (aShift == false && aCtrl == false && aAlt == false) {
            
        } else if (aShift == true && aCtrl == false && aAlt == false) {
            
        } else if (aShift == false && aCtrl == true && aAlt == false) {
            
        }
    }
    if (pKey == __KEY__RIGHT) {
        if (aShift == false && aCtrl == false && aAlt == false) {
            
        } else if (aShift == true && aCtrl == false && aAlt == false) {
            
        } else if (aShift == false && aCtrl == true && aAlt == false) {
            
        }
    }
    if (pKey == __KEY__UP) {
        if (aShift == false && aCtrl == false && aAlt == false) {
            
        } else if (aShift == true && aCtrl == false && aAlt == false) {
            
        } else if (aShift == false && aCtrl == true && aAlt == false) {
            
        }
    }
    if (pKey == __KEY__DOWN) {
        if (aShift == false && aCtrl == false && aAlt == false) {
            
        } else if (aShift == true && aCtrl == false && aAlt == false) {
            
        } else if (aShift == false && aCtrl == true && aAlt == false) {
            
        }
    }
}

void GameFormationEditor::KeyUp(int pKey) {
    
}

void GameFormationEditor::Notify(void *pSender, const char *pNotification) {
    
}

void GameFormationEditor::SetUp(LevelFormationBlueprint *pFormation) {
    if (gEditor != NULL) {
        mGameAreaTop = gEditor->mGameAreaTop;
        mGameAreaRight = gEditor->mGameAreaRight;
        mGameAreaBottom = gEditor->mGameAreaBottom;
        mGameAreaLeft = gEditor->mGameAreaLeft;
        
        mCenterX = (float)((int)(mGameAreaLeft + (mGameAreaRight - mGameAreaLeft) / 2.0f + 0.5f));
        mCenterY = (float)((int)(mGameAreaTop + (mGameAreaBottom - mGameAreaTop) / 2.0f + 0.5f));
        
        if (gGame) {
            mEditorFormation.mX = (float)((int)(gGame->mGameAreaLeft + (gGame->mGameAreaRight - gGame->mGameAreaLeft) / 2.0f + 0.5f));
            mEditorFormation.mY = (float)((int)(gGame->mGameAreaTop + (gGame->mGameAreaBottom - gGame->mGameAreaTop) / 2.0f + 0.5f));
        }
    }
    
    if (pFormation != NULL) {
        FJSONNode *aLoadNode = pFormation->Save();
        if (aLoadNode != NULL) {
            mFormation.Load(aLoadNode);
        }
        delete aLoadNode;
    } else {
        Load();
    }
    
    PickDefaultModes();
    
}

void GameFormationEditor::PickDefaultModes() {
    bool aHasTracer = false;
    for (int i=0;i<BLUEPRINT_TRACER_COUNT;i++) {
        if (mFormation.mTracer[i].IsValid()) {
            aHasTracer = true;
        }
    }
    
    if (aHasTracer && mFormation.mNodeList.mCount <= 0) {
        mTracerMode = true;
        mFormationMode = FORMATION_MODE_MOVE_POINT;
        mTracerMode = FORMATION_MODE_MOVE_POINT;
    } else {
        mTracerMode = false;
        mTracerMode = FORMATION_MODE_ADD_POINT;
        if (mFormation.mNodeList.mCount > 0) {
            mFormationMode = FORMATION_MODE_MOVE_POINT;
        } else {
            mFormationMode = FORMATION_MODE_ADD_POINT;
        }
    }
}

void GameFormationEditor::Close() {
    
    mFormation.Print();
    mFormation.Reset();
    mEditorFormation.Reset();
    
    mEditor->CloseFormationEditor();
}

void GameFormationEditor::Clear() {
    mFormation.Reset();
    for (int i=0;i<BLUEPRINT_TRACER_COUNT;i++) {
        mFormation.mTracer[i].Nuke();
    }
    
    Refresh();
    mTracerMode = FORMATION_MODE_ADD_POINT;
    mFormationMode = FORMATION_MODE_ADD_POINT;
}

void GameFormationEditor::Refresh() {
    if (gGame != NULL) {
        gGame->DisposeAllObjects();
    }
    
    for (int i=0;i<BLUEPRINT_TRACER_COUNT;i++) {
        mFormation.mTracer[i].RefreshSpawnNodeList();
    }
    
    mFormation.Build(&mEditorFormation);
    mEditorFormation.Spawn(NULL, NULL);
}

void GameFormationEditor::Save() {
    
    if (gEditor == NULL) { return; }
    
    FString aPath = gDirDocuments + FString("formation_export_") + FString(gEditor->mExportIndex) + FString(".json");
    
    FJSON aJSON;
    aJSON.mRoot = mFormation.Save();
    aJSON.Save(aPath.c());
    
    FString aName = GenerateName();
    aJSON.Save(gDirDocuments + aName + ".json");
    aJSON.Save(gDirExport + aName + ".json");
    
}

void GameFormationEditor::Load() {
    
    if (gEditor == NULL) { return; }
    
    FString aPath = gDirDocuments + FString("formation_export_") + FString(gEditor->mExportIndex) + FString(".json");
    
    FJSON aJSON;
    aJSON.Load(aPath.c());
    Log("Path: %s\n", aPath.c());
    aJSON.Print();
    mFormation.Load(aJSON.mRoot);
    Refresh();
    PickDefaultModes();
    
}

void GameFormationEditor::Print() {
    mFormation.Print();
    
    FString aName = GenerateName();
    Log("Formation Name: %s\n", aName.c());
}


void GameFormationEditor::DeleteNode() {
    mFormation.Remove(mFormation.mSelectedNodeIndex);
}

void GameFormationEditor::DeleteTracer() {
    mFormation.TracerNuke();
    Refresh();
}

void GameFormationEditor::SpawnSelect(int pIndex) {
    
    Log("Select Spawn @ [%d]\n\n", pIndex);
    if (mTracerEnabled == true) {
        LevelFormationTracerBlueprint *aTracer = TracerGet();
        if (aTracer != NULL) {
            aTracer->mSelectedSpawnNodeIndex = pIndex;
        }
    } else {
        mFormation.mSelectedNodeIndex = pIndex;
    }
    
}

int GameFormationEditor::SpawnIndex() {
    
    if (mTracerEnabled == true) {
        LevelFormationTracerBlueprint *aTracer = TracerGet();
        if (aTracer != NULL) {
            return aTracer->mSelectedSpawnNodeIndex;
        }
    } else {
        return mFormation.mSelectedNodeIndex;
    }
    return -1;
}

void GameFormationEditor::SpawnPickBalloon() {
    LevelFormationNodeBlueprint *aSpawn = SpawnGet();
    if (aSpawn == NULL) { Refresh(); return; }
    aSpawn->mObjectType = GAME_OBJECT_TYPE_BALLOON;
    Refresh();
}

void GameFormationEditor::SpawnPickBrickHead() {
    LevelFormationNodeBlueprint *aSpawn = SpawnGet();
    if (aSpawn == NULL) { Refresh(); return; }
    aSpawn->mObjectType = GAME_OBJECT_TYPE_BRICKHEAD;
    Refresh();
}

void GameFormationEditor::SpawnPickBomb() {
    LevelFormationNodeBlueprint *aSpawn = SpawnGet();
    if (aSpawn == NULL) { Refresh(); return; }
    aSpawn->mObjectType = GAME_OBJECT_TYPE_BOMB;
    Refresh();
}

void GameFormationEditor::SpawnPickTurtle() {
    LevelFormationNodeBlueprint *aSpawn = SpawnGet();
    if (aSpawn == NULL) { Refresh(); return; }
    aSpawn->mObjectType = GAME_OBJECT_TYPE_TURTLE;
    Refresh();
}

LevelFormationNodeBlueprint *GameFormationEditor::SpawnGet() {
    LevelFormationNodeBlueprint *aResult = NULL;
    if (mTracerEnabled == true) {
        LevelFormationTracerBlueprint *aTracer = TracerGet();
        if (aTracer != NULL) {
            aResult = (LevelFormationNodeBlueprint *)aTracer->mSpawnNodeList.Fetch(aTracer->mSelectedSpawnNodeIndex);
        }
    } else {
        aResult = (LevelFormationNodeBlueprint *)mFormation.mNodeList.Fetch(mFormation.mSelectedNodeIndex);
    }
    return aResult;
}

LevelFormationTracerBlueprint *GameFormationEditor::TracerGet() {
    if (mTracerEnabled == true) {
        if (mFormation.mCurrentTracerIndex >= 0 && mFormation.mCurrentTracerIndex < BLUEPRINT_TRACER_COUNT) {
            return &(mFormation.mTracer[mFormation.mCurrentTracerIndex]);
        }
    }
    return NULL;
}





FString GameFormationEditor::GetShortNameForGameObjectType(int pGameObjectType) {
    FString aResult;
    if (pGameObjectType == GAME_OBJECT_TYPE_BRICKHEAD) {
        aResult = "r";
    } else {
        aResult = "b";
    }
    return aResult;
}

FString GameFormationEditor::GetPathSpeedName(int pSpeedClass) {
    FString aResult = "";
    if (pSpeedClass == SPEED_CLASS_EXTRA_SLOW) {
        aResult = "spxs";
    } else if (pSpeedClass == SPEED_CLASS_SLOW) {
        aResult = "sps";
    } else if (pSpeedClass == SPEED_CLASS_MEDIUM_SLOW) {
        aResult = "spms";
    } else if (pSpeedClass == SPEED_CLASS_MEDIUM_FAST) {
        aResult = "spmf";
    } else if (pSpeedClass == SPEED_CLASS_FAST) {
        aResult = "spf";
    } else if (pSpeedClass == SPEED_CLASS_EXTRA_FAST) {
        aResult = "spxf";
    } else if (pSpeedClass == SPEED_CLASS_INSANE) {
        aResult = "spxx";
    } else { //"Default /
        aResult = "spm";
    }
    return aResult;
}

FString GameFormationEditor::GetObjectListName(FIntList *pList) {
    FString aResult = "";
    
    
    bool aShouldSaveAll = false;
    
#define GO_TYPE_CNT 32
    int aTypeCount[GO_TYPE_CNT];
    memset(aTypeCount, 0, sizeof(aTypeCount));
    
    for (int i=0;i<pList->mCount;i++) {
        int aObjectType = pList->mData[i];
        if (aObjectType >= 0 && aObjectType < GO_TYPE_CNT) {
            aTypeCount[aObjectType] += 1;
        }
    }
    
    int aMonoType = -1;
    int aDifferentTypes = 0;
    for (int i=0;i<GO_TYPE_CNT;i++) {
        if (aTypeCount[i] == pList->mCount) { aMonoType = i; }
        if (aTypeCount[i] > 0) { aDifferentTypes += 1; }
    }
    
    if (aMonoType != -1) {
        FString aTypeName = GetShortNameForGameObjectType(aMonoType);
        aResult = FString("cfg") + FString(pList->mCount) + FString("x") + aTypeName;
        
    } else if (aDifferentTypes > 1) {
        aShouldSaveAll = true;
    }
    
    if (aShouldSaveAll == true) {
        FJSONNode *aSpawnNodeListNode = new FJSONNode();
        aSpawnNodeListNode->mNodeType = JSON_NODE_TYPE_ARRAY;
        
        aResult.Append("cfg");
        for (int i=0;i<pList->mCount;i++) {
            int aObjectType = pList->mData[i];
            FString aTypeName = GetShortNameForGameObjectType(aObjectType);
            aResult.Append(aTypeName.c());
        }
    }
    return aResult;
}

FString GameFormationEditor::GenerateTracerName(LevelFormationTracerBlueprint *pTracer) {
    FString aResult;
    FList aChunkList;
    aChunkList.Add(new FString("tra"));
    if (pTracer->mSpecialType == TRACER_SPECIAL_TYPE_CIRCLE) {
        aChunkList.Add(new FString("cir"));
        FString aRadiusString = FString(pTracer->mSpecialRadius) + FString("rad");
        aChunkList.Add(new FString(aRadiusString.c()));
    } else if (pTracer->mSpecialType == TRACER_SPECIAL_TYPE_ROUNDED_RECT) {
        aChunkList.Add(new FString("rrc"));
        FString aSizeString = FString(pTracer->mSpecialRadius) + FString("siz");
        aChunkList.Add(new FString(aSizeString.c()));
        FString aCornerString = FString(pTracer->mSpecialCornerRadius) + FString("crd");
        aChunkList.Add(new FString(aCornerString.c()));
    } else {
        //no special type..
        FString aPolyString = FString(pTracer->mTracerNodeList.mCount) + FString("ply");
        aChunkList.Add(new FString(aPolyString.c()));
    }
    
    if (true) {
        FIntList aTypeList;
        for (int i=0;i<pTracer->mSpawnNodeList.mCount;i++) {
            LevelFormationNodeBlueprint *aNodeBlueprint = (LevelFormationNodeBlueprint *)pTracer->mSpawnNodeList.mData[i];
            aTypeList.Add(aNodeBlueprint->mObjectType);
        }
        FString aTypeString = GetObjectListName(&aTypeList);
        if (aTypeString.mLength > 0) {
            aChunkList.Add(new FString(aTypeString.c()));
        }
    }
    
    for (int i=0;i<aChunkList.mCount;i++) {
        FString *aChunk = (FString *)aChunkList.mData[i];
        aResult.Append(aChunk->c());
        if (i < (aChunkList.mCount - 1)) {
            aResult.Append('_');
        }
    }
    
    FreeList(FString, aChunkList);
    return aResult;
}

FString GameFormationEditor::GenerateGridName() {
    FString aResult = "";
    FList aChunkList;
    
    aChunkList.Add(new FString("grd"));
    
    if (mGrid.mGridType == SNAP_GRID_TYPE_RECT) {
        aChunkList.Add(new FString("rec"));
        FString aSizeString = FString(mGrid.mGridRectWidth) + "x" + FString(mGrid.mGridRectHeight);
        aChunkList.Add(new FString(aSizeString.c()));
        FString aSpacingString = FString(mGrid.mGridRectSpacing) + "spc";
        aChunkList.Add(new FString(aSpacingString.c()));
    }
    
    if (mGrid.mGridType == SNAP_GRID_TYPE_CIRCLE) {
        aChunkList.Add(new FString("cir"));
        FString aSpacingString = FString(mGrid.mGridCircleRingSpacing) + "rsp";
        aChunkList.Add(new FString(aSpacingString.c()));
        FString aCountString = FString(mGrid.mGridCircleRingCount) + "rct";
        aChunkList.Add(new FString(aCountString.c()));
        FString aRadialString = FString(mGrid.mGridCircleRadialCount) + "rdc";
        aChunkList.Add(new FString(aRadialString.c()));
    }
    
    if (mGrid.mGridType == SNAP_GRID_TYPE_STAR) {
        aChunkList.Add(new FString("sta"));
        FString aRadInnerString = FString(mGrid.mGridStarInnerRadius) + "rdi";
        aChunkList.Add(new FString(aRadInnerString.c()));
        
        FString aRadOuterString = FString(mGrid.mGridStarOuterRadius) + "rdo";
        aChunkList.Add(new FString(aRadOuterString.c()));
        
        FString aPointCountString = FString(mGrid.mGridStarLinePointCount) + "ptc";
        aChunkList.Add(new FString(aPointCountString.c()));
        
        FString aArmCountString = FString(mGrid.mGridStarArmCount) + "arc";
        aChunkList.Add(new FString(aArmCountString.c()));
        
        if (mGrid.mGridStarStartRotation != 0) {
            FString aStartRotationString = FString(mGrid.mGridStarStartRotation) + "ros";
            aChunkList.Add(new FString(aStartRotationString.c()));
        }
    }
    
    
    
    if (mGrid.mGridType == SNAP_GRID_TYPE_NGON1) {
        
        if (mGrid.mGridNGON1Sides == 3) { aChunkList.Add(new FString("tri")); }
        if (mGrid.mGridNGON1Sides == 4) { aChunkList.Add(new FString("qud")); }
        if (mGrid.mGridNGON1Sides == 5) { aChunkList.Add(new FString("pen")); }
        if (mGrid.mGridNGON1Sides == 6) { aChunkList.Add(new FString("hex")); }
        if (mGrid.mGridNGON1Sides == 7) { aChunkList.Add(new FString("hep")); }
        if (mGrid.mGridNGON1Sides == 8) { aChunkList.Add(new FString("oct")); }
        if (mGrid.mGridNGON1Sides == 9) { aChunkList.Add(new FString("non")); }
        if (mGrid.mGridNGON1Sides == 10) { aChunkList.Add(new FString("dec")); }
        
        aChunkList.Add(new FString("ng1"));
        FString aSidesString = FString(mGrid.mGridNGON1Sides) + "sid";
        aChunkList.Add(new FString(aSidesString.c()));
        FString aSpacingString = FString(mGrid.mGridNGON1RingSpacing) + "rsp";
        aChunkList.Add(new FString(aSpacingString.c()));
        FString aCountString = FString(mGrid.mGridNGON1RingCount) + "rct";
        aChunkList.Add(new FString(aCountString.c()));
        FString aPointSpacingString = FString(mGrid.mGridNGON1PointSpacing) + "pts";
        aChunkList.Add(new FString(aPointSpacingString.c()));
        if (mGrid.mGridNGON1StartRotation != 0) {
            FString aStartRotationString = FString(mGrid.mGridNGON1StartRotation) + "ros";
            aChunkList.Add(new FString(aStartRotationString.c()));
        }
    }
    
    int aCount = 0;
    int aOnCount = 0;
    float aForgiveness = 2.0f;
    
    for (int i=0;i<mGrid.mGridList.mCount;i++) {
        bool aHit = false;
        EnumList(LevelFormationNodeBlueprint, aNode, mFormation.mNodeList) {
            float aX = aNode->mEditorX;
            float aY = aNode->mEditorY;
            float aDistance = Distance(mGrid.mGridList.GetX(i), mGrid.mGridList.GetY(i), aX, aY);
            if (aDistance <= aForgiveness) {
                aHit = true;
            }
        }
        
        if (aHit == true) {
            aOnCount++;
        }
        aCount++;
    }
    
    if (aOnCount >= aCount) {
        aChunkList.Add(new FString("solid"));
    } else {
        
        if (aCount > 0) {
            
            float aPercent = ((float)aOnCount) / ((float)aCount);
            int aPct = int(round(aPercent * 100.0f));
            
            FString aFillString = FString(aPct) + "ful";
            aChunkList.Add(new FString(aFillString.c()));
            
        }
    }
    
    for (int i=0;i<aChunkList.mCount;i++) {
        FString *aChunk = (FString *)aChunkList.mData[i];
        aResult.Append(aChunk->c());
        if (i < (aChunkList.mCount - 1)) {
            aResult.Append('_');
        }
    }
    
    FreeList(FString, aChunkList);
    return aResult;
}

FString GameFormationEditor::GenerateNodesName() {
    FString aResult = "";
    
    FList aPickList;
    
    EnumList(LevelFormationNodeBlueprint, aNode, mFormation.mNodeList) {
        aPickList.Add(aNode);
    }
    FIntList aTypeList;
    
    float aForgiveness = 2.0f;
    while (aPickList.mCount > 0) {
        int aChosenIndex = 0;
        LevelFormationNodeBlueprint *aFirstNode = (LevelFormationNodeBlueprint *)aPickList.First();
        float aTopY = aFirstNode->mEditorY;
        float aLeftX = aFirstNode->mEditorX;
        
        int aIndex = 0;
        EnumList(LevelFormationNodeBlueprint, aNode, aPickList) {
            if (aNode->mEditorY < aTopY) {
                aTopY = aNode->mEditorY;
                aLeftX = aNode->mEditorX;
                aChosenIndex = aIndex;
            }
            ++aIndex;
        }
        
        aIndex = 0;
        EnumList(LevelFormationNodeBlueprint, aNode, aPickList) {
            float aDiffY = fabsf(aNode->mEditorY - aTopY);
            if (aDiffY <= aForgiveness) {
                if (aNode->mEditorX < aLeftX) {
                    aLeftX = aNode->mEditorX;
                    aChosenIndex = aIndex;
                }
            }
            ++aIndex;
        }
        LevelFormationNodeBlueprint *aChosenNode = (LevelFormationNodeBlueprint *)aPickList.Fetch(aChosenIndex);
        aPickList.RemoveAtIndex(aChosenIndex);
        aTypeList.Add(aChosenNode->mObjectType);
    }
    aResult = FString("nodes_") + GetObjectListName(&aTypeList);
    
    int aCount = 0;
    int aOnCount = 0;
    aForgiveness = 2.0f;
    EnumList(LevelFormationNodeBlueprint, aNode, mFormation.mNodeList) {
        bool aHit = false;
        for (int i=0;i<mGrid.mGridList.mCount;i++) {
            float aX = aNode->mEditorX;
            float aY = aNode->mEditorY;
            float aDistance = Distance(mGrid.mGridList.GetX(i), mGrid.mGridList.GetY(i), aX, aY);
            if (aDistance <= aForgiveness) { aHit = true; }
        }
        if (aHit == true) { aOnCount++; }
        aCount++;
    }
    if (aCount == aOnCount) {
        aResult += "_allg";
    } else {
        int aOffCount = aCount - aOnCount;
        aResult += FString(aOnCount) + FString("on") + FString(aOffCount) + FString("off");
    }
    return aResult;
}

FString GameFormationEditor::GenerateName() {
    
    FString aResult = "f_";
    FList aSliceList;
    
    bool aUseGridName = false;
    for (int i=0;i<BLUEPRINT_TRACER_COUNT;i++) {
        if (mFormation.mTracer[i].IsValid()) {
            
            if (mFormation.mTracer[i].mSpecialType == TRACER_SPECIAL_TYPE_NONE) {
                aUseGridName = true;
            }
        }
    }
    if (mFormation.mNodeList.mCount > 0) {
        aUseGridName = true;
    }
    if (aUseGridName) {
        FString aGridName = GenerateGridName();
        aSliceList.Add(new FString(aGridName.c()));
    }
    
    if (mFormation.mNodeList.mCount > 0) {
        FString aNodeListName = GenerateNodesName();
        aSliceList.Add(new FString(aNodeListName.c()));
    }
    
    for (int i=0;i<BLUEPRINT_TRACER_COUNT;i++) {
        if (mFormation.mTracer[i].IsValid()) {
            FString aTracerName = GenerateTracerName(&mFormation.mTracer[i]);
            aSliceList.Add(new FString(aTracerName.c()));
        }
    }
    
    for (int i=0;i<aSliceList.mCount;i++) {
        FString *aSlice = (FString *)aSliceList.mData[i];
        aResult.Append(aSlice->c());
        if (i < (aSliceList.mCount - 1)) {
            aResult.Append("__");
        }
    }
    FreeList(FString, aSliceList);
    
    
    return aResult;
}





