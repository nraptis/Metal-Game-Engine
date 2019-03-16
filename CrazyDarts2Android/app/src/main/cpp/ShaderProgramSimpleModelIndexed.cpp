//
//  ShaderProgramSimpleModelIndexed.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/15/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "core_includes.h"
#include "os_core_graphics.h"
#include "ShaderProgramSimpleModelIndexed.hpp"

ShaderProgramSimpleModelIndexed::ShaderProgramSimpleModelIndexed(const char *pVertexPath, const char *pFragmentPath) : ShaderProgram(pVertexPath, pFragmentPath) {
    mDataOffset = 0;
    
    mSlotTexture = -1;
    mSlotTextureCoords = -1;
}

void ShaderProgramSimpleModelIndexed::Compile() {
    
    ShaderProgram::Compile();
    
    if (IsValid() == false) return;
    
    //mSlotColors = glGetAttribLocation(mProgram, "Colors");
    mSlotTexture = glGetUniformLocation(mProgram, "Texture");
    mSlotTextureCoords = glGetAttribLocation(mProgram, "TextureCoords");
    
    Log("*******\n");
    Log("Shader[%s] mSlotProjectionUniform = %d\n", mName.c(), mSlotProjectionUniform);
    Log("Shader[%s] mSlotModelViewUniform = %d\n", mName.c(), mSlotModelViewUniform);
    Log("Shader[%s] mSlotModulateUniform = %d\n", mName.c(), mSlotModulateUniform);
    Log("Shader[%s] mSlotPositions = %d\n", mName.c(), mSlotPositions);
    Log("Shader[%s] mSlotTextureCoords = %d\n", mName.c(), mSlotTextureCoords);
    Log("Shader[%s] mSlotTexture = %d\n", mName.c(), mSlotTexture);
    
    Log("*******\n");
}

void ShaderProgramSimpleModelIndexed::BindUniform(FUniforms *pUniform) {
    if (pUniform && pUniform->GetType() == UNIFORM_TYPE_BASIC) {
        ShaderProgram::BindUniform(pUniform);
    } else {
        Log("Uniform wrong type? [%x]\n", pUniform);
    }
}

void ShaderProgramSimpleModelIndexed::ArrayBufferData(int pIndex, int pOffset) {
    if (pIndex != -1) if (pIndex != -1) { glBindBuffer(GL_ARRAY_BUFFER, pIndex); }
    glEnableVertexAttribArray(mSlotPositions);
    int aStride = 3 + 3;
    unsigned char *aOffset = NULL;
    aOffset = &(aOffset[pOffset]);
    glVertexAttribPointer(mSlotPositions, 3, GL_FLOAT, GL_FALSE, (aStride << 2), aOffset);
    mDataOffset = pOffset;
}

void ShaderProgramSimpleModelIndexed::ArrayBufferPositions(int pIndex, int pOffset) {
    if (pIndex != -1) if (pIndex != -1) { glBindBuffer(GL_ARRAY_BUFFER, pIndex); }
    glEnableVertexAttribArray(mSlotPositions);
    int aStride = 3 + 3;
    unsigned char *aOffset = NULL;
    aOffset = &(aOffset[pOffset + mDataOffset]);
    glVertexAttribPointer(mSlotPositions, 3, GL_FLOAT, GL_FALSE, (aStride << 2), aOffset);
}

void ShaderProgramSimpleModelIndexed::ArrayBufferTextureCoords(int pIndex, int pOffset) {
    if (pIndex != -1) if (pIndex != -1) { glBindBuffer(GL_ARRAY_BUFFER, pIndex); }
    glEnableVertexAttribArray(mSlotTextureCoords);
    int aStride = 3 + 3;
    unsigned char *aOffset = NULL;
    aOffset = &(aOffset[pOffset + mDataOffset]);
    glVertexAttribPointer(mSlotTextureCoords, 3, GL_FLOAT, GL_FALSE, (aStride << 2), aOffset);
}


