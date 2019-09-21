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
    
    /*
    Graphics::PipelineStateSetShape2DAlphaBlending();
    Graphics::SetColor(1.0f, 0.0f, 0.0f, 0.85f);
     
    Graphics::DrawPoint(mTransform.mX, mTransform.mY, 10.0f);
    
    Graphics::SetColor(1.0f, 0.0f, 0.25f, 1.0f);
    mEdgePointList2D.DrawEdges(2.0f);
    */
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
    
    
    float aTopY = -1.80f;
    float aBottomY = 2.15f;
    
    
    float aRightX = 2.2f;
    float aRightCenterX = aRightX / 2.0f;
    float aTopArcVerticalCompressionFactor = 0.6f;
    
    float aX = 0.0f;
    float aY = 0.0f;
    
    float aKnotX = 0.0f;
    float aKnotY = aTopY;
    
    int aArcPointCount = 8;
    
    float aLeftStartX1 = -aRightCenterX - aRightCenterX;
    float aLeftStartY1 = aTopY + 0.65f;
    
    float aLeftStartX2 = -aRightCenterX - aRightCenterX;
    float aLeftStartY2 = aTopY;
    
    float aRightStartX1 = aRightCenterX + aRightCenterX;
    float aRightStartY1 = aTopY;
    
    float aRightStartX2 = aRightCenterX + aRightCenterX;
    float aRightStartY2 = aTopY + 0.65f;
    
    
    
    
    mEdgePointList3DBase.Add(aLeftStartX1, aLeftStartY1 );
    mEdgePointList3DBase.Add(aLeftStartX2, aLeftStartY2 );
    
    
    
    for (int i=(aArcPointCount-2);i>=1;i--) {
        float aPercent = ((float)i) / ((float)(aArcPointCount - 1));
        float aRotation = -90.0f + 180.0f * aPercent;
        float aDirX = Sin(aRotation);
        float aDirY = -Cos(aRotation);
        aX = -aRightCenterX - aDirX * aRightCenterX;
        aY = aTopY + aDirY * aRightCenterX * aTopArcVerticalCompressionFactor;
        
        if (aPercent > 0.5f) {
            aY += (aPercent - 0.5f) * 0.65f;
            
        }
        
        mEdgePointList3DBase.Add(aX, aY);
    }
    
    mEdgePointList3DBase.Add(aKnotX, aKnotY);
    
    for (int i=1;i<(aArcPointCount - 1);i++) {
        float aPercent = ((float)i) / ((float)(aArcPointCount - 1));
        float aRotation = -90.0f + 180.0f * aPercent;
        float aDirX = Sin(aRotation);
        float aDirY = -Cos(aRotation);
        aX = aRightCenterX + aDirX * aRightCenterX;
        aY = aTopY + aDirY * aRightCenterX * aTopArcVerticalCompressionFactor;
        
        if (aPercent > 0.5f) {
            aY += (aPercent - 0.5f) * 0.65f;
            
        }
        
        mEdgePointList3DBase.Add(aX, aY);
    }
    
    mEdgePointList3DBase.Add(aRightStartX1, aRightStartY1);
    mEdgePointList3DBase.Add(aRightStartX2, aRightStartY2);
    
    int aSidePointCount = 4;
    for (int i=1;i<(aSidePointCount - 1);i++) {
        float aPercent = ((float)i) / ((float)(aSidePointCount));
        float aPercentX = (1.0f - aPercent);
        aPercentX = sinf(aPercentX * PI_2);
        aPercentX = (1.0f - aPercentX);
        aX = aRightStartX2 + (0.0f - aRightStartX2) * aPercentX;
        aY = aRightStartY2 + (aBottomY - aRightStartY2) * aPercent;
        mEdgePointList3DBase.Add(aX, aY);
    }
    
    mEdgePointList3DBase.Add(0.0f, aBottomY);
    
    for (int i=(aSidePointCount - 2);i>=1;i--) {
        float aPercent = ((float)i) / ((float)(aSidePointCount));
        float aPercentX = (1.0f - aPercent);
        aPercentX = sinf(aPercentX * PI_2);
        aPercentX = (1.0f - aPercentX);
        aX = aLeftStartX1 - (aLeftStartX1) * aPercentX;
        aY = aLeftStartY1 + (aBottomY - aLeftStartY1) * aPercent;
        mEdgePointList3DBase.Add(aX, aY);
    }
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
