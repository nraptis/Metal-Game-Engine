//
//  FStringBuffer.cpp
//  RaptisGame
//
//  Created by Nick Raptis on 3/20/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#include "FStringBuffer.h"
#include "core_includes.h"

FStringBuffer::FStringBuffer()
{
    mData = 0;
    
    mLength = 0;
    mSize = 0;
}

FStringBuffer::~FStringBuffer()
{
    
}

void FStringBuffer::Free()
{
    delete [] mData;
    mData = 0;
    
    mLength = 0;
    mSize = 0;
}

void FStringBuffer::Reset()
{
    mLength = 0;
}

void FStringBuffer::SizeSet(int pSize)
{
    if(pSize <= 0)
    {
        Free();
        return;
    }
    
    if(pSize != mSize)
    {
        char *aNewData = new char[pSize + 1];
        
        int aWriteCount = mSize;
        if(pSize < mSize)aWriteCount = pSize;
        
        
        for(int i=0;i<aWriteCount;i++)
        {
            aNewData[i] = mData[i];
        }
        
        for(int i=mSize;i<=pSize;i++)
        {
            aNewData[i] = 0;
        }
        
        delete [] mData;
        mData = aNewData;
        
        mSize = pSize;
        
        if(mLength > mSize)
        {
            mLength = mSize;
        }
        
        
    }
}

void FStringBuffer::SizeEnsure(int pSize)
{
    if(pSize <= 0)
    {
        return;
    }
    
    if(pSize > mSize)
    {
        SizeSet(pSize + (pSize / 2) + 1);
        //SizeSet(pSize + gRand.Get(6) + 1);
    }
    
}

void FStringBuffer::Append(const char *pString, int pCount)
{
    if(pCount <= 0)return;
    
    //Write(pString, 0, pCount);
    WriteTerminate(pString, 0, pCount);
}


int FStringBuffer::WriteTerminate(const char *pString, int pIndex, int pCount)
{
    int aIndex = Write(pString, pIndex, pCount);
    
    if(aIndex <= 0)
    {
        mLength = 0;
        if(mSize > 0)mData[0] = 0;
    }
    else
    {
        mLength = aIndex;
        mData[mLength] = 0;
    }
    
    return aIndex;
}



int FStringBuffer::Write(const char *pString, int pIndex, int pCount)
{
    if(pIndex < 0)
    {
        pCount += pIndex;
        pString = &(pString[-pIndex]);
        pIndex = 0;
    }
    
    if(pCount <= 0)
    {
        return pIndex;
    }
    
    int aNewMinLength = pIndex + pCount;
    
    SizeEnsure(aNewMinLength);
    
    if(mLength < aNewMinLength)
    {
        mLength = aNewMinLength;
        mData[mLength] = 0;
    }
    
    char *aCopy = (char *)pString;
    char *aPaste = (char *)(&(mData[pIndex]));
    
    while(pCount)
    {
        *aPaste = *aCopy;
        
        aPaste++;
        aCopy++;
        
        pCount--;
    }
    
    return aNewMinLength;
}

int FStringBuffer::WriteInt(int pNumber, int pIndex)
{
    static char cStringBufferNumberChar[32];
    static int cStringBufferNumberInt[32];
    
    int aWriteLength = 0;
    int aNumberLength = 0;
    
    if(pNumber < 0)
    {
        cStringBufferNumberChar[0] = '-';
        aWriteLength = 1;
        pNumber = (-pNumber);
    }
    
    if(pNumber == 0)
    {
        cStringBufferNumberInt[0] = 0;
        aNumberLength = 1;
    }
    else
    {
        while(pNumber != 0)
        {
            
            cStringBufferNumberInt[aNumberLength] = (pNumber % 10);
            pNumber = (pNumber / 10);
            aNumberLength++;
        }
    }
    
    while(aNumberLength > 0)
    {
        aNumberLength--;
        cStringBufferNumberChar[aWriteLength] = ('0' + cStringBufferNumberInt[aNumberLength]);
        aWriteLength++;
    }
    
    return Write(cStringBufferNumberChar, pIndex);
}

