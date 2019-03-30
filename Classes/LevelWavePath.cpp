//
//  LevelWavePath.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/15/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelWavePath.hpp"
#include "os_core_graphics.h"
#include "FSpline.h"
#include "FPolyPath.h"
#include "core_includes.h"

static FPointList cPointList;
static FPointList cDumpList;
static FPolyPath cPolyPath;
static FPointList cSegmentList;

LevelWavePathNode::LevelWavePathNode() {
    mX = 0.0f;
    mY = 0.0f;
    mType = PATH_NODE_INVALID;
    mWaitTimer = 0;
    mKillTimer = 8;
}

LevelWavePathNode::~LevelWavePathNode() {
    
}

LevelWavePath::LevelWavePath() {
    mSpeed = 3.0f;
    mDidFinalize = false;
    mDidFailFinalize = false;
    
    mSmooth = true;
    mTempDist = 0.0f;
    
    mTestPer = 0.0f;
    mDemoIndex = 0;
}

LevelWavePath::~LevelWavePath() {
    FreeList(LevelWavePathNode, mNodeList);
    FreeList(LevelWavePathNode, mKillList);
}


void LevelWavePath::Update() {
    EnumList(LevelWavePathNode, aNode, mKillList) {
        aNode->mKillTimer--;
        if (aNode->mKillTimer <= 0) { mDeleteList.Add(aNode); }
    }
    EnumList(LevelWavePathNode, aNode, mDeleteList) {
        mKillList.Remove(aNode);
        delete aNode;
    }
    mDeleteList.RemoveAll();
}

void LevelWavePath::Add(int pType, float pX, float pY, int pWait) {
    //
    //
    //
    LevelWavePathNode *aNode = new LevelWavePathNode();
    aNode->mX = pX;
    aNode->mY = pY;
    aNode->mType = pType;
    aNode->mWaitTimer = pWait;
    mNodeList.Add(aNode);
    mDidFailFinalize = false;
    mDidFinalize = false;
}

void LevelWavePath::AddMove(float pX, float pY, int pWait) {
    Add(PATH_NODE_NORMAL, pX, pY, pWait);
}

void LevelWavePath::Reset() {
    mDidFinalize = false;
    mDidFailFinalize = false;
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelWavePathNode *aNode = ((LevelWavePathNode *)mNodeList.mData[i]);
        mKillList.Add(aNode);
    }
    mNodeList.RemoveAll();
    mPath.RemoveAll();
    mDist.RemoveAll();
}

void LevelWavePath::Finalize() {
    mPath.RemoveAll();
    mDist.RemoveAll();
    mDidFailFinalize = false;
    
    if (mSpeed < 1.0f) {
        mSpeed = 1.0f;
    }
    
    if (mNodeList.mCount < 2) {
        mDidFailFinalize = true;
        return;
    }
    
    LevelWavePathNode *aFirstNode = ((LevelWavePathNode *)mNodeList.First());
    float aStartX = aFirstNode->mX;
    float aStartY = aFirstNode->mY;
    
    mTempX = aStartX;
    mTempY = aStartY;
    mTempDist = 0.0f;
    
    int aIndex = 0;
    
    mDidFinalize = true;
    
    while (aIndex < mNodeList.mCount) {
        LevelWavePathNode *aNode = ((LevelWavePathNode *)mNodeList.mData[aIndex]);
        if (aIndex > 0) {
            if ((aNode->mWaitTimer > 0) || (aIndex == (mNodeList.mCount - 1))) {
                LevelWavePath::AddSegmentBacktrackingFrom(aIndex);
            }
        }
        
        if (aNode->mWaitTimer > 0) {
            for (int i=0;i<aNode->mWaitTimer && i < 80000;i++) {
                mPath.Add(mTempX, mTempY);
                mDist.Add(mTempDist);
            }
        }
        ++aIndex;
    }
}

void LevelWavePath::AddSegmentBacktrackingFrom(int pIndex) {
    
    int aStartIndex = pIndex - 1;
    while (aStartIndex > 0) {
        LevelWavePathNode *aNode = ((LevelWavePathNode *)mNodeList.mData[aStartIndex]);
        if (aNode->mWaitTimer > 0) {
            break;
        } else {
            --aStartIndex;
        }
    }
    
    LevelWavePathNode *aPrev = ((LevelWavePathNode *)mNodeList.mData[aStartIndex]);
    
    cPointList.Reset();
    
    cPointList.Add(aPrev->mX, aPrev->mY);
    
    mTempX = aPrev->mX;
    mTempY = aPrev->mY;
    
    float aTotalDist = 0.0f;
    for (int i=aStartIndex+1;i<=pIndex;i++) {
        LevelWavePathNode *aNode = ((LevelWavePathNode *)mNodeList.mData[i]);
        
        float aDiffX = aNode->mX - aPrev->mX;
        float aDiffY = aNode->mY - aPrev->mY;
        
        float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
        aTotalDist += aDist;
        
        if (aDist > 1.0f) {
            cPointList.Add(aNode->mX, aNode->mY);
        }
        
        aPrev = aNode;
    }
    
    if (aTotalDist <= 0) {
        Log("BAD PATH CHUNK [LEN = %f]\n", aTotalDist);
        return;
    }
    
    
    
    cDumpList.Reset();
    
    float aX = 0.0f;
    float aY = 0.0f;
    
    if (mSmooth == false || cPointList.mCount <= 2) {
        for (int i=0;i<cPointList.mCount;i++) {
            cDumpList.Add(cPointList.mX[i], cPointList.mY[i]);
        }
    } else {
        FSpline aSpline;
        for (int i=0;i<cPointList.mCount;i++) {
            aSpline.Add(cPointList.mX[i], cPointList.mY[i]);
        }
        
        for (float aPos=0.0f;aPos<=aSpline.Max();aPos += 0.05f) {
            aSpline.Get(aPos, aX, aY);
            cDumpList.Add(aX, aY);
        }
        cDumpList.Add(aSpline.GetX(aSpline.Max()), aSpline.GetY(aSpline.Max()));
    }
    
    
    
    if (cDumpList.mCount <= 1) {
        printf("Fatal Error, Point Count[%d]\n", cDumpList.mCount);
        return;
    }
    
    cPolyPath.Reset();
    cPolyPath.Add(&cDumpList);
    cPolyPath.Generate();
    
    bool aDecelerationEnabled = true;
    
    float aDecelerationCutoffDistance = 60.0f;
    float aDecelerationCutoff = cPolyPath.mLength - aDecelerationCutoffDistance;
    float aDeceleration = 0.0f;
    
    bool aAccelerationEnabled = true;
    float aAccelerationDistance = 60.0f;
    float aAccelerationSpeed = 0.0f;
    float aAcceleration = 0.0f;
    
    float aSpeed = mSpeed;
    if (aSpeed > 100.0f) { aSpeed = 100.0f; }
    if (aSpeed < 1.0f) { aSpeed = 1.0f; }
    
    
    if (cPolyPath.mLength < aDecelerationCutoffDistance) {//} || (pIndex >= mNodeList.mCount - 1)) {
        aDecelerationEnabled = false;
    } else {
        aDeceleration = (aSpeed * aSpeed) / (2.0f * aDecelerationCutoffDistance);
    }
    
    if (cPolyPath.mLength > aAccelerationDistance && aAccelerationEnabled == true) {
        aAcceleration = (aSpeed * aSpeed) / (2.0f * aAccelerationDistance);
    } else {
        aAccelerationEnabled = false;
    }
    
    cSegmentList.RemoveAll();
    cSegmentList.Add(cDumpList.mX[0], cDumpList.mY[0]);
    mDist.Add(mTempDist);
    
    float aCurrentDist = 0.00f;
    while (aSpeed > 0.05f && aCurrentDist < cPolyPath.mLength) {
        
        if (aDecelerationEnabled == true && aCurrentDist > aDecelerationCutoff) {
            aCurrentDist += aSpeed;
            aSpeed -= aDeceleration;
        } else if (aAccelerationEnabled == true && aCurrentDist < aAccelerationDistance) {
            aAccelerationSpeed += aAcceleration;
            if (aAccelerationSpeed > aSpeed) {
                aAccelerationSpeed = aSpeed;
            }
            aCurrentDist += aAccelerationSpeed;
        } else {
            aCurrentDist += aSpeed;
        }
        
        float aInterpX = 0.0f;
        float aInterpY = 0.0f;
        cPolyPath.GetWithDist(aCurrentDist, aInterpX, aInterpY);
        cSegmentList.Add(aInterpX, aInterpY);
        mDist.Add(mTempDist + aCurrentDist);
    }
    
    float aLastX = cDumpList.mX[cDumpList.mCount - 1];
    float aLastY = cDumpList.mY[cDumpList.mCount - 1];
    float aSegmentLastX = 0.0f;
    float aSegmentLastY = 0.0f;
    if (cSegmentList.mCount > 0) {
        aSegmentLastX = cSegmentList.mX[cSegmentList.mCount - 1];
        aSegmentLastY = cSegmentList.mY[cSegmentList.mCount - 1];
    }
    
    float aDistanceToEnd = DistanceSquared(aLastX, aLastY, aSegmentLastX, aSegmentLastY);
    
    if (aDistanceToEnd > 0.5f) {
        cSegmentList.Add(aLastX, aLastY);
        mDist.Add(aCurrentDist + cPolyPath.mLength);
    } else {
        cSegmentList.mX[cSegmentList.mCount - 1] = aLastX;
        cSegmentList.mY[cSegmentList.mCount - 1] = aLastY;
        mDist.mData[mDist.mCount - 1] = mTempDist + cPolyPath.mLength;
    }
    mTempX = aLastX;
    mTempY = aLastY;
    
    mTempDist += cPolyPath.mLength;
    
    mPath.Add(&cSegmentList);
    
    cSegmentList.Reset();
    cPolyPath.Reset();
}

void LevelWavePath::Draw() {
    
    mTestPer += 0.01f;
    if (mTestPer >= 1.0f) {
        mTestPer -= 1.0f;
    }
    if (mDidFinalize == false && mDidFailFinalize == false) {
        Finalize();
    }
    
    LevelWavePathNode *aPrev = NULL;
    LevelWavePathNode *aNode = NULL;
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    for (int i=0;i<mNodeList.mCount;i++) {
        aNode = ((LevelWavePathNode *)mNodeList.mData[i]);
        if (aPrev) {
            
            Graphics::SetColor(0.44f, 0.66f, 0.125f, 0.15f);
            Graphics::DrawLine(aPrev->mX, aPrev->mY, aNode->mX, aNode->mY, 2.5f);
            
            Graphics::SetColor(0.66f, 0.66f, 0.66f, 0.15f);
            Graphics::DrawLine(aPrev->mX, aPrev->mY, aNode->mX, aNode->mY, 1.5f);
        }
        
        aPrev = aNode;
    }
    
    for (int i=0;i<mNodeList.mCount;i++) {
        aNode = ((LevelWavePathNode *)mNodeList.mData[i]);
        
        if (aNode->mWaitTimer > 0) {
            Graphics::SetColor(0.125f, 0.25f, 0.88f, 0.5f);
            Graphics::OutlineRect(aNode->mX - 25.0f, aNode->mY - 25.0f, 50.0f, 50.0f, 3.0f);
        }
        
        if (aNode->mType == PATH_NODE_NORMAL) {
            Graphics::SetColor(0.125f, 0.88f, 0.125f, 0.6f);
            Graphics::OutlineRect(aNode->mX - 8.0f, aNode->mY - 8.0f, 16.0f, 16.0f, 3.0f);
        }
    }
    
    Graphics::SetColor(0.65f, 0.25f, 0.25f, 0.65f);
    mPath.DrawEdgesOpen();
    
    /*
    Graphics::SetColor(1.0f, 0.65f, 0.45f, 0.75f);
    if (mPath.mCount > 0) {
        for (int i=0;i<mPath.mCount;i++) {
            float aPercent = ((float)i) / ((float)(mPath.mCount - 1));
            Graphics::SetColor(aPercent, 0.25f, 0.25f, 0.75f);
            Graphics::DrawPoint(mPath.mX[i], mPath.mY[i], 2.0f);
        }
        
        mDemoIndex += 1;
        if (mDemoIndex >= mPath.mCount) { mDemoIndex = 0; }
        
        float aX = mPath.mX[mDemoIndex];
        float aY = mPath.mY[mDemoIndex];
        
        Graphics::SetColor(0.66f, 1.0f, 0.44f, 1.0f);
        Graphics::DrawPoint(aX, aY, 20.0f);
    }
    */
}



void LevelWavePath::SetSpeedClass(int pSpeedClass) {
    if (pSpeedClass == WAVE_SPEED_EXTRA_SLOW) {
        mSpeed = 1.5f;
    } else if (pSpeedClass == WAVE_SPEED_SLOW) {
        mSpeed = 2.25f;
    } else if (pSpeedClass == WAVE_SPEED_MEDIUM_SLOW) {
        mSpeed = 3.65f;
    } else if (pSpeedClass == WAVE_SPEED_MEDIUM_FAST) {
        mSpeed = 6.25f;
    } else if (pSpeedClass == WAVE_SPEED_FAST) {
        mSpeed = 9.0f;
    } else if (pSpeedClass == WAVE_SPEED_EXTRA_FAST) {
        mSpeed = 12.0f;
    } else if (pSpeedClass == WAVE_SPEED_INSANE) {
        mSpeed = 18.0f;
    } else { //"Default /
        mSpeed = 6.0f;
    }
}




