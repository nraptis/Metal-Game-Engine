//
//  LevelFormationConfiguration.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nick Raptis on 9/8/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelFormationConfiguration_hpp
#define LevelFormationConfiguration_hpp

#include "GameObject.hpp"

class LevelFormation;
class LevelFormationConfiguration {
public:
    LevelFormationConfiguration();
    ~LevelFormationConfiguration();
    
    void                                        Reset();
    void                                        Apply(LevelFormation *pFormation);
    
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

#endif /* LevelFormationConfiguration_hpp */
