//
//  GameTestOverlay.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 5/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef GameTestOverlay_hpp
#define GameTestOverlay_hpp

#include "GFXApp.hpp"
//#include "FloatingCamera.hpp"
//#include "Dart.hpp"
//#include "Balloon.hpp"

#include "EditorMenuGameTestUtils.hpp"
#include "EditorMenuGameTest.hpp"

class Game;
class GameTestOverlay : public FCanvas {
public:
    GameTestOverlay();
    virtual ~GameTestOverlay();
    
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
    
    
};

#endif /* GameTestOverlay_hpp */
