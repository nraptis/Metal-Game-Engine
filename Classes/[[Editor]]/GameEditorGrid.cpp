//
//  GameEditorGrid.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 5/5/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "GameEditorGrid.hpp"
#include "os_core_graphics.h"
#include "core_includes.h"


GameEditorGrid::GameEditorGrid() {
    
    mCenterX = 256.0f;
    mCenterY = 256.0f;
    
    mGridEnabled = true;
    mGridType = SNAP_GRID_TYPE_RECT;
    
    mGridRectWidth = 7;
    mGridRectHeight = 7;
    mGridRectSpacing = 44;
    
    mGridCircleRingSpacing = 40;
    mGridCircleRingCount = 8;
    mGridCircleRadialCount = 24;
    
    mGridStarInnerRadius = 72;
    mGridStarOuterRadius = 160;
    mGridStarLinePointCount = 3;
    mGridStarArmCount = 5;
    mGridStarStartRotation = 9;
    
    mGridNGON1Sides = 5;
    mGridNGON1RingSpacing = 52;
    mGridNGON1RingCount = 6;
    mGridNGON1PointSpacing = 40;
    mGridNGON1StartRotation = 0;
    
    mSaveGridTimer = 0;
    
    LoadGridState();
    BuildGrid();
    
}

GameEditorGrid::~GameEditorGrid() {
    
}

void GameEditorGrid::Update() {
    mSaveGridTimer += 1;
    if (mSaveGridTimer >= 200) {
        SaveGridState();
        mSaveGridTimer = 0;
    }
}

void GameEditorGrid::Draw() {
    Graphics::PipelineStateSetShape2DAlphaBlending();
    Graphics::SetColor(1.0f, 0.85f, 1.0f, 0.75f);
    Graphics::SetColor(1.0f, 0.5f, 0.75f, 0.65f);
    mGridList.OutlinePoints(4.0f, 2.0f);
    Graphics::SetColor();
}

void GameEditorGrid::GridSnap(float *pX, float *pY) {
    if (mGridEnabled) {
        float aBestDist = 60.0f * 60.0f;
        int aIndex = mGridList.GetClosestIndex(*pX, *pY, aBestDist);
        if (aIndex != -1) {
            *pX = mGridList.GetX(aIndex);
            *pY = mGridList.GetY(aIndex);
        }
    }
}

void GameEditorGrid::BuildGrid() {
    
    if (mGridType == SNAP_GRID_TYPE_RECT) { BuildRectGrid(); }
    if (mGridType == SNAP_GRID_TYPE_CIRCLE) { BuildCircleGrid(); }
    if (mGridType == SNAP_GRID_TYPE_STAR) { BuildStarGrid(); }
    if (mGridType == SNAP_GRID_TYPE_NGON1) { BuildNGON1Grid(); }
    if (mGridType == SNAP_GRID_TYPE_NGON2) { BuildNGON2Grid(); }
    
}

void GameEditorGrid::BuildRectGrid() {
    
    mGridList.RemoveAll();
    
    if (mGridRectWidth < 1) { mGridRectWidth = 1; }
    if (mGridRectHeight < 1) { mGridRectHeight = 1; }
    if (mGridRectSpacing < 0) { mGridRectSpacing = 0; }
    
    float aTotalWidth = mGridRectWidth * mGridRectSpacing;
    float aTotalHeight = mGridRectHeight * mGridRectSpacing;
    
    float aLeft = round(mCenterX - (aTotalWidth / 2.0f) + mGridRectSpacing / 2);
    float aTop = round(mCenterY - (aTotalHeight / 2.0f) + mGridRectSpacing / 2);
    
    for (int i=0;i<mGridRectWidth;i++) {
        
        float aX = aLeft + ((float)mGridRectSpacing) * ((float)i);
        
        for (int n=0;n<mGridRectHeight;n++) {
            float aY = aTop + ((float)mGridRectSpacing) * ((float)n);
            mGridList.Add(aX, aY);
        }
    }
}

void GameEditorGrid::BuildCircleGrid() {
    mGridList.RemoveAll();
    mGridList.Add(mCenterX, mCenterY);
    
    if (mGridCircleRingSpacing < 1) { mGridCircleRingSpacing = 1; }
    if (mGridCircleRingCount < 1) { mGridCircleRingCount = 1; }
    if (mGridCircleRadialCount < 1) { mGridCircleRadialCount = 1; }
    
    float aArmLength = 0.0f;
    for (int aRing = 1;aRing<=mGridCircleRingCount;aRing++) {
        
        aArmLength = ((float)aRing) * ((float)mGridCircleRingSpacing);
        
        
        for (int i=0;i<mGridCircleRadialCount;i++) {
            
            float aPercent = ((float)i) / ((float)mGridCircleRadialCount);
            float aAngle = aPercent * 360.0f;
            float aDirX = Sin(aAngle), aDirY = -Cos(aAngle);
            
            float aX = mCenterX + aDirX * aArmLength;
            float aY = mCenterY + aDirY * aArmLength;
            
            mGridList.Add(aX, aY);
        }
    }
}

void GameEditorGrid::BuildStarGrid() {
    
    
    mGridList.RemoveAll();
    mGridList.Add(mCenterX, mCenterY);
    
    if (mGridStarArmCount < 3) { mGridStarArmCount = 3; }
    if (mGridStarInnerRadius < 10) { mGridStarInnerRadius = 10; }
    if (mGridStarOuterRadius < 20) { mGridStarOuterRadius = 20; }
    if (mGridStarLinePointCount < 0) { mGridStarLinePointCount = 0; }
    if (mGridStarStartRotation < -360) { mGridStarStartRotation = -360; }
    if (mGridStarStartRotation > 360) { mGridStarStartRotation = 360; }
    
    
    float aRadOuter = ((float)mGridStarOuterRadius);
    float aRadInner = ((float)mGridStarInnerRadius);
    
    
    for (int i=0;i<mGridStarArmCount;i++) {
        float aPercent1 = ((float)i) / ((float)mGridStarArmCount);
        float aAngle1 = aPercent1 * 360.0f + (float)mGridStarStartRotation;
        
        float aPercent2 = ((float)(i+1)) / ((float)mGridStarArmCount);
        float aAngle2 = aPercent2 * 360.0f + (float)mGridStarStartRotation;
        
        float aAngleMid = (aAngle1 + aAngle2) * 0.5f;
        
        float aDirX1 = Sin(aAngle1), aDirY1 = -Cos(aAngle1);
        float aX1 = mCenterX + aDirX1 * aRadOuter;
        float aY1 = mCenterY + aDirY1 * aRadOuter;
        
        float aDirXMid = Sin(aAngleMid), aDirYMid = -Cos(aAngleMid);
        float aXMid = mCenterX + aDirXMid * aRadInner;
        float aYMid = mCenterY + aDirYMid * aRadInner;
        
        float aDirX2 = Sin(aAngle2), aDirY2 = -Cos(aAngle2);
        float aX2 = mCenterX + aDirX2 * aRadOuter;
        float aY2 = mCenterY + aDirY2 * aRadOuter;
        
        
        float aInterpDirX1 = aXMid - aX1;
        float aInterpDirY1 = aYMid - aY1;
        float aInterpDist1 = aInterpDirX1 * aInterpDirX1 + aInterpDirY1 * aInterpDirY1;
        
        
        float aInterpDirX2 = aXMid - aX2;
        float aInterpDirY2 = aYMid - aY2;
        float aInterpDist2 = aInterpDirX2 * aInterpDirX2 + aInterpDirY2 * aInterpDirY2;
        
        if (aInterpDist1 > SQRT_EPSILON && aInterpDist2 > SQRT_EPSILON) {
            aInterpDist1 = sqrtf(aInterpDist1);
            aInterpDist2 = sqrtf(aInterpDist1);
            
            aInterpDirX1 /= aInterpDist1;
            aInterpDirY1 /= aInterpDist1;
            
            aInterpDirX2 /= aInterpDist2;
            aInterpDirY2 /= aInterpDist2;
            
            for (int k=0;k<mGridStarLinePointCount;k++) {
                
                float aPercent = ((float)(k + 1)) / ((float)(mGridStarLinePointCount + 1));
                
                mGridList.Add(aX1 + aInterpDirX1 * aPercent * aInterpDist1,
                              aY1 + aInterpDirY1 * aPercent * aInterpDist1);
                
                mGridList.Add(aX2 + aInterpDirX2 * aPercent * aInterpDist2,
                              aY2 + aInterpDirY2 * aPercent * aInterpDist2);
                
                
                
            }
            
            
        }
        
        
        
        
        
        mGridList.Add(aXMid, aYMid);
        mGridList.Add(aX2, aY2);
        
        
        
        
        
    }
    
    
    //mGridStarArmCount
    
    /*
    FPointList aRingList;
    float aArmLength = 0.0f;
    for (int aRing = 1;aRing<=mGridNGON1RingCount;aRing++) {
        aArmLength = ((float)aRing) * ((float)mGridNGON1RingSpacing);
        aRingList.RemoveAll();
        for (int i=0;i<mGridNGON1Sides;i++) {
            float aPercent = ((float)i) / ((float)mGridNGON1Sides);
            float aAngle = aPercent * 360.0f + (float)mGridNGON1StartRotation;
            float aDirX = Sin(aAngle), aDirY = -Cos(aAngle);
            float aX = mCenterX + aDirX * aArmLength;
            float aY = mCenterY + aDirY * aArmLength;
            aRingList.Add(aX, aY);
        }
        
        float aX1 = aRingList.mX[0];
        float aY1 = aRingList.mY[0];
        
        float aX2 = aRingList.mX[1];
        float aY2 = aRingList.mY[1];
        
        float aDist = Distance(aX1, aY1, aX2, aY2);
        
        int aLineCount = (int)round(aDist / (float)mGridNGON1PointSpacing);
        
        for (int i=1;i<=aRingList.mCount;i++) {
            
            int aIndex1 = i-1;
            int aIndex2 = i;
            if (aIndex2 == aRingList.mCount) { aIndex2 = 0; }
            
            aX1 = aRingList.mX[aIndex1];
            aY1 = aRingList.mY[aIndex1];
            
            aX2 = aRingList.mX[aIndex2];
            aY2 = aRingList.mY[aIndex2];
            
            mGridList.Add(aX1, aY1);
            
            float aDiffX = aX2 - aX1;
            float aDiffY = aY2 - aY1;
            
            aDist = aDiffX * aDiffX + aDiffY * aDiffY;
            
            if (aDist > SQRT_EPSILON) {
                aDist = sqrtf(aDist);
                aDiffX /= aDist;
                aDiffY /= aDist;
            }
            if (aLineCount > 2) {
                for (int aInterp=1;aInterp<(aLineCount - 1);aInterp++) {
                    float aPercent = ((float)aInterp) / ((float)(aLineCount - 1));
                    mGridList.Add(aX1 + aDiffX * aPercent * aDist,
                                  aY1 + aDiffY * aPercent * aDist);
                }
            }
        }
    }
    */
    
    
}

void GameEditorGrid::BuildNGON1Grid() {
    mGridList.RemoveAll();
    mGridList.Add(mCenterX, mCenterY);
    if (mGridNGON1Sides < 3) { mGridNGON1Sides = 3; }
    if (mGridNGON1RingSpacing < 1) { mGridNGON1RingSpacing = 1; }
    if (mGridNGON1RingCount < 1) { mGridNGON1RingCount = 1; }
    if (mGridNGON1PointSpacing < 10) { mGridNGON1PointSpacing = 10; }
    if (mGridNGON1StartRotation < -360) { mGridNGON1StartRotation = -360; }
    if (mGridNGON1StartRotation > 360) { mGridNGON1StartRotation = 360; }
    FPointList aRingList;
    float aArmLength = 0.0f;
    for (int aRing = 1;aRing<=mGridNGON1RingCount;aRing++) {
        aArmLength = ((float)aRing) * ((float)mGridNGON1RingSpacing);
        aRingList.RemoveAll();
        for (int i=0;i<mGridNGON1Sides;i++) {
            float aPercent = ((float)i) / ((float)mGridNGON1Sides);
            float aAngle = aPercent * 360.0f + (float)mGridNGON1StartRotation;
            float aDirX = Sin(aAngle), aDirY = -Cos(aAngle);
            float aX = mCenterX + aDirX * aArmLength;
            float aY = mCenterY + aDirY * aArmLength;
            aRingList.Add(aX, aY);
        }
        
        float aX1 = aRingList.mX[0];
        float aY1 = aRingList.mY[0];
        
        float aX2 = aRingList.mX[1];
        float aY2 = aRingList.mY[1];
        
        float aDist = Distance(aX1, aY1, aX2, aY2);
        
        int aLineCount = (int)round(aDist / (float)mGridNGON1PointSpacing);
        
        for (int i=1;i<=aRingList.mCount;i++) {
            
            int aIndex1 = i-1;
            int aIndex2 = i;
            if (aIndex2 == aRingList.mCount) { aIndex2 = 0; }
            
            aX1 = aRingList.mX[aIndex1];
            aY1 = aRingList.mY[aIndex1];
            
            aX2 = aRingList.mX[aIndex2];
            aY2 = aRingList.mY[aIndex2];
            
            mGridList.Add(aX1, aY1);
            
            float aDiffX = aX2 - aX1;
            float aDiffY = aY2 - aY1;
            
            aDist = aDiffX * aDiffX + aDiffY * aDiffY;
            
            if (aDist > SQRT_EPSILON) {
                aDist = sqrtf(aDist);
                aDiffX /= aDist;
                aDiffY /= aDist;
            }
            if (aLineCount > 2) {
                for (int aInterp=1;aInterp<(aLineCount - 1);aInterp++) {
                    float aPercent = ((float)aInterp) / ((float)(aLineCount - 1));
                    mGridList.Add(aX1 + aDiffX * aPercent * aDist,
                                  aY1 + aDiffY * aPercent * aDist);
                }
            }
        }
    }
}

void GameEditorGrid::BuildNGON2Grid() {
    
}

void GameEditorGrid::SaveGridState() {
    FString aPath = gDirDocuments + FString("editor_grid_dots.json");
    FJSON aJSON;
    FJSONNode *aConfigNode = new FJSONNode();
    aJSON.mRoot = aConfigNode;
    aConfigNode->AddDictionaryInt("grid_type", mGridType);
    
    aConfigNode->AddDictionaryInt("rect_width", mGridRectWidth);
    aConfigNode->AddDictionaryInt("rect_height", mGridRectHeight);
    aConfigNode->AddDictionaryInt("rect_spacing", mGridRectSpacing);
    
    aConfigNode->AddDictionaryInt("circle_ring_spacing", mGridCircleRingSpacing);
    aConfigNode->AddDictionaryInt("circle_ring_count", mGridCircleRingCount);
    aConfigNode->AddDictionaryInt("circle_radial_count", mGridCircleRadialCount);
    
    aConfigNode->AddDictionaryInt("star_inner_rad", mGridStarInnerRadius);
    aConfigNode->AddDictionaryInt("star_outer_rad", mGridStarOuterRadius);
    aConfigNode->AddDictionaryInt("star_line_point_count", mGridStarLinePointCount);
    aConfigNode->AddDictionaryInt("star_arm_count", mGridStarArmCount);
    aConfigNode->AddDictionaryInt("star_start_rot", mGridStarStartRotation);
    
    aConfigNode->AddDictionaryInt("ngon1_sides", mGridNGON1Sides);
    aConfigNode->AddDictionaryInt("ngon1_ring_spacing", mGridNGON1RingSpacing);
    aConfigNode->AddDictionaryInt("ngon1_ring_count", mGridNGON1RingCount);
    aConfigNode->AddDictionaryInt("ngon1_point_spacing", mGridNGON1PointSpacing);
    aConfigNode->AddDictionaryInt("ngon1_start_rotation", mGridNGON1StartRotation);
    
    aJSON.Save(aPath.c());
}

void GameEditorGrid::LoadGridState() {
    
    FString aPath = gDirDocuments + FString("editor_grid_dots.json");
    FJSON aJSON;
    aJSON.Load(aPath.c());
    FJSONNode *aConfigNode = aJSON.mRoot;
    if (aConfigNode == NULL) return;
    
    mGridType = aConfigNode->GetInt("grid_type", mGridType);
    
    mGridRectWidth = aConfigNode->GetInt("rect_width", mGridRectWidth);
    mGridRectHeight = aConfigNode->GetInt("rect_height", mGridRectHeight);
    mGridRectSpacing = aConfigNode->GetInt("rect_spacing", mGridRectSpacing);
    
    mGridCircleRingSpacing = aConfigNode->GetInt("circle_ring_spacing", mGridCircleRingSpacing);
    mGridCircleRingCount = aConfigNode->GetInt("circle_ring_count", mGridCircleRingCount);
    mGridCircleRadialCount = aConfigNode->GetInt("circle_radial_count", mGridCircleRadialCount);
    
    
    mGridStarInnerRadius = aConfigNode->GetInt("star_inner_rad", mGridStarInnerRadius);
    mGridStarOuterRadius = aConfigNode->GetInt("star_outer_rad", mGridStarOuterRadius);
    mGridStarLinePointCount = aConfigNode->GetInt("star_line_point_count", mGridStarLinePointCount);
    mGridStarArmCount = aConfigNode->GetInt("star_arm_count", mGridStarArmCount);
    mGridStarStartRotation = aConfigNode->GetInt("star_start_rot", mGridStarStartRotation);
    
    mGridNGON1Sides = aConfigNode->GetInt("ngon1_sides", mGridNGON1Sides);
    mGridNGON1RingSpacing = aConfigNode->GetInt("ngon1_ring_spacing", mGridNGON1RingSpacing);
    mGridNGON1RingCount = aConfigNode->GetInt("ngon1_ring_count", mGridNGON1RingCount);
    mGridNGON1PointSpacing = aConfigNode->GetInt("ngon1_point_spacing", mGridNGON1PointSpacing);
    mGridNGON1StartRotation = aConfigNode->GetInt("ngon1_start_rotation", mGridNGON1StartRotation);
    
    BuildGrid();
}


