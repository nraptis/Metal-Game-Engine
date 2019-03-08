//
//  ShaderProgram.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/8/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "ShaderProgram.hpp"
#include "FFile.hpp"
#include "core_includes.h"

ShaderProgram::ShaderProgram(const char *pVertexPath, const char *pFragmentPath) {
    
    mVertexProgramFile = pVertexPath;
    mFragmentProgramFile = pFragmentPath;
    
    mName = FString(pVertexPath);
    mName.RemoveExtension();
    mName.Replace("_vertex_", "_");
    
    mProgram = SHADER_INVALID_PROGRAM;
    mVertexShader = SHADER_INVALID_SHADER;
    mFragmentShader = SHADER_INVALID_SHADER;
    
    mSlotUniforms = -1;
    mSlotPositions = -1;
    mSlotTextureCoords = -1;
    mSlotNormals = -1;
    mSlotUNormals = -1;
    mSlotTangents = -1;
    mSlotData = -1;
    mSlotTextures = -1;
}

ShaderProgram::~ShaderProgram() {
    printf("Destroying Shader %s\n", mName.c());
    
    Kill();
}

bool ShaderProgram::IsValid() {
    if (mProgram != SHADER_INVALID_PROGRAM && mProgram != 0) {
        return true;
    }
    return false;
}

void ShaderProgram::Use() {
    if (mProgram != SHADER_INVALID_PROGRAM && mProgram != 0) {
        glUseProgram(mProgram);
    }
}

void ShaderProgram::SetUniformNames(const char *pVertexUniformName, const char *pFragmentUniformName) {
    mVertexUniformName = pVertexUniformName;
    mFragmentUniformName = pFragmentUniformName;
    
}

void ShaderProgram::Compile() {
    printf("ShaderProgram::Compile(%s)\n", mName.c());
    
    mProgram = glCreateProgram();
    
    mVertexShader = ShaderCompileVertex(mVertexProgramFile.c());
    mFragmentShader = ShaderCompileFragment(mFragmentProgramFile.c());
    
    
    glAttachShader(mProgram, mVertexShader);
    glAttachShader(mProgram, mFragmentShader);
    
    glLinkProgram(mProgram);
    
    // 3
    GLint linkSuccess;
    glGetProgramiv(mProgram, GL_LINK_STATUS, &linkSuccess);
    if (linkSuccess == GL_FALSE) {
        printf("FAILED TO LINK SHADER [%s]\n", mName.c());
        
        GLchar messages[256];
        glGetProgramInfoLog(mProgram, sizeof(messages), 0, &messages[0]);
        printf("%s\n", messages);
        
        Kill();
        
        return;
    }
    
    printf("Linking Shader [%s] Is Successful!\n", mName.c());
    
    
}

void ShaderProgram::Kill() {
    if (mVertexShader != SHADER_INVALID_SHADER && mVertexShader != 0) {
        if (mProgram != SHADER_INVALID_PROGRAM && mProgram != 0) {
            glDetachShader(mProgram, mVertexShader);
        }
        glDeleteShader(mVertexShader);
    }
    if (mFragmentShader != SHADER_INVALID_SHADER && mFragmentShader != 0) {
        if (mProgram != SHADER_INVALID_PROGRAM && mProgram != 0) {
            glDetachShader(mProgram, mFragmentShader);
        }
        glDeleteShader(mFragmentShader);
    }
    
    if (mProgram != SHADER_INVALID_PROGRAM && mProgram != 0) {
        glDeleteProgram(mProgram);
    }
    
    mVertexShader = SHADER_INVALID_SHADER;
    mFragmentShader = SHADER_INVALID_SHADER;
    mProgram = SHADER_INVALID_PROGRAM;
}

unsigned int ShaderProgram::ShaderCompile(const char *pShaderPath, GLenum pShaderType) {
    unsigned int aShader = 0;
    FFile aFile;
    aFile.Load(pShaderPath);
    if (aFile.mLength > 0) {
        aShader = glCreateShader(pShaderType);
        const char *aData = (const char*)(aFile.mData);
        int aLength = (int)aFile.mLength;
        glShaderSource(aShader, 1, &aData, &(aLength));
        glCompileShader(aShader);
        int aCompileSuccess;
        glGetShaderiv(aShader, GL_COMPILE_STATUS, &aCompileSuccess);
        if (aCompileSuccess == GL_FALSE) {
            GLchar aErrorMessage[1024];
            glGetShaderInfoLog(aShader, sizeof(aErrorMessage), 0, &aErrorMessage[0]);
            printf("Shader Error!\n");
            printf("%s", aErrorMessage);
        }
    }
    return aShader;
}

unsigned int ShaderProgram::ShaderCompileVertex(const char *pShaderPath) {
    return ShaderCompile(pShaderPath, GL_VERTEX_SHADER);
}

unsigned int ShaderProgram::ShaderCompileFragment(const char *pShaderPath) {
    return ShaderCompile(pShaderPath, GL_FRAGMENT_SHADER);
}

