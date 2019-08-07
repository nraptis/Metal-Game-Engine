//
//  LevelSection.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/14/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelSection_hpp
#define LevelSection_hpp

#define SECTION_FLY_IN_NONE 0
#define SECTION_FLY_IN_LEFT 1
#define SECTION_FLY_IN_TOP 2
#define SECTION_FLY_IN_RIGHT 3

#include "GameObject.hpp"
#include "LevelWave.hpp"
#include "LevelSectionPermanent.hpp"

class LevelSection {
public:
    LevelSection();
    ~LevelSection();
    
    void                                Reset();
    void                                Restart();
    
    void                                Spawn();
    void                                Update();
    void                                Draw();
    
    float                               mX;
    float                               mY;
    
    void                                FlyInReset(int pType);
    int                                 mFlyInType;
    int                                 mFlyInTimer;
    int                                 mFlyInTime;
    
    
    void                                DisposeObject(GameObject *pObject);
    
    void                                AddWave(LevelWave *pLevelWave);
    FList                               mWaveList;
    
    
    void                                AddPerm(LevelSectionPermanent *pPerm);
    FList                               mPermList;
    
    
    
    int                                 mCandidateWaveIndex;
    
    LevelWave                           *mCandidateWave;
    int                                 mCandidateWaveDelay;
    
    FList                               mActiveWaveList;
    FList                               mRemoveActiveWaveList;
    
    //Mainly for editor, if we want to start later in the queue
    int                                 mStartWaveIndex;
    
    int                                 mDelay;
    
    bool                                mIsComplete;
    
    //We ourselves are killed by external controller.
    int                                 mKillTimer;
    
    bool                                mLoadError;
    void                                Load(const char *pFile);
    
private:
    
    FList                               mKillWaveList;
    FList                               mDeleteWaveList;
    
    
    FList                               mKillPermList;
    FList                               mDeletePermList;
    
    
    
};

#endif /* LevelSection_hpp */
