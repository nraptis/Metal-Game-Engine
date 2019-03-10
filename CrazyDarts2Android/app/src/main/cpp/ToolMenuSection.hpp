//
//  ToolMenuSection.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/4/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef ToolMenuSection_hpp
#define ToolMenuSection_hpp

#include "UIRoundedRect.hpp"
#include "UIButton.hpp"

class ToolMenu;
class ToolMenuSection : public FCanvas {
public:
    ToolMenuSection();
    virtual ~ToolMenuSection();

    virtual void                            Update();
    virtual void                            Draw();
    virtual void                            Layout();

    void                                    SetTransparentBackground();

    virtual void                            Notify(void *pSender, const char *pNotification);

    int                                     mSectionDepth;

    UIRoundedRect                           mSectionBackgroundOutline;
    UIRoundedRect                           mSectionBackground;

    FList                                   mSectionList;

    ToolMenu                                *mMenu;
};

#endif
