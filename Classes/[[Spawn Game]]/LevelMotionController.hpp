//
//  LevelMotionController.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/13/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelMotionController_hpp
#define LevelMotionController_hpp

#include "GameObject.hpp"

class LevelMotionController {
public:
    LevelMotionController();
    ~LevelMotionController();
    
    void                                Reset();
    void                                Restart();
    
    void                                Update();
    void                                Draw();
    
    //Since the permanents will be positioned relative
    //to the "section" we need a base position and real
    float                               mBaseX;
    float                               mBaseY;
    
    float                               mX;
    float                               mY;
    
    int                                 mKillTimer;
    
};


#endif /* LevelMotionController_hpp */
