//
//  FreeLife.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 9/20/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "FreeLife.hpp"
#include "Game.hpp"
#include "GFXApp.hpp"

FreeLife::FreeLife() {
    
    mGameObjectType = GAME_OBJECT_TYPE_FREE_LIFE;
    
    mSpinSpeed = 0.0f;
    mTransform3D.mSpin = 0.0f;
    
    mModel = &gWadModels.mExtraLife;
    mSprite = &gWadModels.mExtraLifeMap;
    mUniform = &(gGame->mRenderer->mUniformPhongBalloon);
    
    BuildEdgePointListBase();
}

FreeLife::~FreeLife() {
    
}

void FreeLife::Update() {
    Balloon::Update();
    BuildEdgePointList();
}

void FreeLife::Draw() {
    
    Balloon::Draw();
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    Graphics::SetColor(1.0f, 0.0f, 0.0f, 0.85f);
     
    Graphics::DrawPoint(mTransform.mX, mTransform.mY, 10.0f);
    
    Graphics::SetColor(1.0f, 0.0f, 0.25f, 1.0f);
    mEdgePointList2D.DrawEdges(2.0f);
}

bool FreeLife::WillCollide(float pStartX, float pStartY, float pEndX, float pEndY) {
    float aMidX = (pStartX + pEndX) * 0.5f;
    float aMidY = (pStartY + pEndY) * 0.5f;
    if (mEdgePointList2D.ContainsPoint(pStartX, pStartY)) { return true; }
    if (mEdgePointList2D.ContainsPoint(aMidX, aMidY)) { return true; }
    if (mEdgePointList2D.ContainsPoint(pEndX, pEndY)) { return true; }
    return false;
}

void FreeLife::BuildEdgePointListBase() {
    mEdgePointList3DBase.RemoveAll();
    
    
    float aTopY = -1.65f;
    float aBottomY = 2.15f;
    
    
    float aRightX = 2.0f;
    float aRightCenterX = aRightX / 2.0f;
    float aTopArcVerticalCompressionFactor = 0.8f;
    
    float aX = 0.0f;
    float aY = 0.0f;
    
    int aArcPointCount = 12;
    for (int i=0;i<aArcPointCount;i++) {
        float aPercent = ((float)i) / ((float)(aArcPointCount - 1));
        float aRotation = 270.0f - 90.0f * aPercent;
        float aDirX = Sin(aRotation);
        float aDirY = -Cos(aRotation);
        aX = aRightCenterX + aDirX * aRightCenterX;
        aY = aTopY + aDirY * aRightCenterX * aTopArcVerticalCompressionFactor;
        mEdgePointList3DBase.Add(aX, aY);
    }
    
    int aSidePointCount = 6;
    
    for (int i=0;i<aSidePointCount;i++) {
        float aPercent = ((float)i) / ((float)(aSidePointCount));
        
        
    }
    
    //aBottomY
    
    
    
}

void FreeLife::BuildEdgePointList() {
    
    gGame->Convert2DTransformTo3D(&mTransform, &mTransform3D);
    
    mEdgePointList3D.RemoveAll();
    for (int i=0;i<mEdgePointList3DBase.mCount;i++) {
        mEdgePointList3D.Add(mEdgePointList3DBase.mX[i] + mTransform3D.mX, mEdgePointList3DBase.mY[i] + mTransform3D.mY);
    }
    
    mEdgePointList2D.RemoveAll();
    
    float aX = 0.0f;
    float aY = 0.0f;
    for (int i=0;i<mEdgePointList3D.mCount;i++) {
        
        aX = mEdgePointList3D.mX[i];
        aY = mEdgePointList3D.mY[i];
        
        aX = gGame->Convert3DXTo2D(aX);
        aY = gGame->Convert3DYTo2D(aY);
        
        mEdgePointList2D.Add(aX, aY);
    }
}
