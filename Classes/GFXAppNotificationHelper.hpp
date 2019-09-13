//
//  GFXAppNotificationHelper.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 9/12/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef GFXAppNotificationHelper_hpp
#define GFXAppNotificationHelper_hpp

#include "FCanvas.hpp"

class GFXAppNotificationHelper : public FCanvas {
public:
    
    virtual void                                Notify(void *pSender, const char *pNotification) override;
    
};

#endif
