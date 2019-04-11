//
//  LevelSectionPermanentBlueprint.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/5/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelSectionPermanentBlueprint.hpp"
#include "GameEditor.hpp"
#include "LevelSectionPermanent.hpp"

LevelSectionPermanentBlueprint::LevelSectionPermanentBlueprint() {
    mPath.mPerm = this;
    
    mEditorX = 0.0f; mEditorY = 0.0f;
    mPercentX = 0.0f; mPercentY = 0.0f;
    mBaseGameX = 0.0f; mBaseGameY = 0.0f;
    mGameX = 0.0f; mGameY = 0.0f;
    
    mKillTimer = 8;
}

LevelSectionPermanentBlueprint::~LevelSectionPermanentBlueprint() {
    
}

void LevelSectionPermanentBlueprint::Reset() {
    mPath.Reset();
}

//mPath
void LevelSectionPermanentBlueprint::Update() {
    mPath.Update();
    
    
}

void LevelSectionPermanentBlueprint::Draw(bool pSelected) {
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


void LevelSectionPermanentBlueprint::ApplyEditorConstraints() {
    
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

void LevelSectionPermanentBlueprint::ShiftX(float pShiftX) {
    if (mConstraint.mTypeX == X_CONSTRAINT_NONE) {
        mEditorX = mEditorX + pShiftX;
    } else {
        mConstraint.mOffsetX += pShiftX;
    }
}

void LevelSectionPermanentBlueprint::ShiftY(float pShiftY) {
    if (mConstraint.mTypeY == Y_CONSTRAINT_NONE) {
        mEditorY = mEditorY + pShiftY;
    } else {
        mConstraint.mOffsetY += pShiftY;
    }
}

void LevelSectionPermanentBlueprint::Build(LevelSectionPermanent *pPerm) {
    
    if (pPerm == NULL) { return; }
    
    pPerm->Reset();
    mPath.Build(&pPerm->mPath);
    
    FPoint aPoint;
    aPoint.mX = mPercentX / 100.0f;
    aPoint.mY = mPercentY / 100.0f;
    
    if (mConstraint.HasX()) {
        aPoint.mX = mConstraint.GameX(false);
        
        pPerm->mBaseX = aPoint.mX;
    } else {
        pPerm->mBaseX = gGame->mGameAreaLeft + (gGame->mGameAreaRight - gGame->mGameAreaLeft) * aPoint.mX;
    }
    
    if (mConstraint.HasY()) {
        aPoint.mY = mConstraint.GameY(false);
        pPerm->mBaseY = aPoint.mY;
    } else {
        pPerm->mBaseY = gGame->mGameAreaTop + (gGame->mGameAreaBottom - gGame->mGameAreaTop) * aPoint.mY;
    }
    
    
    /*
    
    
    for (int i=0;i<mNodeList.mCount;i++) {
     
    }
    
    */
    
}



FJSONNode *LevelSectionPermanentBlueprint::Save() {
    FJSONNode *aExport = new FJSONNode();
    
    
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
    
    if (mPath.mNodeList.mCount > 0) {
        aExport->AddDictionary("path", mPath.Save());
    }
    
    return aExport;
}

void LevelSectionPermanentBlueprint::Load(FJSONNode *pNode) {
    Reset();
    if (pNode == NULL) { return; }
    
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
}
