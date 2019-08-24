//
//  EditorMenuPermSpawnPicker.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/22/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef EditorMenuPermSpawnPicker_hpp
#define EditorMenuPermSpawnPicker_hpp


#include "ToolMenu.hpp"

class GameEditor;
class GamePermanentEditor;

class EditorMenuPermSpawnPickerCell : public UIButton {
public:
    EditorMenuPermSpawnPickerCell();
    virtual ~EditorMenuPermSpawnPickerCell();
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

class EditorMenuPermSpawnPicker : public ToolMenu {
public:
    EditorMenuPermSpawnPicker(GamePermanentEditor *pEditor);
    virtual ~EditorMenuPermSpawnPicker();
    
    virtual void                            Layout() override;
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    virtual void                            Update() override;
    
    GamePermanentEditor                     *mEditor;
    ToolMenuSection                         *mPickerSection;
    
    FList                                   mCells;
    FList                                   mCellQueue;
};

#endif /* EditorMenuPermSpawnPicker_hpp */
