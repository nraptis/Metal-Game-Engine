//
//  GameFormationEditor.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/30/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef GameFormationEditor_hpp
#define GameFormationEditor_hpp

#include "GFXApp.hpp"
#include "Game.hpp"
#include "EditorMenuFormationUtilities.hpp"
#include "EditorMenuFormation.hpp"
#include "LevelWaveSpawnFormationBlueprint.hpp"
#include "LevelWaveSpawnFormation.hpp"

#define FORMATION_MODE_ADD_POINT 0
#define FORMATION_MODE_MOVE_POINT 1
#define FORMATION_MODE_SELECT_POINT 2


class GameEditor;
class GameFormationEditor : public FCanvas {
public:
    GameFormationEditor(GameEditor *pEditor);
    virtual ~GameFormationEditor();
    
    virtual void                                SetFrame(float pX, float pY, float pWidth, float pHeight) override;
    
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
    
    GameEditor                                  *mEditor;
    EditorMenuFormationUtilities                *mMenuUtils;
    EditorMenuFormation                         *mMenuFormation;
    
    
    int                                         mFormationMode;
    
    
    bool                                        mTracerEnabled;
    int                                         mTracerMode;
    
    
    bool                                        mGridEnabled;
    int                                         mGridSize;
    int                                         mGridSpacing;
    
    
    
    
    
    
    
    
    void                                        Close();
    
    void                                        Refresh();
    
    void                                        SetUp(LevelWaveSpawnFormationBlueprint *pFormation);
    LevelWaveSpawnFormationBlueprint            mFormation;
    
    float                                       mGameAreaTop;
    float                                       mGameAreaRight;
    float                                       mGameAreaBottom;
    float                                       mGameAreaLeft;
    
    float                                       mCenterX;
    float                                       mCenterY;
    
    LevelWaveSpawnFormation                     mEditorFormation;
    
};

extern GameFormationEditor *gFormationEditor;

#endif /* GameFormationEditor_hpp */
