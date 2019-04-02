//
//  FormationCollection.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/1/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "FormationCollection.hpp"
#include "LevelWaveSpawnFormationBlueprint.hpp"

#include "FJSON.hpp"

FormationCollection gFormationCollection;

FormationCollection::FormationCollection() {
    
}

FormationCollection::~FormationCollection() {
    
    FreeList(FString, mList);
    
    FStringMapNode *aNode = mMap.mListHead;
    while (aNode != NULL) {
        LevelWaveSpawnFormation *aFormation = ((LevelWaveSpawnFormation *)aNode->mObject);
        delete aFormation;
        aNode = aNode->mListNext;
    }
}

void FormationCollection::Load() {
    
    FreeList(FString, mList);
    
    mList.Add(new FString("formation_square_2x2_filled_stationary"));
    mList.Add(new FString("formation_square_3x3_filled_stationary"));
    mList.Add(new FString("formation_square_3x3_outline_stationary"));
    mList.Add(new FString("formation_square_4x4_filled_stationary"));
    mList.Add(new FString("formation_square_4x4_outline_stationary"));
    mList.Add(new FString("formation_square_5x5_filled_stationary"));
    mList.Add(new FString("formation_square_5x5_outline_stationary"));
    
    EnumList(FString, aString, mList) {
        
        if (Load(aString->c())) {
            
        } else {
            printf("FAILED to Load Formation [%s]\n", aString->c());
        }
    }
    
    
    
}

bool FormationCollection::Load(const char *pName) {
    FJSON aJSON;
    aJSON.Load(pName);
    LevelWaveSpawnFormationBlueprint aBlueprint;
    aBlueprint.Load(aJSON.mRoot);
    if (aBlueprint.IsValid()) {
        LevelWaveSpawnFormation *aFormation = new LevelWaveSpawnFormation();
        aBlueprint.Build(aFormation);
        mMap.Add(pName, aFormation);
        
        printf("Loaded Formation [%llx][%s]\n", (unsigned long long)aFormation, pName);
        
        return true;
    }
    return false;
}

