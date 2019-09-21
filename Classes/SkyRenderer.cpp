//
//  SkyRenderer.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 9/14/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "SkyRenderer.hpp"


SkyRenderer::SkyRenderer() {
    mGrid.Size(100, 6);
}

SkyRenderer::~SkyRenderer() {
    
}

//b2dce1
//aedce3
//8ee1f5
//54d4f5
//3abceb
//37baea

void SkyRenderer::Refresh(float pTop, float pRight, float pBottom, float pLeft, float pPadding) {
 
    
    pTop -= pPadding;
    pBottom += pPadding;
    
    pRight += pPadding;
    pLeft -= pPadding;
    
    //FColor("b2dce1").Print("b2dce1");
    //FColor("aedce3").Print("aedce3");
    //FColor("8ee1f5").Print("8ee1f5");
    //FColor("54d4f5").Print("54d4f5");
    //FColor("3abceb").Print("3abceb");
    //FColor("37baea").Print("37baea");
    
    int aGridWidth = mGrid.mWidth;
    int aGridHeight = mGrid.mHeight;
    
    float aWidth = (pRight - pLeft);
    float aHeight = (pBottom - pTop);
    
    
    float aPercentY[6];
    
    aPercentY[0] = 0.0f;
    aPercentY[1] = 0.125f;
    aPercentY[2] = 0.265f;
    aPercentY[3] = 1.0f - aPercentY[2];
    aPercentY[4] = 1.0f - aPercentY[1];
    aPercentY[5] = 1.0f;
    
    
    
    
    
    
    
    float aLeft = pLeft - pPadding;
    for (int i=0;i<aGridWidth;i++) {
        
        float aPercentX = ((float)i) / ((float)(aGridWidth - 1));
        
        for (int n=0;n<aGridHeight;n++) {
            
            
            float aX = pLeft + (aWidth * aPercentX);
            float aY = pTop + (aHeight * aPercentY[n]);
            
            //printf("Sky[%d][%d] = (%f | %f)\n", i, n, aX, aY);
            
            
            mGrid.SetXYZ(i, n, aX, aY, 0.0f);
            //mGrid.SetRGBA(i, n, gRand.F(), gRand.F(), gRand.F(), 0.5f + gRand.F(0.5f));
            
        }
        
    }
    
    float aSeedColorR[6];
    float aSeedColorG[6];
    float aSeedColorB[6];
    
    aSeedColorR[0] = 0.698039f;
    aSeedColorR[1] = 0.682353f;
    aSeedColorR[2] = 0.556863f;
    aSeedColorR[3] = 0.329412f;
    aSeedColorR[4] = 0.227451f;
    aSeedColorR[5] = 0.215686f;
    
    
    aSeedColorG[0] = 0.862745f;
    aSeedColorG[1] = 0.862745f;
    aSeedColorG[2] = 0.882353f;
    aSeedColorG[3] = 0.831373f;
    aSeedColorG[4] = 0.737255f;
    aSeedColorG[5] = 0.729412f;
    
    aSeedColorB[0] = 0.882353f;
    aSeedColorB[1] = 0.890196f;
    aSeedColorB[2] = 0.960784f;
    aSeedColorB[3] = 0.960784f;
    aSeedColorB[4] = 0.921569f;
    aSeedColorB[5] = 0.917647f;
    
    for (int i=0;i<6;i++) {
        aSeedColorR[i] *= 0.50f;
        aSeedColorG[i] *= 0.55f;
        aSeedColorB[i] *= 0.65f;
    }
    
    for (int n=0;n<aGridHeight;n++) {
        for (int i=0;i<aGridWidth;i++) {
            
            mGrid.SetRGBA(i, n, aSeedColorR[n], aSeedColorG[n], aSeedColorB[n], 1.0f);
            
            
        }
    }
    
    
    //[b2dce1] FColor(, , , 0.698039f);
    //[aedce3] FColor(, , , 0.682353f);
    //[8ee1f5] FColor(, , , 0.556863f);
    //[54d4f5] FColor(, , , 0.329412f);
    //[3abceb] FColor(, , , 0.227451f);
    //[37baea] FColor(, , , 0.215686f);
    
    
    //mDrawQuad.Siz
    
    //mDrawQuad
    
}

void SkyRenderer::Update() {
    
}

void SkyRenderer::Draw() {
    mGrid.Draw();
}


