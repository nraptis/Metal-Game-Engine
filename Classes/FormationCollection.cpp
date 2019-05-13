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
    
    //Rect Grid Types...
    mNameList.Add(new FString("f_grid_rect_1x4_46spc_solid__nodes_cfg4xb_allg.json"));
    mNameList.Add(new FString("f_grid_rect_1x5_46spc_solid__nodes_cfg5xb_allg.json"));
    mNameList.Add(new FString("f_grid_rect_1x6_46spc_solid__nodes_cfg6xb_allg.json"));
    mNameList.Add(new FString("f_grid_rect_2x2_44spc_solid__nodes_cfg4xb_allg.json"));
    mNameList.Add(new FString("f_grid_rect_3x3_34spc_33ful__nodes_cfg3xb_allg.json"));
    mNameList.Add(new FString("f_grid_rect_3x3_34spc_56ful__nodes_cfg5xb_allg.json"));
    mNameList.Add(new FString("f_grid_rect_3x3_44spc_33ful__nodes_cfg3xb_allg.json"));
    mNameList.Add(new FString("f_grid_rect_3x3_44spc_56ful__nodes_cfg5xb_allg.json"));
    mNameList.Add(new FString("f_grid_rect_3x3_44spc_89ful__nodes_cfg8xb_allg.json"));
    mNameList.Add(new FString("f_grid_rect_3x3_44spc_solid__nodes_cfg9xb_allg.json"));
    mNameList.Add(new FString("f_grid_rect_4x1_46spc_solid__nodes_cfg4xb_allg.json"));
    mNameList.Add(new FString("f_grid_rect_4x4_34spc_25ful__nodes_cfg4xb_allg.json"));
    mNameList.Add(new FString("f_grid_rect_4x4_46spc_50ful__nodes_cfg8xb_allg.json"));
    mNameList.Add(new FString("f_grid_rect_4x4_46spc_75ful__nodes_cfg12xb_allg.json"));
    mNameList.Add(new FString("f_grid_rect_4x4_46spc_solid__nodes_cfg16xb_allg.json"));
    mNameList.Add(new FString("f_grid_rect_5x1_46spc_solid__nodes_cfg5xb_allg.json"));
    mNameList.Add(new FString("f_grid_rect_5x5_34spc_20ful__nodes_cfg5xb_allg.json"));
    mNameList.Add(new FString("f_grid_rect_5x5_34spc_36ful__nodes_cfg9xb_allg.json"));
    mNameList.Add(new FString("f_grid_rect_5x5_46spc_52ful__nodes_cfg13xb_allg.json"));
    mNameList.Add(new FString("f_grid_rect_5x5_46spc_64ful__nodes_cfg16xb_allg.json"));
    mNameList.Add(new FString("f_grid_rect_5x5_46spc_84ful__nodes_cfg21xb_allg.json"));
    mNameList.Add(new FString("f_grid_rect_5x5_46spc_96ful__nodes_cfg24xb_allg.json"));
    mNameList.Add(new FString("f_grid_rect_5x5_46spc_solid__nodes_cfg25xb_allg.json"));
    mNameList.Add(new FString("f_grid_rect_6x1_46spc_solid__nodes_cfg6xb_allg.json"));
    mNameList.Add(new FString("f_grid_rect_6x6_34spc_17ful__nodes_cfg6xb_allg.json"));
    mNameList.Add(new FString("f_grid_rect_6x6_46spc_89ful__nodes_cfg32xb_allg.json"));
    mNameList.Add(new FString("f_grid_rect_6x6_46spc_solid__nodes_cfg36xb_allg.json"));
    
    mNameList.Add(new FString("f_grid_circ_40rngs_1rngc_5radc_83ful__nodes_cfg5xb_allg.json"));
    mNameList.Add(new FString("f_grid_circ_46rngs_1rngc_6radc_86ful__nodes_cfg6xb_allg.json"));
    mNameList.Add(new FString("f_grid_circ_46rngs_1rngc_6radc_solid__nodes_cfg7xb_allg.json"));
    mNameList.Add(new FString("f_grid_circ_56rngs_1rngc_7radc_88ful__nodes_cfg7xb_allg.json"));
    mNameList.Add(new FString("f_grid_circ_56rngs_1rngc_7radc_solid__nodes_cfg8xb_allg.json"));
    mNameList.Add(new FString("f_grid_circ_60rngs_1rngc_8radc_89ful__nodes_cfg8xb_allg.json"));
    mNameList.Add(new FString("f_grid_circ_60rngs_1rngc_8radc_solid__nodes_cfg9xb_allg.json"));
    mNameList.Add(new FString("f_grid_circ_70rngs_1rngc_9radc_solid__nodes_cfg10xb_allg.json"));
    mNameList.Add(new FString("f_grid_circ_70rngs_1rngc_9radc_90ful__nodes_cfg9xb_allg.json"));
    mNameList.Add(new FString("f_grid_circ_75rngs_1rngc_10radc_91ful__nodes_cfg10xb_allg.json"));
    mNameList.Add(new FString("f_grid_circ_75rngs_1rngc_10radc_solid__nodes_cfg11xb_allg.json"));
    mNameList.Add(new FString("f_grid_circ_82rngs_1rngc_11radc_92ful__nodes_cfg11xb_allg.json"));
    mNameList.Add(new FString("f_grid_circ_82rngs_1rngc_11radc_solid__nodes_cfg12xb_allg.json"));
    mNameList.Add(new FString("f_grid_circ_88rngs_1rngc_12radc_92ful__nodes_cfg12xb_allg.json"));
    mNameList.Add(new FString("f_grid_circ_88rngs_1rngc_12radc_solid__nodes_cfg13xb_allg.json"));
    mNameList.Add(new FString("f_grid_circ_92rngs_1rngc_12radc_92ful__nodes_cfg18xb12on6off.json"));
    mNameList.Add(new FString("f_grid_circ_120rngs_1rngc_16radc_94ful__nodes_cfg16xb_allg.json"));
    mNameList.Add(new FString("f_grid_circ_74rngs_1rngc_10radc_91ful__nodes_cfg26xb10on16off.json"));
    mNameList.Add(new FString("f_grid_circ_4x4_44spc_75ful__nodes_cfg28xb12on16off.json"));
    
    //Triangles...
    mNameList.Add(new FString("f_grid_tri_ngon1_3sid_91rngs_1rngc_42pnts_180roff_90ful__nodes_cfg9xb_allg.json"));
    mNameList.Add(new FString("f_grid_tri_ngon1_3sid_54rngs_1rngc_30pnts_86ful__nodes_cfg6xb_allg.json"));
    mNameList.Add(new FString("f_grid_tri_ngon1_3sid_54rngs_1rngc_30pnts_180roff_86ful__nodes_cfg6xb_allg.json"));
    mNameList.Add(new FString("f_grid_tri_ngon1_3sid_54rngs_1rngc_130pnts_180roff_solid__nodes_cfg4xb_allg.json"));
    mNameList.Add(new FString("f_grid_tri_ngon1_3sid_54rngs_1rngc_130pnts_solid__nodes_cfg4xb_allg.json"));
    mNameList.Add(new FString("f_grid_tri_ngon1_3sid_71rngs_2rngc_44pnts_68ful__nodes_cfg15xb_allg.json"));
    mNameList.Add(new FString("f_grid_tri_ngon1_3sid_71rngs_2rngc_44pnts_180roff_68ful__nodes_cfg15xb_allg.json"));
    mNameList.Add(new FString("f_grid_tri_ngon1_3sid_91rngs_1rngc_42pnts_90ful__nodes_cfg9xb_allg.json"));
    
    //Large Stars
    mNameList.Add(new FString("f_grid_large_star_01.json"));
    mNameList.Add(new FString("f_grid_large_star_02.json"));
    mNameList.Add(new FString("f_grid_large_star_03.json"));
    
    //Oddball Stars
    mNameList.Add(new FString("f_grid_star_72radi_34rado_0pntc_4armc_89ful__nodes_cfg8xb_allg.json"));
    mNameList.Add(new FString("f_grid_star_80radi_40rado_0pntc_5armc_35roff_91ful__nodes_cfg10xb_allg.json"));
    mNameList.Add(new FString("f_grid_star_80radi_40rado_0pntc_5armc_91ful__nodes_cfg10xb_allg.json"));
    mNameList.Add(new FString("f_grid_star_120radi_60rado_1pntc_5armc_23roff_29ful__nodes_cfg16xb6on10off.json"));
    
    //Pentagons
    mNameList.Add(new FString("f_grid_penta_ngon1_5sid_45rngs_1rngc_31pnts_35roff_83ful__nodes_cfg5xb_allg.json"));
    mNameList.Add(new FString("f_grid_penta_ngon1_5sid_45rngs_1rngc_31pnts_solid__nodes_cfg6xb_allg.json"));
    mNameList.Add(new FString("f_grid_penta_ngon1_5sid_45rngs_2rngc_31pnts_35roff_94ful__nodes_cfg15xb_allg.json"));
    mNameList.Add(new FString("f_grid_penta_ngon1_5sid_45rngs_2rngc_31pnts_solid__nodes_cfg16xb_allg.json"));
    mNameList.Add(new FString("f_grid_penta_ngon1_5sid_48rngs_3rngc_39pnts_35roff_48ful__nodes_cfg30xb15on15off.json"));
    mNameList.Add(new FString("f_grid_penta_ngon1_5sid_48rngs_3rngc_39pnts_35roff_solid__nodes_cfg31xb_allg.json"));
    mNameList.Add(new FString("f_grid_penta_ngon1_5sid_48rngs_3rngc_39pnts_solid__nodes_cfg31xb_allg.json"));
    
    //Hexagons
    mNameList.Add(new FString("f_grid_hexa_ngon1_6sid_46rngs_1rngc_30pnts_86ful__nodes_cfg6xb_allg.json"));
    mNameList.Add(new FString("f_grid_hexa_ngon1_6sid_46rngs_1rngc_30pnts_solid__nodes_cfg7xb_allg.json"));
    mNameList.Add(new FString("f_grid_hexa_ngon1_6sid_46rngs_1rngc_36pnts_30roff_86ful__nodes_cfg6xb_allg.json"));
    mNameList.Add(new FString("f_grid_hexa_ngon1_6sid_46rngs_1rngc_36pnts_30roff_solid__nodes_cfg7xb_allg.json"));
    mNameList.Add(new FString("f_grid_hexa_ngon1_6sid_46rngs_2rngc_30pnts_68ful__nodes_cfg13xb_allg.json"));
    mNameList.Add(new FString("f_grid_hexa_ngon1_6sid_46rngs_2rngc_30pnts_95ful__nodes_cfg18xb_allg.json"));
    mNameList.Add(new FString("f_grid_hexa_ngon1_6sid_46rngs_2rngc_30pnts_solid__nodes_cfg19xb_allg.json"));
    mNameList.Add(new FString("f_grid_hexa_ngon1_6sid_46rngs_2rngc_36pnts_30roff_63ful__nodes_cfg12xb_allg.json"));
    mNameList.Add(new FString("f_grid_hexa_ngon1_6sid_46rngs_2rngc_36pnts_30roff_95ful__nodes_cfg18xb_allg.json"));
    mNameList.Add(new FString("f_grid_hexa_ngon1_6sid_46rngs_2rngc_36pnts_30roff_solid__nodes_cfg19xb_allg.json"));
    mNameList.Add(new FString("f_grid_hexa_ngon1_6sid_46rngs_2rngc_40pnts_solid__nodes_cfg13xb_allg.json"));
    mNameList.Add(new FString("f_grid_hexa_ngon1_6sid_46rngs_3rngc_34pnts_49ful__nodes_cfg18xb_allg.json"));
    mNameList.Add(new FString("f_grid_hexa_ngon1_6sid_46rngs_3rngc_34pnts_81ful__nodes_cfg30xb_allg.json"));
    mNameList.Add(new FString("f_grid_hexa_ngon1_6sid_46rngs_3rngc_34pnts_97ful__nodes_cfg36xb_allg.json"));
    mNameList.Add(new FString("f_grid_hexa_ngon1_6sid_46rngs_3rngc_34pnts_solid__nodes_cfg37xb_allg.json"));
    mNameList.Add(new FString("f_grid_hexa_ngon1_6sid_46rngs_3rngc_36pnts_30roff_49ful__nodes_cfg18xb_allg.json"));
    mNameList.Add(new FString("f_grid_hexa_ngon1_6sid_46rngs_3rngc_36pnts_30roff_65ful__nodes_cfg24xb_allg.json"));
    mNameList.Add(new FString("f_grid_hexa_ngon1_6sid_46rngs_3rngc_36pnts_30roff_81ful__nodes_cfg30xb_allg.json"));
    mNameList.Add(new FString("f_grid_hexa_ngon1_6sid_46rngs_3rngc_36pnts_30roff_97ful__nodes_cfg36xb_allg.json"));
    mNameList.Add(new FString("f_grid_hexa_ngon1_6sid_46rngs_3rngc_36pnts_30roff_solid__nodes_cfg37xb_allg.json"));
    mNameList.Add(new FString("f_grid_hexa_ngon1_6sid_46rngs_3rngc_44pnts_96ful__nodes_cfg24xb_allg.json"));
    mNameList.Add(new FString("f_grid_hexa_ngon1_6sid_46rngs_3rngc_66pnts_95ful__nodes_cfg18xb_allg.json"));
    mNameList.Add(new FString("f_grid_hexa_ngon1_6sid_46rngs_3rngc_66pnts_solid__nodes_cfg19xb_allg.json"));
    
    //Circle tracers...
    mNameList.Add(new FString("f_tr_circ_80sz_cfg4xb_spm.json"));
    mNameList.Add(new FString("f_tr_circ_80sz_cfg4xb_spmf.json"));
    mNameList.Add(new FString("f_tr_circ_80sz_cfg4xb_spms.json"));
    mNameList.Add(new FString("f_tr_circ_80sz_cfg4xb_sps.json"));
    mNameList.Add(new FString("f_tr_circ_80sz_cfg4xb_spxs.json"));
    mNameList.Add(new FString("f_tr_circ_100sz_cfg5xb_spm.json"));
    mNameList.Add(new FString("f_tr_circ_100sz_cfg5xb_spmf.json"));
    mNameList.Add(new FString("f_tr_circ_100sz_cfg5xb_spms.json"));
    mNameList.Add(new FString("f_tr_circ_100sz_cfg5xb_sps.json"));
    mNameList.Add(new FString("f_tr_circ_100sz_cfg5xb_spxs.json"));
    mNameList.Add(new FString("f_tr_circ_120sz_cfg6xb_spm.json"));
    mNameList.Add(new FString("f_tr_circ_120sz_cfg6xb_spmf.json"));
    mNameList.Add(new FString("f_tr_circ_120sz_cfg6xb_spms.json"));
    mNameList.Add(new FString("f_tr_circ_120sz_cfg6xb_spxs.json"));
    mNameList.Add(new FString("f_tr_circ_140sz_cfg7xb_spm.json"));
    mNameList.Add(new FString("f_tr_circ_140sz_cfg7xb_spmf.json"));
    mNameList.Add(new FString("f_tr_circ_140sz_cfg7xb_spms.json"));
    mNameList.Add(new FString("f_tr_circ_140sz_cfg7xb_sps.json"));
    mNameList.Add(new FString("f_tr_circ_140sz_cfg7xb_spxs.json"));
    mNameList.Add(new FString("f_tr_circ_160sz_cfg8xb_spm.json"));
    mNameList.Add(new FString("f_tr_circ_160sz_cfg8xb_spmf.json"));
    mNameList.Add(new FString("f_tr_circ_160sz_cfg8xb_spms.json"));
    mNameList.Add(new FString("f_tr_circ_160sz_cfg8xb_sps.json"));
    mNameList.Add(new FString("f_tr_circ_160sz_cfg8xb_spxs.json"));
    mNameList.Add(new FString("f_tr_circ_180sz_cfg9xb_spm.json"));
    mNameList.Add(new FString("f_tr_circ_180sz_cfg9xb_spmf.json"));
    mNameList.Add(new FString("f_tr_circ_180sz_cfg9xb_spms.json"));
    mNameList.Add(new FString("f_tr_circ_180sz_cfg9xb_sps.json"));
    mNameList.Add(new FString("f_tr_circ_180sz_cfg9xb_spxs.json"));
    mNameList.Add(new FString("f_tr_circ_200sz_cfg10xb_spm.json"));
    mNameList.Add(new FString("f_tr_circ_200sz_cfg10xb_spmf.json"));
    mNameList.Add(new FString("f_tr_circ_200sz_cfg10xb_spms.json"));
    mNameList.Add(new FString("f_tr_circ_200sz_cfg10xb_sps.json"));
    mNameList.Add(new FString("f_tr_circ_200sz_cfg10xb_spxs.json"));
    
    //RR Tracers...
    mNameList.Add(new FString("f_tr_rrct_160sz_42cr_cfg2xb_spxs.json"));
    mNameList.Add(new FString("f_tr_rrct_140sz_42cr_cfg2xb_spm.json"));
    mNameList.Add(new FString("f_tr_rrct_140sz_42cr_cfg2xb_spmf.json"));
    mNameList.Add(new FString("f_tr_rrct_140sz_42cr_cfg2xb_spms.json"));
    mNameList.Add(new FString("f_tr_rrct_140sz_42cr_cfg2xb_sps.json"));
    mNameList.Add(new FString("f_tr_rrct_140sz_42cr_cfg2xb_spxs.json"));
    mNameList.Add(new FString("f_tr_rrct_140sz_42cr_cfg3xb_spm.json"));
    mNameList.Add(new FString("f_tr_rrct_140sz_42cr_cfg3xb_spmf.json"));
    mNameList.Add(new FString("f_tr_rrct_140sz_42cr_cfg3xb_spms.json"));
    mNameList.Add(new FString("f_tr_rrct_140sz_42cr_cfg3xb_sps.json"));
    mNameList.Add(new FString("f_tr_rrct_140sz_42cr_cfg3xb_spxs.json"));
    mNameList.Add(new FString("f_tr_rrct_140sz_42cr_cfg4xb_spm.json"));
    mNameList.Add(new FString("f_tr_rrct_140sz_42cr_cfg4xb_spmf.json"));
    mNameList.Add(new FString("f_tr_rrct_140sz_42cr_cfg4xb_spms.json"));
    mNameList.Add(new FString("f_tr_rrct_140sz_42cr_cfg4xb_sps.json"));
    mNameList.Add(new FString("f_tr_rrct_140sz_42cr_cfg4xb_spxs.json"));
    mNameList.Add(new FString("f_tr_rrct_160sz_42cr_cfg2xb_spm.json"));
    mNameList.Add(new FString("f_tr_rrct_160sz_42cr_cfg2xb_spmf.json"));
    mNameList.Add(new FString("f_tr_rrct_160sz_42cr_cfg2xb_spms.json"));
    mNameList.Add(new FString("f_tr_rrct_160sz_42cr_cfg2xb_sps.json"));
    mNameList.Add(new FString("f_tr_rrct_160sz_42cr_cfg5xb_spm.json"));
    mNameList.Add(new FString("f_tr_rrct_160sz_42cr_cfg5xb_spmf.json"));
    mNameList.Add(new FString("f_tr_rrct_160sz_42cr_cfg5xb_spms.json"));
    mNameList.Add(new FString("f_tr_rrct_160sz_42cr_cfg5xb_sps.json"));
    mNameList.Add(new FString("f_tr_rrct_160sz_42cr_cfg5xb_spxs.json"));
    mNameList.Add(new FString("f_tr_rrct_190sz_42cr_cfg6xb_spm.json"));
    mNameList.Add(new FString("f_tr_rrct_190sz_42cr_cfg6xb_spmf.json"));
    mNameList.Add(new FString("f_tr_rrct_190sz_42cr_cfg6xb_spms.json"));
    mNameList.Add(new FString("f_tr_rrct_190sz_42cr_cfg6xb_sps.json"));
    mNameList.Add(new FString("f_tr_rrct_190sz_42cr_cfg6xb_spxs.json"));
    mNameList.Add(new FString("f_tr_rrct_210sz_42cr_cfg7xb_spm.json"));
    mNameList.Add(new FString("f_tr_rrct_210sz_42cr_cfg7xb_spmf.json"));
    mNameList.Add(new FString("f_tr_rrct_210sz_42cr_cfg7xb_spms.json"));
    mNameList.Add(new FString("f_tr_rrct_210sz_42cr_cfg7xb_sps.json"));
    mNameList.Add(new FString("f_tr_rrct_210sz_42cr_cfg7xb_spxs.json"));
    mNameList.Add(new FString("f_tr_rrct_250sz_42cr_cfg8xb_spm.json"));
    mNameList.Add(new FString("f_tr_rrct_250sz_42cr_cfg8xb_spmf.json"));
    mNameList.Add(new FString("f_tr_rrct_250sz_42cr_cfg8xb_spms.json"));
    mNameList.Add(new FString("f_tr_rrct_250sz_42cr_cfg8xb_sps.json"));
    mNameList.Add(new FString("f_tr_rrct_250sz_42cr_cfg8xb_spxs.json"));
    mNameList.Add(new FString("f_tr_rrct_280sz_42cr_cfg9xb_spm.json"));
    mNameList.Add(new FString("f_tr_rrct_280sz_42cr_cfg9xb_spmf.json"));
    mNameList.Add(new FString("f_tr_rrct_280sz_42cr_cfg9xb_spms.json"));
    mNameList.Add(new FString("f_tr_rrct_280sz_42cr_cfg9xb_sps.json"));
    mNameList.Add(new FString("f_tr_rrct_280sz_42cr_cfg9xb_spxs.json"));
    mNameList.Add(new FString("f_tr_rrct_300sz_42cr_cfg10xb_spm.json"));
    mNameList.Add(new FString("f_tr_rrct_300sz_42cr_cfg10xb_spmf.json"));
    mNameList.Add(new FString("f_tr_rrct_300sz_42cr_cfg10xb_spms.json"));
    mNameList.Add(new FString("f_tr_rrct_300sz_42cr_cfg10xb_sps.json"));
    mNameList.Add(new FString("f_tr_rrct_300sz_42cr_cfg10xb_spxs.json"));
    mNameList.Add(new FString("f_tr_rrct_320sz_90cr_cfg10xb_spm.json"));
    mNameList.Add(new FString("f_tr_rrct_320sz_90cr_cfg10xb_spmf.json"));
    mNameList.Add(new FString("f_tr_rrct_320sz_90cr_cfg10xb_spms.json"));
    mNameList.Add(new FString("f_tr_rrct_320sz_90cr_cfg10xb_sps.json"));
    mNameList.Add(new FString("f_tr_rrct_320sz_90cr_cfg10xb_spxs.json"));
    
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
