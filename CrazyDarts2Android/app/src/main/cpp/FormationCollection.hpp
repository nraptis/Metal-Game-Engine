//
//  FormationCollection.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/1/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef FormationCollection_hpp
#define FormationCollection_hpp

#include "FList.hpp"
#include "FString.h"
#include "FHashMap.hpp"
#include "LevelWaveSpawnFormation.hpp"


class FormationCollection {
public:
    FormationCollection();
    ~FormationCollection();
    
    void                                Load();
    bool                                Load(const char *pName);
    
    LevelWaveSpawnFormation             *Get(const char *pName);
    
    FList                               mNameList;
    FList                               mFormationList;
    
    FStringMap                          mMap;
    
};

extern FormationCollection gFormationCollection;

#endif
