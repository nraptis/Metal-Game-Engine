//
//  ShaderProgram.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/8/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp

#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#include "FString.h"

#define SHADER_INVALID_PROGRAM 99999999
#define SHADER_INVALID_SHADER 99999999

class ShaderProgram {
public:
    ShaderProgram(const char *pVertexPath, const char *pFragmentPath);
    ~ShaderProgram();
    
    void                        SetUniformNames(const char *pVertexUniformName, const char *pFragmentUniformName);
    
    
    
    void                        Compile();
    
    bool                        IsValid();
    
    void                        Use();
    
    void                        Kill();
    
    unsigned int                ShaderCompileVertex(const char *pShaderPath);
    unsigned int                ShaderCompileFragment(const char *pShaderPath);
    unsigned int                ShaderCompile(const char *pShaderPath, GLenum pShaderType);
    
    FString                     mName;
    FString                     mVertexProgramFile;
    FString                     mFragmentProgramFile;
    
    FString                     mVertexUniformName;
    FString                     mFragmentUniformName;
    
    
    unsigned int                mProgram;
    unsigned int                mVertexShader;
    unsigned int                mFragmentShader;
    
    int                         mSlotUniforms;
    int                         mSlotPositions;
    int                         mSlotTextureCoords;
    int                         mSlotNormals;
    int                         mSlotUNormals;
    int                         mSlotTangents;
    int                         mSlotData;
    int                         mSlotTextures;
    
    
    /*
    struct TheStruct
    {
        vec3 first;
        vec4 second;
        mat4x3 third;
    };
    */
    
};

#endif /* ShaderProgram_hpp */
