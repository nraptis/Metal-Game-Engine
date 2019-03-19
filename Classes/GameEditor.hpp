//
//  GameEditorEditor.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/17/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef GameEditorEditor_hpp
#define GameEditorEditor_hpp


#include "GFXApp.hpp"
#include "FloatingCamera.hpp"
#include "Game.hpp"
#include "EditorMenuSections.hpp"
#include "GamePathEditor.hpp"
#include "LevelWavePathBlueprint.hpp"
#include "LevelWaveBlueprint.hpp"
#include "LevelSectionBlueprint.hpp"

class GameEditor : public FCanvas {
public:
    GameEditor(Game *pGame);
    virtual ~GameEditor();
    
    
    virtual void                                Layout() override;
    
    virtual void                                Update() override;
    virtual void                                Draw() override;
    
    virtual void                                TouchDown(float pX, float pY, void *pData) override;
    virtual void                                TouchMove(float pX, float pY, void *pData) override;
    virtual void                                TouchUp(float pX, float pY, void *pData) override;
    virtual void                                TouchFlush() override;
    
    virtual void                                KeyDown(int pKey) override;
    virtual void                                KeyUp(int pKey) override;
    
    virtual void                                Notify(void *pSender, const char *pNotification) override;
    
    void                                        Load();
    
    void                                        SetOverlay(FCanvas *pCanvas);
    
    
    
    void                                        WaveAdd();
    void                                        WaveRemove();
    void                                        WaveSelectNext();
    void                                        WaveSelectPrev();
    void                                        WaveDeselect();
    
    
    void                                        OpenPathEditor();
    void                                        ClosePathEditor();
    
    
    
    LevelSectionBlueprint                       *mCurrentSection;
    
    
    
    //Our current "overlay" which will be either "path editor" or "tool container" etc...
    FCanvas                                     *mOverlay;
    
    
    
    
    Game                                        *mGame;
    GamePathEditor                              *mPathEditor;
    
    
    EditorMenuSections                          *mMenuSections;
    
    FCanvas                                     *mToolContainer;
    
    
    
    float                                       mSpawnZoneTop;
    float                                       mSpawnZoneRight;
    float                                       mSpawnZoneLeft;
    float                                       mSpawnZoneBottom;
    
    float                                       mPeekZoneTop;
    float                                       mPeekZoneRight;
    float                                       mPeekZoneBottom;
    float                                       mPeekZoneLeft;
    
    float                                       mQuarterZoneTop;
    float                                       mQuarterZoneRight;
    float                                       mQuarterZoneLeft;
    float                                       mQuarterZoneBottom;
    
    float                                       mPlayZoneBottom;
    
    float                                       mCenterH;
    float                                       mCenterV;
    
    
};

extern GameEditor *gEditor;

#endif /* GameEditorEditor_hpp */
