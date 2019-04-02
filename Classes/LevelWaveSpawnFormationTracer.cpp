//
//  LevelWaveSpawnFormationTracerTracer.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/31/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelWaveSpawnFormationTracer.hpp"
#include "os_core_graphics.h"
#include "FPolyPath.h"
#include "LevelWavePath.hpp"
#include "core_includes.h"

static FPointList cDumpList;
static FPolyPath cPolyPath;
static FPointList cSegmentList;


LevelWaveSpawnFormationTracer::LevelWaveSpawnFormationTracer() {
    
    SetSpeedClass(WAVE_SPEED_MEDIUM);
    
    //TODO: Remove
    mSpeed = 42.0f;
    
    mKillTimer = 8;
    
}

LevelWaveSpawnFormationTracer::~LevelWaveSpawnFormationTracer() {
    printf("LevelWaveSpawnFormationTracer::~LevelWaveSpawnFormationTracer()\n");
    FreeList(LevelWaveSpawnFormationTracerNode, mNodeList);
    FreeList(LevelWaveSpawnFormationTracerNode, mNodeKillList);
}

void LevelWaveSpawnFormationTracer::Reset() {
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelWaveSpawnFormationTracerNode *aNode = ((LevelWaveSpawnFormationTracerNode *)mNodeList.mData[i]);
        mNodeKillList.Add(aNode);
    }
    mNodeList.RemoveAll();
    
    mPath.RemoveAll();
    mDist.RemoveAll();
    
}

void LevelWaveSpawnFormationTracer::Spawn() {
    
    EnumList(LevelWaveSpawnFormationTracerNode, aNode, mNodeList) {
        aNode->SetUp();
    }
    
    cDumpList.Reset();
    
    if (true) {
        for (int i=0;i<mNodeList.mCount;i++) {
            LevelWaveSpawnFormationTracerNode *aNode = ((LevelWaveSpawnFormationTracerNode *)mNodeList.mData[i]);
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
        //cSegmentList.Add(aLastX, aLastY);
        //mDist.Add(aCurrentDist + cPolyPath.mLength);
    } else {
        cSegmentList.mX[cSegmentList.mCount - 1] = aLastX;
        cSegmentList.mY[cSegmentList.mCount - 1] = aLastY;
        mDist.mData[mDist.mCount - 1] = cPolyPath.mLength;
    }
    
    mPath.Add(&cSegmentList);
}

void LevelWaveSpawnFormationTracer::Update() {
    
    EnumList(LevelWaveSpawnFormationTracerNode, aNode, mNodeList) {
        aNode->Update();
    }
    
    EnumList(LevelWaveSpawnFormationTracerNode, aNode, mNodeKillList) {
        aNode->mKillTimer--;
        if (aNode->mKillTimer <= 0) { mNodeDeleteList.Add(aNode); }
    }
    EnumList(LevelWaveSpawnFormationTracerNode, aNode, mNodeDeleteList) {
        mNodeKillList.Remove(aNode);
        delete aNode;
    }
    mNodeDeleteList.RemoveAll();
}

void LevelWaveSpawnFormationTracer::SetSpeedClass(int pSpeedClass) {
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

