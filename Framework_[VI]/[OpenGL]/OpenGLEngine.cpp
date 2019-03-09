//
//  OpenGLEngine.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/8/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "OpenGLEngine.hpp"
#include "FFile.hpp"
#include "core_includes.h"
#include "FApp.hpp"

static int gRenderBuffer0 = NULL;
static int gRenderBuffer1 = NULL;

static int gDepthBuffer = NULL;

OpenGLEngine::OpenGLEngine() {
    mIsReady = false;
}

OpenGLEngine::~OpenGLEngine() {
    
}

void OpenGLEngine::SetUp() {
    
    printf("OpenGLEngine::SetUp()\n");
    
    GLuint aFrameBuffer;
    glGenFramebuffers(1, &aFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, aFrameBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, gRenderBuffer0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, gRenderBuffer1);
    
    
    
    //gGLSlotPosition = glGetAttribLocation(gGLProgram, "Position");
    //gGLSlotTexCoord = glGetAttribLocation(gGLProgram, "TexCoordIn");
    //gGLSlotColor = glGetAttribLocation(gGLProgram, "SourceColor");
    
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, gDepthBuffer);
    
    BuildPrograms();
    
    mIsReady = true;
}

void OpenGLEngine::BuildPrograms() {
    
    
    mShaderProgramShape = new ShaderProgram("shape_vertex_shader.glsl", "shape_fragment_shader.glsl");
    mShaderProgramShape->Compile();
    //
    //
    
    
    mShaderProgramSprite = new ShaderProgram("sprite_vertex_shader.glsl", "sprite_fragment_shader.glsl");
    //mShaderProgramSprite->SetUniformNames("SpriteVertexUniforms", "SpriteFragmentUniforms");
    
    mShaderProgramSprite->Compile();
    
    
}

bool OpenGLEngine::IsReady() {
    return mIsReady;
}

void OpenGLEngine::Prerender() {
    
}

void OpenGLEngine::Postrender() {
    
}

void OpenGLEngine::UseProgram(ShaderProgram *pProgram) {
    if (pProgram != NULL) {
        pProgram->Use();
    } else {
        if (pProgram) {
            printf("Could Not Use Program [%s]", pProgram->mName.c());
        } else {
            printf("Could Not Use Program [???]");
        }
    }
}

void OpenGLEngine::UseProgramSprite() {
    UseProgram(mShaderProgramSprite);
}
