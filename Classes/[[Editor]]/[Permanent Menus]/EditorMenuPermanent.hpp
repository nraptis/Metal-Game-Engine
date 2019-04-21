//
//  EditorMenuPermanent.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/6/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef EditorMenuPermanent_hpp
#define EditorMenuPermanent_hpp

#include "ToolMenu.hpp"

class GamePermanentEditor;
class EditorMenuPermanent : public ToolMenu {
public:
    EditorMenuPermanent(GamePermanentEditor *pEditor);
    virtual ~EditorMenuPermanent();
    
    virtual void                            Layout() override;
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    virtual void                            Update() override;
    
    GamePermanentEditor                     *mEditor;
    
    
    ToolMenuPanel                           *mPanelEditor;
    UISegment                               *mSegmentMode;
    
    
    ToolMenuPanel                           *mSnapsPanel;
    ToolMenuSectionRow                      *mRowSnaps1;
    UICheckBox                              *mCheckBoxPermSnapsEnabled;
    UIButton                                *mButtonSnapsBreakX;
    UIButton                                *mButtonSnapsBreakY;
    
    ToolMenuSectionRow                      *mRowSnaps2;
    UILabel                                 *mLabelOffsetX;
    UILabel                                 *mLabelOffsetY;
    UIButton                                *mButtonResetOffsetX;
    UIButton                                *mButtonResetOffsetY;
    
    
    
    
    
    ToolMenuPanel                           *mPermPanel;
    ToolMenuSectionRow                      *mRowPermanent1;
    UIButton                                *mButtonDeletePermanent;
    UIButton                                *mButtonEditPermanentPaths;
    
    ToolMenuSectionRow                      *mRowPermanent2;
    UIButton                                *mButtonAddPath;
    UIButton                                *mButtonDeletePath;
    
};

#endif /* EditorMenuPermanent_hpp */
