//
//  LevelSectionBlueprint.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelSectionBlueprint_hpp
#define LevelSectionBlueprint_hpp

#include "LevelWaveBlueprint.hpp"
#include "FList.hpp"

class LevelSectionBlueprint {
public:
    LevelSectionBlueprint();
    ~LevelSectionBlueprint();
    
    void                                        Draw();
    
    
    void                                        WaveAdd();
    void                                        WaveRemove();
    void                                        WaveSelectNext();
    void                                        WaveSelectPrev();
    void                                        WaveDeselect();
    
    
    FList                                       mWaveList;
    
    LevelWaveBlueprint                          *mCurrentWave;
    
    
    
};

#endif /* LevelSectionBlueprint_hpp */
