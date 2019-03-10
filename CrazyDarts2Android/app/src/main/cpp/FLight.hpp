//
//  FLight.hpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/15/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#ifndef FLight_hpp
#define FLight_hpp

class FLight {
public:
    inline FLight(float pIntensity) {
        mIntensity = pIntensity;
    }
    FLight();
    float mIntensity;
};

class FLightAmbient {
public:
    FLightAmbient();
    
    float mRed;
    float mGreen;
    float mBlue;
    
    float mAmbientIntensity;
};

class FLightDiffuse {
public:
    
    FLightDiffuse();

    float mRed;
    float mGreen;
    float mBlue;
    
    float mAmbientIntensity;
    float mDiffuseIntensity;
    
    float mDirX;
    float mDirY;
    float mDirZ;
};

class FLightPhong {
public:
    
    
    inline FLightPhong(float pRed, float pGreen, float pBlue) {
        mRed = pRed;
        mGreen = pGreen;
        mBlue = pBlue;
        
        mAmbientIntensity = 0.0f;
        mDiffuseIntensity = 0.25f;
        mSpecularIntensity = 0.75f;
        
        mDirX = 0.0f;
        mDirY = 0.0f;
        mDirZ = -1.0f;
        
        mShininess = 32.0f;
    }
    
    inline FLightPhong(float pRed, float pGreen, float pBlue, float mAmbientIntensity, float mDiffuseIntensity, float mSpecularIntensity, float pDirX, float pDirY, float pDirZ, float pShininess, float pEyeDirX, float pEyeDirY, float pEyeDirZ) {
        mRed = pRed;
        mGreen = pGreen;
        mBlue = pBlue;
        
        mAmbientIntensity = mAmbientIntensity;
        mDiffuseIntensity = mDiffuseIntensity;
        mSpecularIntensity = mSpecularIntensity;
        
        mDirX = 0.0f;
        mDirY = 0.0f;
        mDirZ = -1.0f;
        
        mShininess = 32.0f;
    }
    
    FLightPhong();
    
    float mRed;
    float mGreen;
    float mBlue;
    
    float mAmbientIntensity;
    float mDiffuseIntensity;
    float mSpecularIntensity;
    
    float mDirX;
    float mDirY;
    float mDirZ;
    
    float mShininess;
};


#endif
