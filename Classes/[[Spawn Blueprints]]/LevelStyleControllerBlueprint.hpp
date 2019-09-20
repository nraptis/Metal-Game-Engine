//
//  LevelStyleControllerBlueprint.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nick Raptis on 9/19/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelStyleControllerBlueprint_hpp
#define LevelStyleControllerBlueprint_hpp

#include "LevelStyleController.hpp"
#include "FJSON.hpp"

class LevelStyleControllerBlueprint {
public:
    
    LevelStyleControllerBlueprint();
    ~LevelStyleControllerBlueprint();
    
    void                                        Update();
    void                                        Reset();
    
    void                                        Build(LevelStyleController *pStyleController);
    
    bool                                        ShouldSave();
    
    FJSONNode                                   *Save();
    void                                        Load(FJSONNode *pNode);
    
    bool                                        mDisableThreads;
    bool                                        mEnableBobbleMode;
    bool                                        mRandomizeSpin;
    
};
    

#endif /* LevelStyleControllerBlueprint_hpp */
