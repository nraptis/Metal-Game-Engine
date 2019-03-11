//
//  FFrameController.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/9/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef FFrameController_hpp
#define FFrameController_hpp


#define FRAME_CONTROLLER_HISTORY_COUNT 200

class FFrameController {
public:
    FFrameController();
    ~FFrameController();
    
    //Call this when the OS decides to render a frame...
    //Returns number of updates to make...
    int                                     Frame();
    
    
    int                                     mUpdatesPerSecond;
    
    //The app has come alive from the background...
    void                                    Active();
    
    //The app has gone into the backgrond;
    void                                    Inactive();
    
    
    unsigned long                           mFrameTime[FRAME_CONTROLLER_HISTORY_COUNT];
    int                                     mUpdateCount[FRAME_CONTROLLER_HISTORY_COUNT];
    
    
    int                                     mFrameCount;
    int                                     mConsecutiveBadReads;
    
    unsigned int                            mStartTime;
    
    int                                     mMiliseconds;
    int                                     mSeconds;
    int                                     mFPS;
    int                                     mUPS;
    
    
private:
    
    void                                    Flush();
    
};

#endif /* FFrameController_hpp */
