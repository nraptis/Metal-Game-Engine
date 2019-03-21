//
//  LevelWaveBlueprint.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelWaveBlueprint_hpp
#define LevelWaveBlueprint_hpp

#include "LevelWavePathBlueprint.hpp"


class LevelWaveBlueprint {
public:
    LevelWaveBlueprint();
    ~LevelWaveBlueprint();
    
    void                                        Clear();
    
    void                                        Draw(bool pSelected);
    LevelWavePathBlueprint                      mPath;
    
    bool                                        mSmooth;
    float                                       mSpeed;
    
    void                                        ApplyEditorConstraints();
    
    void                                        Build();
    void                                        Build(LevelWavePath *pPath);
    
    FJSONNode                                   *Save();
    void                                        Load(FJSONNode *pNode);
    
};

#endif
