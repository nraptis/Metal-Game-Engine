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

//static int gFrameBuffer = NULL;
//static int gRenderBuffer0 = NULL;
//static int gRenderBuffer1 = NULL;
//static int gDepthBuffer = NULL;

OpenGLEngine::OpenGLEngine() {
    mIsReady = false;
}

OpenGLEngine::~OpenGLEngine() {
    
}

void OpenGLEngine::SetUp() {
    
    /*
    glGenFramebuffers(1, &gFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, gFrameBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, gRenderBuffer0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, gRenderBuffer1);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, gDepthBuffer);
    */
    
    BuildPrograms();
    
    mIsReady = true;
}

void OpenGLEngine::BuildPrograms() {
    
    mShaderProgramShape2D = new ShaderProgram("shape_2d_vertex_shader.glsl", "shape_2d_fragment_shader.glsl");
    mShaderProgramShape2D->Compile();
    
    
    mShaderProgramShape3D = new ShaderProgramShape3D("shape_3d_vertex_shader.glsl", "shape_3d_fragment_shader.glsl");
    mShaderProgramShape3D->Compile();
    
    
    
    
    
    
    
    
    
    mShaderProgramSprite = new ShaderProgramSprite("sprite_vertex_shader.glsl", "sprite_fragment_shader.glsl");
    mShaderProgramSprite->Compile();
    
    mShaderProgramSpriteWhite = new ShaderProgramSpriteWhite("sprite_white_vertex_shader.glsl", "sprite_white_fragment_shader.glsl");
    mShaderProgramSpriteWhite->Compile();
    
    
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
        Graphics::SetShaderProgram(pProgram);
        pProgram->Use();
    } else {
        if (pProgram) {
            printf("Could Not Use Program [%s]", pProgram->mName.c());
        } else {
            printf("Could Not Use Program [???]");
        }
    }
}

void OpenGLEngine::UseProgramShape2D() {
    UseProgram(mShaderProgramShape2D);
}

void OpenGLEngine::UseProgramShape3D() {
    UseProgram(mShaderProgramShape3D);
}

void OpenGLEngine::UseProgramSprite() {
    UseProgram(mShaderProgramSprite);
}

void OpenGLEngine::UseProgramSpriteWhite() {
    UseProgram(mShaderProgramSpriteWhite);
}
