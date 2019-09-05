//
//  FModelDataPacked.cpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/7/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#include "core_includes.h"
#include "FModelDataPacked.hpp"
#include "FApp.hpp"
#include "FTexture.hpp"
#include "FList.hpp"
#include "FFloatBufferCache.hpp"
#include "FIndexBufferCache.hpp"

FModelDataPacked::FModelDataPacked() {
    mIndex = NULL;
    mIndexCount = 0;
    
    mData = NULL;
    mDataCount = 0;
    
    mHasXYZ = false;
    mHasUVW = false;
    mHasNormals = false;
    mHasTangents = false;
    mHasUNormals = false;
    
    mUseUVW = true;
    mUseNormals = true;
    mUseTangents = false;
    mUseUNormals = false;
    
    mStride = 0;
    
    mBuffer = NULL;
}

FModelDataPacked::~FModelDataPacked() {
    Free();
}

void FModelDataPacked::Free() {
    DiscardBuffer();
    DiscardData();
    DiscardIndex();
}

void FModelDataPacked::DiscardBuffer() {
    delete mBuffer;
    mBuffer = NULL;
}

void FModelDataPacked::DiscardData() {
    delete [] mData;
    mData = NULL;
    mDataCount = 0;
    mStride = 0;
    mHasXYZ = false;
    mHasUVW = false;
    mHasNormals = false;
    mHasTangents = false;
    mHasUNormals = false;
}

void FModelDataPacked::DiscardIndex() {
    delete [] mIndex;
    mIndex = NULL;
    mIndexCount = 0;
}

void FModelDataPacked::FitUVW(float pStartU, float pEndU, float pStartV, float pEndV) {
    
    if ((pStartU <= 0.0f) && (pStartV <= 0.0f) && (pEndU >= 1.0f) && (pEndV >= 1.0f)) { return; }
    
    if (mHasUVW == false) { return; }
    if (mDataCount <= 0) { return; }
    
    float aSpanU = pEndU - pStartU;
    float aSpanV = pEndV - pStartV;
    
    int aStartIndex = 0;
    if (mHasXYZ) { aStartIndex += 3; }
    
    int aStride = 0;
    if (mHasXYZ) { aStride += 3; }
    if (mHasUVW) { aStride += 3; }
    if (mHasNormals) { aStride += 3; }
    if (mHasTangents) { aStride += 3; }
    if (mHasUNormals) { aStride += 3; }
    
    int aIndex = aStartIndex;
    
    float aU = 0.0f, aV = 0.0f;
    while (aIndex < mDataCount) {
        aU = mData[aIndex];
        aV = mData[aIndex + 1];
        aU = (pStartU + aSpanU * aU);
        aV = (pStartV + aSpanV * aV);
        mData[aIndex] = aU;
        mData[aIndex + 1] = aV;
        aIndex += aStride;
    }
}

void FModelDataPacked::Save(const char *pFile) {
    FFile aFile;
    Save(&aFile);
    aFile.Save(pFile);
}

void FModelDataPacked::Save(FFile *pFile) {
    if (!pFile) { return; }
    
    //We start with 8 32 bit words.
    pFile->WriteInt(mHasXYZ);
    pFile->WriteInt(mHasUVW);
    pFile->WriteInt(mHasNormals);
    pFile->WriteInt(mHasTangents);
    pFile->WriteInt(mHasUNormals);
    pFile->WriteInt(0);
    pFile->WriteInt(0);
    pFile->WriteInt(0);
    
    //Now the data count.
    pFile->WriteInt(mDataCount);
    
    //Now the data.
    for (int i=0;i<mDataCount;i++) {
        pFile->WriteFloat(mData[i]);
    }
    
    //Now the index count.
    pFile->WriteInt(mIndexCount);
    
    //Now the indices.
    for (int i=0;i<mIndexCount;i++) {
        pFile->WriteShort(mIndex[i]);
    }
}

void FModelDataPacked::LoadData(FFile *pFile, FSprite *pSprite) {
    
    Free();
    
    if (pFile == NULL) { return; }
    
    mFileName = pFile->mFileName.c();
    mFileName.RemovePath();
    
    //We start with 8 32 bit words.
    mHasXYZ = pFile->ReadInt();
    mHasUVW = pFile->ReadInt();
    mHasNormals = pFile->ReadInt();
    mHasTangents = pFile->ReadInt();
    
    mHasUNormals = pFile->ReadInt();
    pFile->ReadInt();
    pFile->ReadInt();
    pFile->ReadInt();
    
    
    //Now the data count.
    mDataCount = pFile->ReadInt();
    
    //Now the data.
    mData = new float[mDataCount];
    for (int i=0;i<mDataCount;i++) {
        mData[i] = pFile->ReadFloat();
    }

    //Now the index count.
    mIndexCount = pFile->ReadInt();
    
    mIndex = new GFX_MODEL_INDEX_TYPE[mIndexCount+1];
    for (int i=0;i<mIndexCount;i++) {
        mIndex[i] = pFile->ReadShort();
    }
    
    if (pSprite != NULL) {
        float aStartU = pSprite->mTextureRect.GetStartU();
        float aStartV = pSprite->mTextureRect.GetStartV();
        
        float aEndU = pSprite->mTextureRect.GetEndU();
        float aEndV = pSprite->mTextureRect.GetEndV();
        
        FitUVW(aStartU, aEndU, aStartV, aEndV);
    }
    
    mBuffer = new FBuffer(sizeof(float) * mDataCount, BUFFER_TYPE_ARRAY);
    
    WriteBuffers();
}

void FModelDataPacked::LoadData(const char *pFile, FSprite *pSprite) {
    FFile aFile;
    const char *aResourcePath = gRes.GetResourcePathOfType(pFile, RESOURCE_TYPE_MODEL_DATA);
    while ((aResourcePath != NULL)) {
        aFile.LoadDirect((char *)aResourcePath);
        if (aFile.mLength > 0) { break; }
        aResourcePath = gRes.GetNextResourcePath();
    }
    
    if (aFile.mLength == 0) {
        aFile.Load(pFile);
    }
    
    LoadData(&aFile, pSprite);
}

void FModelDataPacked::LoadOBJ(FFile *pFile) {
    Free();
    
    mFileName = pFile->mFileName.c();
    mFileName.RemovePath();
    
    FModelData aTemp;
    FModelDataIndexed aData;
    aTemp.LoadOBJ(pFile);
    FModelDataOptimizer *aOptimizer = new FModelDataOptimizer();
    aOptimizer->Convert(&aTemp, &aData);
    delete aOptimizer;
    aOptimizer = NULL;
    
    LoadIndexedModel(&aData);
}

void FModelDataPacked::LoadOBJ(const char *pFile) {
    FFile aFile;
    const char *aResourcePath = gRes.GetResourcePathOfType(pFile, RESOURCE_TYPE_MODEL_OBJ);
    while ((aResourcePath != NULL)) {
        aFile.LoadDirect((char *)aResourcePath);
        if (aFile.mLength > 0) { break; }
        aResourcePath = gRes.GetNextResourcePath();
    }
    if (aFile.mLength == 0) {
        aFile.Load(pFile);
    }
    LoadOBJ(&aFile);
}


void FModelDataPacked::LoadIndexedModel(FModelDataIndexed *pModel) {
    
    Free();
    if (pModel == NULL) { return; }
    
    if (pModel->mXYZCount > 0) {
        mHasXYZ = true;
        mStride = 3;
        int aNodeCount = pModel->mXYZCount;
        
        if (pModel->mUVWCount > 0 && mUseUVW) {
            mHasUVW = true;
            mStride += 3;
        }
        
        if (pModel->mNormalCount > 0 && mUseNormals) {
            mHasNormals = true;
            mStride += 3;
        }
        
        mDataCount = mStride * aNodeCount;
        mData = new float[mDataCount];
        
        int aWriteIndex = 0;
        for (int i=0;i<aNodeCount;i++) {
            int aIndex = i * 3;
            if (mHasXYZ) {
                mData[aWriteIndex++] = pModel->mXYZ[aIndex + 0];
                mData[aWriteIndex++] = pModel->mXYZ[aIndex + 1];
                mData[aWriteIndex++] = pModel->mXYZ[aIndex + 2];
            }
            if (mHasUVW) {
                mData[aWriteIndex++] = pModel->mUVW[aIndex + 0];
                mData[aWriteIndex++] = pModel->mUVW[aIndex + 1];
                mData[aWriteIndex++] = pModel->mUVW[aIndex + 2];
            }
            if (mHasNormals) {
                mData[aWriteIndex++] = pModel->mNormal[aIndex + 0];
                mData[aWriteIndex++] = pModel->mNormal[aIndex + 1];
                mData[aWriteIndex++] = pModel->mNormal[aIndex + 2];
            }
        }
        
        mBuffer = new FBuffer(sizeof(float) * mDataCount, BUFFER_TYPE_ARRAY);
        
        WriteBuffers();
    }
    
    if (pModel->mIndexCount > 0) {
        mIndexCount = pModel->mIndexCount;
        mIndex = new GFX_MODEL_INDEX_TYPE[mIndexCount+1];
        for (int i=0;i<mIndexCount;i++) {
            mIndex[i] = pModel->mIndex[i];
        }
    }
    
}


void FModelDataPacked::WriteBuffers() {
    Graphics::BufferArrayWrite(mBuffer, mData, sizeof(float) * mDataCount);
}

