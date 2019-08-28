//
//  GameOverlay.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 8/27/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef GameOverlay_hpp
#define GameOverlay_hpp

#include "GFXApp.hpp"
#include "EditorMenuGameTestUtils.hpp"
#include "EditorMenuGameTest.hpp"

class Game;
class GameOverlay : public FCanvas {
public:
    GameOverlay();
    virtual ~GameOverlay();
    
    virtual void                                Layout() override;
    virtual void                                Update() override;
    virtual void                                Draw() override;
    
    virtual void                                TouchDown(float pX, float pY, void *pData) override;
    virtual void                                TouchMove(float pX, float pY, void *pData) override;
    virtual void                                TouchUp(float pX, float pY, void *pData) override;
    virtual void                                TouchFlush() override;
    
    virtual void                                Notify(void *pSender, const char *pNotification) override;
    
    
    FObjectList                                 mEffectListBalloonBursts;
    FObjectList                                 mEffectListDartFadeStar;
    
};

extern GameOverlay *gGameOverlay;

#endif

