//
//  StatsMenu.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nick Raptis on 9/22/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef StatsMenu_hpp
#define StatsMenu_hpp

#include "ToolMenu.hpp"



class StatsMenu : public ToolMenu {
public:
    StatsMenu();
    virtual ~StatsMenu();
    
    virtual void                            Update();
    virtual void                            Layout();
    virtual void                            Notify(void *pSender, const char *pNotification);
    
    
    ToolMenuSectionRow                      *mRowProgress;
    UILabel                                 *mLabelProgress;
    UILabel                                 *mLabelPercent;
    
    
    
};

#endif /* StatsMenu_hpp */
