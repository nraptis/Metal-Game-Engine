//
//  FJSON.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/17/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef FJSON_hpp
#define FJSON_hpp

#include "FString.h"
#include "FList.hpp"
#include "FHashMap.hpp"

#define JSON_TYPE_UNDEFINED -1
#define JSON_TYPE_DICTIONARY 0
#define JSON_TYPE_ARRAY 1

class FJSONNode {
public:
    FJSONNode();
    ~FJSONNode();
    
    void                        AddDictionary(const char *pKey, FJSONNode *pNode);
    void                        AddArray(FJSONNode *pNode);
    
    const char                  *mKey;
    const char                  *mValue;
    
    FJSONNode                   **mList;
    int                         mListCount;
    int                         mListSize;
    
    FStringMap                  *mInfo;
    int                         mInfoCount;
    
    int                         mType;
    
    void                        Print();
    void                        Print(int pDepth);
    
};

class FJSON {
public:
    FJSON();
    ~FJSON();
    
    
    void                        Clear();
    
    void                        Load(const char *pFile);
    void                        Parse(const char *pData, int pLength);
    
    FJSONNode                   *mRoot;
    
private:
    
    inline bool                 IsWhiteSpace(char pChar) { return pChar <= 32; }
    inline bool                 IsNumber(char pChar) {
        if (pChar >= '0' && pChar <= '9') { return true; }
        if (pChar == '-') { return true; }
        if (pChar == '+') { return true; }
        if (pChar == '.') { return true; }
        return false;
    }
    
    inline bool                 IsAlphabetic(char pChar) {
        if (pChar >= 'a' && pChar <= 'z') { return true; }
        if (pChar >= 'A' && pChar <= 'Z') { return true; }
        return false;
    }
    
    inline char                 *EndOfQuote(char *pChar) {
        //Assumption *pChar = '\"'
        ++pChar;
        while (*pChar != 0) {
            if (*pChar == '\"') {
                return pChar;
            } else if (*pChar == '\\') {
                pChar++;
                if (*pChar == 'b' ||
                    *pChar == 'f' ||
                    *pChar == 'n' ||
                    *pChar == 'r' ||
                    *pChar == 't' ||
                    *pChar == '\"' ||
                    *pChar == '\\') {
                    pChar++;
                } else {
                    printf("Illegal character following \\\n\n\n");
                    return 0;
                }
            } else {
                ++pChar;
            }
        }
        return NULL;
    }
    
    
    inline char                 *GetQuotedString(char *pStart, char *pEnd) {
        
        int aLength = (int)(pEnd - pStart);
        char *aResult = new char[aLength + 1];
        
        char *aPaste = aResult;
        char *aCopy = pStart + 1;
        while (aCopy < pEnd) {
            if (*aCopy == '\\') {
                ++aCopy;
                if (*aCopy == 'b') {
                    *aPaste++ = '\b';
                    aCopy++;
                } else if (*aCopy == 'f') {
                    *aPaste++ = '\f';
                    aCopy++;
                } else if (*aCopy == 'n') {
                    *aPaste++ = '\n';
                    aCopy++;
                } else if (*aCopy == 'r') {
                    *aPaste++ = '\r';
                    aCopy++;
                } else if (*aCopy == 't') {
                    *aPaste++ = '\t';
                    aCopy++;
                } else if (*aCopy == '\"') {
                    *aPaste++ = '\"';
                    aCopy++;
                } else if (*aCopy == '\\') {
                    *aPaste++ = '\\';
                    aCopy++;
                }
            } else {
                *aPaste++ = *aCopy++;
            }
        }
        *aPaste = 0;
        return aResult;
    }
    
    
    
    inline char                 *EndOfNumber(char *pChar) {
        //Assumption *pChar = NUM
        ++pChar;
        while (IsNumber(*pChar)) {
            ++pChar;
        }
        --pChar;
        return pChar;
    }
    
    
    inline char                 *GetNumber(char *pStart, char *pEnd) {
        
        int aLength = (int)(pEnd - pStart);
        char *aResult = new char[aLength + 1];
        char *aPaste = aResult;
        char *aCopy = pStart;
        while (aCopy <= pEnd) {
            *aPaste++ = *aCopy++;
        }
        *aPaste = 0;
        return aResult;
    }
    
    
    
    inline char                 *EndOfAlphabetic(char *pChar) {
        //Assumption *pChar = NUM
        ++pChar;
        while (IsAlphabetic(*pChar)) {
            ++pChar;
        }
        --pChar;
        return pChar;
    }
    
    
    inline char                 *GetAlphabetic(char *pStart, char *pEnd) {
        
        int aLength = (int)(pEnd - pStart);
        char *aResult = new char[aLength + 1];
        char *aPaste = aResult;
        char *aCopy = pStart;
        while (aCopy <= pEnd) {
            *aPaste++ = *aCopy++;
        }
        *aPaste = 0;
        return aResult;
    }
    
    
    
    
    //Assume that we pass in character AFTER the "{"
    //with the parent node as last item on pStack
    char                        *ParseHelperDictionary(char *pData, FList *pStack, bool *pSuccess);
    
    //Assume that we pass in character AFTER the "["
    //with the parent node as last item on pStack
    char                        *ParseHelperArray(char *pData, FList *pStack, bool *pSuccess);
    
    
};



#endif /* FJSON_hpp */
