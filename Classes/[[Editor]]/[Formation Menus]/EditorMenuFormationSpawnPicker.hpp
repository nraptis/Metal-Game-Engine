//
//  EditorMenuFormationSpawnPicker.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/5/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef EditorMenuFormationSpawnPicker_hpp
#define EditorMenuFormationSpawnPicker_hpp

#include "ToolMenu.hpp"

class GameFormationEditor;
class EditorMenuFormationSpawnPickerCell : public UIButton {
public:
    EditorMenuFormationSpawnPickerCell();
    virtual ~EditorMenuFormationSpawnPickerCell();
    virtual void                            Layout() override;
    virtual void                            Update() override;
    virtual void                            Draw() override;
    int                                     mIndex;
    bool                                    mSelected;
    void                                    SetSelected(bool pSelected);
    UIRoundedRect                           mCheckBackground;
    UIRoundedRect                           mCheckOutline;
    int                                     mSpawnIndex;
};

class EditorMenuFormationSpawnPicker : public ToolMenu {
public:
    EditorMenuFormationSpawnPicker(GameFormationEditor *pEditor);
    virtual ~EditorMenuFormationSpawnPicker();
    
    virtual void                            Layout() override;
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    virtual void                            Update() override;
    
    GameFormationEditor                     *mEditor;
    
    
    
    ToolMenuPanel                           *mPanelObjectTypes;
    
    ToolMenuSectionRow                      *mRowObjectTypes1;
    ToolMenuSectionRow                      *mRowObjectTypes2;
    
    UIButton                                *mButtonPickBalloon;
    UIButton                                *mButtonPickBrickHead;
    
    
    bool                                    mTracerEnabled;
    
    ToolMenuSection                         *mPickerSection;
    
    FList                                   mCells;
    FList                                   mCellQueue;
    
};

#endif /* EditorMenuFormationSpawnPicker_hpp */
