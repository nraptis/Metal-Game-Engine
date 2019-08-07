//
//  LevelGroup.hpp
//  Crazy Darts 2 Mac
//
//  Created by Doombot on 8/6/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelGroup_hpp
#define LevelGroup_hpp

#include "FList.hpp"
#include "LevelNode.hpp"

class LevelGroup {
public:
    LevelGroup();
    ~LevelGroup();
    
    void                                AddNode(LevelNode *pNode);
    FList                               mNodeList;
    
    //Just passes along LevelNode objects...
    void                                Build(FList *pList);
    
    //Out of all the nodes, only spawn X of them...
    int                                 mCount;
    bool                                mShuffle;
    
};

#endif
