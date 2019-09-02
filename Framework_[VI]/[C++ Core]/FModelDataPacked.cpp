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

FFloatBufferCacheByteAligned256 cModelVertexCache;
FIndexBufferCache cModelIndexCache;

FModelDataPacked::FModelDataPacked() {
    mIndex = 0;
    mIndexCount = 0;
    
    mData = 0;
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
    
    
    //mBufferIndex = -1;
    //mBufferIndexOffset = 0;
    
}

FModelDataPacked::~FModelDataPacked() {
    Free();
}

void FModelDataPacked::Free() {
    delete mBuffer;
    mBuffer = NULL;
    
    delete [] mIndex;
    mIndex = 0;
    mIndexCount = 0;
    
    delete [] mData;
    mData = 0;
    mDataCount = 0;
    
    mStride = 0;
    
    mHasXYZ = false;
    mHasUVW = false;
    mHasNormals = false;
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
    for (int i=0;i<mDataCount;i++) {
        pFile->WriteShort(mIndex[i]);
    }
}

void FModelDataPacked::LoadData(FFile *pFile, FSprite *pSprite) {
    
    Free();
    if (!pFile) { return; }
    
    if (pFile->mLength < 10) { return; }
    
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
    aFile.Load(pFile);
    LoadData(&aFile, pSprite);
}

void FModelDataPacked::LoadOBJ(FFile *pFile) {
    Free();
    FModelData aTemp;
    FModelDataIndexed aData;
    aTemp.LoadOBJ(pFile);
    FModelDataOptimizer *aOptimizer = new FModelDataOptimizer();
    aOptimizer->Convert(&aTemp, &aData);
    delete aOptimizer;
    aOptimizer = NULL;
    
    if (aData.mIndexCount > 0 && aData.mXYZCount > 0) {
        mHasXYZ = true;
        mStride = 3;
        int aNodeCount = aData.mXYZCount;
        
        if (aData.mUVWCount > 0 && mUseUVW) {
            mHasUVW = true;
            mStride += 3;
        }
        
        if (aData.mNormalCount > 0 && mUseNormals) {
            mHasNormals = true;
            mStride += 3;
        }
        
        mIndexCount = aData.mIndexCount;
        mIndex = new GFX_MODEL_INDEX_TYPE[mIndexCount+1];
        for (int i=0;i<mIndexCount;i++) {
            mIndex[i] = aData.mIndex[i];
        }
        
        mDataCount = mStride * aNodeCount;
        mData = new float[mDataCount];
        
        int aWriteIndex = 0;
        for (int i=0;i<aNodeCount;i++) {
            int aIndex = i * 3;
            if (mHasXYZ) {
                mData[aWriteIndex++] = aData.mXYZ[aIndex + 0];
                mData[aWriteIndex++] = aData.mXYZ[aIndex + 1];
                mData[aWriteIndex++] = aData.mXYZ[aIndex + 2];
            }
            if (mHasUVW) {
                mData[aWriteIndex++] = aData.mUVW[aIndex + 0];
                mData[aWriteIndex++] = aData.mUVW[aIndex + 1];
                mData[aWriteIndex++] = aData.mUVW[aIndex + 2];
            }
            if (mHasNormals) {
                mData[aWriteIndex++] = aData.mNormal[aIndex + 0];
                mData[aWriteIndex++] = aData.mNormal[aIndex + 1];
                mData[aWriteIndex++] = aData.mNormal[aIndex + 2];
            }
        }
        
        mBuffer = new FBuffer(sizeof(float) * mDataCount, BUFFER_TYPE_ARRAY);
        
        WriteBuffers();
        //mBufferIndex = Graphics::BufferElementGenerate(sizeof(GFX_MODEL_INDEX_TYPE) * mIndexCount);
        
        /*
        cModelVertexCache.Get(sizeof(float) * mDataCount);
        if (cModelVertexCache.mResult.mSuccess) {
            mBufferVertex = cModelVertexCache.mResult.mBufferIndex;
            mBufferVertexOffset = cModelVertexCache.mResult.mBufferOffset;
            //
            Graphics::BufferArrayWrite(mBufferVertex, mData, mBufferVertexOffset, sizeof(float) * mDataCount);
        } else {
            Log("Unable to get vertex buffer space for model...\n");
            mBufferVertex = -1;
            mBufferVertexOffset = -1;
        }
        */
        
        /*
        cModelIndexCache.Get(sizeof(GFX_MODEL_INDEX_TYPE) * mIndexCount);
        if (cModelIndexCache.mResult.mSuccess) {
            mBufferIndex = cModelIndexCache.mResult.mBufferIndex;
            mBufferIndexOffset = cModelIndexCache.mResult.mBufferOffset;
            //
            Graphics::BufferElementWrite(mBufferIndex, mIndex, mBufferIndexOffset, sizeof(GFX_MODEL_INDEX_TYPE) * mIndexCount);
        } else {
            Log("Unable to get index buffer space for model...\n");
            mBufferIndex = -1;
            mBufferIndexOffset = -1;
        }
        */
        
        
        //Log("Loaded Packed Model [%s] VB[i:%d s:%lu o:%d] IB[i:%d s:%d o:%d]\n", mFileName.c(), mBufferVertex, mDataCount * sizeof(float), mBufferVertexOffset, mBufferIndex, mIndexCount * sizeof(GFX_MODEL_INDEX_TYPE), mBufferIndexOffset);
    }
}

void FModelDataPacked::LoadOBJ(const char *pFile) {
    
    mFileName = pFile;
    mFileName.RemovePath();
    mFileName.RemoveExtension();
    
    FFile aFile;
    aFile.Load(pFile);
    LoadOBJ(&aFile);
}

void FModelDataPacked::WriteBuffers() {
    Graphics::BufferArrayWrite(mBuffer, mData, sizeof(float) * mDataCount);
}

void FModelDataPacked::Draw() {
    
    
}

void FModelDataPacked::Draw(FTexture *pTexture) {
    
}

void FModelDataPacked::BindBuffers() {
    
}

void FModelDataPacked::KillBuffers() {
    
    
}


