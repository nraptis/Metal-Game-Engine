//
//  LevelSectionPermBlueprint.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/5/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelSectionPermBlueprint.hpp"
#include "GameEditor.hpp"
#include "LevelSectionPerm.hpp"

LevelSectionPermBlueprint::LevelSectionPermBlueprint() {
    mPath.mPerm = this;
    
    mSpawnEqualSpacing = true;
    mSpawnSpacing = 120;
    
    mEditorX = 0.0f; mEditorY = 0.0f;
    mPercentX = 0.0f; mPercentY = 0.0f;
    mBaseGameX = 0.0f; mBaseGameY = 0.0f;
    mGameX = 0.0f; mGameY = 0.0f;
    
    mObjectType = GAME_OBJECT_TYPE_BALLOON;
    
    mKillTimer = 8;
}

LevelSectionPermBlueprint::~LevelSectionPermBlueprint() {
    
}

void LevelSectionPermBlueprint::Reset() {
    mPath.Reset();
    mMotionController.Reset();
    for (int i=0;i<PERM_MAX_SPAWN_COUNT;i++) {
        mSpawn[i].Reset();
    }
    mSpawnCount = 1;
}

void LevelSectionPermBlueprint::Update() {
    mPath.Update();
    
    if (IsPathPerm()) {
        //We don't support stacking these...
        mMotionController.Reset();
    }
    
    if (mSpawnCount < 1) mSpawnCount = 1;
    if (mSpawnCount > PERM_MAX_SPAWN_COUNT) mSpawnCount = PERM_MAX_SPAWN_COUNT;
    
    if (mSelectedSpawnIndex < 0) { mSelectedSpawnIndex = 0; }
    if (mSelectedSpawnIndex >= mSpawnCount) { mSelectedSpawnIndex = mSpawnCount - 1; }
}

void LevelSectionPermBlueprint::Draw(bool pSelected) {
    mPath.Draw(pSelected);
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    if (pSelected) {
        Graphics::SetColor(1.0f, 0.45f, 0.35f, 0.75f);
        Graphics::DrawLine(mEditorX - 5.0f, mEditorY - 5.0f, mEditorX + 5.0f, mEditorY + 5.0f, 2.0f);
        Graphics::DrawLine(mEditorX + 5.0f, mEditorY - 5.0f, mEditorX - 5.0f, mEditorY + 5.0f, 2.0f);
        if (mConstraint.mTypeX != X_CONSTRAINT_NONE) {
            Graphics::SetColor(1.0f, 0.0f, 0.0f, 0.75f);
            Graphics::DrawLine(mEditorX, mEditorY - 10.0f, mEditorX, mEditorY + 10.0f, 1.5f);
        }
        if (mConstraint.mTypeY != Y_CONSTRAINT_NONE) {
            Graphics::SetColor(1.0f, 0.0f, 0.0f, 0.75f);
            Graphics::DrawLine(mEditorX - 10.0f, mEditorY, mEditorX + 10.0f, mEditorY, 1.5f);
        }
    } else {
        Graphics::SetColor(0.25f, 0.55f, 0.45f, 0.75f);
        Graphics::DrawLine(mEditorX - 4.0f, mEditorY - 4.0f, mEditorX + 4.0f, mEditorY + 4.0f, 1.0f);
        Graphics::DrawLine(mEditorX + 4.0f, mEditorY - 4.0f, mEditorX - 4.0f, mEditorY + 4.0f, 1.0f);
        
        if (mConstraint.mTypeX != X_CONSTRAINT_NONE) {
            Graphics::SetColor(1.0f, 0.0f, 0.0f, 0.5f);
            Graphics::DrawLine(mEditorX, mEditorY - 10.0f, mEditorX, mEditorY + 10.0f, 1.0f);
        }
        if (mConstraint.mTypeY != Y_CONSTRAINT_NONE) {
            Graphics::SetColor(1.0f, 0.0f, 0.0f, 0.5f);
            Graphics::DrawLine(mEditorX - 10.0f, mEditorY, mEditorX + 10.0f, mEditorY, 1.0f);
        }
    }
    Graphics::SetColor();
}


void LevelSectionPermBlueprint::ApplyEditorConstraints() {
    
    if (gEditor != NULL) {
        if (mConstraint.mTypeX == X_CONSTRAINT_LEFT_EXIT) { mEditorX = gEditor->mExitZoneLeft; }
        if (mConstraint.mTypeX == X_CONSTRAINT_LEFT_SPAWN) { mEditorX = gEditor->mSpawnZoneLeft; }
        if (mConstraint.mTypeX == X_CONSTRAINT_LEFT_PEEK) { mEditorX = gEditor->mPeekZoneLeft; }
        if (mConstraint.mTypeX == X_CONSTRAINT_LEFT_QUARTER) { mEditorX = gEditor->mQuarterZoneLeft; }
        if (mConstraint.mTypeX == X_CONSTRAINT_CENTER) { mEditorX = gEditor->mCenterH; }
        if (mConstraint.mTypeX == X_CONSTRAINT_RIGHT_QUARTER) { mEditorX = gEditor->mQuarterZoneRight; }
        if (mConstraint.mTypeX == X_CONSTRAINT_RIGHT_PEEK) { mEditorX = gEditor->mPeekZoneRight; }
        if (mConstraint.mTypeX == X_CONSTRAINT_RIGHT_SPAWN) { mEditorX = gEditor->mSpawnZoneRight; }
        if (mConstraint.mTypeX == X_CONSTRAINT_RIGHT_EXIT) { mEditorX = gEditor->mExitZoneRight; }
        
        if (mConstraint.mTypeY == Y_CONSTRAINT_TOP_EXIT) { mEditorY = gEditor->mExitZoneTop; }
        if (mConstraint.mTypeY == Y_CONSTRAINT_TOP_SPAWN) { mEditorY = gEditor->mSpawnZoneTop; }
        if (mConstraint.mTypeY == Y_CONSTRAINT_TOP_PEEK) { mEditorY = gEditor->mPeekZoneTop; }
        if (mConstraint.mTypeY == Y_CONSTRAINT_TOP_QUARTER) { mEditorY = gEditor->mQuarterZoneTop; }
        if (mConstraint.mTypeY == Y_CONSTRAINT_CENTER) { mEditorY = gEditor->mCenterV; }
        if (mConstraint.mTypeY == Y_CONSTRAINT_BOTTOM_QUARTER) { mEditorY = gEditor->mQuarterZoneBottom; }
        if (mConstraint.mTypeY == Y_CONSTRAINT_BOTTOM) { mEditorY = gEditor->mPlayZoneBottom; }
        
    }
    
    mPath.ApplyEditorConstraints();
    
    if (gEditor) {
        
        gEditor->mSection.PermRefreshPositions();
        gEditor->RefreshPlayback();
    }
}

int LevelSectionPermBlueprint::CountProgressObjects() {
    int aResult = 0;
    
    if (IsPathPerm()) {
        
        for (int i=0;i<mSpawnCount;i++) {
            aResult += mSpawn[i].CountProgressObjects();
        }
    } else {
        
        if (mFormationID.mLength > 0) {
            aResult += LevelFormationBlueprint::CountProgressObjects(mFormationID.c());
        } else {
            if (gGame->DoesObjectTypeCountTowardsProgressCount(mObjectType)) {
                aResult += 1;
            }
        }
    }
    return aResult;
}

void LevelSectionPermBlueprint::ShiftX(float pShiftX) {
    if (mConstraint.mTypeX == X_CONSTRAINT_NONE) {
        mEditorX = mEditorX + pShiftX;
    } else {
        mConstraint.mOffsetX += pShiftX;
    }
    if (gEditor) {
        gEditor->mSection.PermRefreshPositions();
        gEditor->RefreshPlayback();
    }
}

void LevelSectionPermBlueprint::ShiftY(float pShiftY) {
    if (mConstraint.mTypeY == Y_CONSTRAINT_NONE) {
        mEditorY = mEditorY + pShiftY;
    } else {
        mConstraint.mOffsetY += pShiftY;
    }
    if (gEditor) {
        gEditor->mSection.PermRefreshPositions();
        gEditor->RefreshPlayback();
    }
}

void LevelSectionPermBlueprint::ShiftSpawnFromIndex(int pIndex) {
    if (mSpawnCount >= PERM_MAX_SPAWN_COUNT) { return; }
    if (pIndex >= (mSpawnCount)) { return; }
    if (pIndex < 0) { pIndex = 0; }
    for (int i=mSpawnCount;i>pIndex;i--) {
        FJSONNode *aSave = mSpawn[i-1].Save();
        mSpawn[i].Load(aSave);
        delete aSave;
    }
    mSpawnCount++;
}

void LevelSectionPermBlueprint::DeletePath() {
    mPath.Reset();
}

bool LevelSectionPermBlueprint::IsPathPerm() {
    if (mPath.mNodeList.mCount > 0) {
        return true;
    }
    return false;
}



void LevelSectionPermBlueprint::Build(LevelSectionPerm *pPerm) {
    
    if (pPerm == NULL) { return; }
    
    pPerm->Reset();
    mPath.Build(&pPerm->mPath);
    
    if (mFormationID.mLength > 0) {
        pPerm->mFormationID = mFormationID.c();
        
        
    }
    pPerm->mObjectType = mObjectType;
    
    pPerm->mSpawnEqualSpacing = mSpawnEqualSpacing;
    pPerm->mSpawnSpacing = ((float)mSpawnSpacing);
    
    FVec2 aPoint;
    aPoint.mX = mPercentX / 100.0f;
    aPoint.mY = mPercentY / 100.0f;
    
    if (mConstraint.HasX()) {
        aPoint.mX = mConstraint.GameX(true);
        pPerm->mBaseX = aPoint.mX;
    } else {
        pPerm->mBaseX = gGame->mGameAreaLeft + (gGame->mGameAreaRight - gGame->mGameAreaLeft) * aPoint.mX;
    }
    
    if (mConstraint.HasY()) {
        aPoint.mY = mConstraint.GameY(true);
        pPerm->mBaseY = aPoint.mY;
    } else {
        pPerm->mBaseY = gGame->mGameAreaTop + (gGame->mGameAreaBottom - gGame->mGameAreaTop) * aPoint.mY;
    }
    
    float aShiftX = 0.0f;
    float aShiftY = 0.0f;
    if (mConstraint.mTypeX != X_CONSTRAINT_NONE) {
        aShiftX += mConstraint.mOffsetX;
    }
    if (mConstraint.mTypeY != Y_CONSTRAINT_NONE) {
        aShiftY += mConstraint.mOffsetY;
    }
    
    pPerm->mPath.Shift(-pPerm->mBaseX + aShiftX, -pPerm->mBaseY + aShiftY);
    
    
    //Only include spawns when we have a path...
    
    if (pPerm->mPath.mNodeList.mCount > 0) {
        
        if (mSpawnCount < 1) mSpawnCount = 1;
        if (mSpawnCount > PERM_MAX_SPAWN_COUNT) mSpawnCount = PERM_MAX_SPAWN_COUNT;
        
        for (int i=0;i<mSpawnCount;i++) {
            LevelPermSpawn *aSpawn = new LevelPermSpawn(pPerm, &pPerm->mPath);
            
            aSpawn->mFormationID = mSpawn[i].mFormationID.c();
            aSpawn->mObjectType = mSpawn[i].mObjectType;
            aSpawn->mSpacingOffset = mSpawn[i].mSpawnSpacingOffset;
            
            if (mSpawn[i].mMotionController.IsEmpty() == false) {
                mSpawn[i].mMotionController.Build(&(aSpawn->mMotionController));
            }
            
            mSpawn[i].mStyleController.Build(&(aSpawn->mStyleController));
            
            if (mSpawn[i].mFormationID.mLength > 0) {
                mSpawn[i].mFormationConfiguration.Build(&(aSpawn->mFormationConfiguration));
            }
            
            pPerm->mSpawnList.Add(aSpawn);
        }
    } else {
        
        if (mMotionController.IsEmpty() == false) {
            mMotionController.Build(&pPerm->mMotionController);
        }
        
        mStyleController.Build(&(pPerm->mStyleController));
        
        if (mFormationID.mLength > 0) {
            mFormationConfiguration.Build(&(pPerm->mFormationConfiguration));
        }
    }
    
    
    
}



FJSONNode *LevelSectionPermBlueprint::Save() {
    FJSONNode *aExport = new FJSONNode();
    
    if (mSpawnEqualSpacing != true) { aExport->AddDictionaryBool("equal_spacing", mSpawnEqualSpacing); }
    
    if (mSpawnSpacing != 120) { aExport->AddDictionaryInt("spawn_spacing", mSpawnSpacing); }
    
    if (mConstraint.mTypeX == X_CONSTRAINT_NONE) {
        
        float aLeft = gEditor->mGameAreaLeft;
        float aRight = gEditor->mGameAreaRight;
        
        //100x percision
        float aX = (mEditorX - aLeft) / (aRight - aLeft) * 100.0f;
        aExport->AddDictionaryFloat("x", aX);
    } else {
        if (mConstraint.mTypeX != X_CONSTRAINT_NONE) {
            aExport->AddDictionaryInt("x_con", mConstraint.mTypeX);
        }
        if (mConstraint.mOffsetX != 0.0f) {
            aExport->AddDictionaryFloat("x_con_offset", mConstraint.mOffsetX);
        }
        if (mConstraint.mTargetX != -1 && mConstraint.mTypeX == X_CONSTRAINT_TARGET) {
            aExport->AddDictionaryInt("x_con_target", mConstraint.mTargetX);
        }
    }
    
    if (mConstraint.mTypeY == Y_CONSTRAINT_NONE) {
        float aTop = gEditor->mGameAreaTop;
        float aBottom = gEditor->mGameAreaBottom;
        //100x percision
        float aY = (mEditorY - aTop) / (aBottom - aTop) * 100.0f;
        aExport->AddDictionaryFloat("y", aY);
    } else {
        if (mConstraint.mTypeY != Y_CONSTRAINT_NONE) {
            aExport->AddDictionaryInt("y_con", mConstraint.mTypeY);
        }
        if (mConstraint.mOffsetY != 0.0f) {
            aExport->AddDictionaryFloat("y_con_offset", mConstraint.mOffsetY);
        }
        if (mConstraint.mTargetY != -1 && mConstraint.mTypeY == Y_CONSTRAINT_TARGET) {
            aExport->AddDictionaryInt("y_con_target", mConstraint.mTargetY);
        }
    }
    
    if (IsPathPerm()) {
        aExport->AddDictionary("path", mPath.Save());
        
        //We only save the spawn list when we have a
        //path... The LIST follows the PATH...
        FJSONNode *aSpawnList = new FJSONNode();
        aSpawnList->mNodeType = JSON_NODE_TYPE_ARRAY;
        for (int i=0;i<mSpawnCount;i++) {
            aSpawnList->AddArray(mSpawn[i].Save());
        }
        aExport->AddDictionary("spawn", aSpawnList);
    } else {
     
        if (mMotionController.IsEmpty() == false) {
            aExport->AddDictionary("motion", mMotionController.Save());
        }
        if (mStyleController.ShouldSave() == true) {
            aExport->AddDictionary("style", mStyleController.Save());
        }
        
        
        if (mFormationID.mLength > 0) {
            //Possibility 1.) We have a formation...
            aExport->AddDictionaryString("formation", mFormationID.c());
            aExport->AddDictionary("formation_config", mFormationConfiguration.Save());
        } else {
            //Possibility 2.) We have an object...
            if (mObjectType != GAME_OBJECT_TYPE_BALLOON) {
                aExport->AddDictionaryInt("type", mObjectType);
            }
        }
    }
    
    
    
    
    return aExport;
}

void LevelSectionPermBlueprint::Load(FJSONNode *pNode) {
    Reset();
    if (pNode == NULL) { return; }
    
    mSpawnEqualSpacing = pNode->GetBool("equal_spacing", true);
    mSpawnSpacing = pNode->GetInt("spawn_spacing", 120);
    
    mConstraint.mTypeX = pNode->GetInt("x_con", X_CONSTRAINT_NONE);
    mConstraint.mTargetX = pNode->GetInt("x_con_target", -1);
    mConstraint.mOffsetX = pNode->GetFloat("x_con_offset", 0.0f);
    
    mConstraint.mTypeY = pNode->GetInt("y_con", Y_CONSTRAINT_NONE);
    mConstraint.mTargetY = pNode->GetInt("y_con_target", -1);
    mConstraint.mOffsetY = pNode->GetFloat("y_con_offset", 0.0f);
    
    mPercentX = 0.0f;
    mPercentX = pNode->GetFloat("x", mPercentX);
    
    if (gEditor != NULL) {
        float aLeft = gEditor->mGameAreaLeft;
        float aRight = gEditor->mGameAreaRight;
        mEditorX = aLeft + (aRight - aLeft) * (mPercentX / 100.0f);
    }
    
    mPercentY = 0.0f;
    mPercentY = pNode->GetFloat("y", mPercentY);
    if (gEditor != NULL) {
        float aTop = gEditor->mGameAreaTop;
        float aBottom = gEditor->mGameAreaBottom;
        mEditorY = aTop + (aBottom - aTop) * (mPercentY / 100.0f);
    }
    
    FJSONNode *aPathNode = pNode->GetDictionary("path");
    mPath.Load(aPathNode);
    
    mSpawnCount = 0;
    if (mPath.mNodeList.mCount > 0) {
        FJSONNode *aSpawnList = pNode->GetArray("spawn");
        if (aSpawnList != NULL) {
            EnumJSONArray(aSpawnList, aSpawnNode) {
                mSpawn[mSpawnCount].Load(aSpawnNode);
                ++mSpawnCount;
            }
        }
    }
    
    //if (mSpawnCount < 0) { mSpawnCount = 0; }
    if (mSpawnCount > WAVE_MAX_SPAWN_COUNT) { mSpawnCount = WAVE_MAX_SPAWN_COUNT; }
    
    
    if (mSpawnCount == 0) {
        FJSONNode *aMotionNode = pNode->GetDictionary("motion");
        mMotionController.Load(aMotionNode);
        
        FJSONNode *aStyleNode = pNode->GetDictionary("style");
        mStyleController.Load(aStyleNode);
        
        
        mFormationID = pNode->GetString("formation", mFormationID);
        
        if (mFormationID.mLength > 0) {
            //Possibility 1.) We have a formation...
            
            FJSONNode *aFormationConfigurationNode = pNode->GetDictionary("formation_config");
            mFormationConfiguration.Load(aFormationConfigurationNode);
            
        } else {
            //Possibility 2.) We have an object...
            mObjectType = pNode->GetInt("type", mObjectType);
        }
    }
    
    
    
    
    
}
