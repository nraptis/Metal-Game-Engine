//
//  EditorMenuMotion.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/13/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef EditorMenuMotion_hpp
#define EditorMenuMotion_hpp

#include "ToolMenu.hpp"
#include "EditorMenuMotionTypePanel.hpp"
#include "LevelMotionControllerBlueprint.hpp"


class GameEditor;
class GamePermanentEditor;

class EditorMenuMotion : public ToolMenu {
public:
    EditorMenuMotion(GameEditor *pEditor);
    EditorMenuMotion(GamePermanentEditor *pEditor);
    
    void                                    Init();
    virtual ~EditorMenuMotion();
    
    virtual void                            Layout() override;
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    virtual void                            Update() override;
    
    
    void                                    CheckSlicePanels();
    
    bool                                    mIsForPermSpawn;
    
    GameEditor                              *mEditor;
    GamePermanentEditor                     *mPermEditor;
    LevelMotionControllerBlueprint          *mMotionController;
    
    
    ToolMenuPanel                           *mPanelMainControls;
    ToolMenuSectionRow                      *mRowMain1;
    ToolMenuSectionRow                      *mRowMain2;
    ToolMenuSectionRow                      *mRowMain3;
    ToolMenuSectionRow                      *mRowMain4;
    
    UIButton                                *mButtonAddNegate;
    UIButton                                *mButtonAddRotate;
    UIButton                                *mButtonAddOscillateV;
    UIButton                                *mButtonAddOscillateH;
    UIButton                                *mButtonAddOscillateRotation;
    UICheckBox                              *mCheckBoxPlayOnEnter;
    UICheckBox                              *mCheckBoxPlayOnExit;
    
    
    
    UIButton                                *mButtonRemoveAll;
    UIButton                                *mButtonRemoveFirst;
    UIButton                                *mButtonRemoveLast;
    
    
    
    ToolMenuPanel                           *mPanelTypes;
    
    FList                                   mTypePanelList;
    
    //EditorMenuMotionTypePanel               *
    
    

    
    
};

#endif /* EditorMenuMotion_hpp */
