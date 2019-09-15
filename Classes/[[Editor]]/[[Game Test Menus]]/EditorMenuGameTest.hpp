//
//  EditorMenuGameTest.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 5/10/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef EditorMenuGameTest_hpp
#define EditorMenuGameTest_hpp

#include "ToolMenu.hpp"


class GamePermanentEditor;
class EditorMenuGameTest : public ToolMenu {
public:
    EditorMenuGameTest();
    virtual ~EditorMenuGameTest();
    
    virtual void                            Layout() override;
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    virtual void                            Update() override;
    
    ToolMenuSectionRow                      *mRowMain1;
    UIButton                                *mButtonClose;
    UIButton                                *mButtonRestart;
    
    
    
    
};

#endif /* EditorMenuGameTest_hpp */
