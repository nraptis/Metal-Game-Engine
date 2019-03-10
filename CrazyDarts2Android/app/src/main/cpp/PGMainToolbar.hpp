//
//  PGMainToolbar.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/2/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef PGMainToolbar_hpp
#define PGMainToolbar_hpp

#include "DragableCanvas.hpp"
#include "UIRoundedRect.hpp"
#include "UIButton.hpp"
#include "UISlider.hpp"
#include "UISegment.hpp"
#include "ToolMenuSection.hpp"
#include "ToolMenuSectionRow.hpp"

class PGMainToolbar : public DragableCanvas {
public:
    PGMainToolbar();
    virtual ~PGMainToolbar();

    virtual void                            Update();
    virtual void                            Draw();
    virtual void                            Layout();

    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();

    virtual void                            Notify(void *pSender, const char *pNotification);

    //Step 1
    void                                    SetTitle(const char *pText);

    //Step 2
    void                                    AddRow(ToolMenuSectionRow *pRow);


    void                                    Expand();
    void                                    Collapse();
    bool                                    mExpanded;
    float                                   mExpandedWidth;

    void                                    SetExpandedLayout();
    void                                    SetCollapsedLayout();
    

    FCanvas                                 mContent;
    UIButton                                mButtonMinimize;
    FList                                   mRowList;

    UIRoundedRect                           mToolbarBackground;
    UIRoundedRect                           mToolbarBackgroundOutline;
    UIRoundedRect                           mToolbarBackgroundShadow;

    ToolMenuSectionRow                      mMainRow;
    ToolMenuSectionRow                      mRow1;
    ToolMenuSectionRow                      mRow2;


    UISegment                               *mSegmentBackground;

    UIButton                                *mButtonNodeEditor;
    UIButton                                *mButtonPathEditor;
    UIButton                                *mButtonQuadEditor;
    UIButton                                *mButtonSceneEditor;


    UILabel                                 *mLabelTitle;

    UILabel                                 *mLabel1;
    UILabel                                 *mLabel2;
    UILabel                                 *mLabel3;

    UICheckBox                              *mCheck1;
    UICheckBox                              *mCheck2;
    UICheckBox                              *mCheck3;

};

#endif /* PGMainToolbar_hpp */

