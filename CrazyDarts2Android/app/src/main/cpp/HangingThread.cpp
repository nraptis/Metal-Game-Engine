//
//  HangingThread.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 8/20/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "HangingThread.hpp"
#include "core_includes.h"

HangingThread::HangingThread() {
    
    mKnotCount = gRand.Get(MIN_KNOT_COUNT, MAX_KNOT_COUNT);
    
    for (int i=0;i<mKnotCount;i++) {
        mKnot[i] = new HangingThreadKnot();
    }
    
    for (int i=mKnotCount;i<MAX_KNOT_COUNT;i++) {
        mKnot[i] = 0;
    }
    
    float aColorLitR = 0.93f;
    float aColorLitG = 0.93f;
    float aColorLitB = 0.93f;
    
    float aColorDarkR = 0.45f;
    float aColorDarkG = 0.45f;
    float aColorDarkB = 0.45f;
    
    for (int i=0;i<HANGING_THREAD_SEGMENT_RING_POINT_COUNT;i++) {
        
        int aDiff1 = i - 0;
        int aDiff2 = (HANGING_THREAD_SEGMENT_RING_POINT_COUNT - i);
        int aDiff = aDiff1 < aDiff2 ? aDiff1 : aDiff2;
        
        float aPercent = ((float)aDiff) / ((float)(HANGING_THREAD_SEGMENT_RING_POINT_COUNT / 2));
        aPercent = 1.0f - aPercent;
        aPercent = aPercent * aPercent;
        
        mSegmentColorRed[i] = aColorDarkR + (aColorLitR - aColorDarkR) * aPercent;
        mSegmentColorGreen[i] = aColorDarkG + (aColorLitG - aColorDarkG) * aPercent;
        mSegmentColorBlue[i] = aColorDarkB + (aColorLitB - aColorDarkB) * aPercent;
    }
    
    for (int i=(HANGING_THREAD_SEGMENT_RING_POINT_COUNT/2);i<HANGING_THREAD_SEGMENT_RING_POINT_COUNT;i++) {
        mSegmentColorRed[i] *= 0.55f;
        mSegmentColorGreen[i] *= 0.55f;
        mSegmentColorBlue[i] *= 0.55f;
    }
    
    mOffsetX = 0.0f;
    mOffsetY = 0.0f;
    mOffsetZ = 0.0f;
    
    
}

HangingThread::~HangingThread() {
    
    FreeList(HangingThreadSegment, mSegmentList);
    FreeList(HangingThreadSegment, mSegmentQueue);
    
    for (int i=0;i<mKnotCount;i++) {
        delete mKnot[i];
        mKnot[i] = NULL;
    }
    
}

void HangingThread::Update() {
    
}

void HangingThread::Draw3D() {
    mNodeList.DrawTris();
}

void HangingThread::Setup() {
    
    float aX = 0.0f;
    float aY = 0.0f;
    float aZ = 0.0f;
    
    float aMaxStartRot = 7.0f;
    
    float aRotZ = gRand.GetFloat(0.0f, aMaxStartRot, true);
    float aRotY = gRand.GetFloat(0.0f, aMaxStartRot, true);
    
    float aMaxOffset = 0.65f;
    float aHopDist = 1.5f;
    
    for (int i=0;i<mKnotCount;i++) {
        
        mKnot[i]->mBaseX = aX;
        mKnot[i]->mBaseY = aY;
        mKnot[i]->mBaseZ = aZ;
        
        FVec3 aDown = FVec3(0.0f, 1.0f, 0.0f);
        
        aDown = aDown.RotateZ(aRotZ);
        aDown = aDown.RotateX(aRotY);
        aDown *= aHopDist;
        
        float aNextX = aX + aDown.mX;
        float aNextY = aY + aDown.mY;
        
        if (aNextX >= aMaxOffset) {
            aNextX = aMaxOffset - gRand.GetFloat(0.125f);
            aRotZ = gRand.GetFloat(-7.0f, -1.0f);
        } else if (aNextX <= -aMaxOffset) {
            aNextX = -aMaxOffset + gRand.GetFloat(0.125f);
            aRotZ = gRand.GetFloat(1.0f, 7.0f);
        } else {
            aRotZ += gRand.GetFloat(-9.0f, 9.0f);
        }
        
        aX = aNextX;
        aY = aNextY;
        aZ = aZ;
        
        
        aZ -= 0.25f + gRand.GetFloat(0.05f);
    }
    
}


void HangingThread::ApplyEnvironmentals(float pWind, float pBounce) {
    
    
    float aWindShiftMax = 2.45f;
    for (int i=0;i<mKnotCount;i++) {
        float aPercent = ((float)i) / ((float)(mKnotCount - 1));
        mKnot[i]->mOffsetX = aWindShiftMax * pWind * aPercent;
    }
    
    
    
}

void HangingThread::Generate(float pWind, float pBounce) {
    
    ApplyEnvironmentals(pWind, pBounce);
    
    
    mSpline.Reset();
    for (int i=0;i<mKnotCount;i++) {
        HangingThreadKnot *aCur = mKnot[i];
        mSpline.Add(aCur->GetX(), aCur->GetY(), aCur->GetZ());
    }
    mSpline.Solve();
    
    EnumList(HangingThreadSegment, aSegment, mSegmentList) {
        mSegmentQueue.Add(aSegment);
    }
    mSegmentList.RemoveAll();
    
    float aHopSize = 0.25f;
    float aSplineX, aSplineY, aSplineZ;
    
    for (float aPos=0.0f;aPos<=mSpline.Max();aPos+=aHopSize) {
        
        mSpline.Get(aPos, aSplineX, aSplineY, aSplineZ);
        
        HangingThreadSegment *aSegment = (HangingThreadSegment *)mSegmentQueue.PopLast();
        if (aSegment == NULL) {
            aSegment = new HangingThreadSegment();
        }
        
        mSegmentList.Add(aSegment);
        
        aSegment->mX = aSplineX + mOffsetX;
        aSegment->mY = aSplineY + mOffsetY;
        aSegment->mZ = aSplineZ + mOffsetZ;
    }
    
    //At the end of this, all segments will have a "norm" except for
    //the last segment. We will not use the
    
    float aDiffX = 0.0f;
    float aDiffY = 0.0f;
    float aDiffZ = 0.0f;
    
    HangingThreadSegment *aCur = NULL, *aPrev = NULL;
    for (int i=1;i<mSegmentList.mCount;i++) {
        
        aPrev = (HangingThreadSegment *)(mSegmentList.mData[i - 1]);
        aCur = (HangingThreadSegment *)(mSegmentList.mData[i]);
        
        aDiffX = aCur->mX - aPrev->mX;
        aDiffY = aCur->mY - aPrev->mY;
        aDiffZ = aCur->mZ - aPrev->mZ;
        
        float aLength = aDiffX * aDiffX + aDiffY * aDiffY + aDiffZ * aDiffZ;
        
        if (aLength > SQRT_EPSILON) {
            aLength = sqrtf(aLength);
            aDiffX /= aLength;
            aDiffY /= aLength;
            aDiffZ /= aLength;
        } else {
            aDiffX = 0.0f;
            aDiffY = -1.0f;
            aDiffZ = 0.0;
        }
        
        aPrev->mNormX = aDiffX;
        aPrev->mNormY = aDiffY;
        aPrev->mNormZ = aDiffZ;
    }
    
    aCur->mNormX = aDiffX;
    aCur->mNormY = aDiffY;
    aCur->mNormZ = aDiffZ;
    
    float aThickness = 0.085f;
    
    FVec3 aOrigin = FVec3(0.0f, 0.0f, 0.0f);
    for (int i=0;i<mSegmentList.mCount;i++) {
        
        HangingThreadSegment *aSegment = (HangingThreadSegment *)(mSegmentList.mData[i]);
        
        float aX = aSegment->mX;
        float aY = aSegment->mY;
        float aZ = aSegment->mZ;
        
        float aNormX = aSegment->mNormX;
        float aNormY = aSegment->mNormY;
        float aNormZ = aSegment->mNormZ;
        
        FVec3 aNorm = FVec3(aNormX, aNormY, aNormZ);
        FVec3 aFacing = FVec3(0.0f, 0.0f, 1.0f);
        
        aFacing = aFacing.GetProjected(aOrigin, aNorm);
        aFacing.Normalize();
        
        for (int k=0;k<HANGING_THREAD_SEGMENT_RING_POINT_COUNT;k++) {
            
            float aPercent = ((float)k) / ((float)(HANGING_THREAD_SEGMENT_RING_POINT_COUNT));
            float aRotation = aPercent * 360.0f;
            
            FVec3 aArm = Rotate3D(aFacing, aNorm, aRotation);
            
            aSegment->mRingX[k] = aX + aArm.mX * aThickness;
            aSegment->mRingY[k] = aY + aArm.mY * aThickness;
            aSegment->mRingZ[k] = aZ + aArm.mZ * aThickness;
        }
    }
    
    mNodeList.Reset();
    
    int aWriteIndex = 0;
    for (int i=1;i<mSegmentList.mCount;i++) {
        
        aPrev = (HangingThreadSegment *)(mSegmentList.mData[i - 1]);
        aCur = (HangingThreadSegment *)(mSegmentList.mData[i]);
        
        int aIndexPrev = (HANGING_THREAD_SEGMENT_RING_POINT_COUNT - 1);
        int aIndex = 0;
        
        while (aIndex < HANGING_THREAD_SEGMENT_RING_POINT_COUNT) {
            
            
            float aTopX1 = aPrev->mRingX[aIndexPrev];
            float aTopY1 = aPrev->mRingY[aIndexPrev];
            float aTopZ1 = aPrev->mRingZ[aIndexPrev];
            
            float aTopX2 = aPrev->mRingX[aIndex];
            float aTopY2 = aPrev->mRingY[aIndex];
            float aTopZ2 = aPrev->mRingZ[aIndex];
            
            float aBottomX1 = aCur->mRingX[aIndexPrev];
            float aBottomY1 = aCur->mRingY[aIndexPrev];
            float aBottomZ1 = aCur->mRingZ[aIndexPrev];
            
            float aBottomX2 = aCur->mRingX[aIndex];
            float aBottomY2 = aCur->mRingY[aIndex];
            float aBottomZ2 = aCur->mRingZ[aIndex];
            
            float aColorRed1 = mSegmentColorRed[aIndexPrev];
            float aColorGreen1 = mSegmentColorGreen[aIndexPrev];
            float aColorBlue1 = mSegmentColorBlue[aIndexPrev];
            
            float aColorRed2 = mSegmentColorRed[aIndex];
            float aColorGreen2 = mSegmentColorGreen[aIndex];
            float aColorBlue2 = mSegmentColorBlue[aIndex];
            
            /////////////////////////
            
            mNodeList.SetXYZ(aWriteIndex, aTopX1, aTopY1, aTopZ1);
            mNodeList.SetRGBA(aWriteIndex, aColorRed1, aColorGreen1, aColorBlue1, 1.0f);
            aWriteIndex++;
            
            mNodeList.SetXYZ(aWriteIndex, aTopX2, aTopY2, aTopZ2);
            mNodeList.SetRGBA(aWriteIndex, aColorRed2, aColorGreen2, aColorBlue2, 1.0f);
            aWriteIndex++;
            
            mNodeList.SetXYZ(aWriteIndex, aBottomX1, aBottomY1, aBottomZ1);
            mNodeList.SetRGBA(aWriteIndex, aColorRed1, aColorGreen1, aColorBlue1, 1.0f);
            aWriteIndex++;
            
            /////////////////////////
            
            mNodeList.SetXYZ(aWriteIndex, aBottomX1, aBottomY1, aBottomZ1);
            mNodeList.SetRGBA(aWriteIndex, aColorRed1, aColorGreen1, aColorBlue1, 1.0f);
            aWriteIndex++;
            
            mNodeList.SetXYZ(aWriteIndex, aTopX2, aTopY2, aTopZ2);
            mNodeList.SetRGBA(aWriteIndex, aColorRed2, aColorGreen2, aColorBlue2, 1.0f);
            aWriteIndex++;
            
            mNodeList.SetXYZ(aWriteIndex, aBottomX2, aBottomY2, aBottomZ2);
            mNodeList.SetRGBA(aWriteIndex, aColorRed2, aColorGreen2, aColorBlue2, 1.0f);
            aWriteIndex++;
            
            /////////////////////////
            
            aIndexPrev = aIndex;
            aIndex++;
        }
    }
}

