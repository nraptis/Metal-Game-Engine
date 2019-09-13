//
//  Transition.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 9/12/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef Transition_hpp
#define Transition_hpp

#include "FCanvas.hpp"

#define TRANSITION_MODE_PENDING -1
#define TRANSITION_MODE_ANIMATE_IN 0
#define TRANSITION_MODE_WAIT_IN 1
#define TRANSITION_MODE_SWAP 2
#define TRANSITION_MODE_WAIT_OUT 3
#define TRANSITION_MODE_ANIMATE_OUT 4
#define TRANSITION_MODE_COMPLETE 5

//Notification hooks: "transition_swap", "transition_complete"

#include "FCanvas.hpp"

class Transition : public FCanvas {
public:
    Transition();
    virtual ~Transition();
    
    virtual void                                Layout() override;
    virtual void                                Update() override;
    virtual void                                Draw() override;
    
    int                                         mMode;
    
    
    int                                         mModeTimeAnimateIn;
    int                                         mModeTimeWaitIn;
    int                                         mModeTimeSwap;
    int                                         mModeTimeWaitOut;
    int                                         mModeTimeAnimateOut;
    
    
    int                                         mTime;
    int                                         mTimer;
    
    float                                       mPercent;
    
    
    
};

#endif /* Transition_hpp */
