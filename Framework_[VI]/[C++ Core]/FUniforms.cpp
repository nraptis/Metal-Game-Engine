//
//  FUniforms.cpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/22/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#include "FUniforms.hpp"
#include "os_core_graphics.h"

FUniforms::FUniforms() {
    
}

FUniforms::~FUniforms() {
    
}

unsigned int FUniforms::GetVertexSize() {
    return sizeof(float) * 32;
}

unsigned int FUniforms::GetFragmentSize() {
    return sizeof(float) * 4;
}

void FUniforms::WriteVertexToBuffer(void *pData, unsigned int pOffset) {
    char *aContents = (char *)pData;
    char *aPtr = &aContents[pOffset];
    static int aMatrixSize = sizeof(float) * 16;
    memcpy(aPtr, mProjection.m, aMatrixSize);
    aPtr = &(aPtr[aMatrixSize]);
    memcpy(aPtr, mModelView.m, aMatrixSize);
}

void FUniforms::WriteFragmentToBuffer(void *pData, unsigned int pOffset) {
    char *aContents = (char *)pData;
    char *aPtr = &aContents[pOffset];
    static int aSize = sizeof(mColor);
    memcpy(aPtr, &mColor, aSize);
}

FUniformsLightAmbient::FUniformsLightAmbient() {
    
}

FUniformsLightAmbient::~FUniformsLightAmbient() {
    
}

unsigned int FUniformsLightAmbient::GetVertexSize() {
    int aSize = FUniforms::GetVertexSize();
    return aSize;
}

unsigned int FUniformsLightAmbient::GetFragmentSize() {
    int aSize = FUniforms::GetFragmentSize();
    aSize += sizeof(mLight);
    return aSize;
}

void FUniformsLightAmbient::WriteVertexToBuffer(void *pData, unsigned int pOffset) {
    FUniforms::WriteVertexToBuffer(pData, pOffset);
}

void FUniformsLightAmbient::WriteFragmentToBuffer(void *pData, unsigned int pOffset) {
    char *aContents = (char *)pData;
    char *aPtr = &aContents[pOffset];
    static int aColorSize = sizeof(mColor);
    static int aLightSize = sizeof(mLight);
    memcpy(aPtr, &mColor, aColorSize);
    aPtr = &(aPtr[aColorSize]);
    memcpy(aPtr, &mLight, aLightSize);
}



FUniformsLightAmbientDiffuse::FUniformsLightAmbientDiffuse() {
    
}

FUniformsLightAmbientDiffuse::~FUniformsLightAmbientDiffuse() {
    
}

unsigned int FUniformsLightAmbientDiffuse::GetVertexSize() {
    int aSize = FUniformsLightAmbient::GetVertexSize();
    return aSize;
}

unsigned int FUniformsLightAmbientDiffuse::GetFragmentSize() {
    int aSize = FUniforms::GetFragmentSize();
    aSize += sizeof(mLight);
    return aSize;
}

void FUniformsLightAmbientDiffuse::WriteVertexToBuffer(void *pData, unsigned int pOffset) {
    FUniformsLightAmbient::WriteVertexToBuffer(pData, pOffset);
}

void FUniformsLightAmbientDiffuse::WriteFragmentToBuffer(void *pData, unsigned int pOffset) {
    char *aContents = (char *)pData;
    char *aPtr = &aContents[pOffset];
    static int aColorSize = sizeof(mColor);
    static int aLightSize = sizeof(mLight);
    
    memcpy(aPtr, &mColor, aColorSize);
    aPtr = &(aPtr[aColorSize]);
    memcpy(aPtr, &mLight, aLightSize);
}


void FUniformsLightAmbientDiffuse::Print() {
    
    /*
    printf("*** BEGIN FUniformsLightAmbientDiffuse ***\n");
    
    printf("mDiffuse.mRed = %f;\n", mDiffuse.mRed);
    printf("mDiffuse.mGreen = %f;\n", mDiffuse.mGreen);
    printf("mDiffuse.mBlue = %f;\n", mDiffuse.mBlue);
    printf("mDiffuse.mIntensity = %f;\n", mDiffuse.mIntensity);
    printf("***\n");
    printf("mDiffuse.mDirX = %f;\n", mDiffuse.mDirX);
    printf("mDiffuse.mDirY = %f;\n", mDiffuse.mDirY);
    printf("mDiffuse.mDirZ = %f;\n", mDiffuse.mDirZ);
    
    printf("*** END FUniformsLightAmbientDiffuse ***\n");
    */
}




FUniformsLightPhong::FUniformsLightPhong() {
    
}

FUniformsLightPhong::~FUniformsLightPhong() {
    
}

unsigned int FUniformsLightPhong::GetVertexSize() {
    int aSize = FUniforms::GetVertexSize();
    return aSize;
}

unsigned int FUniformsLightPhong::GetFragmentSize() {
    int aSize = FUniforms::GetFragmentSize();
    aSize += sizeof(mLight);
    return aSize;
}

void FUniformsLightPhong::WriteVertexToBuffer(void *pData, unsigned int pOffset) {
    FUniforms::WriteVertexToBuffer(pData, pOffset);
}

void FUniformsLightPhong::WriteFragmentToBuffer(void *pData, unsigned int pOffset) {
    char *aContents = (char *)pData;
    char *aPtr = &aContents[pOffset];
    static int aColorSize = sizeof(mColor);
    static int aLightSize = sizeof(mLight);
    
    memcpy(aPtr, &mColor, aColorSize);
    aPtr = &(aPtr[aColorSize]);
    
    memcpy(aPtr, &mLight, aLightSize);
    //aPtr = &(aPtr[aLightSize]);
    
    //memcpy(aPtr, &mDiffuse, aDiffuseSize);
    
}


void FUniformsLightPhong::Print() {
    
    
    
    printf("*** BEGIN FUniformsLightPhong ***\n");
    
    
    printf("mLight.mAmbientIntensity = %f;\n", mLight.mAmbientIntensity);
    printf("mLight.mDiffuseIntensity = %f;\n", mLight.mDiffuseIntensity);
    printf("mLight.mSpecularIntensity = %f;\n", mLight.mSpecularIntensity);
    
    printf("mLight.mRed = %f;\n", mLight.mRed);
    printf("mLight.mGreen = %f;\n", mLight.mGreen);
    printf("mLight.mBlue = %f;\n", mLight.mBlue);
    
    
    printf("mLight.mDirX = %f;\n", mLight.mDirX);
    printf("mLight.mDirY = %f;\n", mLight.mDirY);
    printf("mLight.mDirZ = %f;\n", mLight.mDirZ);

    printf("mLight.mShininess = %f;\n", mLight.mShininess);
    
    printf("******* For Uni **********\n");
    
    printf("mUniform.mLight.mAmbientIntensity = %f;\n", mLight.mAmbientIntensity);
    printf("mUniform.mLight.mDiffuseIntensity = %f;\n", mLight.mDiffuseIntensity);
    printf("mUniform.mLight.mSpecularIntensity = %f;\n", mLight.mSpecularIntensity);
    
    printf("mUniform.mLight.mRed = %f;\n", mLight.mRed);
    printf("mUniform.mLight.mGreen = %f;\n", mLight.mGreen);
    printf("mUniform.mLight.mBlue = %f;\n", mLight.mBlue);
    
    printf("mUniform.mLight.mDirX = %f;\n", mLight.mDirX);
    printf("mUniform.mLight.mDirY = %f;\n", mLight.mDirY);
    printf("mUniform.mLight.mDirZ = %f;\n", mLight.mDirZ);
    
    printf("mUniform.mLight.mShininess = %f;\n", mLight.mShininess);
    
    printf("*** END FUniformsLightPhong ***\n");
}
