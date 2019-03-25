//
//  DiffuseConfiguration.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/25/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef DiffuseConfiguration_hpp
#define DiffuseConfiguration_hpp

#include "FUniforms.hpp"

class DiffuseConfiguration {
public:
    DiffuseConfiguration();
    ~DiffuseConfiguration();
    
    void                                Print();
    
    void                                Compute();
    
    FUniformsLightDiffuse               mUniform;
    
    float                               mDirectionRotationPrimary;
    float                               mDirectionRotationSecondary;
    
};


#endif /* DiffuseConfiguration_hpp */
