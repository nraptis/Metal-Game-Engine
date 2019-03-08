//
//  PhongConfiguration.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 2/27/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "PhongConfiguration.hpp"
#include "core_includes.h"

PhongConfiguration::PhongConfiguration() {
    
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
    
    mDirectionRotationPrimary = 34.064598;
    mDirectionRotationSecondary = 49.372952;
    
    mUniform.mLight.mAmbientIntensity = 0.35f;
    mUniform.mLight.mDiffuseIntensity = 0.65f;
    mUniform.mLight.mSpecularIntensity = 0.75f;
    mUniform.mLight.mRed = 1.000000;
    mUniform.mLight.mGreen = 1.000000;
    mUniform.mLight.mBlue = 1.000000;
    mUniform.mLight.mDirX = 0.364717;
    mUniform.mLight.mDirY = -0.758964;
    mUniform.mLight.mDirZ = 0.539402;
    mUniform.mLight.mShininess = 3.0f;
    
    //mUniform.mLight.mAmbientIntensity = 0.0f;
    //mUniform.mLight.mDiffuseIntensity = 0.0f;
    //mUniform.mLight.mSpecularIntensity = 1.000000;
    
}

PhongConfiguration::~PhongConfiguration() {
    
}

void PhongConfiguration::Print() {
    
    printf("**** BEGIN PhongConfiguration... ***\n");
    
    printf("mDirectionRotationPrimary = %f;\n", mDirectionRotationPrimary);
    printf("mDirectionRotationSecondary = %f;\n", mDirectionRotationSecondary);
    
    printf("mEyeRotationPrimary = %f;\n", mEyeRotationPrimary);
    printf("mEyeRotationSecondary = %f;\n", mEyeRotationSecondary);
    
    mUniform.Print();
    
    printf("**** END PhongConfiguration... ***\n");
    
}

void PhongConfiguration::Compute() {
    //
    FVec3 aDir = FVec3(0.0f, 0.0f, 1.0f);
    aDir = Rotate3D(aDir, FVec3(1.0f, 0.0f, 0.0f), mDirectionRotationSecondary);
    aDir = Rotate3D(aDir, FVec3(0.0f, 1.0f, 0.0f), mDirectionRotationPrimary);
    
    mUniform.mLight.mDirX = aDir.mX;
    mUniform.mLight.mDirY = aDir.mY;
    mUniform.mLight.mDirZ = aDir.mZ;
}



