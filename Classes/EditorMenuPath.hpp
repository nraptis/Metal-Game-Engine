//
//  EditorMenuPathMain.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef EditorMenuPathMain_hpp
#define EditorMenuPathMain_hpp

#include "ToolMenu.hpp"


class GamePathEditor;
class EditorMenuPath : public ToolMenu {
public:
    EditorMenuPath(GamePathEditor *pEditor);
    virtual ~EditorMenuPath();
    
    virtual void                            Layout();
    virtual void                            Notify(void *pSender, const char *pNotification);
    
    
    ToolMenuPanel                           *mPathControls;
    ToolMenuSectionRow                      *mRowControls1;
    UIButton                                *mButtonPrintPath;
    UIButton                                *mButtonSavePath;
    UIButton                                *mButtonLoadPath;
    
    
    
    ToolMenuPanel                           *mEditorPanel;
    UISegment                               *mSegmentMode;
    
    ToolMenuSectionRow                      *mRowVisuals;
    UICheckBox                              *mCheckBoxSmooth;
    UICheckBox                              *mCheckBoxPreview;
    
    
    ToolMenuSectionRow                      *mRowAlignment;
    UILabel                                 *mLabelA1;
    UIAlignmentPicker                       *mAlignmentPicker1;
    UILabel                                 *mLabelA2;
    UIAlignmentPicker                       *mAlignmentPicker2;
    
    
    GamePathEditor                          *mEditor;
    
};


#endif /* EditorMenuPathMain_hpp */
