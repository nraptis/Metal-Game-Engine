//
//  LevelFormationTracerTracerNode.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/1/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelFormationTracerNode.hpp"
#include "LevelFormationTracer.hpp"
#include "LevelPath.hpp"
#include "LevelWave.hpp"
#include "GameLevelController.hpp"
#include "Game.hpp"
#include "Balloon.hpp"

LevelFormationTracerNode::LevelFormationTracerNode(LevelFormationTracer *pTracer) {
    
    mTracer = pTracer;
    
    mBaseX = 0.0f;
    mBaseY = 0.0f;
    
    mKillTimer = 8;
}

LevelFormationTracerNode::~LevelFormationTracerNode() {
    
}

void LevelFormationTracerNode::Update() {
    
}

void LevelFormationTracerNode::Draw() {
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    Graphics::SetColor(1.0f, 0.85f, 0.25f, 0.85f);
    Graphics::DrawPoint(mX, mY, 6.0f);
    
    Graphics::SetColor();
}

void LevelFormationTracerNode::SetUp() {
    if (gGame != NULL) {
        float aLeft = gGame->mGameAreaLeft;
        float aRight = gGame->mGameAreaRight;
        float aTop = gGame->mGameAreaTop;
        float aBottom = gGame->mGameAreaBottom;
        
        float aWidth = aRight - aLeft;
        float aHeight = aBottom - aTop;
        
        mX = (mBaseX / 100.0f) * aWidth;
        mY = (mBaseY / 100.0f) * aHeight;
    }
}

LevelFormationTracerNode *LevelFormationTracerNode::Clone(LevelFormationTracer *pTracer) {
    
    LevelFormationTracerNode *aClone = new LevelFormationTracerNode(pTracer);
    
    aClone->mBaseX = mBaseX;
    aClone->mBaseY = mBaseY;
    
    return aClone;
}

