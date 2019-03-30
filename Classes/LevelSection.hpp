//
//  LevelSection.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/14/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelSection_hpp
#define LevelSection_hpp

#include "GameObject.hpp"
#include "LevelWave.hpp"

class LevelSection {
public:
    LevelSection();
    ~LevelSection();
    
    void                                Reset();
    void                                Restart();
    
    void                                Spawn();
    void                                Update();
    void                                Draw();
    
    void                                Dispose();
    void                                DisposeObject(GameObject *pObject);
    void                                DisposeWave(LevelWave *pLevelWave);
    
    void                                AddWave(LevelWave *pLevelWave);
    FList                               mWaveList;
    LevelWave                           *mCurrentWave;
    int                                 mCurrentWaveIndex;
    
    int                                 mDelay;
    
    bool                                mIsComplete;
    
    int                                 mKillTimer;
    
    FList                               mKillList;
    FList                               mDeleteList;
    
};

#endif /* LevelSection_hpp */
