//
//  ShaderProgramModelIndexedLightedPhong.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/15/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "core_includes.h"
#include "os_core_graphics.h"
#include "ShaderProgramModelIndexedLightedPhong.hpp"

//
//  ShaderProgramModelIndexedLightedPhong.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/24/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "ShaderProgramModelIndexedLightedPhong.hpp"

//
//  ShaderProgramModelIndexedLightedPhong.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/15/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//



#include "core_includes.h"
#include "os_core_graphics.h"
#include "ShaderProgramModelIndexedLightedPhong.hpp"


ShaderProgramModelIndexedLightedPhong::ShaderProgramModelIndexedLightedPhong(const char *pVertexPath, const char *pFragmentPath) : ShaderProgram(pVertexPath, pFragmentPath) {
    mDataOffset = 0;
    
    mSlotTexture = -1;
    mSlotTextureCoords = -1;
    mSlotNormals = -1;
    
    mSlotAmbient = -1;
}

void ShaderProgramModelIndexedLightedPhong::Compile() {
    
    ShaderProgram::Compile();
    
    if (IsValid() == false) return;
    
    
    mSlotNormalMatrixUniform = glGetUniformLocation(mProgram, "NormalMatrix");
    
    //mSlotColors = glGetAttribLocation(mProgram, "Colors");
    mSlotTexture = glGetUniformLocation(mProgram, "Texture");
    mSlotAmbient = glGetUniformLocation(mProgram, "Ambient");
    mSlotDiffuse = glGetUniformLocation(mProgram, "Diffuse");
    mSlotSpecular = glGetUniformLocation(mProgram, "Specular");
    
    
    mSlotMaterial = glGetUniformLocation(mProgram, "Material");
    
    
    
    mSlotTextureCoords = glGetAttribLocation(mProgram, "TextureCoords");
    mSlotNormals = glGetAttribLocation(mProgram, "Normals");
    
    
    
    Log("*******\n");
    Log("Shader[%s] mSlotProjectionMatrixUniform = %d\n", mName.c(), mSlotProjectionMatrixUniform);
    Log("Shader[%s] mSlotModelViewMatrixUniform = %d\n", mName.c(), mSlotModelViewMatrixUniform);
    Log("Shader[%s] mSlotNormalMatrixUniform = %d\n", mName.c(), mSlotNormalMatrixUniform);
    
    
    Log("Shader[%s] mSlotModulateColorUniform = %d\n", mName.c(), mSlotModulateColorUniform);
    Log("Shader[%s] mSlotPositions = %d\n", mName.c(), mSlotPositions);
    Log("Shader[%s] mSlotTextureCoords = %d\n", mName.c(), mSlotTextureCoords);
    Log("Shader[%s] mSlotNormals = %d\n", mName.c(), mSlotNormals);
    
    Log("Shader[%s] mSlotTexture = %d\n", mName.c(), mSlotTexture);
    Log("Shader[%s] mSlotAmbient = %d\n", mName.c(), mSlotAmbient);
    Log("Shader[%s] mSlotDiffuse = %d\n", mName.c(), mSlotDiffuse);
    Log("Shader[%s] mSlotSpecular = %d\n", mName.c(), mSlotSpecular);
    
    Log("Shader[%s] mSlotMaterial = %d\n", mName.c(), mSlotMaterial);
    
    Log("*******\n");
}

void ShaderProgramModelIndexedLightedPhong::BindUniform(FUniforms *pUniform) {
    if (pUniform && pUniform->GetType() == UNIFORM_TYPE_LIGHT_PHONG) {
        FUniformsLightPhong *aUniform = (FUniformsLightPhong *)pUniform;
        ShaderProgram::BindUniform(pUniform);
        
        glUniformMatrix4fv(mSlotNormalMatrixUniform, 1, 0, aUniform->mNormal.m);
        
        
        glUniform4f(mSlotAmbient, aUniform->mLight.mRed, aUniform->mLight.mGreen, aUniform->mLight.mBlue,aUniform->mLight.mAmbientIntensity);
        glUniform4f(mSlotDiffuse, aUniform->mLight.mDirX, aUniform->mLight.mDirY, aUniform->mLight.mDirZ, aUniform->mLight.mDiffuseIntensity);
        glUniform2f(mSlotSpecular, aUniform->mLight.mShininess, aUniform->mLight.mSpecularIntensity);
        
    } else {
        Log("Uniform wrong type? [%x]\n", pUniform);
    }
}

void ShaderProgramModelIndexedLightedPhong::ArrayBufferData(FBuffer *pBuffer, int pOffset) {
    if (pBuffer != NULL && pBuffer->mBindIndex != -1) {
        glBindBuffer(GL_ARRAY_BUFFER, pBuffer->mBindIndex);
    }
    glEnableVertexAttribArray(mSlotPositions);
    int aStride = 3 + 3 + 3;
    unsigned char *aOffset = NULL;
    aOffset = &(aOffset[pOffset]);
    glVertexAttribPointer(mSlotPositions, 3, GL_FLOAT, GL_FALSE, (aStride << 2), aOffset);
    mDataOffset = pOffset;
}

void ShaderProgramModelIndexedLightedPhong::ArrayBufferPositions(FBuffer *pBuffer, int pOffset) {
    if (pBuffer != NULL && pBuffer->mBindIndex != -1) {
        glBindBuffer(GL_ARRAY_BUFFER, pBuffer->mBindIndex);
    }
    glEnableVertexAttribArray(mSlotPositions);
    int aStride = 3 + 3 + 3;
    unsigned char *aOffset = NULL;
    aOffset = &(aOffset[pOffset + mDataOffset]);
    glVertexAttribPointer(mSlotPositions, 3, GL_FLOAT, GL_FALSE, (aStride << 2), aOffset);
}

void ShaderProgramModelIndexedLightedPhong::ArrayBufferTextureCoords(FBuffer *pBuffer, int pOffset) {
    if (pBuffer != NULL && pBuffer->mBindIndex != -1) {
        glBindBuffer(GL_ARRAY_BUFFER, pBuffer->mBindIndex);
    }
    glEnableVertexAttribArray(mSlotTextureCoords);
    int aStride = 3 + 3 + 3;
    unsigned char *aOffset = NULL;
    aOffset = &(aOffset[pOffset + mDataOffset]);
    glVertexAttribPointer(mSlotTextureCoords, 3, GL_FLOAT, GL_FALSE, (aStride << 2), aOffset);
}

void ShaderProgramModelIndexedLightedPhong::ArrayBufferNormals(FBuffer *pBuffer, int pOffset) {
    if (pBuffer != NULL && pBuffer->mBindIndex != -1) {
        glBindBuffer(GL_ARRAY_BUFFER, pBuffer->mBindIndex);
    }
    glEnableVertexAttribArray(mSlotNormals);
    int aStride = 3 + 3 + 3;
    unsigned char *aOffset = NULL;
    aOffset = &(aOffset[pOffset + mDataOffset]);
    glVertexAttribPointer(mSlotNormals, 3, GL_FLOAT, GL_FALSE, (aStride << 2), aOffset);
}
