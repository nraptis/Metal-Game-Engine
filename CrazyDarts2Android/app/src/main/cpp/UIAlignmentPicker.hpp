//
//  UIAlignmentPicker.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/6/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef UIAlignmentPicker_hpp
#define UIAlignmentPicker_hpp

#include "FCanvas.hpp"
#include "UIRoundedRect.hpp"
#include "UIAlignmentPickerButton.hpp"
#include "FPoint.h"

class UIAlignmentPicker : public FCanvas {
public:
    UIAlignmentPicker();
    virtual ~UIAlignmentPicker();

    virtual void                            Layout();

    virtual void                            Notify(void *pSender, const char *pNotification);

    void                                    SetTarget(FIntPoint *pTarget);
    void                                    UpdateDisplay();
    
    UIAlignmentPickerButton                 *mButtonTL;
    UIAlignmentPickerButton                 *mButtonTC;
    UIAlignmentPickerButton                 *mButtonTR;

    UIAlignmentPickerButton                 *mButtonML;
    UIAlignmentPickerButton                 *mButtonMC;
    UIAlignmentPickerButton                 *mButtonMR;

    UIAlignmentPickerButton                 *mButtonBL;
    UIAlignmentPickerButton                 *mButtonBC;
    UIAlignmentPickerButton                 *mButtonBR;

    FIntPoint                               *mTarget;
    int                                     mAlignX;
    int                                     mAlignY;

};

#endif
