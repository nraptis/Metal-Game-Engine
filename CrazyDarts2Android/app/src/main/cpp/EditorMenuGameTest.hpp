//
//  EditorMenuGameTest.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 5/10/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef EditorMenuGameTest_hpp
#define EditorMenuGameTest_hpp

#include "ToolMenu.hpp"


class GamePermanentEditor;
class EditorMenuGameTest : public ToolMenu {
public:
    EditorMenuGameTest();
    virtual ~EditorMenuGameTest();
    
    virtual void                            Layout() override;
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    virtual void                            Update() override;
    
    ToolMenuSectionRow                      *mRowMain1;
    UIButton                                *mButtonCloseEditor;
    UIButton                                *mButtonResetPerm;
    
    ToolMenuPanel                           *mMenuPathSpawn;
    UIStepper                               *mStepperPathSpawnCount;
    UIStepper                               *mStepperPathSpawnSpacing;
    
    ToolMenuSectionRow                      *mRowPathSpawn1;
    UICheckBox                              *mCheckBoxPathSpawnEqualSpacing;
    
    ToolMenuPanel                           *mMenusPanel;
    ToolMenuSectionRow                      *mRowMenus1;
    UIButton                                *mButtonMenuSpawnPicker;
    UIButton                                *mButtonMenuPermPicker;
    
    ToolMenuSectionRow                      *mRowMenus2;
    UIButton                                *mButtonMenuAttachment;
    UIButton                                *mButtonMenuMotionPerm;
    UIButton                                *mButtonMenuMotionSpawn;
    
    
};

#endif /* EditorMenuGameTest_hpp */
