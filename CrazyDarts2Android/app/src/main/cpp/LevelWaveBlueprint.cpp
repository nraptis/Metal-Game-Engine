//
//  LevelWaveBlueprint.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelWaveBlueprint.hpp"
#include "GameEditor.hpp"
#include "LevelWave.hpp"

LevelWaveBlueprint::LevelWaveBlueprint() {
    mPath.mWave = this;
}

LevelWaveBlueprint::~LevelWaveBlueprint() {
    
}

void LevelWaveBlueprint::Clear() {
    mPath.Clear();
}

void LevelWaveBlueprint::Draw(bool pSelected) {
    mPath.Draw(pSelected);
}


void LevelWaveBlueprint::ApplyEditorConstraints() {
    
    for (int aLoops = 0;aLoops<40;aLoops++) {
        for (int i=0;i<mPath.mNodeList.mCount;i++) {
            LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mPath.mNodeList.mData[i];
            
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_TARGET) {
                LevelWavePathBlueprintNode *aTarget = (LevelWavePathBlueprintNode *)mPath.mNodeList.mData[aNode->mConstraint.mTargetX];
                if (aTarget != 0) {
                    aNode->mX = aTarget->mX;
                }
            }
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_TARGET) {
                LevelWavePathBlueprintNode *aTarget = (LevelWavePathBlueprintNode *)mPath.mNodeList.mData[aNode->mConstraint.mTargetY];
                if (aTarget != 0) {
                    aNode->mY = aTarget->mY;
                }
            }
            
            
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_LEFT_EXIT) { aNode->mX = gEditor->mExitZoneLeft; }
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_LEFT_SPAWN) { aNode->mX = gEditor->mSpawnZoneLeft; }
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_LEFT_PEEK) { aNode->mX = gEditor->mPeekZoneLeft; }
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_LEFT_QUARTER) { aNode->mX = gEditor->mQuarterZoneLeft; }
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_CENTER) { aNode->mX = gEditor->mCenterH; }
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_RIGHT_QUARTER) { aNode->mX = gEditor->mQuarterZoneRight; }
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_RIGHT_PEEK) { aNode->mX = gEditor->mPeekZoneRight; }
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_RIGHT_SPAWN) { aNode->mX = gEditor->mSpawnZoneRight; }
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_RIGHT_EXIT) { aNode->mX = gEditor->mExitZoneRight; }
            
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_TOP_EXIT) { aNode->mY = gEditor->mExitZoneTop; }
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_TOP_SPAWN) { aNode->mY = gEditor->mSpawnZoneTop; }
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_TOP_PEEK) { aNode->mY = gEditor->mPeekZoneTop; }
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_TOP_QUARTER) { aNode->mY = gEditor->mQuarterZoneTop; }
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_CENTER) { aNode->mY = gEditor->mCenterV; }
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_BOTTOM_QUARTER) { aNode->mY = gEditor->mQuarterZoneBottom; }
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_BOTTOM) { aNode->mY = gEditor->mPlayZoneBottom; }
            
        }
    }
    Build();
}

void LevelWaveBlueprint::Build() {
    if (gGame) {
#ifdef EDITOR_MODE
        Build(&gGame->mEditorWave);
#endif
    }
}

void LevelWaveBlueprint::Build(LevelWave *pWave) {
    
    if (pWave == NULL) { return; }
    
    
    //if (mSpeed < 0.5f) { mSpeed = 0.5f; }
    //if (mSpeed > 50.0f) { mSpeed = 50.0f; }
    
    pWave->Reset();
    
    pWave->mPath.mSmooth = mPath.mSmooth;
    pWave->mPath.SetSpeedClass(mPath.mSpeedClass);
    //mSpeedClass = WAVE_SPEED_MEDIUM;
    
    
    
    for (int i=0;i<mPath.mNodeList.mCount;i++) {
        LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mPath.mNodeList.mData[i];
        FPoint aPoint = mPath.GetNormalizedPos(aNode);
        
        if (aNode->mConstraint.HasX()) {
            aPoint.mX = aNode->mConstraint.GameX(false);
            aNode->mBaseGameX = aPoint.mX;
        } else {
            aNode->mBaseGameX = gGame->mGameAreaLeft + (gGame->mGameAreaRight - gGame->mGameAreaLeft) * aPoint.mX;
        }
        
        if (aNode->mConstraint.HasY()) {
            aPoint.mY = aNode->mConstraint.GameY(false);
            aNode->mBaseGameY = aPoint.mY;
        } else {
            aNode->mBaseGameY = gGame->mGameAreaTop + (gGame->mGameAreaBottom - gGame->mGameAreaTop) * aPoint.mY;
        }
    }
    
    for (int aLoops = 0;aLoops<40;aLoops++) {
        for (int i=0;i<mPath.mNodeList.mCount;i++) {
            LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mPath.mNodeList.mData[i];
            if (aNode->mConstraint.mTypeX == X_CONSTRAINT_TARGET) {
                LevelWavePathBlueprintNode *aTarget = (LevelWavePathBlueprintNode *)mPath.mNodeList.mData[aNode->mConstraint.mTargetX];
                if (aTarget != 0) { aNode->mBaseGameX = aTarget->mBaseGameX; }
            }
            if (aNode->mConstraint.mTypeY == Y_CONSTRAINT_TARGET) {
                LevelWavePathBlueprintNode *aTarget = (LevelWavePathBlueprintNode *)mPath.mNodeList.mData[aNode->mConstraint.mTargetY];
                if (aTarget != 0) { aNode->mBaseGameY = aTarget->mBaseGameY; }
            }
        }
    }
    
    for (int i=0;i<mPath.mNodeList.mCount;i++) {
        LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mPath.mNodeList.mData[i];
        
        if (aNode->mConstraint.HasX() || aNode->mConstraint.mTypeX == X_CONSTRAINT_TARGET) {
            aNode->mGameX = aNode->mBaseGameX + aNode->mConstraint.mOffsetX;
        } else {
            aNode->mGameX = aNode->mBaseGameX;
        }
        
        if (aNode->mConstraint.HasY() || aNode->mConstraint.mTypeY == Y_CONSTRAINT_TARGET) {
            aNode->mGameY = aNode->mBaseGameY + aNode->mConstraint.mOffsetY;
        } else {
            aNode->mGameY = aNode->mBaseGameY;
        }
    }
    
    for (int i=0;i<mPath.mNodeList.mCount;i++) {
        LevelWavePathBlueprintNode *aNode = (LevelWavePathBlueprintNode *)mPath.mNodeList.mData[i];
        
        float aChamferSize = ((float) aNode->mChamferSize);
        if (aNode->mChamferSize > 0 &&
            i > 0 &&
            i < (mPath.mNodeList.mCount - 1)) {
            
            LevelWavePathBlueprintNode *aPrevNode = (LevelWavePathBlueprintNode *)mPath.mNodeList.mData[i - 1];
            LevelWavePathBlueprintNode *aNextNode = (LevelWavePathBlueprintNode *)mPath.mNodeList.mData[i + 1];
            
            float aDiffBackX = aPrevNode->mGameX - aNode->mGameX;
            float aDiffBackY = aPrevNode->mGameY - aNode->mGameY;
            
            float aDiffNextX = aNextNode->mGameX - aNode->mGameX;
            float aDiffNextY = aNextNode->mGameY - aNode->mGameY;
            
            float aLengthBack = aDiffBackX * aDiffBackX + aDiffBackY * aDiffBackY;
            float aLengthNext = aDiffNextX * aDiffNextX + aDiffNextY * aDiffNextY;
            
            if (aLengthBack > SQRT_EPSILON) {
                aLengthBack = sqrtf(aLengthBack);
                aDiffBackX /= aLengthBack;
                aDiffBackY /= aLengthBack;
                
            } else {
                aDiffBackX = 0.0f;
                aDiffBackY = -1.0f;
            }
            
            if (aLengthNext > SQRT_EPSILON) {
                aLengthNext = sqrtf(aLengthNext);
                aDiffNextX /= aLengthNext;
                aDiffNextY /= aLengthNext;
                
            } else {
                aDiffNextX = 0.0f;
                aDiffNextY = -1.0f;
            }
            
            
            pWave->mPath.AddMove(aNode->mGameX + aDiffBackX * aChamferSize,
                           aNode->mGameY + aDiffBackY * aChamferSize);
            pWave->mPath.AddMove(aNode->mGameX + aDiffNextX * aChamferSize,
                           aNode->mGameY + aDiffNextY * aChamferSize);
        } else {
            pWave->mPath.AddMove(aNode->mGameX, aNode->mGameY, aNode->mWaitTimer);
        }
    }
}



FJSONNode *LevelWaveBlueprint::Save() {
    FJSONNode *aExport = new FJSONNode();
    aExport->AddDictionaryBool("blueprint", true);
    aExport->AddDictionaryBool("smooth", mPath.mSmooth);
    aExport->AddDictionaryInt("speed_class", mPath.mSpeedClass);
    aExport->AddDictionary("path", mPath.Save());
    return aExport;
}

void LevelWaveBlueprint::Load(FJSONNode *pNode) {
    Clear();
    if (pNode == NULL) { return; }
    mPath.mSmooth = pNode->GetBool("smooth", mPath.mSmooth);
    mPath.mSpeedClass = pNode->GetInt("speed_class", mPath.mSpeedClass);
    FJSONNode *aPathNode = pNode->GetArray("path");
    mPath.Load(aPathNode);
}
