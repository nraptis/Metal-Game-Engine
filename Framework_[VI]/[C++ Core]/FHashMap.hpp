//
//  FHashMap.hpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/3/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#ifndef FHashMap_hpp
#define FHashMap_hpp

#include "FList.hpp"

class FHashMap;
class FHashMapNode {
    friend class FHashMap;
    
public:
    FHashMapNode();
    virtual ~FHashMapNode();
    
    void                                        *mKey;
    void                                        *mObject;
    
private:
    
    FHashMapNode                                *mListPrev;
    FHashMapNode                                *mListNext;
    FHashMapNode                                *mTableNext;
    int                                         mTableIndex;
    
};

class FHashMap {
public:
    FHashMap();
    ~FHashMap();
    
    void                                        Add(void *pKey, void *pObject);
    void                                        Remove(void *pKey);
    bool                                        Exists(void *pKey);
    void                                        *Get(void *pKey);
    
    static inline unsigned int                  Hash(void *pKey) {
        unsigned long aResult = (unsigned long)pKey;
        aResult = ((aResult >> 16) ^ (aResult));
        return (unsigned int)aResult;
    }
    
    static int                                  IncreaseTableSize(int pTableCount);
    
    bool                                        IsEmpty();
    
    void                                        RemoveAll();
    
    void                                        AddObjectsToList(FList *pList);
    void                                        AddObjectsToListAndRemoveAll(FList *pList);
    
    void                                        GetAllNodes(void *pKey, FList &pList);
    
public:
    void                                        Print();
    void                                        PrintList();
    FHashMapNode                                *mListHead;
    FHashMapNode                                *mListTail;
    
protected:
    
    void                                        ListAdd(FHashMapNode *pNode);
    void                                        ListRemove(FHashMapNode *pNode);
    void                                        SetTableSize(int pSize);
    
    FHashMapNode                                **mTable;
    int                                         mTableCount;
    int                                         mTableSize;
    
    FList                                       mQueue;
};

class FIntMap;
class FIntMapNode {
    friend class FIntMap;
    
public:
    FIntMapNode();
    virtual ~FIntMapNode();
    
    int                                         mKey;
    void                                        *mObject;
    
private:
    
    FIntMapNode                                 *mListPrev;
    FIntMapNode                                 *mListNext;
    FIntMapNode                                 *mTableNext;
    int                                         mTableIndex;
    
};

class FIntMap {
public:
    FIntMap();
    ~FIntMap();
    
    void                                        Add(int pKey, void *pObject);
    void                                        Remove(int pKey);
    bool                                        Exists(int pKey);
    void                                        *Get(int pKey);
    
    static inline unsigned int                  Hash(int pKey) {
        unsigned long aResult = (unsigned long)pKey;
        aResult = ((aResult >> 16) ^ (aResult));
        return (unsigned int)aResult;
    }
    
    bool                                        IsEmpty();
    
    void                                        RemoveAll();
    
    void                                        AddObjectsToList(FList *pList);
    void                                        AddObjectsToListAndRemoveAll(FList *pList);
    
public:
    void                                        Print();
    void                                        PrintList();
    FIntMapNode                                *mListHead;
    FIntMapNode                                *mListTail;
    
protected:
    
    void                                        ListAdd(FIntMapNode *pNode);
    void                                        ListRemove(FIntMapNode *pNode);
    void                                        SetTableSize(int pSize);
    
    FIntMapNode                                **mTable;
    int                                         mTableCount;
    int                                         mTableSize;
    
    FList                                       mQueue;
};

#endif /* FHashMap_hpp */
