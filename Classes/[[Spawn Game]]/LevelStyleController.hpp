//
//  LevelStyleController.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nick Raptis on 9/19/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelStyleController_hpp
#define LevelStyleController_hpp

#include "GameObject.hpp"
#include "FList.hpp"

class LevelStyleController {
public:
    LevelStyleController();
    ~LevelStyleController();
    
    void                                Reset();
    
    void                                ApplyToObject(GameObject *pObject);
    void                                ApplyToObjectList(FList *pList);
    
    bool                                mDisableThreads;
    bool                                mEnableBobbleMode;
    bool                                mRandomizeSpin;
    
    
};


#endif /* LevelStyleController_hpp */
