//
//  FFloatList.cpp
//  DigMMMac
//
//  Created by Nicholas Raptis on 2/14/15.
//  Copyright (c) 2015 Nick Raptis. All rights reserved.
//

#include "FFloatList.h"


FFloatList::FFloatList()
{
    mCount = 0;
    mSize = 0;
    mData = 0;
}

FFloatList::~FFloatList()
{
    Clear();
}

void FFloatList::Clear()
{
    delete[] mData;
    
    mCount = 0;
    mSize = 0;
    
    mData = 0;
}

void FFloatList::Add(float pFloat)
{
    if(mCount >= mSize)
    {
        Size(mCount + (mCount / 2) + 1);
    }
    
    mData[mCount] = pFloat;
    mCount++;
}

void FFloatList::Add(FFloatList *pList)
{
    if(pList)
    {
        if(pList->mCount > mSize)
        {
            Size(pList->mCount);
        }
        for(int i = 0; i<pList->mCount; i++)
        {
            Add(pList->mData[i]);
        }
    }
}

void FFloatList::AddValues(int pCount, float pFloat1, float pFloat2, float pFloat3, float pFloat4, float pFloat5, float pFloat6, float pFloat7, float pFloat8, float pFloat9, float pFloat10, float pFloat11, float pFloat12, float pFloat13, float pFloat14, float pFloat15)
{
    if(pCount >= 15)
    {
        Add(pFloat1); Add(pFloat2); Add(pFloat3); Add(pFloat4); Add(pFloat5);
        Add(pFloat6); Add(pFloat7); Add(pFloat8); Add(pFloat9); Add(pFloat10);
        Add(pFloat11); Add(pFloat12); Add(pFloat13); Add(pFloat14); Add(pFloat15);
    }
    else
    {
        if(pCount > 0)Add(pFloat1);
        if(pCount > 1)Add(pFloat2);
        if(pCount > 2)Add(pFloat3);
        if(pCount > 3)Add(pFloat4);
        if(pCount > 4)Add(pFloat5);
        if(pCount > 5)Add(pFloat6);
        if(pCount > 6)Add(pFloat7);
        if(pCount > 7)Add(pFloat8);
        if(pCount > 8)Add(pFloat9);
        if(pCount > 9)Add(pFloat10);
        if(pCount > 10)Add(pFloat11);
        if(pCount > 11)Add(pFloat12);
        if(pCount > 12)Add(pFloat13);
        if(pCount > 13)Add(pFloat14);
        if(pCount > 14)Add(pFloat15);
    }
}


void FFloatList::AddValuesReset(int pCount, float pFloat1, float pFloat2, float pFloat3, float pFloat4, float pFloat5, float pFloat6, float pFloat7, float pFloat8, float pFloat9, float pFloat10, float pFloat11, float pFloat12, float pFloat13, float pFloat14, float pFloat15)
{
    mCount = 0;
    
    AddValues(pCount, pFloat1, pFloat2, pFloat3, pFloat4, pFloat5,
               pFloat6, pFloat7, pFloat8, pFloat9, pFloat10,
               pFloat11, pFloat12, pFloat13, pFloat14, pFloat15);
}

float FFloatList::Get(int pSlot) {
    float aResult = 0;
    if ((pSlot >= 0) && (pSlot < mCount)) {
        aResult = mData[pSlot];
    }
    return aResult;
}

void FFloatList::Set(int pSlot, float pFloat)
{
    if(pSlot >= mSize)
    {
        SetSize(pSlot + 1);
    }
    if(pSlot >= mCount)
    {
        mCount = (pSlot + 1);
    }
    
    if(pSlot >= 0)
    {
        mData[pSlot] = pFloat;
    }
}

void FFloatList::Reset()
{
    mCount = 0;
}

void FFloatList::Size(int pSize)
{
    if(pSize != mSize)
    {
        if(pSize <= 0)
        {
            Clear();
        }
        else
        {
            if(mCount >= pSize)mCount=pSize;
            float *aNew = new float[pSize];
            for(int i = 0; i<mCount; i++)aNew[i] = mData[i];
            for(int i = mCount; i<pSize; i++)aNew[i] = 0;
            
            delete[] mData;
            mData = aNew;
            mSize = pSize;
        }
    }
}

void FFloatList::Save(FFile *pFile)
{
    if(pFile)
    {
        pFile->WriteInt(mCount);
        
        for(int i = 0; i<mCount; i++)
        {
            pFile->WriteFloat(mData[i]);
        }
    }
}

void FFloatList::Load(FFile *pFile)
{
    Clear();
    
    if(pFile)
    {
        int aCount = pFile->ReadInt();
        Size(aCount);
        for(int i = 0; i<aCount; i++)
        {
            mData[i] = pFile->ReadFloat();
        }
        mCount = aCount;
    }
}

void FFloatList::Reverse()
{
    if(mCount > 1)
    {
        int aStartIndex = 0;
        int aEndIndex = (mCount - 1);
        
        float aHold = 0;
        
        while (aStartIndex < aEndIndex)
        {
            aHold = mData[aEndIndex];
            
            mData[aEndIndex] = mData[aStartIndex];
            
            mData[aStartIndex] = aHold;
            
            aStartIndex++;
            aEndIndex--;
        }
    }
}

void FFloatList::Clone(FFloatList *pPointList)
{
    if(pPointList)
    {
        if(pPointList->mCount > mSize)
        {
            Size(pPointList->mCount);
        }
        
        Reset();
        
        int aCount = pPointList->mCount;
        
        for(int i = 0; i<aCount; i++)
        {
            Add(pPointList->mData[i]);
        }
    }
}

int FFloatList::GetPrintLineCount()
{
    int aLineCount = 0;
    
    if(mCount > 0)
    {
        int aIndex = 0;
        bool aDone = false;
        
        while (aDone == false)
        {
            aLineCount++;
            aIndex += 15;
            if(aIndex >= mCount)aDone = true;
        }
        
    }
    
    return aLineCount;
}


FString FFloatList::GetPrintLine(int pLineNumber)
{
    FString aResult = "AddValues(";
    
    if(pLineNumber == 0)aResult = "AddValuesReset(";
    
    
    int aStartIndex = pLineNumber * 15;
    int aEndIndex = (aStartIndex + 15);
    
    bool aFinish = false;
    
    if(aEndIndex >= mCount)
    {
        aFinish = true;
        aEndIndex = mCount;
    }
    
    int aLineCount = (aEndIndex - aStartIndex);
    if(aLineCount <= 0)aLineCount = 0;
    
    FString aLineCountString = FString(aLineCount);
    if(aLineCountString.mLength <= 1)aLineCountString += " ";
    
    aResult += aLineCountString;
    aResult += ", ";
    
    while (aLineCount > 0)
    {
        int aIndex = mData[aStartIndex];
        FString aIndexString = FString(aIndex);
        
        aResult += aIndexString;
        
        aStartIndex++;
        aLineCount--;
        
        if(aLineCount > 0)
        {
            aResult += FString(", ");
        }
        else
        {
            aResult += FString(")");
        }
    }
    
    return aResult;
}

FString FFloatList::GetPrintString(const char *pVariableName)
{
    FString aResult = "";
    
    int aLineCount = GetPrintLineCount();
    for(int i = 0; i<aLineCount; i++)
    {
        FString aLine = GetPrintLine(i);
        aLine = FString(FString(pVariableName) + FString(".") + FString(aLine.c()) + FString(";\n")).c();
        aResult += aLine;
    }
    
    return aResult;
}

