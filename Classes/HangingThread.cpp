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
    
    mSpawnOffsetX = 0.0f;
    mSpawnOffsetY = 0.0f;
    mSpawnOffsetZ = 0.8f;
    
}

HangingThread::~HangingThread() {
    
}


void HangingThread::Setup() {
    
    //float aInitial
    
    float aX = mSpawnOffsetX;
    float aY = mSpawnOffsetY;
    float aZ = mSpawnOffsetZ;
    
    float aMaxStartRot = 7.0f;
    
    float aRotZ = gRand.GetFloat(0.0f, aMaxStartRot, true);
    float aRotY = gRand.GetFloat(0.0f, aMaxStartRot, true);
    
    float aMaxOffset = 2.25f;
    float aHopDist = 2.85f;
    
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
        float aNextZ = aZ + aDown.mZ;
        
        if (aNextX >= aMaxOffset) {
            aNextX = aMaxOffset - gRand.GetFloat(0.125f);
            aRotZ = gRand.GetFloat(-7.0f, -1.0f);
        } else if (aNextX <= -aMaxOffset) {
            aNextX = -aMaxOffset + gRand.GetFloat(0.125f);
            aRotZ = gRand.GetFloat(1.0f, 7.0f);
        } else {
            aRotZ += gRand.GetFloat(-9.0f, 9.0f);
        }
        
        if (aNextZ >= aMaxOffset) {
            aNextZ = aMaxOffset - gRand.GetFloat(0.125f);
            aRotY = gRand.GetFloat(-9.0f, -2.0f);
        } else if (aNextZ <= -aMaxOffset) {
            aNextZ = -aMaxOffset + gRand.GetFloat(0.125f);
            aRotY = gRand.GetFloat(2.0f, 9.0f);
        } else {
            aRotY += gRand.GetFloat(-7.0f, 7.0f);
        }
        
        aX = aNextX;
        aY = aNextY;
        aZ = aNextZ;
    }
}

void HangingThread::Update() {
    
}

void HangingThread::Draw() {
    
}

void HangingThread::Draw3D() {
    
    Graphics::PipelineStateSetShape3DAlphaBlending();
    for (int i=0;i<mKnotCount;i++) {
        HangingThreadKnot *aCur = mKnot[i];
        Graphics::SetColor(1.0f, 1.0f, 1.0f, 1.0f);
        Graphics::DrawBox(aCur->mBaseX, aCur->mBaseY, aCur->mBaseZ,
                          aCur->mBaseX, aCur->mBaseY, aCur->mBaseZ + 0.25f,
                          0.25f);
    }
    
    
    Generate();
    
    float aSplineX, aSplineY, aSplineZ;
    for (float aPos=0.0f;aPos<=mSpline.Max();aPos+=0.25f) {
        
        mSpline.Get(aPos, aSplineX, aSplineY, aSplineZ);
        
        Graphics::SetColor(1.0f, 0.0f, 0.0f, 1.0f);
        Graphics::DrawBox(aSplineX, aSplineY, aSplineZ,
                          aSplineX, aSplineY, aSplineZ + 0.15f,
                          0.25f);
        
        
    }
    
    
    
}

void HangingThread::Generate() {
    
    mSpline.Reset();
    for (int i=0;i<mKnotCount;i++) {
        HangingThreadKnot *aCur = mKnot[i];
        mSpline.Add(aCur->mBaseX, aCur->mBaseY, aCur->mBaseZ);
    }
    mSpline.Solve();
    
    
    
    
    
}

