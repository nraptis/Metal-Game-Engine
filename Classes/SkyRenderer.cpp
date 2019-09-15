//
//  SkyRenderer.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 9/14/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "SkyRenderer.hpp"


SkyRenderer::SkyRenderer() {
    
    mGrid.Size(5, 8);
    
}

SkyRenderer::~SkyRenderer() {
    
}


void SkyRenderer::Refresh(float pTop, float pRight, float pBottom, float pLeft, float pPadding) {
 
    mGrid.Clear();
    mGrid.Size(5, 8);
    
    
    int aGridWidth = mGrid.mWidth;
    int aGridHeight = mGrid.mHeight;
    
    float aWidth = (pRight - pLeft);
    float aHeight = (pBottom - pTop);
    
    float aLeft = pLeft - pPadding;
    for (int i=0;i<aGridWidth;i++) {
        for (int n=0;n<aGridHeight;n++) {
            
            float aPercentX = ((float)i) / ((float)(aGridWidth - 1));
            float aPercentY = ((float)n) / ((float)(aGridHeight - 1));
            
            float aX = pLeft + (aWidth * aPercentX);
            float aY = pTop + (aHeight * aPercentY);
            
            printf("Sky[%d][%d] = (%f | %f)\n", i, n, aX, aY);
            
            mGrid.SetXYZ(i, n, aX, aY, 0.0f);
            mGrid.SetRGBA(i, n, gRand.F(), gRand.F(), gRand.F(), 0.5f + gRand.F(0.5f));
            
        }
        
    }
    
    //mDrawQuad.Siz
    
    //mDrawQuad
    
}

void SkyRenderer::Update() {
    
}

void SkyRenderer::Draw() {
    
    
    
    //Graphics::PipelineStateSetShape3DAlphaBlending();
    
    Graphics::PipelineStateSetShapeNodeNoBlending();
    Graphics::SetColor();
    mGrid.Draw();
    
}


