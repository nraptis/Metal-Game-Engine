//
//  FFile.cpp
//  CoreDemo
//
//  Created by Nick Raptis on 10/1/13.
//  Copyright (c) 2013 Nick Raptis. All rights reserved.
//

#include "FFile.hpp"
#include "core_includes.h"
#include "os_core_outlets.h"
#include "FResource.h"

FFile::FFile()
{
	mLength = 0;
	mCursorRead = 0;
	mCursorWrite = 0;
	mData = 0;
}

FFile::~FFile()
{
	Clear();
}

void FFile::Clear()
{
	delete [] mData;
	mLength = 0;
	mCursorRead = 0;
	mCursorWrite = 0;
	mData = 0;
}

void FFile::Size(int pSize)
{
    if(pSize <= 0)
    {
        Clear();
    }
    else if(pSize != mLength)
    {
        unsigned char *aNew = new unsigned char[pSize];
        
        if(mLength > pSize)mLength = pSize;
        if(mCursorRead > pSize)mCursorRead = pSize;
        if(mCursorWrite > pSize)mCursorWrite = pSize;
        
        
        for(int i=0; i<mLength; i++)aNew[i] = mData[i];
        for(int i=mLength; i<pSize; i++)aNew[i] = 0;
        
        mLength = pSize;
        
        delete[] mData;
        mData = aNew;
    }
}


void FFile::Write(char *write, int theLength)
{
	while (theLength > 0)
	{
		WriteChar(*write);
		write++;
		theLength--;
	}
}


void FFile::Write(char *write)
{
	//char *aPtr=write;
	//while(*aPtr)aPtr++;
	//Write(write,(int)(aPtr-write));
}

void FFile::WriteFloat(float pWrite)
{
	if((mCursorWrite + 4) > mLength)Size(mCursorWrite + (mCursorWrite / 2) + 4);
	*(float*)(&(mData[mCursorWrite])) = pWrite;
	mCursorWrite += 4;
}

void FFile::WriteBool(bool pWrite)
{
    if(pWrite)WriteChar(1);
    else WriteChar(0);
}

void FFile::WriteChar(char pWrite)
{
    if((mCursorWrite + 1) > mLength)Size(mCursorWrite + (mCursorWrite / 2) + 1);
    *(unsigned char*)(&(mData[mCursorWrite])) = pWrite;
    mCursorWrite += 1;
}

void FFile::WriteShort(short pWrite)
{
    if((mCursorWrite + 2) > mLength)Size(mCursorWrite + (mCursorWrite / 2) + 2);
    *(short*)(&(mData[mCursorWrite])) = pWrite;
    mCursorWrite += 2;
}

void FFile::WriteInt(int pWrite)
{
	if((mCursorWrite + 4) > mLength)Size(mCursorWrite + (mCursorWrite / 2) + 4);
	*(int*)(&(mData[mCursorWrite])) = pWrite;
	mCursorWrite += 4;
}

bool FFile::ReadBool()
{
	return (ReadChar() != 0);
}

char FFile::ReadChar()
{
    char aResult = 0;
    if((mCursorRead + 1) < mLength)
    {
        aResult = *(char*)(&(mData[mCursorRead]));
        mCursorRead += 1;
    }
    return aResult;
}

short FFile::ReadShort()
{
    short aResult = 0;
    if((mCursorRead + 2) < mLength)
    {
        aResult = *(short*)(&(mData[mCursorRead]));
        mCursorRead += 2;
    }
    return aResult;
}

int FFile::ReadInt()
{
    int aResult = 0;
    if((mCursorRead + 4) < mLength)
    {
        aResult = *(int*)(&(mData[mCursorRead]));
        mCursorRead += 4;
    }
    return aResult;
}

float FFile::ReadFloat()
{
    float aResult = 0.0f;
    if((mCursorRead + 4) < mLength)
    {
        aResult = *(float*)(&(mData[mCursorRead]));
        mCursorRead += 4;
    }
    return aResult;
}

void FFile::WriteColor(FColor pColor)
{
    WriteFloat(pColor.mRed);
    WriteFloat(pColor.mGreen);
    WriteFloat(pColor.mBlue);
    WriteFloat(pColor.mAlpha);
}

FColor FFile::ReadColor()
{
    FColor aResult;
    aResult.mRed = ReadFloat();
    aResult.mGreen = ReadFloat();
    aResult.mBlue = ReadFloat();
    aResult.mAlpha = ReadFloat();
    return aResult;
}

void FFile::WriteString(char *pString)
{
	int aLength = FString::Length(pString);

	if((aLength < 0) || (aLength > 2000))
	{
		Log("Fail!! [%d]\n\n", aLength);
		aLength = 0;
	}

	WriteShort((short)aLength);
	for(int i=0; i<aLength; i++)WriteChar(pString[i]);
}

FString FFile::ReadString()
{
	FString aResult;

    short aLengthShort = ReadShort();
    int aLength = (int)aLengthShort;
	if((aLength > 2048) || (aLength < 0))
	{
		aLength = 0;


		aResult = "<Err>";
	}
	else
	{

		if(aLength > 0)
		{
			char *aData = new char[aLength + 1];
			aData[aLength] = 0;

			for(int i = 0; i < aLength; i++)
			{
				aData[i] = ReadChar();
			}

			aResult.Set(aData);
			delete[] aData;
		}
		else
		{
			aResult = "";
		}
	}
    
	return aResult;
}

void FFile::Print()
{
    
     int aRow=0;
     int aIndex=0;
     FString aPrint;
     Log("\n**FFile Print**\n");
     while(aIndex<mLength)
     {
         aPrint += FString(((int)mData[aIndex]));
         if(aPrint.mLength <= 1)aPrint = FString(FString("0") + aPrint).c();
         
         //aPrint+=Log("%2X", (void *)();
                     
         aPrint += ", ";
     aIndex++;
     
     aRow++;
     if(aRow>=10)
     {
     aRow=0;
     Log("__[%s]\n", aPrint.c());
     aPrint.Clear();
     }
     }
     Log("__[%s]__\n", aPrint.c());
    aPrint.Clear();
     //aPrint="";
     
     /*
     while(aIndex<mSize)
     {
     aPrint+=SLog("%2X", (int)mData[aIndex])+",";
     aIndex++;
     
     aRow++;
     if(aRow>=10)
     {
     aRow=0;
     Log("++[%s]\n", aPrint.c());
     aPrint="";
     }
     }
    */
     
     Log("++[%s]\n", aPrint.c());
    
}


void FFile::Save(char *pFile)
{
	if(mLength > 0)
	{
		if(mCursorWrite > 0)
		{
			os_write_file(pFile, mData, mCursorWrite);
		}
		else
		{
			os_write_file(pFile, mData, mLength);
		}
	}
	else
	{
		os_write_file(pFile, mData, mLength);
	}

    
    //FString aPath;os_getTestDirectory(&aPath);
    //aPath = FString(FString(pFile) + FString(aPath.c())).c();
    //os_write_file(aPath.c(), mData, mLength);
}

void FFile::LoadDirect(char *pFile)
{
    Clear();
    
    mData = os_read_file(pFile, mLength);
    
    if(mLength > 0)
    {
        mFileName = pFile;
        mFileName.RemovePath();
    }
}

void FFile::Load(char *pFile)
{
    Clear();
    
	const char *aResourcePath = gRes.GetResourcePathFile(pFile);
	while ((aResourcePath != 0) && (mLength <= 0))
	{
        mFileName = aResourcePath;
        mData = os_read_file(mFileName.c(), mLength);
        aResourcePath = gRes.GetNextResourcePath();
    }

	if(mLength <= 0)
	{
        mFileName = pFile;
        mData = os_read_file(mFileName.c(), mLength);
	}

    if((mLength <= 0) && (gDirBundle.mLength > 0))
    {
		mFileName = gDirBundle + FString(pFile);

		mData = os_read_file(mFileName.c(), mLength);
    }
    
    if((mLength <= 0) && (gDirDocuments.mLength > 0))
    {
		mFileName = gDirDocuments + FString(pFile);
		mData = os_read_file(mFileName.c(), mLength);
    }
    
	//mLength
    /*
	Clear();
	if(!pFile)return;
    
	int aFileLength=-1;
	int aFile=open(pFile,O_BINARY|O_RDONLY);
	
    if(aFile==-1)
    {
        aFile=open(FString(gDirBundle + pFile).c(),O_BINARY|O_RDONLY);
    }
    
    if(aFile==-1)
    {
        aFile=open(FString(gDirDocuments + pFile).c(),O_BINARY|O_RDONLY);
    }
    
	if(aFile!=-1)
	{
		struct stat aFileStats;
		if(fstat(aFile,&aFileStats) == 0)aFileLength=aFileStats.st_size;
		if(aFileLength<1)return;
		mLength=aFileLength;
		mSize=mLength;
		mWriteCursor=(mLength<<3);
		mData=new unsigned char[mLength+256];
		read(aFile,mData,mLength);
		close(aFile);
	}
    else
    {
        FString aErrorString = FString(pFile);
        aErrorString.RemovePath(false);
    }
    */
}



FFileSequence::FFileSequence()
{
    
}

FFileSequence::~FFileSequence()
{
    
}

bool FFileSequence::LoadSequence(const char *pFileBase, const char *pExtension, FList &pList, int pStartIndex, int pEndIndex, int pLeadingZeroCount) {
    bool aResult = false;
    FString aFileBase = pFileBase;
    FString aExtension = pExtension;
    FString aNumberString = FString(pStartIndex);
    if (aNumberString.mLength < pLeadingZeroCount) {
        FString aZeroString;
		aZeroString.InsChars('0', (pLeadingZeroCount - aNumberString.mLength), 0);
        aNumberString = (aZeroString + aNumberString);
    }
    
    FString aCheck = (aFileBase + aNumberString + FString(".") + aExtension);
    if (os_fileExists(aCheck.c())) {
        pList += new FString(aCheck);
        aResult=true;
    }

    if ((aResult == false) && (gDirBundle.mLength > 0)) {
        aCheck = (gDirBundle + aFileBase + aNumberString + FString(".") + aExtension);
        if (os_fileExists(aCheck.c())) {
            pList += new FString(aCheck);
            aFileBase = (gDirBundle + aFileBase);
            aResult=true;
        }
    }
    
    if ((aResult == false) && (gDirDocuments.mLength > 0)) {
        aCheck = (gDirDocuments + aFileBase + aNumberString + FString(".") + aExtension);
        if (os_fileExists(aCheck.c())) {
            pList += new FString(aCheck);
            aFileBase = (gDirDocuments + aFileBase);
            aResult=true;
        }
    }
    
    if (aResult) {
        for (int aIndex=pStartIndex+1;((aIndex<=pEndIndex) || (pEndIndex == -1));aIndex++) {
            aNumberString = FString(aIndex);
            if (aNumberString.mLength < pLeadingZeroCount) {
                FString aZeroString;
                aZeroString.InsChars('0', (pLeadingZeroCount - aNumberString.mLength), 0);
                aNumberString = (aZeroString + aNumberString);
            }
            aCheck = (aFileBase + aNumberString + FString(".") + aExtension);
            if (os_fileExists(aCheck.c())) {
                pList += new FString(aCheck);
            } else {
                break;
            }
        }
    }
    
    return aResult;
}

bool FFileSequence::LoadSequence(const char *pFileBase, const char *pExtension, FList &pList, int pStartIndex, int pEndIndex)
{
    bool aResult = false;
    
    for(int aLeadingZeros=1;((aLeadingZeros<8) && (aResult==false));aLeadingZeros++)
    {
        aResult = LoadSequence(pFileBase, pExtension, pList, pStartIndex, pEndIndex, aLeadingZeros);
    }
    
    return aResult;
}

bool FFileSequence::LoadSequence(const char *pFileBase, FList &pList, int pStartIndex, int pEndIndex) {
    bool aResult = false;
    if (!aResult) {
        aResult = LoadSequence(pFileBase, "png", pList, pStartIndex, pEndIndex);
    }
    if (!aResult) {
        aResult = LoadSequence(pFileBase, "jpg", pList, pStartIndex, pEndIndex);
    }
    if (!aResult) {
        aResult = LoadSequence(pFileBase, "obj", pList, pStartIndex, pEndIndex);
    }
    return aResult;
}

bool FFileSequence::LoadSequence(const char *pFileBase, const char *pExtension, int pStartIndex, int pEndIndex, int pLeadingZeroCount)
{
    FreeList(FString, mList);
    return FFileSequence::LoadSequence(pFileBase, pExtension, mList, pStartIndex, pEndIndex, pLeadingZeroCount);
}

bool FFileSequence::LoadSequence(const char *pFileBase, const char *pExtension, int pStartIndex, int pEndIndex)
{
    FreeList(FString, mList);
    return FFileSequence::LoadSequence(pFileBase, pExtension, mList, pStartIndex, pEndIndex);
}

bool FFileSequence::LoadSequence(const char *pFileBase, int pStartIndex, int pEndIndex)
{
    FreeList(FString, mList);
    return FFileSequence::LoadSequence(pFileBase, mList, pStartIndex, pEndIndex);
}




int FloatToInt(float pFloat)
{
    return *((int*)(&pFloat));
}

float IntToFloat(int pInt)
{
    return *((float*)(&pInt));
}
