//
//  GamePathEditor.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef GamePathEditor_hpp
#define GamePathEditor_hpp

#include "GFXApp.hpp"
#include "Game.hpp"
#include "EditorMenuPathControl.hpp"
#include "EditorMenuPath.hpp"
#include "FPointList.h"
#include "LevelWavePathBlueprint.hpp"
#include "LevelWaveBlueprint.hpp"
#include "LevelSectionBlueprint.hpp"

#define PATH_MODE_CREATE 0
#define PATH_MODE_EDIT 1
#define PATH_MODE_SELECT 2

class GameEditor;
class GamePathEditor : public FCanvas {
public:
    GamePathEditor(GameEditor *pEditor);
    virtual ~GamePathEditor();
    
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
    
    void                                        Load();
    
    //FPointList                                  mPath;
    int                                         mPathMode;
    void                                        *mSelectedTouch;
    
    float                                       mSelectPathStartX;
    float                                       mSelectPathStartY;
    
    float                                       mSelectTouchStartX;
    float                                       mSelectTouchStartY;
    
    
    void                                        PathRefresh();
    void                                        PathReset();
    
    void                                        PathPrint();
    
    void                                        PathDeletePoint();
    
    void                                        ConstrainXToPoint();
    bool                                        mConstrainXToPoint;
    
    void                                        ConstrainYToPoint();
    bool                                        mConstrainYToPoint;
    
    void                                        ConstraintXToType(int pType);
    void                                        ConstraintYToType(int pType);
    
    void                                        ConstraintXToPrev();
    void                                        ConstraintXToNext();
    
    void                                        ConstraintYToPrev();
    void                                        ConstraintYToNext();
    
    
    
    
    GameEditor                                  *mEditor;
    EditorMenuPathControl                       *mMenuControls;
    EditorMenuPath                              *mMenuPaths;
    
    void                                        Close();
    
    void                                        SetUp(LevelWaveBlueprint *pWave);
    LevelWavePathBlueprint                      *mPath;
    LevelWaveBlueprint                          *mWave;
};

#endif /* GamePathEditor_hpp */
