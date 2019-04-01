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
    
}

LevelWaveSpawnFormation::~LevelWaveSpawnFormation() {
    FreeList(LevelWaveSpawnFormationNode, mNodeList);
    FreeList(LevelWaveSpawnFormationNode, mNodeKillList);
    
    FreeList(LevelWaveSpawnFormationTracer, mTracerList);
    FreeList(LevelWaveSpawnFormationTracer, mTracerKillList);
}


void LevelWaveSpawnFormation::Reset() {
    
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelWaveSpawnFormationNode *aNode = ((LevelWaveSpawnFormationNode *)mNodeList.mData[i]);
        mNodeKillList.Add(aNode);
    }
    mNodeList.RemoveAll();
    
    
    
    for (int i=0;i<mTracerList.mCount;i++) {
        LevelWaveSpawnFormationTracer *aNode = ((LevelWaveSpawnFormationTracer *)mTracerList.mData[i]);
        mTracerKillList.Add(aNode);
    }
    mNodeList.RemoveAll();
}

void LevelWaveSpawnFormation::Update() {
    
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

