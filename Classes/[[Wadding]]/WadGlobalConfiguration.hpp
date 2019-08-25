//
//  WadGlobalConfiguration.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 8/24/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef WadGlobalConfiguration_hpp
#define WadGlobalConfiguration_hpp

class WadGlobalConfiguration {
public:
    WadGlobalConfiguration();
    ~WadGlobalConfiguration();
    
    //Ask the configuration if we should, in fact, reload...
    bool                                        ShouldReload();
    
    //Notify the configuration that we are, in fact, reloading...
    void                                        NotifyReload();
    
    
    void                                        SetAssetScale(int pScale);
    int                                         mAssetScale;
    int                                         mPrevAssetScale;
    
    void                                        SetSpriteScale(int pScale);
    int                                         mSpriteScale;
    int                                         mPrevSpriteScale;
    
    bool                                        mAutoScale;
    
    void                                        Print();
    
    
    
};

extern WadGlobalConfiguration gWadConfiguration;

#endif /* WadGlobalConfiguration_hpp */
