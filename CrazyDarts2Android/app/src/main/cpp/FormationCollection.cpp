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
    
    //FList                               mNameList;
    //FList                               mFormationList;
    
    FreeList(FString, mNameList);
    FreeList(LevelWaveSpawnFormation, mFormationList);
    
    /*
    FStringMapNode *aNode = mMap.mListHead;
    while (aNode != NULL) {
        LevelWaveSpawnFormation *aFormation = ((LevelWaveSpawnFormation *)aNode->mObject);
        delete aFormation;
        aNode = aNode->mListNext;
    }
    */
}

void FormationCollection::Load() {
    
    FreeList(FString, mNameList);
    FreeList(LevelWaveSpawnFormation, mFormationList);
    mMap.RemoveAll();
    
    
    mNameList.Add(new FString("formation_square_2x2_filled_stationary"));
    mNameList.Add(new FString("formation_square_3x3_filled_stationary"));
    mNameList.Add(new FString("formation_square_3x3_outline_stationary"));
    mNameList.Add(new FString("formation_square_4x4_filled_stationary"));
    mNameList.Add(new FString("formation_square_4x4_outline_stationary"));
    mNameList.Add(new FString("formation_square_5x5_filled_stationary"));
    mNameList.Add(new FString("formation_square_5x5_outline_stationary"));
    mNameList.Add(new FString("formation_2count_tracer_3x5_rect_s_stationary"));
    mNameList.Add(new FString("formation_4count_tracer_3x3_rect_ms_stationary"));
    mNameList.Add(new FString("formation_3count_tracer_3x3_rect_s_2count_line_9_hor_stationary"));
    mNameList.Add(new FString("formation_octosquare_7x7_filled_stationary"));
    mNameList.Add(new FString("formation_octosquare_7x7_outline_stationary"));
    mNameList.Add(new FString("formation_octosquare_7x7_outline_cross_stationary"));
    mNameList.Add(new FString("formation_tracer_5x5_rect_xs_tracer_3x3_rect_xs_stationary"));
    
    mNameList.Add(new FString("formation_6count_tracer_2x4_rect_xs_stationary"));
    
    
    
    
    
    
    
    
    
    
    EnumList(FString, aString, mNameList) {
        
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
        aFormation->mID = pName;
        mFormationList.Add(aFormation);
        
        printf("Loaded Formation [%llx][%s]\n", (unsigned long long)aFormation, pName);
        
        return true;
    }
    return false;
}

LevelWaveSpawnFormation *FormationCollection::Get(const char *pName) {
    
    LevelWaveSpawnFormation *aFormation = (LevelWaveSpawnFormation *)mMap.Get(pName);
    if (aFormation != NULL) {
        //IMPORTANT: Are you cloning all the variables correctly?
        return aFormation->Clone();
    }
    return NULL;
}
