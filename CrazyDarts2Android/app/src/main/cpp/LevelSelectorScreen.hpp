//
//  LevelSelectorScreen.hpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/13/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#ifndef LevelSelectorScreen_hpp
#define LevelSelectorScreen_hpp

#include "FScrollCanvasPaged.hpp"

class LightConfigurationScene;

class LevelSelectorScreen : public FScrollCanvasPaged {
public:
    LevelSelectorScreen();
    virtual ~LevelSelectorScreen();
    
    
    LightConfigurationScene                 *mPage1;
    FCanvas                                 *mPage2;
    FCanvas                                 *mPage3;
    
    
    
};


#endif

