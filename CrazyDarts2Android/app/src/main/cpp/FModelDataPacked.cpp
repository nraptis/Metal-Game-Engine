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

void FModelDataPacked::SetTexture(FTexture *pTexture) {
    SET_TEXTURE_BODY;
}

void FModelDataPacked::SetSprite(FSprite *pSprite, bool pFixUVW) {
    if (pSprite) {
        SetTexture(pSprite->mTexture);
        if (pFixUVW) {
            float aStartU = pSprite->mTextureRect.GetStartU();
            float aStartV = pSprite->mTextureRect.GetStartV();
            
            float aEndU = pSprite->mTextureRect.GetEndU();
            float aEndV = pSprite->mTextureRect.GetEndV();
            
            FitUVW(aStartU, aEndU, aStartV, aEndV);
        }
    }
}

void FModelDataPacked::FitUVW(float pStartU, float pEndU, float pStartV, float pEndV) {
    
    /*
    if ((pStartU == 0) && (pStartV == 0) && (pEndU == 1) && (pEndV == 1)) {
        return;
    }
    
    if (mUVWCount <= 0) return;
    
    float aSpanU = pEndU - pStartU;
    float aSpanV = pEndV - pStartV;
    
    int aIndex = 0;
    float aU, aV;
    for (int i=0;i<mUVWCount;i++) {
        
        
        aIndex = i * 3;
        
        aU = mUVW[aIndex];
        aV = mUVW[aIndex+1];
        
        aU = (pStartU + aSpanU * aU);
        aV = (pStartV + aSpanV * aV);
        
        mUVW[aIndex] = aU;
        mUVW[aIndex+1] = aV;
    }
    */
}

void FModelDataPacked::Save(const char *pFile) {
    FFile aFile;
    Save(&aFile);
    aFile.Save(pFile);
}

void FModelDataPacked::Save(FFile *pFile) {
    if (!pFile) return;
    
}

void FModelDataPacked::LoadData(FFile *pFile) {
    if(!pFile) return;
    
}

void FModelDataPacked::LoadData(const char *pFile) {
    FFile aFile;
    aFile.Load(pFile);
    LoadData(&aFile);
}

void FModelDataPacked::Load(const char *pFile) {
    
    FString aBasePath = pFile;
    aBasePath.RemoveExtension();
    
    FString aPath = aBasePath + FString(".3dp");
    
    LoadData(aPath.c());
    
    if (mDataCount == 0) {
        aPath = aBasePath + FString(".obj");
        LoadOBJ(aPath.c());
    }
    
    if (mDataCount == 0) {
        aPath = aBasePath + FString(".OBJ");
        LoadOBJ(aPath.c());
    }
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
        
        gPackedModelList.Add(this);
        
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


