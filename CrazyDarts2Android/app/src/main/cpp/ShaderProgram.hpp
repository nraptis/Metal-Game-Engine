//
//  ShaderProgram.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/8/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp

#include "FString.h"
#include "FUniforms.hpp"

#define SHADER_INVALID_PROGRAM 99999999
#define SHADER_INVALID_SHADER 99999999

class ShaderProgram {
public:
    ShaderProgram(const char *pVertexPath, const char *pFragmentPath);
    ~ShaderProgram();
    
    virtual void                Compile();
    virtual void                BindUniform(FUniforms *pUniform);
    
    virtual void                ArrayBufferData(int pIndex, int pOffset);
    virtual void                ArrayBufferPositions(int pIndex,int pOffset);
    virtual void                ArrayBufferTextureCoords(int pIndex, int pOffset);
    virtual void                ArrayBufferNormals(int pIndex, int pOffset);
    
    bool                        IsValid();
    
    void                        Use();
    
    void                        Kill();
    
    unsigned int                ShaderCompileVertex(const char *pShaderPath);
    unsigned int                ShaderCompileFragment(const char *pShaderPath);
    unsigned int                ShaderCompile(const char *pShaderPath, unsigned int pShaderType);
    
    FString                     mName;
    FString                     mFragmentProgramFile;
    FString                     mVertexProgramFile;
    
    unsigned int                mProgram;
    unsigned int                mVertexShader;
    unsigned int                mFragmentShader;
    
    int                         mSlotProjectionUniform;
    int                         mSlotModelViewUniform;
    int                         mSlotModulateUniform;
    
    int                         mSlotPositions;
    //int                         mSlotTextureCoords;
    //int                         mSlotNormals;
    //int                         mSlotUNormals;
    //int                         mSlotTangents;
    //int                         mSlotData;
    
    //int                         mSlotTexture;
    
};

#endif /* ShaderProgram_hpp */
