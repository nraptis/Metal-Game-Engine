//
//  LevelWaveFormation.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/15/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelWaveSpawnFormation.hpp"
#include "LevelWaveSpawnFormationTracer.hpp"

LevelWaveSpawnFormation::LevelWaveSpawnFormation() {
    
    mRotation = 0.0f;
}

LevelWaveSpawnFormation::~LevelWaveSpawnFormation() {
    
    printf("LevelWaveSpawnFormation::~LevelWaveSpawnFormation()\n");
    
    FreeList(LevelWaveSpawnFormationNode, mNodeList);
    FreeList(LevelWaveSpawnFormationNode, mNodeKillList);
    
    FreeList(LevelWaveSpawnFormationTracer, mTracerList);
    FreeList(LevelWaveSpawnFormationTracer, mTracerKillList);
}


void LevelWaveSpawnFormation::Reset() {
    printf("LevelWaveSpawnFormation::Reset()\n");
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelWaveSpawnFormationNode *aNode = ((LevelWaveSpawnFormationNode *)mNodeList.mData[i]);
        aNode->Reset();
        mNodeKillList.Add(aNode);
    }
    mNodeList.RemoveAll();
    
    for (int i=0;i<mTracerList.mCount;i++) {
        LevelWaveSpawnFormationTracer *aTracer = ((LevelWaveSpawnFormationTracer *)mTracerList.mData[i]);
        aTracer->Reset();
        mTracerKillList.Add(aTracer);
    }
    mTracerList.RemoveAll();
}

void LevelWaveSpawnFormation::Spawn() {
    EnumList(LevelWaveSpawnFormationNode, aNode, mNodeList) {
        aNode->Spawn();
    }
    EnumList(LevelWaveSpawnFormationTracer, aTracer, mTracerList) {
        aTracer->Spawn();
    }
}

void LevelWaveSpawnFormation::Update() {
    
    EnumList(LevelWaveSpawnFormationNode, aNode, mNodeList) {
        aNode->Update();
    }
    
    EnumList(LevelWaveSpawnFormationTracer, aTracer, mTracerList) {
        aTracer->Update();
    }
    
    EnumList(LevelWaveSpawnFormationNode, aNode, mNodeKillList) {
        aNode->mKillTimer--;
        if (aNode->mKillTimer <= 0) { mNodeDeleteList.Add(aNode); }
    }
    EnumList(LevelWaveSpawnFormationNode, aNode, mNodeDeleteList) {
        mNodeKillList.Remove(aNode);
        delete aNode;
    }
    mNodeDeleteList.RemoveAll();
    
    
    EnumList(LevelWaveSpawnFormationTracer, aTracer, mTracerKillList) {
        aTracer->mKillTimer--;
        if (aTracer->mKillTimer <= 0) { mTracerDeleteList.Add(aTracer); }
    }
    EnumList(LevelWaveSpawnFormationTracer, aTracer, mTracerDeleteList) {
        mTracerKillList.Remove(aTracer);
        delete aTracer;
    }
    mTracerDeleteList.RemoveAll();
}

void LevelWaveSpawnFormation::Draw() {
    
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    Graphics::SetColor(1.0f, 0.65f, 1.0f, 0.75f);
    EnumList(LevelWaveSpawnFormationTracer, aTracer, mTracerList) {
        
        for (int i=0;i<aTracer->mPath.mCount;i++) {
            
            float aX = aTracer->mPath.mX[i];
            float aY = aTracer->mPath.mY[i];
            
            if (mRotation != 0.0f) {
                FVec2 aPoint;
                aPoint.mX = aX; aPoint.mY = aY;
                aPoint = PivotPoint(aPoint, mRotation);
                aX = aPoint.mX; aY = aPoint.mY;
            }
            
            aX += mX;
            aY += mY;
            
            Graphics::DrawPoint(aX + 2.0f, aY + 2.0f, 4.0f);
            
            
        }
        
        
        
    }
    
    
}

