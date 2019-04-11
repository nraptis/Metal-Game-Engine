//
//  DiffuseLightMenu.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/25/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef DiffuseLightMenu_hpp
#define DiffuseLightMenu_hpp

#include "ToolMenu.hpp"
#include "FPoint.hpp"

class DiffuseConfiguration;
class DiffuseLightMenu : public ToolMenu {
public:
    DiffuseLightMenu(DiffuseConfiguration *pConfiguration);
    virtual ~DiffuseLightMenu();
    
    virtual void                            Layout();
    virtual void                            Notify(void *pSender, const char *pNotification);
    
    void                                    RefreshTestMode();
    
    DiffuseConfiguration                    *mDiffuse;
    
    ToolMenuPanel                           *mDirectionPanel;
    UISlider                                *mSliderDirectionRotationPrimary;
    UISlider                                *mSliderDirectionRotationSecondary;
    
    ToolMenuPanel                           *mColorPanel;
    UISlider                                *mSliderColorR;
    UISlider                                *mSliderColorG;
    UISlider                                *mSliderColorB;
    
    ToolMenuPanel                           *mIntensityPanel;
    UISlider                                *mSliderIntensityAmbient;
    UISlider                                *mSliderIntensityDiffuse;
    
};

#endif /* DiffuseLightMenu_hpp */
