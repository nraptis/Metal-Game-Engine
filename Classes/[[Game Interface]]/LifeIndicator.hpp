//
//  LifeIndicator.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 9/3/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LifeIndicator_hpp
#define LifeIndicator_hpp

#include "FCanvas.hpp"

class LifeIndicator : public FCanvas {
public:
    LifeIndicator();
    virtual ~LifeIndicator();
    
    virtual void                                Update() override;
    virtual void                                Draw() override;
    
    void                                        BecomeFull();
    void                                        BecomeEmpty();
    
    bool                                        mFull;
    
};


#endif /* LifeIndicator_hpp */
