//
//  FModelDataSequence.cpp
//  DoomKnights
//
//  Created by Nick Raptis on 1/20/12.
//  Copyright (c) 2012 Nick Raptis. All rights reserved.
//

#include "FModelDataSequence.h"
#include "FModelData.h"
#include "FFile.hpp"
#include "FTexture.hpp"

FModelDataSequence::FModelDataSequence() {
    mTexture = 0;
    mParent = 0;
    mSize = 0;
    mCount = 0;
    mData = 0;
    mDisableNormal = false;
    mDisableUVW = false;
    mDisableIndices = false;
    mUsesBaseXYZ = false;
    mUsesBaseNormal = false;
    mUsesBaseUVW = true;
}

FModelDataSequence::~FModelDataSequence() {
    Free();
}

void FModelDataSequence::Add(FModelDataIndexed *pData) {
    if (pData == 0) return;
    if (mCount <= mSize) {
        mSize = mCount + mCount / 2 + 1;
        
        FModelDataIndexed **aData = new FModelDataIndexed*[mSize];
        
        for(int i=mCount;i<mSize;i++)aData[i]=0;
        for(int i=0;i<mCount;i++)aData[i]=mData[i];
        
        delete[]mData;
        
        mData=aData;
    }
    
    mData[mCount] = pData;
    mCount++;
    
}


void FModelDataSequence::Load(const char *pFileBase, int pStartIndex, int pEndIndex, const char *pFileReferenceName)
{
    Free();
    
    FModelDataOptimizer *aOptimizer = new FModelDataOptimizer();
    
    FModelData *aBaseModel = new FModelData(); //LoadOBJ(pFileReferenceName);
    aBaseModel->LoadOBJ(pFileReferenceName);
    
    bool aDidFindBase = false;
    
    FList aFileList;
    
    FFileSequence aSequence;
    aSequence.LoadSequence(pFileBase, "obj", aFileList, pStartIndex, pEndIndex);
    
    //FFileSequence::LoadSequence(pFileBase, "obj", aFileFList, pStartIndex, pEndIndex);
    
    //EnumList(FString, aString, aFileFList)
    //{
    //    FModelDataIndexed aTest;
    //    aTest.Load(aString->c());
        
    //    Log("Index Count: %d {%d  %d  %d}\n", aTest.mIndexCount, aTest.mXYZCount, aTest.mUVWCount, aTest.mNormalCount);
    //}
    
    int aIndex=0;
    EnumList(FString, aString, aFileList)//aSequence.mObjects)
    {
        
        FModelData *aData = new FModelData();// LoadOBJ(aString->c());
        aData->LoadOBJ(aString->c());
        
        if((aData != 0) && (aDidFindBase == false))
        {
            
            bool aSharedBase = false;
            
            if(aBaseModel == 0)
            {
                aBaseModel = aData;
                aSharedBase = true;
            }
            else if(aBaseModel->mXYZCount <= 0)
            {
                aBaseModel = aData;
                aSharedBase = true;
            }
            
            aOptimizer->Generate(aBaseModel);
            mParent=aOptimizer->Convert(aBaseModel);
            
            aDidFindBase = true;
            
            if(aSharedBase)
            {
                aBaseModel = 0;
            }
        }
        
        FModelDataIndexed *aNew = new FModelDataIndexed();
        
        aOptimizer->SolveXYZ(aData, aNew);
        
        if(aData->mNormalCount > 0)aOptimizer->SolveNormal(aData, aNew);
        
        if(aData->mUVWCount > 0)aOptimizer->SolveUVW(aData, aNew);
        
        Add(aNew);
        
        delete aData;
        aIndex++;
    }
    
    delete aBaseModel;
    delete aOptimizer;
}

void FModelDataSequence::Free()
{
    delete mParent;
    mParent=0;
    
    for(int i=0;i<mCount;i++)
    {
        delete mData[i];
    }
    
    delete [] mData;
    mData = 0;
    
    mCount = 0;
    mSize = 0;
}

void FModelDataSequence::FlipXY()
{
    for(int i=0;i<mCount;i++)
    {
        mData[i]->FlipXY();
    }
    if(mParent)mParent->FlipXY();
}

void FModelDataSequence:: FlipYZ()
{
    for(int i=0;i<mCount;i++)
    {
        mData[i]->FlipXY();
    }
    if(mParent)mParent->FlipXY();
}

void FModelDataSequence::FlipZX()
{

    for(int i=0;i<mCount;i++)
    {
        mData[i]->FlipXY();
    }
    if(mParent)mParent->FlipXY();
}

void FModelDataSequence::NegateX()
{
    for(int i=0;i<mCount;i++)
    {
        mData[i]->NegateX();
    }
    if(mParent)mParent->NegateX();
}

void FModelDataSequence::NegateY()
{
    for(int i=0;i<mCount;i++)
    {
        mData[i]->NegateY();
    }
    if(mParent)mParent->NegateY();
}

void FModelDataSequence::NegateZ()
{
    for(int i=0;i<mCount;i++)
    {
        mData[i]->NegateZ();
    }
    if(mParent)mParent->NegateZ();
}

void FModelDataSequence::Draw(float pFrame)
{
    if((mParent != 0) && (mCount > 0))
    {
        int aFrame = (int)pFrame;
        if(aFrame < 0)aFrame=0;
        if(aFrame >= mCount)aFrame = (mCount - 1);
        
        FModelDataIndexed *aData = mData[aFrame];

        
        //bool aParentXYZ = false;
        //bool aParentUVW = false;
        
        
        int aIndexCount = aData->mIndexCount;
        GFX_MODEL_INDEX_TYPE *aIndex = aData->mIndex;
        
        if(aIndex == 0)
        {
            aIndex = mParent->mIndex;
            aIndexCount = mParent->mIndexCount;
        }
        
        int aVertexCount = aData->mXYZCount;
        if(aVertexCount <= 0)aVertexCount = mParent->mXYZCount;
        
        float *aXYZ = aData->mXYZ;
        if(aXYZ == 0)aXYZ = mParent->mXYZ;
        
        float *aUVW = aData->mUVW;
        if(aUVW == 0)aUVW = mParent->mUVW;
        
        float *aNormal = aData->mNormal;
        if(aNormal == 0)aNormal = mParent->mNormal;
        
        Graphics::DrawModelIndexed(aData->mXYZ, aData->mXYZCount, mParent->mUVW, mParent->mUVWCount, mUsesBaseNormal ? mParent->mNormal : aData->mNormal, mUsesBaseNormal ? mParent->mNormalCount : aData->mNormalCount, mParent->mIndex, mParent->mIndexCount, mTexture);
    }
}

void FModelDataSequence::GetCentroid(int pFrame, float &pCentroidX, float &pCentroidY, float &pCentroidZ)
{
    
    FModelDataIndexed *aCheck = new FModelDataIndexed();
    
    if(mParent)
    {
        //if(mParent->mIndexCount > 0)
        aCheck->CopyIndex(mParent->mIndex, mParent->mIndexCount);
    }
    
    int aFrame = (int)pFrame;
    if(aFrame < 0)aFrame=0;
    if(aFrame >= mCount)aFrame = (mCount - 1);
    
    FModelDataIndexed *aData = mData[aFrame];
    
    if(aData)
    {
        aCheck->CopyXYZ(aData->mXYZ, aData->mXYZCount);
    }
    aCheck->GetCentroid(pCentroidX, pCentroidY, pCentroidZ);
    
}



void FModelDataSequence::Save(const char *pFile)
{
    if(!mParent)return;
    
    //Log("Saving Data Sequence [%d Nodes] [Index: %d  UVW: %d]\n", mFList.mCount, mParent->mIndexCount, mParent->mUVWCount);
    
    FFile aFile;
    
    if(mDisableUVW)
    {
        mParent->DiscardUVW();
        for(int i=0;i<mCount;i++)mData[i]->DiscardUVW();
    }
    
    if(mDisableNormal)
    {
        mParent->DiscardNormal();
        for(int i=0;i<mCount;i++)mData[i]->DiscardNormal();
    }
    
    
    if(mDisableIndices)
    {
        if(mParent->mIndexCount > 0)
        {
            for(int i=0;i<mCount;i++)
            {
                if(mData[i]->mIndexCount <= 0)
                {
                    int aPreIndCount = mParent->mIndexCount;
                    int aPreXYZCount = mData[i]->mXYZCount;
                    
                    mData[i]->CopyIndex(mParent->mIndex, mParent->mIndexCount);
                    mData[i]->DiscardIndices();
                    
                    Log("Data[%d] Stripped[%d Index %d XYZ] to [%d XYZ]\n", i, aPreIndCount, aPreXYZCount, mData[i]->mXYZCount);
                }
            }
        }
        else
        {
            for(int i=0;i<mCount;i++)
            {
                mData[i]->DiscardIndices();
            }
        }
        
        
        mParent->DiscardIndices();
    }
    
    
    
    if(mUsesBaseNormal)
    {
        for(int i=0;i<mCount;i++)
        {
            mData[i]->DiscardNormal();
        }
    }
    else
    {
        mParent->DiscardNormal();
    }
    
    if(mUsesBaseUVW)
    {
        for(int i=0;i<mCount;i++)
        {
            mData[i]->DiscardUVW();
        }
    }
    else
    {
        mParent->DiscardUVW();
    }

    
    mParent->Save(&aFile);
    aFile.WriteInt(mCount);
    
    int aXYZCount = 0;
    int aUVWCount = 0;
    int aNormalCount = 0;
    
    for(int i=0;i<mCount;i++)
    {
        mData[i]->Save(&aFile);
        
        if(mData[i]->mXYZCount > 0)aXYZCount++;
        if(mData[i]->mUVWCount > 0)aUVWCount++;
        if(mData[i]->mNormalCount > 0)aNormalCount++;
    }
    
    Log("[----- Saving %s ------]\n", pFile);
    
    Log("Model Count: %d\n", mCount);
    
    Log("XYZ on %d nodex (parent = %s)\n", aXYZCount, (mParent->mXYZ ? "yes" : "no"));
    if(aXYZCount > 0 && mParent->mXYZ != 0)Log("***Duplicates for XYZ\n");
    
    Log("UVW on %d nodex (parent = %s)\n", aUVWCount, (mParent->mUVW ? "yes" : "no"));
    if(aUVWCount > 0 && mParent->mUVW != 0)Log("***Duplicates for UVW\n");
    
    Log("Normal on %d nodex (parent = %s)\n", aNormalCount, (mParent->mNormal ? "yes" : "no"));
    if(aNormalCount > 0 && mParent->mNormal != 0)Log("***Duplicates for Normal\n");
    
    Log("[---------------------]\n\n");
    
    
    aFile.Save(pFile);
    
    //Log("Data Sequenced Saved [%s]\n\nData Sequence Size [%d] (%d)\n\n", pFile, aFile.mLength, aFile.mLength / (1000000));
}

void FModelDataSequence::Load(const char *pFile)
{
    Free();
    
    FFile aFile;
    aFile.Load(pFile);
    
    if(aFile.mLength <= 0)
    {
        FString aAltPath = FString(pFile) + FString(".seq");
        aFile.Load(aAltPath);
    }
    
    mParent = new FModelDataIndexed();
    mParent->LoadData(&aFile);
    //mParent->InvertV();
    
    int aFListCount = aFile.ReadInt();
    //Log("**** OBJ Sequence FList Count: %d\n", aFListCount);
    for(int i=0;i<aFListCount;i++)
    {
        FModelDataIndexed *aData = new FModelDataIndexed();
        aData->LoadData(&aFile);
        Add(aData);
    }
    
    mUsesBaseNormal = (mParent->mNormalCount > 0);
}


void FModelDataSequence::SetSprite(FSprite *pSprite, bool pFixUVW)
{
    for(int i=0;i<mCount;i++)
    {
        //if(mData[i])
        //{
        //    mData[i]->SetSprite(pSprite, pFixUVW);
        //}
    }
    if(mParent)
    {
        mParent->SetSprite(pSprite, pFixUVW);
    }
    
    SetTexture(pSprite->mTexture);
}

void FModelDataSequence::SetTexture(FTexture *pTexture)
{
    SET_TEXTURE_BODY;
}


