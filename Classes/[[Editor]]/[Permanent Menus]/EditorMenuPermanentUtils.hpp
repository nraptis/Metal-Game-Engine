//
//  EditorMenuPermanentUtils.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/6/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef EditorMenuPermanentUtils_hpp
#define EditorMenuPermanentUtils_hpp

#include "ToolMenu.hpp"

class GamePermanentEditor;
class EditorMenuPermanentUtils : public ToolMenu {
public:
    EditorMenuPermanentUtils(GamePermanentEditor *pEditor);
    virtual ~EditorMenuPermanentUtils();
    
    virtual void                            Layout() override;
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    virtual void                            Update() override;
    
    GamePermanentEditor                     *mEditor;
    
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

#endif /* EditorMenuPermanentUtils_hpp */
