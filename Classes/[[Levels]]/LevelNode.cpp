//
//  LevelNode.cpp
//  Crazy Darts 2 Mac
//
//  Created by Doombot on 8/6/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelNode.hpp"

LevelNode::LevelNode(const char *pSectionName) {
    mSectionName = pSectionName;
    
    mKeepAliveTimer = 0;
    mForceKillTimer = 0;
    
}

//Fly-in-speed?
//Mirror-able?

LevelNode::~LevelNode() {
    
}
