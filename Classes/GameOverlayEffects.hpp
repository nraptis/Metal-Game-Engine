//
//  GameOverlayEffectsEffects.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 9/3/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef GameOverlayEffectsEffects_hpp
#define GameOverlayEffectsEffects_hpp

#include "GFXApp.hpp"

class Game;
class GameObject;
class Balloon;
class FreeLife;
class GameOverlayEffects : public FCanvas {
public:
    GameOverlayEffects();
    virtual ~GameOverlayEffects();
    
    virtual void                                Layout() override;
    virtual void                                Update() override;
    virtual void                                Draw() override;
    
    void                                        Get2DPos(GameObject *pObject, float &pX, float &pY);
    
    void                                        GenerateBalloonPopAnimation(Balloon *pBalloon);
    void                                        GenerateFreeLifePopAnimation(FreeLife *pFreeLife);
    
    FObjectList                                 mEffectListBalloonBursts;
    FObjectList                                 mEffectListDartFadeStar;
    
    float                                       mSeqFrame01;
    float                                       mSeqFrame02;
    float                                       mSeqFrame03;
    
    
    
    
};

extern GameOverlayEffects *gEffectsOverlay;

#endif /* GameOverlayEffectsEffects_hpp */
