//
//  FormationCollection.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/1/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "FormationCollection.hpp"
#include "LevelFormationBlueprint.hpp"

#include "FJSON.hpp"

FormationCollection gFormationCollection;

FormationCollection::FormationCollection() {
    
}

FormationCollection::~FormationCollection() {
    
    //FList                               mNameList;
    //FList                               mFormationList;
    
    FreeList(FString, mNameList);
    FreeList(LevelFormation, mFormationList);
    
    /*
     FStringMapNode *aNode = mMap.mListHead;
     while (aNode != NULL) {
     LevelFormation *aFormation = ((LevelFormation *)aNode->mObject);
     delete aFormation;
     aNode = aNode->mListNext;
     }
     */
}

void FormationCollection::Load() {
    
    FreeList(FString, mNameList);
    FreeList(LevelFormation, mFormationList);
    mMap.RemoveAll();
    
    
    
    mNameList.Add(new FString("f_grid_rect_2x2_44spc_solid__nodes_cfg4xb"));
    mNameList.Add(new FString("f_grid_rect_3x3_44spc_solid__nodes_cfg9xb"));
    mNameList.Add(new FString("f_grid_rect_4x4_44spc_solid__nodes_cfg16xb"));
    mNameList.Add(new FString("f_grid_rect_5x5_44spc_solid__nodes_cfg25xb"));
    mNameList.Add(new FString("f_grid_rect_4x4_44spc_75ful__nodes_cfg12xb"));
    mNameList.Add(new FString("f_grid_rect_5x5_44spc_64ful__nodes_cfg16xb"));
    mNameList.Add(new FString("f_grid_80rngs_1rngc_10radc_91ful__nodes_cfg10xb"));
    mNameList.Add(new FString("f_grid_60rngs_1rngc_8radc_89ful__nodes_cfg8xb"));
    mNameList.Add(new FString("f_grid_46rngs_1rngc_6radc_solid__nodes_cfg7xb"));
    mNameList.Add(new FString("f_grid_46rngs_1rngc_6radc_86ful__nodes_cfg6xb"));
    mNameList.Add(new FString("f_grid_6sid_50rngs_2rngc_40pnts_6pnts_95ful__nodes_cfg18xb"));
    mNameList.Add(new FString("f_grid_6sid_50rngs_2rngc_40pnts_6pnts_solid__nodes_cfg19xb"));
    mNameList.Add(new FString("f_grid_5sid_50rngs_2rngc_40pnts_6pnts_solid__nodes_cfg16xb"));
    mNameList.Add(new FString("f_grid_5sid_50rngs_2rngc_40pnts_6pnts_94ful__nodes_cfg15xb"));
    mNameList.Add(new FString("f_grid_4sid_50rngs_2rngc_30pnts_1pnts_62ful__nodes_cfg13xb"));
    mNameList.Add(new FString("f_tr_circ_90sz_cfg5xb_spms"));
    mNameList.Add(new FString("f_tr_circ_110sz_cfg6xb_spms"));
    mNameList.Add(new FString("f_grid_rect_1x1_44spc_solid__nodes_cfg1xb__tr_circ_110sz_cfg6xb_spms"));
    mNameList.Add(new FString("f_tr_circ_130sz_cfg7xb_spms"));
    mNameList.Add(new FString("f_grid_rect_1x1_44spc_solid__nodes_cfg1xb__tr_circ_130sz_cfg7xb_spms"));
    mNameList.Add(new FString("f_tr_circ_150sz_cfg8xb_spms"));
    mNameList.Add(new FString("f_grid_rect_1x1_44spc_solid__nodes_cfg1xb__tr_circ_150sz_cfg8xb_spms"));
    mNameList.Add(new FString("f_tr_rrct_200sz_65cr_cfg6xb_spxs"));
    
    
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
    mNameList.Add(new FString("formation_tracer_circle_250r_stationary"));
    mNameList.Add(new FString("formation_tracer_rr_250r_60cr_stationary"));
    mNameList.Add(new FString("formation_tracer_rr_250r_60cr_point_1x1_stationary"));
    
    
    mNameList.Add(new FString("f_tr_14ct_rrct_400rd_100cr_spxs"));
    mNameList.Add(new FString("f_tr_brbrbrbrbr_circ_250rd_spxs~tr_8ct_circ_140rd_spxs.json"));
    
                  
                  
    
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
    LevelFormationBlueprint aBlueprint;
    aBlueprint.Load(aJSON.mRoot);
    if (aBlueprint.IsValid()) {
        LevelFormation *aFormation = new LevelFormation();
        aBlueprint.Build(aFormation);
        mMap.Add(pName, aFormation);
        aFormation->mID = pName;
        mFormationList.Add(aFormation);
        
        printf("Loaded Formation [%llx][%s]\n", (unsigned long long)aFormation, pName);
        
        return true;
    }
    
    return false;
}

LevelFormation *FormationCollection::Get(const char *pName) {
    
    LevelFormation *aFormation = (LevelFormation *)mMap.Get(pName);
    if (aFormation != NULL) {
        //IMPORTANT: Are you cloning all the variables correctly?
        return aFormation->Clone();
    }
    return NULL;
}
