//
//  LevelWaveSpawnFormationTracerTracer.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/31/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelWaveSpawnFormationTracer.hpp"
#include "LevelWaveSpawnFormationNode.hpp"
#include "os_core_graphics.h"
#include "FPolyPath.h"
#include "LevelWavePath.hpp"
#include "core_includes.h"

static FPointList cDumpList;
static FPolyPath cPolyPath;
static FPointList cSegmentList;


LevelWaveSpawnFormationTracer::LevelWaveSpawnFormationTracer(LevelWaveSpawnFormation *pFormation) {
    
    SetSpeedClass(WAVE_SPEED_MEDIUM);
    
    mFormation = pFormation;
    mCount = 5;
    mPathIndex = 0;
    
    
    mKillTimer = 8;
}


LevelWaveSpawnFormationTracer::~LevelWaveSpawnFormationTracer() {
    
    FreeList(LevelWaveSpawnFormationTracerNode, mTracerNodeList);
    FreeList(LevelWaveSpawnFormationTracerNode, mTracerNodeKillList);
    
    FreeList(LevelWaveSpawnFormationNode, mSpawnNodeList);
    FreeList(LevelWaveSpawnFormationNode, mSpawnNodeKillList);
    
}

void LevelWaveSpawnFormationTracer::Reset() {
    for (int i=0;i<mTracerNodeList.mCount;i++) {
        LevelWaveSpawnFormationTracerNode *aNode = ((LevelWaveSpawnFormationTracerNode *)mTracerNodeList.mData[i]);
        mTracerNodeKillList.Add(aNode);
    }
    mTracerNodeList.RemoveAll();
    
    
    
    for (int i=0;i<mSpawnNodeList.mCount;i++) {
        LevelWaveSpawnFormationNode *aNode = ((LevelWaveSpawnFormationNode *)mSpawnNodeList.mData[i]);
        aNode->Reset();
        mSpawnNodeKillList.Add(aNode);
    }
    mSpawnNodeList.RemoveAll();
    
    mPath.RemoveAll();
    mDist.RemoveAll();
    
}

void LevelWaveSpawnFormationTracer::Spawn() {
    
    //In-case we have pre-spawned... Should not have..!
    for (int i=0;i<mSpawnNodeList.mCount;i++) {
        LevelWaveSpawnFormationNode *aNode = ((LevelWaveSpawnFormationNode *)mSpawnNodeList.mData[i]);
        aNode->Reset();
        mSpawnNodeKillList.Add(aNode);
    }
    mSpawnNodeList.RemoveAll();
    
    
    EnumList(LevelWaveSpawnFormationTracerNode, aNode, mTracerNodeList) {
        aNode->SetUp();
    }
    
    cDumpList.Reset();
    
    if (true) {
        for (int i=0;i<mTracerNodeList.mCount;i++) {
            LevelWaveSpawnFormationTracerNode *aNode = ((LevelWaveSpawnFormationTracerNode *)mTracerNodeList.mData[i]);
            cDumpList.Add(aNode->mX, aNode->mY);
        }
    } else {
        //TODO: Other types of tracers...
    }
    
    if (cDumpList.mCount <= 1) {
        printf("Fatal Error, Point Count[%d]\n", cDumpList.mCount);
        return;
    }
    
    cPolyPath.mClosed = true;
    cPolyPath.RemoveAll();
    cPolyPath.Add(&cDumpList);
    cPolyPath.Generate();
    
    //IMPORTANT: Tracers always loop and thus "closed" !!!
    
    float aSpeed = mSpeed;
    if (aSpeed > 100.0f) { aSpeed = 100.0f; }
    if (aSpeed < 1.0f) { aSpeed = 1.0f; }

    cSegmentList.RemoveAll();
    cSegmentList.Add(cDumpList.mX[0], cDumpList.mY[0]);
    mDist.Add(0.0f);
    
    float aCurrentDist = 0.00f;
    while (aCurrentDist < cPolyPath.mLength) {
        aCurrentDist += aSpeed;
        float aInterpX = 0.0f; float aInterpY = 0.0f;
        cPolyPath.GetWithDist(aCurrentDist, aInterpX, aInterpY);
        cSegmentList.Add(aInterpX, aInterpY);
        mDist.Add(aCurrentDist);
    }
    
    //IMPORTANT: Loop back to start...
    float aLastX = cDumpList.mX[0];
    float aLastY = cDumpList.mY[0];
    float aSegmentLastX = 0.0f;
    float aSegmentLastY = 0.0f;
    if (cSegmentList.mCount > 0) {
        aSegmentLastX = cSegmentList.mX[cSegmentList.mCount - 1];
        aSegmentLastY = cSegmentList.mY[cSegmentList.mCount - 1];
    }
    
    //If we land too close to the start, remove the point.
    float aDistanceToEnd = DistanceSquared(aLastX, aLastY, aSegmentLastX, aSegmentLastY);
    if (aDistanceToEnd <= ((aSpeed * aSpeed) * 0.5f)) {
        cSegmentList.mCount -= 1;
        mDist.mCount -= 1;
    }
    
    
    if (cSegmentList.mCount <= 2) { return; }
    
    mPath.Add(&cSegmentList);
    
    
    ///////////////////////////////////////////////
    ///////////////////////////////////////////////
    ///////////////////////////////////////////////
    
    int aPathCount = mPath.mCount;
    for (int i=0;i<mCount;i++) {
        LevelWaveSpawnFormationNode *aFormationNode = new LevelWaveSpawnFormationNode(mFormation);
        aFormationNode->mTracer = this;
        float aPercent = ((float)i) / ((float)mCount);
        aFormationNode->mPathIndexOffset = (int)round(aPercent * ((float)aPathCount));
        
        aFormationNode->Spawn();
        mSpawnNodeList.Add(aFormationNode);
    }
}

void LevelWaveSpawnFormationTracer::Update() {
    
    
    if (mPath.mCount > 2) {
        mPathIndex += 1;
        if (mPathIndex >= (mPath.mCount - 1)) {
            mPathIndex = 0;
        }
    }
    
    EnumList(LevelWaveSpawnFormationTracerNode, aNode, mTracerNodeList) {
        aNode->Update();
    }
    
    EnumList(LevelWaveSpawnFormationNode, aNode, mSpawnNodeList) {
        aNode->Update();
    }
        
    
    EnumList(LevelWaveSpawnFormationTracerNode, aNode, mTracerNodeKillList) {
        aNode->mKillTimer--;
        if (aNode->mKillTimer <= 0) { mTracerNodeDeleteList.Add(aNode); }
    }
    EnumList(LevelWaveSpawnFormationTracerNode, aNode, mTracerNodeDeleteList) {
        mTracerNodeKillList.Remove(aNode);
        delete aNode;
    }
    mTracerNodeDeleteList.RemoveAll();
}

void LevelWaveSpawnFormationTracer::SetSpeedClass(int pSpeedClass) {
    if (pSpeedClass == WAVE_SPEED_EXTRA_SLOW) {
        mSpeed = 0.45f;
    } else if (pSpeedClass == WAVE_SPEED_SLOW) {
        mSpeed = 0.65f;
    } else if (pSpeedClass == WAVE_SPEED_MEDIUM_SLOW) {
        mSpeed = 1.25f;
    } else if (pSpeedClass == WAVE_SPEED_MEDIUM_FAST) {
        mSpeed = 3.75f;
    } else if (pSpeedClass == WAVE_SPEED_FAST) {
        mSpeed = 6.5f;
    } else if (pSpeedClass == WAVE_SPEED_EXTRA_FAST) {
        mSpeed = 9.0f;
    } else if (pSpeedClass == WAVE_SPEED_INSANE) {
        mSpeed = 14.0f;
    } else { //"Default /
        mSpeed = 2.5f;
    }
}

LevelWaveSpawnFormationTracer *LevelWaveSpawnFormationTracer::Clone(LevelWaveSpawnFormation *pFormation) {
    
    LevelWaveSpawnFormationTracer *aClone = new LevelWaveSpawnFormationTracer(pFormation);
    
    aClone->mSpeed = mSpeed;
    aClone->mCount = mCount;
    
    EnumList(LevelWaveSpawnFormationTracerNode, aNode, mTracerNodeList) {
        aClone->mTracerNodeList.Add(aNode->Clone(aClone));
    }
    
    return aClone;
}


void LevelWaveSpawnFormationTracer::GetExtremeties(float &pTop, float &pRight, float &pLeft, float &pBottom) {
    
    //TODO: If we are a special type of tracer, account for the special type boundary...
    
    EnumList(LevelWaveSpawnFormationTracerNode, aNode, mTracerNodeList) {
        if (aNode->mX < pLeft) { pLeft = aNode->mX; }
        if (aNode->mX > pRight) { pRight = aNode->mX; }
        if (aNode->mY < pTop) { pTop = aNode->mY; }
        if (aNode->mY > pBottom) { pBottom = aNode->mY; }
    }
    
    
}


void LevelWaveSpawnFormationTracer::EditorKillAllObjects() {
    
    EnumList(LevelWaveSpawnFormationNode, aNode, mSpawnNodeList) {
        if (aNode->mObject != NULL) {
            aNode->mObject->Kill();
            aNode->mObject = NULL;
        }
    }
}
