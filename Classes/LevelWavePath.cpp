//
//  LevelWavePath.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/15/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelWavePath.hpp"
#include "os_core_graphics.h"
#include "FSpline.h"
#include "core_includes.h"

static FPointList cPointList;

static FPointList cDumpList;
static FFloatList cDistList;

LevelWavePathNode::LevelWavePathNode() {
    mX = 0.0f;
    mY = 0.0f;
    mType = PATH_NODE_INVALID;
    mWaitTimer = 0;

}

LevelWavePathNode::~LevelWavePathNode() {
    
}

LevelWavePath::LevelWavePath() {
    
    mSpeed = 5.0f;
    mDidFinalize = false;
    
}

LevelWavePath::~LevelWavePath() {
    
}

void LevelWavePath::Add(int pType, float pX, float pY) {
    //
    //
    //
    LevelWavePathNode *aNode = new LevelWavePathNode();
    aNode->mX = pX;
    aNode->mY = pY;
    aNode->mType = pType;
    //
    mNodeList.Add(aNode);
}

void LevelWavePath::AddMove(float pX, float pY) {
    Add(PATH_NODE_MOVE, pX, pY);
}

void LevelWavePath::AddStop(float pX, float pY) {
    Add(PATH_NODE_STOP, pX, pY);
}

void LevelWavePath::AddWait(int pTime) {
    LevelWavePathNode *aNode = new LevelWavePathNode();
    aNode->mX = 444.0f;
    aNode->mY = 1000.0f;
    aNode->mType = PATH_NODE_WAIT;
    aNode->mWaitTimer = pTime;
    mNodeList.Add(aNode);
}

void LevelWavePath::Finalize() {
    
    int aFirstNonStopIndex = -1;
    
    float aStartX = 0.0f;
    float aStartY = 0.0f;
    
    if (mNodeList.mCount <= 2) {
        printf("ILLEGAL, TOO SMALL!!!\n");
        return;
    }
    
    for (int i=0;i<mNodeList.mCount && aFirstNonStopIndex == -1;i++) {
        LevelWavePathNode *aNode = ((LevelWavePathNode *)mNodeList.mData[i]);
        
        if (aNode->mType == PATH_NODE_INVALID) {
            printf("ILLEGAL PATH!!!");
            return;
        } else if (aNode->mType != PATH_NODE_WAIT) {
            aFirstNonStopIndex = i;
            aStartX = aNode->mX;
            aStartY = aNode->mY;
        }
    }
    
    if (aFirstNonStopIndex == -1) {
        printf("ILLEGAL PATH: ALL WAIT NDOES\n\n");
        return;
    }
    
    for (int i=aFirstNonStopIndex-1;i>=0;i--) {
        LevelWavePathNode *aNode = ((LevelWavePathNode *)mNodeList.mData[i]);
        aNode->mX = aStartX;
        aNode->mY = aStartY;
    }
    
    float aLastX = aStartX;
    float aLastY = aStartY;
    for (int i=aFirstNonStopIndex+1;i<mNodeList.mCount;i++) {
        LevelWavePathNode *aPrev = ((LevelWavePathNode *)mNodeList.mData[i-1]);
        LevelWavePathNode *aNode = ((LevelWavePathNode *)mNodeList.mData[i]);
        if (aPrev->mType == PATH_NODE_WAIT && aNode->mType == PATH_NODE_WAIT) {
            printf("ILLEGAL PATH: 2 WAITS IN ROW...\n");
            return;
        }
        
        if (aNode->mType == PATH_NODE_WAIT) {
            aNode->mX = aPrev->mX;
            aNode->mY = aPrev->mY;
        }
    }
    
    
    for (int i=0;i<mNodeList.mCount;i++) {
        LevelWavePathNode *aNode = ((LevelWavePathNode *)mNodeList.mData[i]);
        
        FString aType = "??";
        
        if (aNode->mType == PATH_NODE_WAIT) aType = "WAIT";
        if (aNode->mType == PATH_NODE_STOP) aType = "STOP";
        if (aNode->mType == PATH_NODE_MOVE) aType = "MOVE";
        if (aNode->mType == PATH_NODE_INVALID) aType = "INVALID";
        
        printf("Path [%d] {%s}  {%.3f, %.3f} \n", i, aType.c(), aNode->mX, aNode->mY);
    }
    
    //cPointList
    int aSectionStartIndex = 0;
    int aSectionEndIndex = -1;

    int aIndex = 0;
    
    while (aIndex < mNodeList.mCount) {
        LevelWavePathNode *aNode = ((LevelWavePathNode *)mNodeList.mData[aIndex]);
        if (aIndex > 0) {
            if (aNode->mType == PATH_NODE_STOP || (aIndex == (mNodeList.mCount - 1))) {
                LevelWavePath::AddSegmentBacktrackingFrom(aIndex);
            }
        }
        ++aIndex;
    }
    
    
    //int mNodeList.mCount
    
    
    
    
    
    
    mDidFinalize = true;
    
}

void LevelWavePath::AddSegmentBacktrackingFrom(int pIndex) {
    printf("LevelWavePath::AddSegmentBacktrackingFrom(%d)\n", pIndex);
    
    int aStartIndex = pIndex - 1;
    while (aStartIndex > 0) {
        LevelWavePathNode *aNode = ((LevelWavePathNode *)mNodeList.mData[aStartIndex]);
        
        if (aNode->mType == PATH_NODE_STOP || aNode->mType == PATH_NODE_WAIT) {
            break;
        } else {
            --aStartIndex;
        }
    }
    
    printf("LevelWavePath::Backtracking(%d => %d)\n", aStartIndex, pIndex);
    
    LevelWavePathNode *aPrev = ((LevelWavePathNode *)mNodeList.mData[aStartIndex]);
    
    cPointList.Reset();
    
    cPointList.Add(aPrev->mX, aPrev->mY);
    
    float aTotalDist = 0.0f;
    for (int i=aStartIndex+1;i<=pIndex;i++) {
        LevelWavePathNode *aNode = ((LevelWavePathNode *)mNodeList.mData[i]);
        
        float aDiffX = aNode->mX - aPrev->mX;
        float aDiffY = aNode->mY - aPrev->mY;
        
        float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
        aTotalDist += aDist;
        
        if (aDist > 1.0f) {
            cPointList.Add(aNode->mX, aNode->mY);
        }
        
        aPrev = aNode;
    }
    
    if (aTotalDist <= 0) {
        printf("BAD PATH CHUNK [LEN = %f]\n", aTotalDist);
        return;
    }
    
    FSpline aSpline;
    for (int i=0;i<cPointList.mCount;i++) {
        aSpline.Add(cPointList.mX[i], cPointList.mY[i]);
    }
    
    
    //static FPointList cDumpList;
    //static FFloatList cDistList;
    
    cDumpList.Reset();
    cDistList.Reset();
    
    float aX = 0.0f;
    float aY = 0.0f;
    
    for (float aPos=0.0f;aPos<=aSpline.Max();aPos+=0.01f) {
        
        aSpline.Get(aPos, aX, aY);
        mRendumList.Add(aX, aY);
        
        cDumpList.Add(aX, aY);
    }
    
    float aDiffX = 0.0f;
    float aDiffY = 0.0f;
    float aDist = 0.0f;
    float aPrevX = cDumpList.mX[0];
    float aPrevY = cDumpList.mY[0];
    float aLength = 0.0f;
    for (int i=1;i<cDumpList.mCount;i++) {
        aX = cDumpList.mX[i];
        aY = cDumpList.mY[i];
        
        aDiffX = aX - aPrevX;
        aDiffY = aY - aPrevY;
        aDist = aDiffX * aDiffX + aDiffY * aDiffY;
        if (aDist > 0.01f) {
            aDist = sqrtf(aDist);
        }
        cDistList.Add(aDist);
        aLength += aDist;
        
        aPrevX = aX;
        aPrevY = aY;
    }
    
    printf("Total Length: %f\n", aLength);
    
    
}

void LevelWavePath::Dump(bool pDecel) {
    
}

void LevelWavePath::Draw() {
    if (mDidFinalize == false) {
        Finalize();
    }
    
    LevelWavePathNode *aPrev = NULL;
    LevelWavePathNode *aNode = NULL;
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    for (int i=0;i<mNodeList.mCount;i++) {
        aNode = ((LevelWavePathNode *)mNodeList.mData[i]);
        if (aPrev) {
            
            Graphics::SetColor(0.44f, 0.66f, 0.125f, 0.65f);
            Graphics::DrawLine(aPrev->mX, aPrev->mY, aNode->mX, aNode->mY, 2.5f);
            
            Graphics::SetColor(0.66f, 0.66f, 0.66f, 0.45f);
            Graphics::DrawLine(aPrev->mX, aPrev->mY, aNode->mX, aNode->mY, 1.5f);
            
            
        }
        
        aPrev = aNode;
    }
    
    
    for (int i=0;i<mNodeList.mCount;i++) {
        aNode = ((LevelWavePathNode *)mNodeList.mData[i]);

        if (aNode->mType == PATH_NODE_WAIT) {
            Graphics::SetColor(0.125f, 0.25f, 0.88f, 0.5f);
            Graphics::OutlineRect(aNode->mX - 25.0f, aNode->mY - 25.0f, 50.0f, 50.0f, 3.0f);
        }
        
        if (aNode->mType == PATH_NODE_STOP) {
            Graphics::SetColor(1.0f, 0.65f, 0.0f, 0.5f);
            Graphics::OutlineRect(aNode->mX - 15.0f, aNode->mY - 15.0f, 30.0f, 30.0f, 3.0f);
        }
        
        if (aNode->mType == PATH_NODE_MOVE) {
            Graphics::SetColor(0.125f, 0.88f, 0.125f, 0.6f);
            Graphics::OutlineRect(aNode->mX - 8.0f, aNode->mY - 8.0f, 16.0f, 16.0f, 3.0f);
        }
    }
    
    
    mRendumList.DrawPoints();
    
    /*
    //float aDistSpeed = (aDiffSpeedX * aDiffSpeedX) + (aDiffSpeedY * aDiffSpeedY);
    
    
    float aDecelerationX = 0.0f;
    float aDecelerationY = 0.0f;
    
    //float aDecelerationX = (pStartSpeed.mX * pStartSpeed.mX) / (2.0f * aDiffX);
    //float aDecelerationY = (pStartSpeed.mY * pStartSpeed.mY) / (2.0f * aDiffY);
    
    bool aFail = true;
    
    
    //a = (Vf*Vf - Vi*Vi)/(2 * d)
    
    if(aDist > 0.25f)
    {
        aDist = sqrtf(aDist);
        if(aDiffSquaredX >= 0.5f)
        {
            //aDecelerationX = (pEndSpeed.mX * pEndSpeed.mX - pStartSpeed.mX * pStartSpeed.mX) / (2.0f * aDist);
            //aDecelerationX = (pEndSpeed.mX * pEndSpeed.mX - pStartSpeed.mX * pStartSpeed.mX) / (2.0f * aDiffX);
            aDecelerationX = (aDiffSpeedX * aDiffSpeedX) / (2.0f * aDiffX);
            aDecelerationX = (aDiffSpeedX * aDiffSpeedX) / (2.0f * aDist);
            
            
            //aDecelerationX = (aDiffSpeedX * aDiffSpeedX) / (2.0f * aDiffX);
            
            aFail = false;
        }
        
        
        if(aDiffSquaredY >= 0.5f)
        {
            //aDecelerationY = (pEndSpeed.mY * pEndSpeed.mY - pStartSpeed.mY * pStartSpeed.mY) / (2.0f * aDist);
            //aDecelerationY = (pEndSpeed.mY * pEndSpeed.mY - pStartSpeed.mY * pStartSpeed.mY) / (2.0f * aDiffY);
            aDecelerationY = (aDiffSpeedY * aDiffSpeedY) / (2.0f * aDiffY);
            aDecelerationY = (aDiffSpeedY * aDiffSpeedY) / (2.0f * aDist);
            
            
            //aDecelerationY = (aDiffSpeedY * aDiffSpeedY) / (2.0f * aDiffY);
            
            
            aFail = false;
        }
    }
    */
    
}
