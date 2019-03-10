//
//  FUniforms.hpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/22/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#ifndef FUniforms_hpp
#define FUniforms_hpp

#include "FMatrix.h"
#include "FColor.hpp"
#include "FLight.hpp"

#define UNIFORM_TYPE_UNKNOWN -1
#define UNIFORM_TYPE_BASIC 0
#define UNIFORM_TYPE_LIGHT_AMBIENT 1
#define UNIFORM_TYPE_LIGHT_AMBIENT_DIFFUSE 2
#define UNIFORM_TYPE_LIGHT_PHONG 3

/////////////////////////////
//
// Ideal case for uniforms:
// The uniform does not have any bind index,
// the uniform (of varying length) is written to from,
// the ENGINE, onto the UNIFORM ITSELF... Taking initial
// offset and returning resultant offset....
//
// The uniform itself does not have a color... Hmm...
//
/////////////////////////////

class FUniforms {
public:
    FUniforms();
    virtual ~FUniforms();
    
    FMatrix                                 mProjection;
    FMatrix                                 mModelView;
    
    FColor                                  mColor;
    
    virtual unsigned int                    GetType();
    
    virtual unsigned int                    GetVertexSize();
    virtual unsigned int                    GetFragmentSize();
    
    virtual void                            WriteVertexToBuffer(void *pData, unsigned int pOffset);
    virtual void                            WriteFragmentToBuffer(void *pData, unsigned int pOffset);
};

class FUniformsLightAmbient : public FUniforms {
public:
    FUniformsLightAmbient();
    virtual ~FUniformsLightAmbient();
    
    FLightAmbient                           mLight;
    
    virtual unsigned int                    GetType() override;
    
    virtual unsigned int                    GetVertexSize() override;
    virtual unsigned int                    GetFragmentSize() override;
    
    virtual void                            WriteVertexToBuffer(void *pData, unsigned int pOffset) override;
    virtual void                            WriteFragmentToBuffer(void *pData, unsigned int pOffset) override;
};

class FUniformsLightAmbientDiffuse : public FUniformsLightAmbient {
public:
    FUniformsLightAmbientDiffuse();
    virtual ~FUniformsLightAmbientDiffuse();
    
    FLightDiffuse                           mLight;
    
    void                                    Print();
    
    virtual unsigned int                    GetType() override;
    
    virtual unsigned int                    GetVertexSize() override;
    virtual unsigned int                    GetFragmentSize() override;
    
    virtual void                            WriteVertexToBuffer(void *pData, unsigned int pOffset) override;
    virtual void                            WriteFragmentToBuffer(void *pData, unsigned int pOffset) override;
};

class FUniformsLightPhong : public FUniforms {
public:
    FUniformsLightPhong();
    virtual ~FUniformsLightPhong();
    
    FLightPhong                             mLight;
    
    void                                    Print();
    
    virtual unsigned int                    GetType() override;
    
    virtual unsigned int                    GetVertexSize() override;
    virtual unsigned int                    GetFragmentSize() override;
    
    virtual void                            WriteVertexToBuffer(void *pData, unsigned int pOffset) override;
    virtual void                            WriteFragmentToBuffer(void *pData, unsigned int pOffset) override;
};

#endif /* FUniforms_hpp */
