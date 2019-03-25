//
//  EditorMenuPathControl.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef EditorMenuPathControl_hpp
#define EditorMenuPathControl_hpp

#include "ToolMenu.hpp"

class GamePathEditor;
class EditorMenuPathControl : public ToolMenu {
public:
    EditorMenuPathControl(GamePathEditor *pEditor);
    virtual ~EditorMenuPathControl();
    
    virtual void                            Update() override;
    virtual void                            Layout() override;
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    
    ToolMenuSectionRow                      *mRowMain1;
    UIButton                                *mButtonCloseEditor;
    UIButton                                *mButtonResetPath;

    
    
    
    ToolMenuPanel                           *mPathControls;
    ToolMenuSectionRow                      *mRowControls1;
    UIButton                                *mButtonPrintPath;
    UIButton                                *mButtonSavePath;
    UIButton                                *mButtonLoadPath;
    
    ToolMenuSectionRow                      *mRowControls2;
    
    
    
    GamePathEditor                          *mEditor;
    
};

#endif
