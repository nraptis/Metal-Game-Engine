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

class OpenGLEngine {
public:
    
    OpenGLEngine();
    ~OpenGLEngine();
    
    void                        SetUp();
    
    void                        BuildPrograms();
    
    void                        Prerender();
    void                        Postrender();
    
    
    bool                        IsReady();
    bool                        mIsReady;
    
    void                        UseProgram(ShaderProgram *pProgram);
    void                        UseProgramSprite();
    
    
    
    ShaderProgram               *mShaderProgramShape;
    ShaderProgram               *mShaderProgramSprite;
    
    
    
    //int                         mSpriteProgram;
    
    
};


#endif /* OpenGLEngine_hpp */
