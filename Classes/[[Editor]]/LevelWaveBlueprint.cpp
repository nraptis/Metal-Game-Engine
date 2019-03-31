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
    
    for (int i=0;i<MAX_SPAWN_COUNT;i++) {
        mSpawn[i].Reset();
    }
    
    mSelectedSpawnIndex = 0;
    
    mSpawnCount = 1;
    mSpawnSpacing = 92;
    
    mCreationType = WAVE_CREATION_TYPE_PREV_WAVE_START;
    mCreationDelay = 200;
    
    mKillTimer = 100;
}

LevelWaveBlueprint::~LevelWaveBlueprint() {
    
}

void LevelWaveBlueprint::Clear() {
    mPath.Clear();
    for (int i=0;i<MAX_SPAWN_COUNT;i++) {
        mSpawn[i].Reset();
    }
    mSpawnCount = 1;
}

//mPath
void LevelWaveBlueprint::Update() {
    mPath.Update();
    
    if (mSpawnCount < 1) mSpawnCount = 1;
    if (mSpawnCount > MAX_SPAWN_COUNT) mSpawnCount = MAX_SPAWN_COUNT;
    
    if (mSelectedSpawnIndex < 0) { mSelectedSpawnIndex = 0; }
    if (mSelectedSpawnIndex >= mSpawnCount) { mSelectedSpawnIndex = mSpawnCount - 1; }
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
    if (gEditor) {
        Build(&gEditor->mEditorWave);
    }
}

void LevelWaveBlueprint::Build(LevelWave *pWave) {
    
    if (pWave == NULL) { return; }
    
    pWave->Reset();
    
    pWave->mPath.mSmooth = mPath.mSmooth;
    pWave->mPath.SetSpeedClass(mPath.mSpeedClass);
    
    pWave->mCreationType = mCreationType;
    pWave->mCreationDelay = mCreationDelay;
    
    
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
    
    
    if (mSpawnCount < 1) mSpawnCount = 1;
    if (mSpawnCount > MAX_SPAWN_COUNT) mSpawnCount = MAX_SPAWN_COUNT;
    
    pWave->mSpawnSeparationDistance = (float)mSpawnSpacing;
    for (int i=0;i<mSpawnCount;i++) {
        LevelWaveSpawn *aSpawn = new LevelWaveSpawn(pWave, &pWave->mPath);
        
        aSpawn->mOffsetSpawnDistance = mSpawn[i].mSpawnSpacingOffset;
        
        pWave->mSpawnList.Add(aSpawn);
    }
}



FJSONNode *LevelWaveBlueprint::Save() {
    FJSONNode *aExport = new FJSONNode();
    aExport->AddDictionaryBool("blueprint", true);
    aExport->AddDictionaryBool("smooth", mPath.mSmooth);
    aExport->AddDictionaryInt("speed_class", mPath.mSpeedClass);
    aExport->AddDictionaryInt("spawn_spacing", mSpawnSpacing);
    aExport->AddDictionaryInt("creation_type", mCreationType);
    aExport->AddDictionaryInt("creation_delay", mCreationDelay);
    
    
    aExport->AddDictionary("path", mPath.Save());
    
    //
    //
    FJSONNode *aSpawnList = new FJSONNode();
    aSpawnList->mNodeType = JSON_NODE_TYPE_ARRAY;
    for (int i=0;i<mSpawnCount;i++) {
        aSpawnList->AddArray(mSpawn[i].Save());
    }
    aExport->AddDictionary("spawn", aSpawnList);
    
    
    
    //int                                         mSpawnCount;
    //int                                         ;
    
    return aExport;
}

void LevelWaveBlueprint::Load(FJSONNode *pNode) {
    Clear();
    if (pNode == NULL) { return; }
    mPath.mSmooth = pNode->GetBool("smooth", mPath.mSmooth);
    mPath.mSpeedClass = pNode->GetInt("speed_class", mPath.mSpeedClass);
    mSpawnSpacing = pNode->GetInt("spawn_spacing", mSpawnSpacing);
    mCreationType = pNode->GetInt("creation_type", mCreationType);
    mCreationDelay = pNode->GetInt("creation_delay", mCreationDelay);
    
    mSpawnCount = 0;
    FJSONNode *aSpawnList = pNode->GetArray("spawn");
    if (aSpawnList != NULL) {
        EnumJSONArray(aSpawnList, aSpawnNode) {
            mSpawn[mSpawnCount].Load(aSpawnNode);
            ++mSpawnCount;
        }
    }
    if (mSpawnCount <= 0) { mSpawnCount = 1; }
    if (mSpawnCount > MAX_SPAWN_COUNT) { mSpawnCount = MAX_SPAWN_COUNT; }
    
    FJSONNode *aPathNode = pNode->GetArray("path");
    mPath.Load(aPathNode);
}
