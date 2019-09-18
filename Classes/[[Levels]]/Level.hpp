//
//  Level.hpp
//  Crazy Darts 2 Mac
//
//  Created by Doombot on 8/6/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef Level_hpp
#define Level_hpp

#include "FString.hpp"
#include "FList.hpp"
#include "LevelData.hpp"
#include "LevelNode.hpp"
#include "LevelGroup.hpp"


//The level can turn into a LevelData...
class Level {
public:
    Level();
    ~Level();
    
    //TODO: We want to be able to add individual sections one at a time...
    //      however, we also want to be able to add, say, a group of 5 sections
    //      from which we pick 3 sections.
    
    //TODO: The level class itself will be responsible for building out a
    //      flat list of sections. These will come from the groups... LOL!
    
    void                                    AddSection(const char *pSectionName);
    
    LevelData                               *Build();
    
    LevelGroup                              *GetCurrentGroup(); //Always returns a group, if there is no group, makes one...
    
    void                                    GroupBegin();
    void                                    GroupSetCount(int pCount);
    
    
    //What this means, we keep the section on the screen for "ticks" no matter what...
    void                                    SetAliveTimer(int pTicks);
    int                                     mKeepAliveTimer;
    
    //What this means, after ticks counts down, we evacuate the section no matter what...
    void                                    SetKillTimer(int pTicks);
    int                                     mForceKillTimer;
    
    void                                    ResetAll();
    
    
private:
    FList                                   mGroupList;
    FList                                   mTempList;
    
};

#endif /* Level_hpp */
