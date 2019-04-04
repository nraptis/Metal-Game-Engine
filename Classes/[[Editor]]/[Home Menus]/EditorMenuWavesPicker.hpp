//
//  EditorMenuWavesPicker.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/21/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef EditorMenuWavesPicker_hpp
#define EditorMenuWavesPicker_hpp

#include "ToolMenu.hpp"

class GameEditor;

class EditorMenuWavesPickerCell : public UIButton {
public:
    EditorMenuWavesPickerCell();
    virtual ~EditorMenuWavesPickerCell();
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

class EditorMenuWavesPicker : public ToolMenu {
public:
    EditorMenuWavesPicker(GameEditor *pEditor);
    virtual ~EditorMenuWavesPicker();
    
    virtual void                            Layout() override;
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    virtual void                            Update() override;
    
    
    
    GameEditor                              *mEditor;
    ToolMenuSection                         *mPickerSection;
    
    FList                                   mCells;
    FList                                   mCellQueue;
};

#endif /* EditorMenuWavesPicker_hpp */
