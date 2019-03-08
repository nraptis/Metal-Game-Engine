//
//  PathEditorMenu.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/6/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef PathEditorMenu_hpp
#define PathEditorMenu_hpp

#include "ToolMenu.hpp"
#include "FPoint.h"

class PGPathEditor;
class PathEditorMenu : public ToolMenu {
public:
    PathEditorMenu(PGPathEditor *pEditor);
    virtual ~PathEditorMenu();

    virtual void                            Layout();
    virtual void                            Notify(void *pSender, const char *pNotification);

    PGPathEditor                            *mPathEditor;

    ToolMenuSectionRow                      *mRowTop;
    UIButton                                *mButtonScreenTransform;
    UIButton                                *mButtonClose;
    UIButton                                *mButtonPickImage;

    UISegment                               *mSegmentMode;

    ToolMenuPanel                           *mPanelSymmetry;
    ToolMenuPanel                           *mPanelExport;

    ToolMenuSectionRow                      *mRowExportOptions;
    UIAlignmentPicker                       *mAlignmentPickerExport;
    UICheckBox                              *mCheckBoxNormalizeExport;


    
    

};

#endif
