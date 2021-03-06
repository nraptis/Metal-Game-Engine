//
//  GameOverlayInterfaceInterface.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 9/3/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef GameOverlayInterfaceInterface_hpp
#define GameOverlayInterfaceInterface_hpp

#include "GFXApp.hpp"
#include "FButton.hpp"
#include "LifeIndicator.hpp"
#include "FPointList.hpp"

#define MAX_LIFE_INDICATOR_COUNT 16

#define TEXT_BUBBLE_EXPLORE_GRID_RADIUS 18
#define TEXT_BUBBLE_EXPLORE_GRID_STEP_SIZE 8.0f

class Game;
class GameOverlayInterface : public FCanvas {
public:
    GameOverlayInterface();
    virtual ~GameOverlayInterface();
    
    virtual void                                Layout() override;
    virtual void                                Update() override;
    virtual void                                Draw() override;
    
    virtual void                                TouchDown(float pX, float pY, void *pData) override;
    virtual void                                TouchMove(float pX, float pY, void *pData) override;
    virtual void                                TouchUp(float pX, float pY, void *pData) override;
    virtual void                                TouchFlush() override;
    
    virtual void                                Notify(void *pSender, const char *pNotification) override;
    
    void                                        NotifyLivesChanged();
    
    FButton                                     *mPauseButton;
    
    LifeIndicator                               *mLifeIndicator[MAX_LIFE_INDICATOR_COUNT];
    int                                         mLifeIndicatorCount;
    void                                        RefreshLifeIndicators();
    void                                        RefreshLifeIndicatorFrames();
    
    float                                       mCoinFrame[5];
    
    void                                        BuildTextBubbleExploreGrid();
    
    FPointList                                  mTextBubbleExploreList;
    
};

extern GameOverlayInterface *gInterfaceOverlay;


#endif
