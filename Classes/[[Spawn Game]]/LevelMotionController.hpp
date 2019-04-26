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
#include "LevelMotionControllerSlice.hpp"

class LevelMotionController {
public:
    LevelMotionController();
    ~LevelMotionController();
    
    void                                Reset();
    
    void                                Update();
    void                                Draw();

    
    void                                Apply(float pReferenceX, float pReferenceY, GameObject *pObject);
    
    int                                 mKillTimer;
    
    float                               mTestRotation;
    
    
    FList                               mSliceList;
    
    
private:
    FList                               mKillList;
    FList                               mDeleteList;
    
    
};


#endif /* LevelMotionController_hpp */
