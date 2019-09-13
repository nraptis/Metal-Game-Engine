//
//  GFXAppNotificationHelper.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 9/12/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "GFXApp.hpp"
#include "GFXAppNotificationHelper.hpp"
#include "FString.hpp"

void GFXAppNotificationHelper::Notify(void *pSender, const char *pNotification) {
    
    FString aName = pNotification;
    
    if (aName == "transition_swap") {
        gApp->NotifyTransitionSwap();
    }
    
    if (aName == "transition_complete") {
        gApp->NotifyTransitionComplete();
    }
    
    
}

