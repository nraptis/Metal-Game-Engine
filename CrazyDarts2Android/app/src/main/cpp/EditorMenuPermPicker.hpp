//
//  EditorMenuPermPicker.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/22/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef EditorMenuPermPicker_hpp
#define EditorMenuPermPicker_hpp

#include "ToolMenu.hpp"

class GameEditor;
class GamePermanentEditor;

class EditorMenuPermPickerCell : public UIButton {
public:
    EditorMenuPermPickerCell();
    virtual ~EditorMenuPermPickerCell();
    virtual void                            Layout() override;
    virtual void                            Update() override;
    virtual void                            Draw() override;
    int                                     mIndex;
    bool                                    mSelected;
    void                                    SetSelected(bool pSelected);
    UIRoundedRect                           mCheckBackground;
    UIRoundedRect                           mCheckOutline;
    int                                     mNodeCount;
};

class EditorMenuPermPicker : public ToolMenu {
public:
    EditorMenuPermPicker(GamePermanentEditor *pEditor);
    virtual ~EditorMenuPermPicker();
    
    virtual void                            Layout() override;
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    virtual void                            Update() override;
    
    GamePermanentEditor                     *mEditor;
    ToolMenuSection                         *mPickerSection;
    
    FList                                   mCells;
    FList                                   mCellQueue;
};

#endif /* EditorMenuPermPicker_hpp */
