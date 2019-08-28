//
//  StuckDart.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 8/19/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef StuckDart_hpp
#define StuckDart_hpp


class Dart;
class StuckDart {
public:
    StuckDart();
    virtual ~StuckDart();
    
    void                                    Update();
    void                                    Draw();
    
    bool                                    mDelete;
    
    Dart                                    *mDart;
    float                                   mStartDartRotation;
    float                                   mStartReferenceRotation;
    float                                   mStartXDiff;
    float                                   mStartYDiff;
    
    int                                     mWaitTimer;
    
    int                                     mFadeoutTime;
    int                                     mFadeoutTimer;
    
    bool                                    mDidStartFadeout;
    
};

#endif
