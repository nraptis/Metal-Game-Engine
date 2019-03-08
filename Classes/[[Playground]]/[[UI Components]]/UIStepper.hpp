//
//  UIStepper.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/5/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef UIStepper_hpp
#define UIStepper_hpp

#include "ToolMenuSectionRow.hpp"
#include "FSlider.hpp"
#include "UIRoundedRect.hpp"
#include "UILabel.hpp"

class UIStepper : public ToolMenuSectionRow {
public:
    UIStepper();
    virtual ~UIStepper();

    virtual void                                Layout();

    virtual void                                Draw();

    virtual void                                Notify(void *pSender, const char *pNotification);

    float                                       GetValue();
    void                                        SetValue(float *pTargetValue);
    float                                       *mTargetValue;
    float                                       mValue;


    UILabel                                     mLabelTitle;
    UILabel                                     mLabelValue;

    float                                       mLabelTitleWidth;
    float                                       mLabelValueWidth;

    FSlider                                     mBaseSlider;
    float                                       mBarHeight;
    float                                       mBarHeightInner;

    UIRoundedRect                               mRectBar;
    UIRoundedRect                               mRectBarShine;

    UIRoundedRect                               mRectThumb;
    UIRoundedRect                               mRectThumbShine;

    float                                       mPreviousDrawMin;
    float                                       mPreviousDrawMax;
};

#endif
