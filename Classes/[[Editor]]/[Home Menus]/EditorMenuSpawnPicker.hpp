//
//  EditorMenuSpawnPicker.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/29/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef EditorMenuSpawnPicker_hpp
#define EditorMenuSpawnPicker_hpp

#include "ToolMenu.hpp"

class GameEditor;

class EditorMenuSpawnPickerCell : public UIButton {
public:
    EditorMenuSpawnPickerCell();
    virtual ~EditorMenuSpawnPickerCell();
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

class EditorMenuSpawnPicker : public ToolMenu {
public:
    EditorMenuSpawnPicker(GameEditor *pEditor);
    virtual ~EditorMenuSpawnPicker();
    
    virtual void                            Layout() override;
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    virtual void                            Update() override;
    
    GameEditor                              *mEditor;
    ToolMenuSection                         *mPickerSection;
    
    FList                                   mCells;
    FList                                   mCellQueue;
    
};

#endif /* EditorMenuSpawnPicker_hpp */
