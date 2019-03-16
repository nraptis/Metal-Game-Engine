//
//  ShaderProgramModelIndexedLightedAmbientDiffuseDiffuse.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/15/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef ShaderProgramModelIndexedLightedAmbientDiffuseDiffuse_hpp
#define ShaderProgramModelIndexedLightedAmbientDiffuseDiffuse_hpp


#include "ShaderProgram.hpp"


class ShaderProgramModelIndexedLightedAmbientDiffuse: public ShaderProgram {
public:
    ShaderProgramModelIndexedLightedAmbientDiffuse(const char *pVertexPath, const char *pFragmentPath);
    virtual void                Compile() override;
    virtual void                BindUniform(FUniforms *pUniform) override;
    
    virtual void                ArrayBufferData(int pIndex, int pOffset) override;
    virtual void                ArrayBufferPositions(int pIndex,int pOffset) override;
    virtual void                ArrayBufferTextureCoords(int pIndex, int pOffset) override;
    virtual void                ArrayBufferNormals(int pIndex, int pOffset) override;
    
    int                         mSlotTextureCoords;
    int                         mSlotNormals;
    int                         mSlotTexture;
    
    int                         mSlotAmbient;
    int                         mSlotDiffuse;
    
    int                         mDataOffset;
};

#endif /* ShaderProgramModelIndexedLightedAmbientDiffuseDiffuse_hpp */
