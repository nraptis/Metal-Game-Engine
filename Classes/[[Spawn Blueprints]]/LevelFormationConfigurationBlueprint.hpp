//
//  LevelFormationConfigurationBlueprint.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nick Raptis on 9/8/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelFormationConfigurationBlueprint_hpp
#define LevelFormationConfigurationBlueprint_hpp

#include "FJSON.hpp"
#include "LevelMotionControllerBlueprint.hpp"

class LevelFormationConfiguration;
class LevelFormationConfigurationBlueprint {
public:
    LevelFormationConfigurationBlueprint();
    ~LevelFormationConfigurationBlueprint();
    
    void                                        Reset();
    
    FJSONNode                                   *Save();
    void                                        Load(FJSONNode *pNode);
    
    void                                        Build(LevelFormationConfiguration *pConfiguration);
    
    int                                         mTracerSpeedGlobal;
    int                                         mTracerSpeed1;
    int                                         mTracerSpeed2;
    int                                         mTracerSpeed3;
    int                                         mTracerSpeed4;
    int                                         mTracerSpeed5;
    int                                         mTracerSpeed6;
    int                                         mTracerSpeed7;
    int                                         mTracerSpeed8;
    
    
};

#endif /* LevelFormationConfigurationBlueprint_hpp */
