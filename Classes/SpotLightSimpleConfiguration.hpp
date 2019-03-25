//
//  SpotLightSimpleConfiguration.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/24/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef SpotLightSimpleConfiguration_hpp
#define SpotLightSimpleConfiguration_hpp

#include "FUniforms.hpp"



class SpotLightSimpleConfiguration {
public:
    SpotLightSimpleConfiguration();
    ~SpotLightSimpleConfiguration();
    
    void                                Print();
    
    void                                Compute();
    
    FUniformsLightSimpleSpotlight       mUniform;
    
    float                               mDirectionRotationPrimary;
    float                               mDirectionRotationSecondary;
    
    int                                 mSpotlightX;
    int                                 mSpotlightY;
    int                                 mSpotlightZ;
    
};

#endif /* SpotLightSimpleConfiguration_hpp */
