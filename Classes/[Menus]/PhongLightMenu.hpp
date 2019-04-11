//
//  PhongPhongLightMenu.hpp
//  MacMetal
//
//  Created by Nicholas Raptis on 2/21/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#ifndef PhongPhongLightMenu_hpp
#define PhongPhongLightMenu_hpp

#include "ToolMenu.hpp"
#include "FPoint.hpp"

class PhongConfiguration;
class PhongLightMenu : public ToolMenu {
public:
    PhongLightMenu(PhongConfiguration *pConfiguration);
    virtual ~PhongLightMenu();
    
    virtual void                            Layout();
    virtual void                            Notify(void *pSender, const char *pNotification);
    
    void                                    RefreshTestMode();
    
    PhongConfiguration                      *mPhong;
    
    ToolMenuPanel                           *mSpecularPanel;
    UISlider                                *mSliderSpecularShininess;
    UISlider                                *mSliderSpecularEyeRotationPrimary;
    UISlider                                *mSliderSpecularEyeRotationSecondary;
    
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

#endif /* PhongLightMenu_hpp */
