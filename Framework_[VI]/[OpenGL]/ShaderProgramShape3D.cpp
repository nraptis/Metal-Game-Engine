//
//  ShaderProgramShape3D.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/8/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "core_includes.h"
#include "ShaderProgramShape3D.hpp"

ShaderProgramShape3D::ShaderProgramShape3D(const char *pVertexPath, const char *pFragmentPath) : ShaderProgram(pVertexPath, pFragmentPath) {
}

void ShaderProgramShape3D::Compile() {
    
    ShaderProgram::Compile();
    
    if (IsValid() == false) return;
    
    Log("*******\n");
    Log("Shader[%s] mSlotProjectionUniform = %d\n", mName.c(), mSlotProjectionUniform);
    Log("Shader[%s] mSlotModelViewUniform = %d\n", mName.c(), mSlotModelViewUniform);
    Log("Shader[%s] mSlotModulateUniform = %d\n", mName.c(), mSlotModulateUniform);
    Log("Shader[%s] mSlotPositions = %d\n", mName.c(), mSlotPositions);
    
    Log("*******\n");
}

void ShaderProgramShape3D::BindUniform(FUniforms *pUniform) {
    if (pUniform && pUniform->GetType() == UNIFORM_TYPE_BASIC) {
        ShaderProgram::BindUniform(pUniform);
    } else {
        Log("Uniform wrong type? [%x]\n", pUniform);
    }
}

void ShaderProgramShape3D::ArrayBufferPositions(int pIndex, int pOffset) {
    
    if (pIndex != -1) if (pIndex != -1) { glBindBuffer(GL_ARRAY_BUFFER, pIndex); }
    
    glEnableVertexAttribArray(mSlotPositions);
    int aStride = 3;
    unsigned char *aOffset = NULL;
    aOffset = &(aOffset[pOffset]);
    glVertexAttribPointer(mSlotPositions, 3, GL_FLOAT, GL_FALSE, (aStride << 2), aOffset);
}
