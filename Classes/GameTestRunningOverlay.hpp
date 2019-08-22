//
//  GameTestRunningOverlay.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 8/12/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef GameTestRunningOverlay_hpp
#define GameTestRunningOverlay_hpp

#include "GFXApp.hpp"
#include "GameTestRunningMainMenu.hpp"
#include "CameraMenu.hpp"
#include "HangingThreadTestMenu.hpp"

class Game;
class GameTestRunningOverlay : public FCanvas {
public:
    GameTestRunningOverlay();
    virtual ~GameTestRunningOverlay();
    
    virtual void                                Layout() override;
    virtual void                                Update() override;
    virtual void                                Draw() override;
    
    virtual void                                TouchDown(float pX, float pY, void *pData) override;
    virtual void                                TouchMove(float pX, float pY, void *pData) override;
    virtual void                                TouchUp(float pX, float pY, void *pData) override;
    virtual void                                TouchFlush() override;
    
    virtual void                                KeyDown(int pKey) override;
    virtual void                                KeyUp(int pKey) override;
    
    virtual void                                Notify(void *pSender, const char *pNotification) override;
    
    GameTestRunningMainMenu                     *mTestRunningMenu;
    CameraMenu                                  *mCameraMenu;
    HangingThreadTestMenu                       *mHangingThreadMenu;
    
    
};

#endif /* GameTestRunningOverlay_hpp */
