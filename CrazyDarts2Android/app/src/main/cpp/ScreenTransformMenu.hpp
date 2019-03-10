//
//  ScreenTransformMenu.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/7/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef ScreenTransformMenu_hpp
#define ScreenTransformMenu_hpp

#include "ToolMenu.hpp"

class ScreenTransformMenu : public ToolMenu {
public:
    ScreenTransformMenu();
    virtual ~ScreenTransformMenu();

    virtual void                            Layout();
    virtual void                            Notify(void *pSender, const char *pNotification);

    ToolMenuPanel                           *mPanel1;
    ToolMenuPanel                           *mPanel2;
    ToolMenuPanel                           *mPanel3;

    ToolMenuPanel                           *mSubPanel1;
    ToolMenuPanel                           *mSubPanel2;
    ToolMenuPanel                           *mSubPanel3;

    ToolMenuSection                         *mSection1;
    ToolMenuSection                         *mSection2;
    ToolMenuSection                         *mSection3;

    UISlider                                *mSlider1;
    UISlider                                *mSlider2;

    UISegment                               *mSegment1;
    UISegment                               *mSegment2;

    UICheckBox                              *mCB1;
    UICheckBox                              *mCB2;


};

#endif

