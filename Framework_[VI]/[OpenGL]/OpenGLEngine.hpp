//
//  OpenGLEngine.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/8/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef OpenGLEngine_hpp
#define OpenGLEngine_hpp

#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#include "ShaderProgram.hpp"
#include "ShaderProgramSprite.hpp"
#include "ShaderProgramSpriteWhite.hpp"
#include "ShaderProgramShape3D.hpp"

class OpenGLEngine {
public:
    
    OpenGLEngine();
    ~OpenGLEngine();
    
    void                            SetUp();
    
    void                            BuildPrograms();
    
    void                            Prerender();
    void                            Postrender();
    
    
    bool                            IsReady();
    bool                            mIsReady;
    
    void                            UseProgram(ShaderProgram *pProgram);
    
    void                            UseProgramShape2D();
    void                            UseProgramShape3D();
    
    void                            UseProgramSprite();
    void                            UseProgramSpriteWhite();
    
    
    ShaderProgram                   *mShaderProgramShape2D;
    ShaderProgramShape3D            *mShaderProgramShape3D;
    ShaderProgramSprite             *mShaderProgramSprite;
    ShaderProgramSpriteWhite        *mShaderProgramSpriteWhite;
    
    
    GLint                           framebufferWidth;
    GLint                           framebufferHeight;
    
    // The OpenGL ES names for the framebuffer and renderbuffer used to render to this view.
    GLuint                          defaultFramebuffer;
    GLuint                          colorRenderbuffer;
    GLuint                          depthRenderbuffer;
    
    //int                         mSpriteProgram;
    
    
};


#endif /* OpenGLEngine_hpp */
