//
//  CameraMenu.hpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/13/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#ifndef CameraMenu_hpp
#define CameraMenu_hpp

#include "ToolMenu.hpp"
#include "FloatingCamera.hpp"
#include "FPoint.h"

class CameraMenu : public ToolMenu {
public:
    CameraMenu(FloatingCamera *pCamera);
    virtual ~CameraMenu();
    
    virtual void                            Layout();
    virtual void                            Notify(void *pSender, const char *pNotification);
    
    void                                    RefreshTestMode();
    
    FloatingCamera                          *mCamera;
    
    
    UISlider                                *mSliderAspectFOV;
    
    ToolMenuPanel                           *mPanelDummy;
    UISlider                                *mSliderDummyX;
    UISlider                                *mSliderDummyY;
    UISlider                                *mSliderDummyZ;
    
    UISlider                                *mSliderDummyRot1;
    UISlider                                *mSliderDummyRot2;
    
    
    ToolMenuPanel                           *mPanelTarget;
    UISlider                                *mSliderTargetX;
    UISlider                                *mSliderTargetY;
    UISlider                                *mSliderTargetZ;
    
    ToolMenuPanel                           *mPanelView;
    UISlider                                *mSliderViewRotationPrimary;
    UISlider                                *mSliderViewRotationSecondary;
    
    UISlider                                *mSliderViewDistance;
};

#endif

