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

class LevelSection;
class LevelSectionBlueprint {
public:
    LevelSectionBlueprint();
    ~LevelSectionBlueprint();
    
    void                                        Clear();
    
    void                                        Update();
    void                                        Draw();
    
    void                                        WaveAdd();
    void                                        WaveRemove();
    void                                        WaveSelectNext();
    void                                        WaveSelectPrev();
    void                                        WaveDeselect();
    void                                        WaveMoveUp();
    void                                        WaveMoveDown();
    void                                        WaveSelect(int pIndex);
    int                                         WaveCount(int pIndex);

    
    FList                                       mWaveList;
    LevelWaveBlueprint                          *mCurrentWave;
    
    
    void                                        Build();
    void                                        Build(LevelSection *pSection);
    
    
    FJSONNode                                   *Save();
    void                                        Load(FJSONNode *pNode);
    
    
    FList                                       mKillList;
    FList                                       mDeleteList;
    
};

#endif /* LevelSectionBlueprint_hpp */
