//
//  EditorMenuGameTestUtils.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 5/10/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef EditorMenuGameTestUtils_hpp
#define EditorMenuGameTestUtils_hpp

#include "ToolMenu.hpp"


class GamePermanentEditor;
class EditorMenuGameTestUtils : public ToolMenu {
public:
    EditorMenuGameTestUtils();
    virtual ~EditorMenuGameTestUtils();
    
    virtual void                            Layout() override;
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    virtual void                            Update() override;
    
    
};

#endif /* EditorMenuGameTestUtils_hpp */
