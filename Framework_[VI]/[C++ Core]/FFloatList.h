//
//  FFloatList.h
//  DigMMMac
//
//  Created by Nicholas Raptis on 2/14/15.
//  Copyright (c) 2015 Nick Raptis. All rights reserved.
//

#ifndef __DigMMMac__FFloatList__
#define __DigMMMac__FFloatList__

#include "FFile.hpp"

class FFloatList
{
public:
    
    FFloatList();
    virtual ~FFloatList();
    
    inline bool             IsEmpty() { return mCount == 0; }
    
    void                    Clear();
    void                    Reset();
    
    float                   *mData;
    int                     mCount;
    int                     mSize;
    
    void                    Add(FFloatList *pList);
    void                    Add(float pFloat);
    void                    Set(int pSlot, float pFloat);
    
    float	                Get(int pSlot);
    
    void                    Reverse();
    
    void                    AddValues(int pCount, float pFloat1 = 0.0f, float pFloat2 = 0.0f, float pFloat3 = 0.0f, float pFloat4 = 0.0f, float pFloat5 = 0.0f, float pFloat6 = 0.0f, float pFloat7 = 0.0f, float pFloat8 = 0.0f, float pFloat9 = 0.0f, float pFloat10 = 0.0f, float pFloat11 = 0.0f, float pFloat12 = 0.0f, float pFloat13 = 0.0f, float pFloat14 = 0.0f, float pFloat15 = 0.0f);
    void                    AddValuesReset(int pCount, float pFloat1 = 0.0f, float pFloat2 = 0.0f, float pFloat3 = 0.0f, float pFloat4 = 0.0f, float pFloat5 = 0.0f, float pFloat6 = 0.0f, float pFloat7 = 0.0f, float pFloat8 = 0.0f, float pFloat9 = 0.0f, float pFloat10 = 0.0f, float pFloat11 = 0.0f, float pFloat12 = 0.0f, float pFloat13 = 0.0f, float pFloat14 = 0.0f, float pFloat15 = 0.0f);
    
    void                    Size(int pSize);
    inline void             SetSize(int pSize){ Size(pSize); }
    
    void                    Clone(FFloatList *pPointList);
    inline void             Clone(FFloatList &pPointList){ Clone(&pPointList); }
    
    void                    Save(FFile *pFile);
    void                    Load(FFile *pFile);
    
    int                     GetPrintLineCount();
    FString                 GetPrintLine(int pLineNumber);
    FString                 GetPrintString(const char *pVariableName);
};


#endif /* defined(__DigMMMac__FFloatList__) */
