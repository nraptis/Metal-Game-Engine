//
//  SpotLightSimpleConfiguration.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/24/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "SpotLightSimpleConfiguration.hpp"

//
//  SpotLightSimpleConfiguration.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 2/27/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "SpotLightSimpleConfiguration.hpp"
#include "core_includes.h"

SpotLightSimpleConfiguration::SpotLightSimpleConfiguration() {
    
    /*
     mDirectionRotationPrimary = 0.0f;
     mDirectionRotationSecondary = 0.0f;
     
     mEyeRotationPrimary = 0.0f;
     mEyeRotationSecondary = 0.0f;
     
     mDirectionRotationPrimary = 251.250092;
     mDirectionRotationSecondary = 103.125076;
     mEyeRotationPrimary = 0.000000;
     mEyeRotationSecondary = 0.000000;
     
     mUniform.mLight.mAmbientIntensity = 0.35f;
     mUniform.mLight.mDiffuseIntensity = 0.65f;
     
     mUniform.mLight.mSpecularIntensity = 1.0f;
     mUniform.mLight.mRed = 1.000000;
     mUniform.mLight.mGreen = 1.000000;
     mUniform.mLight.mBlue = 1.000000;
     mUniform.mLight.mDirX = 0.215027;
     mUniform.mLight.mDirY = -0.973877;
     mUniform.mLight.mDirZ = 0.072991;
     mUniform.mLight.mShininess = 4.125f;
     */
    
    mDirectionRotationPrimary = 30.0f;
    mDirectionRotationSecondary = 225.0f;

    
    mSpotlightX = round(mUniform.mLight.mSpotlightX);
    mSpotlightY = round(mUniform.mLight.mSpotlightY);
    mSpotlightZ = round(mUniform.mLight.mSpotlightZ);
    
    
}

SpotLightSimpleConfiguration::~SpotLightSimpleConfiguration() {
    
}

void SpotLightSimpleConfiguration::Print() {
    
    Log("**** BEGIN SpotLightSimpleConfiguration... ***\n");
    
    Log("mDirectionRotationPrimary = %f;\n", mDirectionRotationPrimary);
    Log("mDirectionRotationSecondary = %f;\n", mDirectionRotationSecondary);
    
    mUniform.Print();
    
    Log("**** END SpotLightSimpleConfiguration... ***\n");
    
}

void SpotLightSimpleConfiguration::Compute() {
    //
    FVec3 aDir = FVec3(0.0f, 0.0f, 1.0f);
    aDir = Rotate3D(aDir, FVec3(1.0f, 0.0f, 0.0f), mDirectionRotationSecondary);
    aDir = Rotate3D(aDir, FVec3(0.0f, 1.0f, 0.0f), mDirectionRotationPrimary);
    
    mUniform.mLight.mDirX = aDir.mX;
    mUniform.mLight.mDirY = aDir.mY;
    mUniform.mLight.mDirZ = aDir.mZ;
    
    mUniform.mLight.mSpotlightX = (float)(mSpotlightX);
    mUniform.mLight.mSpotlightY = (float)(mSpotlightY);
    mUniform.mLight.mSpotlightZ = (float)(mSpotlightZ);
}



