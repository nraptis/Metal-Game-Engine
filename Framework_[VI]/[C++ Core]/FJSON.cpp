//
//  FJSON.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/17/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "FJSON.hpp"
#include "FFile.hpp"


FJSONNode::FJSONNode() {
    mKey = NULL;
    mValue = NULL;
    
    mList = NULL;
    mListCount = 0;
    mListSize = 0;
    
    mInfo = NULL;
    
    mType = JSON_TYPE_DATA;
}

FJSONNode::~FJSONNode() {
    //printf("Deleting JNode[%s]\n", mKey);
    
    if (mList != NULL) {
        for (int i=0;i<mListCount;i++) {
            delete mList[i];
        }
        delete [] mList;
        mList = NULL;
    }
    
    if (mInfo != NULL) {
        FStringMapNode *aNode = mInfo->mListHead;
        while (aNode != NULL) {
            FJSONNode *aJSONNode = ((FJSONNode *)aNode->mObject);
            delete aJSONNode;
            aNode = aNode->mListNext;
        }
        delete mInfo;
        mInfo = NULL;
    }
}

void FJSONNode::AddDictionary(const char *pKey, FJSONNode *pNode) {
    if (mInfo == NULL) {
        mInfo = new FStringMap();
    }
    mInfo->Add(pKey, pNode);
}

void FJSONNode::AddArray(FJSONNode *pNode) {
    if (mList == NULL) {
        mListSize = 1;
        mList = new FJSONNode*[mListSize];
    }
    if (mListCount >= mListSize) {
        mListSize = (mListCount + mListCount / 2 + 1);
        FJSONNode **aNewList = new FJSONNode*[mListSize];
        for (int i=0;i<mListCount;i++) {
            aNewList[i] = mList[i];
        }
        delete [] mList;
        mList = aNewList;
    }
    mList[mListCount++] = pNode;
}

void FJSONNode::Print() {
    printf("JSON:\n");
    
    if (mInfo != NULL) {
        FStringMapNode *aNode = mInfo->mListHead;
        while (aNode != NULL) {
            
            printf("\t%s: ", aNode->mKey.c());
            
            ((FJSONNode *)aNode->mObject)->Print(2);
            
            aNode = aNode->mListNext;
        }
    }
    
}

void FJSONNode::Print(int pDepth) {
    
    //printf("CD: %d\n", pDepth);
    if (mValue != NULL) {
        printf("%s", mValue);
        return;
    }
    
    for (int i=0;i<pDepth;i++) { printf("\t"); }
    if (mKey != NULL) {
        if (mInfo == NULL && mList == NULL) {
            if (mType == JSON_TYPE_ARRAY) {
                printf("[]\n");
            } else {
                printf("{}\n");
            }
            
        }
    }
    
    if (mInfo != NULL) {
        FStringMapNode *aNode = mInfo->mListHead;
        printf("{\n");
        while (aNode != NULL) {
            
            printf("\n");
            
            for (int i=0;i<pDepth;i++) { printf("\t"); }
            
            printf("%s(%d): ", aNode->mKey.c(), pDepth);
            
            ((FJSONNode *)aNode->mObject)->Print(pDepth + 1);
            
            if (aNode->mListNext != NULL) printf(", ");
            
            aNode = aNode->mListNext;
        }
        printf("\n");
        for (int i=0;i<pDepth;i++) { printf("\t"); }
        printf("}\n");
    }
    
    if (mListCount > 0) {
        printf("[\n");
        
        for (int i=0;i<mListCount;i++) {
            FJSONNode *aNode = mList[i];
            aNode->Print(pDepth + 1);
            if ((i < mListCount - 1)) printf(", ");
        }
        
        printf("\n");
        for (int i=0;i<pDepth;i++) { printf("\t"); }
        printf("]\n");
    }
    
    //if ()
    
}



FJSON::FJSON() {
    mRoot = NULL;
    
    
}

FJSON::~FJSON() {
    Clear();
}

void FJSON::Clear() {
    delete mRoot;
    mRoot = NULL;
}

void FJSON::Load(const char *pFile) {
    FFile aFile;
    aFile.Load(pFile);
    if (aFile.mLength <= 0) {
        bool aBlock = false;
        while (aBlock == false) {
            aBlock = true;
            FString aFileName = FString(pFile);
            aFileName.RemoveExtension();
            aFile.Load(aFileName + FString(".json"));
            if (aFile.mLength > 0) { break; }
            aFile.Load(aFileName + FString(".JSON"));
            if (aFile.mLength > 0) { break; }
            aFile.Load(aFileName + FString(".jsn"));
            if (aFile.mLength > 0) { break; }
            aFile.Load(aFileName + FString(".JSN"));
            if (aFile.mLength > 0) { break; }
            aFileName.RemovePath();
            aFile.Load(aFileName + FString(".json"));
            if (aFile.mLength > 0) { break; }
            aFile.Load(aFileName + FString(".JSON"));
            if (aFile.mLength > 0) { break; }
            aFile.Load(aFileName + FString(".jsn"));
            if (aFile.mLength > 0) { break; }
            aFile.Load(aFileName + FString(".JSN"));
        }
    }
    Parse((const char *)aFile.mData, aFile.mLength);
}

void FJSON::Parse(const char *pData, int pLength) {
    
    Clear();
    if (pData == NULL || pLength <= 2) {
        return;
    }
    
    char *aData = new char[pLength + 1];
    for (int i=0;i<pLength;i++) {
        aData[i] = pData[i];
    }
    aData[pLength] = 0;
    
    FList aStack;
    bool aDictionary = false;
    
    char *aPtr = aData;
    while ((*aPtr != 0) && IsWhiteSpace(*aPtr)) { aPtr++; }
    
    if (*aPtr == '{') {
        ++aPtr;
        aDictionary = true;
    } else if (*aPtr == '[') {
        ++aPtr;
        aDictionary = false;
    } else {
        goto JSON_PARSE_ERROR;
    }
    
    mRoot = new FJSONNode();
    aStack.Add(mRoot);
    
    if (aDictionary) {
        bool aSuccess = true;
        mRoot->mType = JSON_TYPE_DICTIONARY;
        ParseHelperDictionary(aPtr, &aStack, &aSuccess);
        if (aSuccess == false) {
            goto JSON_PARSE_ERROR;
        }
    } else {
        bool aSuccess = true;
        mRoot->mType = JSON_TYPE_ARRAY;
        ParseHelperArray(aPtr, &aStack, &aSuccess);
        if (aSuccess == false) {
            goto JSON_PARSE_ERROR;
        }
    }
    
    delete [] aData;
    return;
    
JSON_PARSE_ERROR:
    
    delete [] aData;
    delete mRoot;
    mRoot = NULL;
}


//Assume that we pass in character AFTER the "{"
//with the parent node as last item on pStack
char *FJSON::ParseHelperDictionary(char *pData, FList *pStack, bool *pSuccess) {
    FJSONNode *aParent = (FJSONNode *)pStack->Last();
    if (aParent == NULL) {
        *pSuccess = false;
        return NULL;
    }
    
    int aElementIndex = 0;
    char *aPtr = pData;
    while (*aPtr) {
        while ((*aPtr != 0) && IsWhiteSpace(*aPtr)) { aPtr++; }
        if (aElementIndex > 0) {
            if (*aPtr == ',') {
                aPtr += 1;
            } else if (*aPtr == '}') {
                aPtr += 1;
                goto ParseHelperDictionary_COMPLETE;
            } else {
                *pSuccess = false;
                return NULL;
            }
        } else {
            if (*aPtr == '}') {
                ++aPtr;
                goto ParseHelperDictionary_COMPLETE;
            }
        }
        while ((*aPtr != 0) && IsWhiteSpace(*aPtr)) { aPtr++; }
        if (*aPtr != '\"') {
            *pSuccess = false;
            return NULL;
        }
        
        char *aEOQ = EndOfQuote(aPtr);
        if (aEOQ == NULL) {
            *pSuccess = false;
            return NULL;
        }
        
        char *aKey = GetQuotedString(aPtr, aEOQ);
        aPtr = aEOQ + 1;
        while ((*aPtr != 0) && IsWhiteSpace(*aPtr)) { aPtr++; }
        
        if (*aPtr != ':') {
            *pSuccess = false;
            delete aKey;
            return NULL;
        }
        ++aPtr;
        while ((*aPtr != 0) && IsWhiteSpace(*aPtr)) { aPtr++; }
        if (*aPtr == '{') {
            ++aPtr;
            
            FJSONNode *aNode = new FJSONNode();
            aNode->mKey = aKey;
            aNode->mType = JSON_TYPE_DICTIONARY;
            aParent->AddDictionary(aKey, aNode);
            pStack->Add(aNode);
            
            aPtr = ParseHelperDictionary(aPtr, pStack, pSuccess);
            if (*pSuccess == false) {
                return NULL;
            }
            
            pStack->PopLast();
            
        } else if (*aPtr == '[') {
            ++aPtr;
            FJSONNode *aNode = new FJSONNode();
            aNode->mKey = aKey;
            aNode->mType = JSON_TYPE_ARRAY;
            aParent->AddDictionary(aKey, aNode);
            delete aKey;
            pStack->Add(aNode);
            aPtr = ParseHelperArray(aPtr, pStack, pSuccess);
            if (*pSuccess == false) {
                return NULL;
            }
            
            pStack->PopLast();
        } else if (*aPtr == '\"') {
            aEOQ = EndOfQuote(aPtr);
            if (aEOQ == NULL) {
                *pSuccess = false;
                delete aKey;
                return NULL;
            }
            
            FJSONNode *aValueNode = new FJSONNode();
            aValueNode->mValue = GetQuotedString(aPtr, aEOQ);
            aParent->AddDictionary(aKey, aValueNode);
            delete aKey;
            aPtr = aEOQ;
            ++aPtr;
        } else if (IsNumber(*aPtr)) {
            char *aEON = EndOfNumber(aPtr);
            if (aEON == NULL) {
                *pSuccess = false;
                delete aKey;
                return NULL;
            }
            
            FJSONNode *aValueNode = new FJSONNode();
            aValueNode->mValue = GetNumber(aPtr, aEON);
            aParent->AddDictionary(aKey, aValueNode);
            delete aKey;
            aPtr = aEON;
            ++aPtr;
        } else if (IsAlphabetic(*aPtr)) {
            char *aEOA = EndOfAlphabetic(aPtr);
            if (aEOA == NULL) {
                *pSuccess = false;
                delete aKey;
                return NULL;
            }
            
            FJSONNode *aValueNode = new FJSONNode();
            aValueNode->mValue = GetNumber(aPtr, aEOA);
            aParent->AddDictionary(aKey, aValueNode);
            delete aKey;
            aPtr = aEOA;
            ++aPtr;
        } else {
            *pSuccess = false;
            delete aKey;
            return NULL;
        }
        ++aElementIndex;
    }
    
ParseHelperDictionary_COMPLETE:
    
    return aPtr;
}

//Assume that we pass in character AFTER the "["
//with the parent node as last item on pStack
char *FJSON::ParseHelperArray(char *pData, FList *pStack, bool *pSuccess) {
    FJSONNode *aParent = (FJSONNode *)pStack->Last();
    
    if (aParent == NULL) {
        *pSuccess = false;
        return NULL;
    }
    
    int aElementIndex = 0;
    char *aPtr = pData;
    while (*aPtr) {
        while ((*aPtr != 0) && IsWhiteSpace(*aPtr)) { aPtr++; }
        if (aElementIndex > 0) {
            if (*aPtr == ',') {
                aPtr += 1;
            } else if (*aPtr == ']') {
                aPtr += 1;
                goto ParseHelperArray_COMPLETE;
            } else {
                *pSuccess = false;
                return NULL;
            }
        } else {
            if (*aPtr == '}') {
                ++aPtr;
                goto ParseHelperArray_COMPLETE;
            }
        }
        
        while ((*aPtr != 0) && IsWhiteSpace(*aPtr)) { aPtr++; }
        
        if (*aPtr == '{') {
            ++aPtr;
            FJSONNode *aNode = new FJSONNode();
            aNode->mType = JSON_TYPE_DICTIONARY;
            aParent->AddArray(aNode);
            pStack->Add(aNode);
            aPtr = ParseHelperDictionary(aPtr, pStack, pSuccess);
            if (*pSuccess == false) {
                return NULL;
            }
            pStack->PopLast();
            
        } else if (*aPtr == '[') {
            ++aPtr;
            FJSONNode *aNode = new FJSONNode();
            aNode->mType = JSON_TYPE_ARRAY;
            aParent->AddArray(aNode);
            pStack->Add(aNode);
            aPtr = ParseHelperArray(aPtr, pStack, pSuccess);
            if (*pSuccess == false) {
                return NULL;
            }
            pStack->PopLast();
        } else if (*aPtr == '\"') {
            char *aEOQ = EndOfQuote(aPtr);
            if (aEOQ == NULL) {
                *pSuccess = false;
                return NULL;
            }
            FJSONNode *aValueNode = new FJSONNode();
            aValueNode->mValue = GetQuotedString(aPtr, aEOQ);
            aParent->AddArray(aValueNode);
            aPtr = aEOQ;
            ++aPtr;
        } else if (IsNumber(*aPtr)) {
            char *aEON = EndOfNumber(aPtr);
            if (aEON == NULL) {
                *pSuccess = false;
                return NULL;
            }
            FJSONNode *aValueNode = new FJSONNode();
            aValueNode->mValue = GetNumber(aPtr, aEON);
            aParent->AddArray(aValueNode);
            aPtr = aEON;
            ++aPtr;
        } else if (IsAlphabetic(*aPtr)) {
            char *aEOA = EndOfAlphabetic(aPtr);
            if (aEOA == NULL) {
                *pSuccess = false;
                return NULL;
            }
            FJSONNode *aValueNode = new FJSONNode();
            aValueNode->mValue = GetAlphabetic(aPtr, aEOA);
            aParent->AddArray(aValueNode);
            aPtr = aEOA;
            ++aPtr;
        } else {
            *pSuccess = false;
            return NULL;
        }
        ++aElementIndex;
    }
    
ParseHelperArray_COMPLETE:
    
    return aPtr;
}
