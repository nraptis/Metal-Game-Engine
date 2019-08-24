//
//  EditorMenuFormation.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/30/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef EditorMenuFormation_hpp
#define EditorMenuFormation_hpp

#include "ToolMenu.hpp"

class GameFormationEditor;
class EditorMenuFormation : public ToolMenu {
public:
    EditorMenuFormation(GameFormationEditor *pEditor);
    virtual ~EditorMenuFormation();
    
    virtual void                            Layout() override;
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    virtual void                            Update() override;
    
    ToolMenuPanel                           *mPanelMain;
    
    ToolMenuSectionRow                      *mRowMain1;
    UIButton                                *mButtonSaveFormation;
    UIButton                                *mButtonLoadFormation;
    UIButton                                *mButtonPrintFormation;
    
    UISegment                               *mSegmentMode;
    
    UISlider                                *mSliderRotation;
    

    
    
    ToolMenuPanel                           *mPanelNodes;
    ToolMenuSectionRow                      *mRowNodes1;
    UIButton                                *mButtonDeleteNode;
    
    ToolMenuSectionRow                      *mRowNodes2;
    ToolMenuSectionRow                      *mRowNodes3;

    
    
    
    GameFormationEditor                     *mEditor;
    
};


#endif /* EditorMenuFormation_hpp */
