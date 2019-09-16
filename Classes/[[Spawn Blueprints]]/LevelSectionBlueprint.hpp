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
#include "LevelSectionPermBlueprint.hpp"
#include "FList.hpp"

class LevelSection;
class LevelSectionBlueprint {
public:
    LevelSectionBlueprint();
    ~LevelSectionBlueprint();
    
    void                                        Reset();
    
    void                                        Update();
    void                                        Draw();
    
    void                                        WaveAdd();
    void                                        WaveInsert();
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
    
    void                                        PermAdd(float pX, float pY);
    void                                        PermRemove();
    void                                        PermSelectNext();
    void                                        PermSelectPrev();
    void                                        PermDeselect();
    void                                        PermMoveUp();
    void                                        PermMoveDown();
    void                                        PermSelect(int pIndex);
    int                                         PermSelectClosest(float pX, float pY);
    void                                        PermRefreshPositions();
    
    FList                                       mPermList;
    LevelSectionPermBlueprint              *mCurrentPerm;
    
    void                                        Build();
    void                                        Build(LevelSection *pSection);
    
    FJSONNode                                   *Save();
    void                                        Load(FJSONNode *pNode);
    
    FList                                       mKillWaveList;
    FList                                       mDeleteWaveList;
    
    FList                                       mKillPermList;
    FList                                       mDeletePermList;
};

#endif /* LevelSectionBlueprint_hpp */
