//
//  MainMenuPlayButton.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 9/12/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef MainMenuPlayButton_hpp
#define MainMenuPlayButton_hpp

#include "FButton.hpp"

class MainMenuPlayButton : public FButton {
public:
    MainMenuPlayButton();
    virtual ~MainMenuPlayButton();
    
    virtual void                                Layout() override;
    virtual void                                Update() override;
    virtual void                                Draw() override;
    
    virtual void                                TouchDown(float pX, float pY, void *pData) override;
    virtual void                                TouchMove(float pX, float pY, void *pData) override;
    virtual void                                TouchUp(float pX, float pY, void *pData) override;
    virtual void                                TouchFlush() override;
};



#endif /* MainMenuPlayButton_hpp */
