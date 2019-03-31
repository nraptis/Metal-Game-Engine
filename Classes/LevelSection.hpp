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
    
    void                                DisposeObject(GameObject *pObject);
    
    void                                AddWave(LevelWave *pLevelWave);
    FList                               mWaveList;
    
    int                                 mCandidateWaveIndex;
    
    LevelWave                           *mCandidateWave;
    int                                 mCandidateWaveDelay;
    
    FList                               mActiveWaveList;
    FList                               mRemoveActiveWaveList;
    
    //Mainly for editor, if we want to start later in the queue
    int                                 mStartWaveIndex;
    
    int                                 mDelay;
    
    bool                                mIsComplete;
    
    FList                               mKillList;
    FList                               mDeleteList;
    
    //We ourselves are killed by external controller.
    int                                 mKillTimer;
    
    void                                Load(const char *pFile);
    
};

#endif /* LevelSection_hpp */
