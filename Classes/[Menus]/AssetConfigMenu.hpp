//
//  AssetConfigMenu.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 8/24/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef AssetConfigMenu_hpp
#define AssetConfigMenu_hpp

#include "ToolMenu.hpp"

class AssetConfigMenu : public ToolMenu {
public:
    AssetConfigMenu();
    virtual ~AssetConfigMenu();
    
    virtual void                            Notify(void *pSender, const char *pNotification);
    
    ToolMenuPanel                           *mPanelScaling;
    ToolMenuSectionRow                      *mRowScaling1;
    ToolMenuSectionRow                      *mRowScaling2;
    ToolMenuSectionRow                      *mRowScaling3;
    
    UISegment                               *mSegmentRetinaScale;
    UISegment                               *mSegmentSpriteScale;
    UICheckBox                              *mCheckBoxAutoScale;
    
    

    ToolMenuPanel                           *mPanelLoading;
    ToolMenuSectionRow                      *mRowLoading1;
    UIButton                                *mButtonReload;
    UIButton                                *mButtonUnload;
    
    
    
};

#endif /* AssetConfigMenu_hpp */
