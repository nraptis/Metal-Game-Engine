//
//  GameRenderer.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 2/26/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef GameRenderer_hpp
#define GameRenderer_hpp

#include "FloatingCamera.hpp"
#include "FModelDataPacked.hpp"
#include "FUniforms.hpp"

class Game;
class GameRenderer {
public:
    GameRenderer(Game *pGame, FloatingCamera *pCamera);
    ~GameRenderer();
    
    void                                Draw3D();
    void                                DumpLightsToUniforms();
    
    Game                                *mGame;
    FloatingCamera                      *mCamera;
    
    FModelDataPacked                    *mDart;
    
    float                               mLightDirX;
    float                               mLightDirY;
    float                               mLightDirZ;
    
    float                               mLightDirRotationPrimaryBase;
    float                               mLightDirRotationSecondaryBase;
    
    float                               mLightRedBase;
    float                               mLightGreenBase;
    float                               mLightBlueBase;
    
    float                               mLightAmbientBase;
    float                               mLightDiffuseBase;
    float                               mLightSpecularBase;
    
    
    FUniformsLightPhong                 mUniformPhongBalloon;
    FUniformsLightPhong                 mUniformPhong;
    FUniformsLightDiffuse               mUniformDiffuse;
    FUniformsLightAmbient               mUniformAmbient;
    
    float                               mDartSpin;
    
    
};

#endif

