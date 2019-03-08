//
//  ToolMenuModalUnderlay.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef ToolMenuModalUnderlay_hpp
#define ToolMenuModalUnderlay_hpp

#include "FCanvas.hpp"
#include "UIButton.hpp"

class ToolMenuModalUnderlay : public FCanvas {
public:
    ToolMenuModalUnderlay();
    virtual ~ToolMenuModalUnderlay();

    virtual void                            Update();
    virtual void                            Draw();

    virtual void                            Layout();
};

#endif /* ToolMenuModalUnderlay_hpp */

