//
//  FStringBuffer.h
//  RaptisGame
//
//  Created by Nick Raptis on 3/20/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#ifndef __RaptisGame__FStringBuffer__
#define __RaptisGame__FStringBuffer__

#include "FString.h"

class FStringBuffer
{
public:
    
    FStringBuffer();
    virtual ~FStringBuffer();
    
    void                                    Free();
    void                                    Reset();
    
    inline char                             *c(){if(mData==0){SizeSet(1);} return mData;}
    
    void                                    SizeSet(int pSize);
    void                                    SizeEnsure(int pSize);
    
    
    void                                    Append(const char *pString, int pCount);
    void                                    Append(const char *pString){Append(pString, FString::Length(pString));}
    void                                    Append(char *pString){Append((const char *)(pString));}
    void                                    Append(FString pString){Append((const char *)(pString.c()), pString.mLength);}

    int                                     WriteInt(int pNumber, int pIndex);

    int                                     Write(const char *pString, int pIndex, int pCount);
    int                                     Write(const char *pString, int pIndex){return Write(pString, pIndex, FString::Length(pString));}
    int                                     Write(char *pString, int pIndex){return Write((const char *)(pString), pIndex);}
    int                                     Write(FString pString, int pIndex){return Write((const char *)(pString.c()), pIndex, pString.mLength);}

    int                                     WriteTerminate(const char *pString, int pIndex, int pCount);
    int                                     WriteTerminate(const char *pString, int pIndex){return WriteTerminate(pString, pIndex, FString::Length(pString));}
    int                                     WriteTerminate(char *pString, int pIndex){return WriteTerminate((const char *)(pString), pIndex);}
    int                                     WriteTerminate(FString pString, int pIndex){return WriteTerminate((const char *)(pString.c()), pIndex, pString.mLength);}
    
    char                                    *mData;
    
    int                                     mLength;
    int                                     mSize;
    
};


#endif /* defined(__RaptisGame__FStringBuffer__) */
