//
//  SimpleSpotLightMenu.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/24/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef SimpleSpotLightMenu_hpp
#define SimpleSpotLightMenu_hpp

#include "ToolMenu.hpp"
#include "FVec2.hpp"


class SpotLightSimpleConfiguration;
class SimpleSpotLightMenu : public ToolMenu {
public:
    SimpleSpotLightMenu(SpotLightSimpleConfiguration *pConfiguration);
    virtual ~SimpleSpotLightMenu();
    
    virtual void                            Layout();
    virtual void                            Notify(void *pSender, const char *pNotification);
    
    void                                    RefreshTestMode();
    
    SpotLightSimpleConfiguration            *mConfig;
    
    
    ToolMenuPanel                           *mSpotlightPanel;
    UIStepper                               *mStepperSpotlightX;
    UIStepper                               *mStepperSpotlightY;
    UIStepper                               *mStepperSpotlightZ;
    
    
    ToolMenuPanel                           *mSpecularPanel;
    UISlider                                *mSliderSpecularShininess;
    
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
    UISlider                                *mSliderIntensitySpecular;
    
};

#endif /* SimpleSpotLightMenu_hpp */
