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
    
    mOffsetX = 0;
    mOffsetY = 0;
    
    
    mGridRectWidth = 7;
    mGridRectHeight = 7;
    mGridRectSpacingH = 44;
    mGridRectSpacingV = 44;
    
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
    
    mGridNGON2Sides = 6;
    mGridNGON2Radius = 200;
    mGridNGON2ScanLineStagger = true;
    mGridNGON2ScanLineStaggerOdd = false;
    mGridNGON2ScanLineOffsetY = 0;
    mGridNGON2ScanLineSpacingV = 46;
    mGridNGON2ScanLineSpacingH = 46;
    mGridNGON2StartRotation = 0;
    
    
    
    
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
    
    
    Graphics::SetColor(0.35f, 0.28f, 0.75f, 0.55f);
    mOutlineList.DrawEdges(1.5f);
    
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
    
    float aCenterX = mCenterX + ((float)mOffsetX);
    float aCenterY = mCenterY + ((float)mOffsetY);
    
    mGridList.RemoveAll();
    
    if (mGridRectWidth < 1) { mGridRectWidth = 1; }
    if (mGridRectHeight < 1) { mGridRectHeight = 1; }
    if (mGridRectSpacingH < 0) { mGridRectSpacingH = 0; }
    if (mGridRectSpacingV < 0) { mGridRectSpacingV = 0; }
    
    
    float aTotalWidth = mGridRectWidth * mGridRectSpacingH;
    float aTotalHeight = mGridRectHeight * mGridRectSpacingV;
    
    float aLeft = round(aCenterX - (aTotalWidth / 2.0f) + mGridRectSpacingH / 2);
    float aTop = round(aCenterY - (aTotalHeight / 2.0f) + mGridRectSpacingV / 2);
    
    float aRight = aLeft + aTotalWidth - mGridRectSpacingH;
    float aBottom = aTop + aTotalHeight - mGridRectSpacingV;
    
    
    mOutlineList.RemoveAll();
    
    if ((mGridRectWidth == 1) && (mGridRectHeight == 1)) {
        mOutlineList.Add(aLeft, aTop);
        mOutlineList.Add(aLeft, aTop);
        mOutlineList.Add(aLeft, aTop);
        mOutlineList.Add(aLeft, aTop);
    } else if (mGridRectWidth == 1) {
        mOutlineList.Add(aLeft, aTop);
        mOutlineList.Add(aLeft, aBottom);
        mOutlineList.Add(aLeft, aBottom);
        mOutlineList.Add(aLeft, aTop);
    } else if (mGridRectHeight == 1) {
        mOutlineList.Add(aLeft, aTop);
        mOutlineList.Add(aRight, aTop);
        mOutlineList.Add(aRight, aTop);
        mOutlineList.Add(aLeft, aTop);
    } else {
        mOutlineList.Add(aLeft, aTop);
        mOutlineList.Add(aRight, aTop);
        mOutlineList.Add(aRight, aBottom);
        mOutlineList.Add(aLeft, aBottom);
    }
    
    for (int i=0;i<mGridRectWidth;i++) {
        
        float aX = aLeft + ((float)mGridRectSpacingH) * ((float)i);
        
        for (int n=0;n<mGridRectHeight;n++) {
            float aY = aTop + ((float)mGridRectSpacingV) * ((float)n);
            mGridList.Add(aX, aY);
        }
    }
}

void GameEditorGrid::BuildCircleGrid() {
    
    float aCenterX = mCenterX + ((float)mOffsetX);
    float aCenterY = mCenterY + ((float)mOffsetY);
    
    mGridList.RemoveAll();
    mGridList.Add(mCenterX, mCenterY);
    
    if (mGridCircleRingSpacing < 1) { mGridCircleRingSpacing = 1; }
    if (mGridCircleRingCount < 1) { mGridCircleRingCount = 1; }
    if (mGridCircleRadialCount < 1) { mGridCircleRadialCount = 1; }
    
    
    mOutlineList.RemoveAll();
    float aArmLength = 0.0f;
    for (int aRing = 1;aRing<=mGridCircleRingCount;aRing++) {
        
        aArmLength = ((float)aRing) * ((float)mGridCircleRingSpacing);
        
        
        for (int i=0;i<mGridCircleRadialCount;i++) {
            
            float aPercent = ((float)i) / ((float)mGridCircleRadialCount);
            float aAngle = aPercent * 360.0f;
            float aDirX = Sin(aAngle), aDirY = -Cos(aAngle);
            
            float aX = aCenterX + aDirX * aArmLength;
            float aY = aCenterY + aDirY * aArmLength;
            
            mGridList.Add(aX, aY);
            
            if (aRing == mGridCircleRingCount) {
                mOutlineList.Add(aX, aY);
            }
            
        }
    }
}

void GameEditorGrid::BuildStarGrid() {
    
    float aCenterX = mCenterX + ((float)mOffsetX);
    float aCenterY = mCenterY + ((float)mOffsetY);
    
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
    
    
    mOutlineList.RemoveAll();
    
    
    for (int i=0;i<mGridStarArmCount;i++) {
        float aPercent1 = ((float)i) / ((float)mGridStarArmCount);
        float aAngle1 = aPercent1 * 360.0f + (float)mGridStarStartRotation;
        
        float aPercent2 = ((float)(i+1)) / ((float)mGridStarArmCount);
        float aAngle2 = aPercent2 * 360.0f + (float)mGridStarStartRotation;
        
        float aAngleMid = (aAngle1 + aAngle2) * 0.5f;
        
        float aDirX1 = Sin(aAngle1), aDirY1 = -Cos(aAngle1);
        float aX1 = aCenterX + aDirX1 * aRadOuter;
        float aY1 = aCenterY + aDirY1 * aRadOuter;
        
        float aDirXMid = Sin(aAngleMid), aDirYMid = -Cos(aAngleMid);
        float aXMid = aCenterX + aDirXMid * aRadInner;
        float aYMid = aCenterY + aDirYMid * aRadInner;
        
        float aDirX2 = Sin(aAngle2), aDirY2 = -Cos(aAngle2);
        float aX2 = aCenterX + aDirX2 * aRadOuter;
        float aY2 = aCenterY + aDirY2 * aRadOuter;
        
        float aInterpDirX1 = aXMid - aX1;
        float aInterpDirY1 = aYMid - aY1;
        float aInterpDist1 = aInterpDirX1 * aInterpDirX1 + aInterpDirY1 * aInterpDirY1;
        
        float aInterpDirX2 = aXMid - aX2;
        float aInterpDirY2 = aYMid - aY2;
        float aInterpDist2 = aInterpDirX2 * aInterpDirX2 + aInterpDirY2 * aInterpDirY2;
        
        mOutlineList.Add(aX1, aY1);
        mOutlineList.Add(aXMid, aYMid);
        mOutlineList.Add(aX2, aY2);
        
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
}

void GameEditorGrid::BuildNGON1Grid() {
    
    float aCenterX = mCenterX + ((float)mOffsetX);
    float aCenterY = mCenterY + ((float)mOffsetY);
    
    mOutlineList.RemoveAll();
    
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
            float aX = aCenterX + aDirX * aArmLength;
            float aY = aCenterY + aDirY * aArmLength;
            aRingList.Add(aX, aY);
            
            if (aRing == mGridNGON1RingCount) {
                mOutlineList.Add(aX, aY);
            }
            
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
    
    float aCenterX = mCenterX + ((float)mOffsetX);
    float aCenterY = mCenterY + ((float)mOffsetY);
    
    
    if (mGridNGON2Sides < 3) { mGridNGON2Sides = 3; }
    if (mGridNGON2Radius < 10) { mGridNGON2Radius = 10; }
    if (mGridNGON2ScanLineSpacingH < 20) { mGridNGON2ScanLineSpacingH = 20; }
    if (mGridNGON2ScanLineSpacingV < 20) { mGridNGON2ScanLineSpacingV = 20; }
    
    mOutlineList.RemoveAll();
    for (int i=0;i<mGridNGON2Sides;i++) {
        float aPercent = ((float)i) / ((float)mGridNGON2Sides);
        float aAngle = aPercent * 360.0f + (float)mGridNGON2StartRotation;
        float aDirX = Sin(aAngle), aDirY = -Cos(aAngle);
        float aX = aCenterX + aDirX * ((float)mGridNGON2Radius);
        float aY = aCenterY + aDirY * ((float)mGridNGON2Radius);
        mOutlineList.Add(aX, aY);
    }
    BuildScanlinePoly(&mOutlineList, mGridNGON2ScanLineOffsetY, mGridNGON2ScanLineSpacingH, mGridNGON2ScanLineSpacingV, mGridNGON2ScanLineStagger, mGridNGON2ScanLineStaggerOdd);
    
    
}

void GameEditorGrid::BuildScanlinePoly(FPointList *pPoly, int pOffsetY, int pSpacingH, int pSpacingV, bool pStaggerH, bool pStaggerOdd) {
    
    mGridList.RemoveAll();
    
    if (pPoly == NULL) { return; }
    if (pPoly->mCount < 3) { return; }
    
    float aMinX = pPoly->GetMinX() - 10.0f;
    float aMaxX = pPoly->GetMaxX() + 10.0f;
    float aMinY = pPoly->GetMinY() - 10.0f;
    float aMaxY = pPoly->GetMaxY() + 10.0f;
    
    float aCenterX = pPoly->GetCenterX();
    
    float aSpacingV = pSpacingV;
    if (aSpacingV < 5.0f) { aSpacingV = 5.0f; }
    
    float aSpacingH = pSpacingH;
    if (aSpacingH < 5.0f) { aSpacingH = 5.0f; }
    
    float aSpacingH2 = aSpacingH / 2.0f;
    
    float aScanLineY = aMinY - (aSpacingV / 2.0f) + ((float)pOffsetY);
    
    bool aHalfShift = !pStaggerOdd;
    
    while (aScanLineY <= aMaxY) {
        
        float aX = aCenterX;
        if ((pStaggerH == true) && (aHalfShift == true)) {
            aX -= aSpacingH2;
        }
        
        while (aX >= aMinX) {
            if (pPoly->ContainsPoint(aX, aScanLineY)) {
                mGridList.Add(aX, aScanLineY);
            }
            aX -= aSpacingH;
        }
        
        aX = aCenterX;
        if ((pStaggerH == true) && (aHalfShift == true)) {
            aX += aSpacingH2;
        } else {
            aX += aSpacingH;
        }
        
        while (aX <= aMaxX) {
            if (pPoly->ContainsPoint(aX, aScanLineY)) {
                mGridList.Add(aX, aScanLineY);
            }
            aX += aSpacingH;
        }
        
        aHalfShift = !aHalfShift;
        aScanLineY += aSpacingV;
    }
}


void GameEditorGrid::SaveGridState() {
    FString aPath = gDirDocuments + FString("editor_grid_dots.json");
    FJSON aJSON;
    FJSONNode *aConfigNode = new FJSONNode();
    aJSON.mRoot = aConfigNode;
    aConfigNode->AddDictionaryInt("grid_type", mGridType);
    if (mOffsetX != 0) { aConfigNode->AddDictionaryInt("grid_offset_x", mOffsetX); }
    if (mOffsetY != 0) { aConfigNode->AddDictionaryInt("grid_offset_y", mOffsetY); }
    
    
    aConfigNode->AddDictionaryInt("rect_width", mGridRectWidth);
    aConfigNode->AddDictionaryInt("rect_height", mGridRectHeight);
    aConfigNode->AddDictionaryInt("rect_spacing_h", mGridRectSpacingH);
    aConfigNode->AddDictionaryInt("rect_spacing_v", mGridRectSpacingV);
    
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
    
    
    
    
    aConfigNode->AddDictionaryInt("ngon2_sides", mGridNGON2Sides);
    aConfigNode->AddDictionaryInt("ngon2_radius", mGridNGON2Radius);
    aConfigNode->AddDictionaryInt("ngon2_offset_y", mGridNGON2ScanLineOffsetY);
    aConfigNode->AddDictionaryInt("ngon2_spacing_v", mGridNGON2ScanLineSpacingV);
    aConfigNode->AddDictionaryInt("ngon2_spacing_h", mGridNGON2ScanLineSpacingH);
    aConfigNode->AddDictionaryInt("ngon2_start_rotation", mGridNGON2StartRotation);
    aConfigNode->AddDictionaryBool("ngon2_stagger", mGridNGON2ScanLineStagger);
    aConfigNode->AddDictionaryBool("ngon2_stagger_odd", mGridNGON2ScanLineStaggerOdd);
    
    
    
    
    aJSON.Save(aPath.c());
}

void GameEditorGrid::LoadGridState() {
    
    FString aPath = gDirDocuments + FString("editor_grid_dots.json");
    FJSON aJSON;
    aJSON.Load(aPath.c());
    FJSONNode *aConfigNode = aJSON.mRoot;
    if (aConfigNode == NULL) return;
    
    mGridType = aConfigNode->GetInt("grid_type", mGridType);
    mOffsetX = aConfigNode->GetInt("grid_offset_x", 0);
    mOffsetY = aConfigNode->GetInt("grid_offset_y", 0);
    
    mGridRectWidth = aConfigNode->GetInt("rect_width", mGridRectWidth);
    mGridRectHeight = aConfigNode->GetInt("rect_height", mGridRectHeight);
    mGridRectSpacingH = aConfigNode->GetInt("rect_spacing_h", mGridRectSpacingH);
    mGridRectSpacingV = aConfigNode->GetInt("rect_spacing_v", mGridRectSpacingV);
    
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
    
    
    mGridNGON2Sides = aConfigNode->GetInt("ngon2_sides", mGridNGON2Sides);
    mGridNGON2Radius = aConfigNode->GetInt("ngon2_radius", mGridNGON2Radius);
    mGridNGON2ScanLineOffsetY = aConfigNode->GetInt("ngon2_offset_y", mGridNGON2ScanLineOffsetY);
    mGridNGON2ScanLineSpacingV = aConfigNode->GetInt("ngon2_spacing_v", mGridNGON2ScanLineSpacingV);
    mGridNGON2ScanLineSpacingH = aConfigNode->GetInt("ngon2_spacing_h", mGridNGON2ScanLineSpacingH);
    mGridNGON2StartRotation = aConfigNode->GetInt("ngon2_start_rotation", mGridNGON2StartRotation);
    mGridNGON2ScanLineStagger = aConfigNode->GetBool("ngon2_stagger", mGridNGON2ScanLineStagger);
    mGridNGON2ScanLineStaggerOdd = aConfigNode->GetBool("ngon2_stagger_odd", mGridNGON2ScanLineStaggerOdd);
    
    
    
    
    BuildGrid();
}

FJSONNode *GameEditorGrid::SaveCurrentGrid() {
    
    FJSONNode *aResult = new FJSONNode();
    
    aResult->AddDictionaryInt("grid_type", mGridType);
    if (mOffsetX != 0) { aResult->AddDictionaryInt("grid_offset_x", mOffsetX); }
    if (mOffsetY != 0) { aResult->AddDictionaryInt("grid_offset_y", mOffsetY); }
    
    if (mGridType == SNAP_GRID_TYPE_RECT) {
        aResult->AddDictionaryInt("rect_width", mGridRectWidth);
        aResult->AddDictionaryInt("rect_height", mGridRectHeight);
        aResult->AddDictionaryInt("rect_spacing_h", mGridRectSpacingH);
        aResult->AddDictionaryInt("rect_spacing_v", mGridRectSpacingV);
    }
    
    if (mGridType == SNAP_GRID_TYPE_CIRCLE) {
        aResult->AddDictionaryInt("circle_ring_spacing", mGridCircleRingSpacing);
        aResult->AddDictionaryInt("circle_ring_count", mGridCircleRingCount);
        aResult->AddDictionaryInt("circle_radial_count", mGridCircleRadialCount);
    }
    
    if (mGridType == SNAP_GRID_TYPE_STAR) {
        aResult->AddDictionaryInt("star_inner_rad", mGridStarInnerRadius);
        aResult->AddDictionaryInt("star_outer_rad", mGridStarOuterRadius);
        aResult->AddDictionaryInt("star_line_point_count", mGridStarLinePointCount);
        aResult->AddDictionaryInt("star_arm_count", mGridStarArmCount);
        aResult->AddDictionaryInt("star_start_rot", mGridStarStartRotation);
    }
    
    if (mGridType == SNAP_GRID_TYPE_NGON1) {
        aResult->AddDictionaryInt("ngon1_sides", mGridNGON1Sides);
        aResult->AddDictionaryInt("ngon1_ring_spacing", mGridNGON1RingSpacing);
        aResult->AddDictionaryInt("ngon1_ring_count", mGridNGON1RingCount);
        aResult->AddDictionaryInt("ngon1_point_spacing", mGridNGON1PointSpacing);
        aResult->AddDictionaryInt("ngon1_start_rotation", mGridNGON1StartRotation);
    }
    
    if (mGridType == SNAP_GRID_TYPE_NGON2) {
        aResult->AddDictionaryInt("ngon2_sides", mGridNGON2Sides);
        aResult->AddDictionaryInt("ngon2_radius", mGridNGON2Radius);
        aResult->AddDictionaryInt("ngon2_offset_y", mGridNGON2ScanLineOffsetY);
        aResult->AddDictionaryInt("ngon2_spacing_v", mGridNGON2ScanLineSpacingV);
        aResult->AddDictionaryInt("ngon2_spacing_h", mGridNGON2ScanLineSpacingH);
        aResult->AddDictionaryInt("ngon2_start_rotation", mGridNGON2StartRotation);
        aResult->AddDictionaryBool("ngon2_stagger", mGridNGON2ScanLineStagger);
        aResult->AddDictionaryBool("ngon2_stagger_odd", mGridNGON2ScanLineStaggerOdd);
        
        
        
        
    }
    
    return aResult;
}

void GameEditorGrid::LoadCurrentGrid(FJSONNode *pNode) {
    
    if (pNode == NULL) { return; }
    
    mGridType = pNode->GetInt("grid_type", mGridType);
    mOffsetX = pNode->GetInt("grid_offset_x", 0);
    mOffsetY = pNode->GetInt("grid_offset_y", 0);
    
    if (mGridType == SNAP_GRID_TYPE_RECT) {
        mGridRectWidth = pNode->GetInt("rect_width", mGridRectWidth);
        mGridRectHeight = pNode->GetInt("rect_height", mGridRectHeight);
        mGridRectSpacingH = pNode->GetInt("rect_spacing_h", mGridRectSpacingH);
        mGridRectSpacingV = pNode->GetInt("rect_spacing_v", mGridRectSpacingV);
    }
    
    if (mGridType == SNAP_GRID_TYPE_CIRCLE) {
        mGridCircleRingSpacing = pNode->GetInt("circle_ring_spacing", mGridCircleRingSpacing);
        mGridCircleRingCount = pNode->GetInt("circle_ring_count", mGridCircleRingCount);
        mGridCircleRadialCount = pNode->GetInt("circle_radial_count", mGridCircleRadialCount);
    }
    
    if (mGridType == SNAP_GRID_TYPE_STAR) {
        mGridStarInnerRadius = pNode->GetInt("star_inner_rad", mGridStarInnerRadius);
        mGridStarOuterRadius = pNode->GetInt("star_outer_rad", mGridStarOuterRadius);
        mGridStarLinePointCount = pNode->GetInt("star_line_point_count", mGridStarLinePointCount);
        mGridStarArmCount = pNode->GetInt("star_arm_count", mGridStarArmCount);
        mGridStarStartRotation = pNode->GetInt("star_start_rot", mGridStarStartRotation);
    }
    
    if (mGridType == SNAP_GRID_TYPE_NGON1) {
        mGridNGON1Sides = pNode->GetInt("ngon1_sides", mGridNGON1Sides);
        mGridNGON1RingSpacing = pNode->GetInt("ngon1_ring_spacing", mGridNGON1RingSpacing);
        mGridNGON1RingCount = pNode->GetInt("ngon1_ring_count", mGridNGON1RingCount);
        mGridNGON1PointSpacing = pNode->GetInt("ngon1_point_spacing", mGridNGON1PointSpacing);
        mGridNGON1StartRotation = pNode->GetInt("ngon1_start_rotation", mGridNGON1StartRotation);
    }
    
    if (mGridType == SNAP_GRID_TYPE_NGON2) {
        mGridNGON2Sides = pNode->GetInt("ngon2_sides", mGridNGON2Sides);
        mGridNGON2Radius = pNode->GetInt("ngon2_radius", mGridNGON2Radius);
        mGridNGON2ScanLineOffsetY = pNode->GetInt("ngon2_offset_y", mGridNGON2ScanLineOffsetY);
        mGridNGON2ScanLineSpacingV = pNode->GetInt("ngon2_spacing_v", mGridNGON2ScanLineSpacingV);
        mGridNGON2ScanLineSpacingH = pNode->GetInt("ngon2_spacing_h", mGridNGON2ScanLineSpacingH);
        mGridNGON2StartRotation = pNode->GetInt("ngon2_start_rotation", mGridNGON2StartRotation);
        mGridNGON2ScanLineStagger = pNode->GetBool("ngon2_stagger", mGridNGON2ScanLineStagger);
        mGridNGON2ScanLineStagger = pNode->GetBool("ngon2_stagger_odd", mGridNGON2ScanLineStaggerOdd);
        
    }
    
    BuildGrid();
}



