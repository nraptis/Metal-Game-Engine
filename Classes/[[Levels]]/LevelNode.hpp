//
//  LevelNode.hpp
//  Crazy Darts 2 Mac
//
//  Created by Doombot on 8/6/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelNode_hpp
#define LevelNode_hpp

#include "FString.hpp"
#include "FList.hpp"

class LevelNode {
public:
    LevelNode(const char *pSectionName);
    ~LevelNode();
    
    FString                             mSectionName; //"section_1.json" or "section_1"
    
    int                                 mKeepAliveTimer;
    int                                 mForceKillTimer;
    
    
    // = 0;
    // = 0;
    
    //Fly-in-speed?
    //Mirror-able?
    
    
    
};

#endif /* LevelNode_hpp */
