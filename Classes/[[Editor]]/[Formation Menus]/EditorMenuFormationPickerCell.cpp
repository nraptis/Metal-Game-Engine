//
//  EditorMenuFormationPickerCell.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/2/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuFormationPickerCell.hpp"
#include "Game.hpp"

EditorMenuFormationPickerCell::EditorMenuFormationPickerCell(LevelFormation *pFormation) {
    mTouchCanceled = false;
    mFormation = pFormation;
    
    mGameScale = 1.0f;
    mGameRect.mWidth = 256.0f;
    mGameRect.mHeight = 256.0f;
    
    mDisplayDelay = 4;
    
    if (mFormation) {
        mFormation->EditorKillAllObjects();
        mFormation->Spawn(NULL);
        mFormation->EditorKillAllObjects();
    }
    
}

EditorMenuFormationPickerCell::~EditorMenuFormationPickerCell() {
    
}

void EditorMenuFormationPickerCell::Layout() {
    UIButton::Layout();
    
    
    if (mFormation != NULL) {
        
        
        mGameRect.mX = 0.0f;
        mGameRect.mY = 0.0f;
        
        mGameRect.mWidth = GAME_WIDTH;
        mGameRect.mHeight = GAME_HEIGHT;
        
        FRect aBounds = FRect(0.0f, 0.0f, mWidth, mHeight);
        
        mGameRect = FRect::FitAspectFit(aBounds, GAME_WIDTH, GAME_HEIGHT, 8.0f, mGameScale);
    }
}

void EditorMenuFormationPickerCell::Update() {
    if (mTouchCanceled) {
        mClickData = NULL;
        mTouchDown = false;
    }
    UIButton::Update();
    
    if (mFormation) {
        mFormation->Update(NULL);
    }
    
}

void EditorMenuFormationPickerCell::Draw() {
    
    //Some visual glitch, non-customer facing...
    //if (mDisplayDelay > 0) { mDisplayDelay--; return; }
    
    UIButton::Draw();
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    
    if (mFormation) {
        
        /*
        EnumList(LevelFormationTracer, aTracer, mFormation->mTracerList) {
            if (aTracer->mTracerNodeList.mCount > 0) {
                
                for (int i=0;i<aTracer->mTracerNodeList.mCount;i++) {
                    
                    LevelFormationTracerNode *aNode1 = (LevelFormationTracerNode *)aTracer->mTracerNodeList.FetchCircular(i - 1);
                    LevelFormationTracerNode *aNode2 = (LevelFormationTracerNode *)aTracer->mTracerNodeList.Fetch(i);
                    
                    float aX1 = (aNode1->mBaseX / 100.0f) * ((float)GAME_WIDTH) + (GAME_WIDTH / 2);
                    float aY1 = (aNode1->mBaseY / 100.0f) * ((float)GAME_HEIGHT) + (GAME_HEIGHT / 2);
                    
                    aX1 *= mGameScale; aY1 *= mGameScale;
                    
                    if (mFormation->mRotation != 0.0f) {
                        FVec2 aPoint;
                        aPoint.mX = aX1; aPoint.mY = aY1;
                        aPoint = PivotPoint(aPoint, mFormation->mRotation);
                        aX1 = aPoint.mX; aY1 = aPoint.mY;
                    }
                    
                    aX1 += mGameRect.mX; aY1 += mGameRect.mY;
                    
                    float aX2 = (aNode2->mBaseX / 100.0f) * ((float)GAME_WIDTH) + (GAME_WIDTH / 2);
                    float aY2 = (aNode2->mBaseY / 100.0f) * ((float)GAME_HEIGHT) + (GAME_HEIGHT / 2);
                    
                    aX2 *= mGameScale; aY2 *= mGameScale;
                    
                    if (mFormation->mRotation != 0.0f) {
                        FVec2 aPoint;
                        aPoint.mX = aX2; aPoint.mY = aY2;
                        aPoint = PivotPoint(aPoint, mFormation->mRotation);
                        aX2 = aPoint.mX; aY2 = aPoint.mY;
                    }
                    
                    aX2 += mGameRect.mX; aY2 += mGameRect.mY;
                    
                    Graphics::SetColor(0.65f, 0.65f, 0.65f, 1.0f);
                    Graphics::DrawLine(aX1, aY1, aX2, aY2, 1.0f);
                }
            }
        }
        */
        
        Graphics::SetColor(1.0f, 0.25f, 0.35f, 0.9f);
        EnumList(LevelFormationNode, aNode, mFormation->mSpawnNodeList) {
            
            float aX = (aNode->mBaseX / 100.0f) * ((float)GAME_WIDTH) + (GAME_WIDTH / 2);
            float aY = (aNode->mBaseY / 100.0f) * ((float)GAME_HEIGHT) + (GAME_HEIGHT / 2);
            
            aX *= mGameScale; aY *= mGameScale;
            
            if (mFormation != NULL) {
                if (mFormation->mRotation != 0.0f) {
                    FVec2 aPoint; aPoint.mX = aX; aPoint.mY = aY;
                    aPoint = PivotPoint(aPoint, mFormation->mRotation);
                    aX = aPoint.mX; aY = aPoint.mY;
                }
            }
            
            aX += mGameRect.mX; aY += mGameRect.mY;
            
            DrawFormationNode(aNode, aX, aY);
            
            
        }
        
        
        EnumList(LevelFormationTracer, aTracer, mFormation->mTracerList) {
            if (aTracer->mSpawnNodeList.mCount > 0) {
                
                for (int i=0;i<aTracer->mSpawnNodeList.mCount;i++) {
                    LevelFormationNode *aNode = (LevelFormationNode *)aTracer->mSpawnNodeList.Fetch(i);
                    
                    float aX = aNode->mX + (GAME_WIDTH / 2);
                    float aY = aNode->mY + (GAME_HEIGHT / 2);
                    aX *= mGameScale; aY *= mGameScale;
                    aX += mGameRect.mX; aY += mGameRect.mY;
                    
                    DrawFormationNode(aNode, aX, aY);
                    
                    
                }
            }
        }
        
    }
    
    
    Graphics::SetColor(1.0f, 0.85f, 0.85f, 0.2f);
    Graphics::OutlineRect(mGameRect.mX, mGameRect.mY, mGameRect.mWidth, mGameRect.mHeight, 0.5f);
    
    
    Graphics::SetColor();
    
    
}

void EditorMenuFormationPickerCell::DrawFormationNode(LevelFormationNode *pNode, float pX, float pY) {
    
    if (pNode == NULL) { return; }
    
    if (pNode->mObjectType == GAME_OBJECT_TYPE_BALLOON) {
        Graphics::SetColor(0.85f, 0.85f, 0.125f, 0.90f);
        Graphics::DrawRect(pX - 1.0f, pY - 1.0f, 3.0f, 3.0f);
    }
    
    if (pNode->mObjectType == GAME_OBJECT_TYPE_BRICKHEAD) {
        Graphics::SetColor(0.56f, 0.56f, 0.74f, 0.90f);
        Graphics::DrawRect(pX - 2.0f, pY - 2.0f, 5.0f, 5.0f);
    }
    
}


