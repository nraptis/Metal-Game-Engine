//
//  LevelData.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/10/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelData_hpp
#define LevelData_hpp

#include "GameObject.hpp"
#include "LevelWave.hpp"
#include "LevelSection.hpp"

//test_section_01.json
//test_section_02.json
//test_section_03.json
//test_section_04.json


class LevelData {
public:
    LevelData();
    virtual ~LevelData();
    
    void                            Update();
    
    void                            DisposeObject(GameObject *pObject);
    void                            DisposeSection(LevelSection *pLevelSection);
    
    void                            Print(const char *pName);
    
    void                            AddSection(LevelSection *pLevelSection);
    FList                           mSectionList;
    LevelSection                    *mCurrentSection;
    int                             mCurrentSectionIndex;
    
    int                             mInitialDelay;
};

#endif /* LevelData_hpp */
