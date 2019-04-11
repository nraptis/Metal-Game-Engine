//
//  EllipseConfigMenu.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/9/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef EllipseConfigMenu_hpp
#define EllipseConfigMenu_hpp

#include "ToolMenu.hpp"
#include "FloatingCamera.hpp"
#include "FPoint.hpp"


class WorldConfigScene;
class EllipseConfigMenu : public ToolMenu {
public:
    EllipseConfigMenu(WorldConfigScene *pScene);
    virtual ~EllipseConfigMenu();
    
    virtual void                            Layout();
    virtual void                            Notify(void *pSender, const char *pNotification);
    
    void                                    RefreshTestMode();
    
    WorldConfigScene                        *mScene;

    
    ToolMenuPanel                           *mPanelDummy;
    UISlider                                *mSliderAxisH;
    UISlider                                *mSliderAxisV;
    UISlider                                *mSliderRotation;

    
    
};


#endif /* EllipseConfigMenu_hpp */
