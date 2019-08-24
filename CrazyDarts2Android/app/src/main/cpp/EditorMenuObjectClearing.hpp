//
//  EditorMenuObjectClearing.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/13/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef EditorMenuObjectClearing_hpp
#define EditorMenuObjectClearing_hpp

#include "ToolMenu.hpp"


class GameEditor;
class EditorMenuObjectClearing : public ToolMenu {
public:
    EditorMenuObjectClearing(GameEditor *pEditor);
    virtual ~EditorMenuObjectClearing();
    
    virtual void                            Layout() override;
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    virtual void                            Update() override;
    
    GameEditor                              *mEditor;
    
    
    ToolMenuSectionRow                      *mRowMain1;
    ToolMenuSectionRow                      *mRowMain2;
    ToolMenuSectionRow                      *mRowMain3;
    
    UIButton                                *mButtonKillAll;
    UIButton                                *mButtonKillAllBalloons;
    UIButton                                *mButtonKillAllNonBalloons;
    UIButton                                *mButtonKillPerms;
    UIButton                                *mButtonKillWaves;
    
    
};

#endif /* EditorMenuObjectClearing_hpp */
