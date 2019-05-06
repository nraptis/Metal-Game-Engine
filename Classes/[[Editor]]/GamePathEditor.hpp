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
#include "FPointList.hpp"
#include "LevelPathBlueprint.hpp"
#include "LevelWaveBlueprint.hpp"
#include "LevelSectionBlueprint.hpp"
#include "LevelSectionPermanentBlueprint.hpp"
#include "EditorMenuFormationGrid.hpp"
#include "GameEditorGrid.hpp"

#define PATH_MODE_CREATE 0
#define PATH_MODE_EDIT 1
#define PATH_MODE_SELECT 2

class GameEditor;
class GamePermanentEditor;
class GamePathEditor : public FCanvas {
public:
    GamePathEditor(GameEditor *pEditor);
    GamePathEditor(GamePermanentEditor *pEditor);
    
    void                                        Init();
    
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
    
    GameEditorGrid                              mGrid;
    
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
    GamePermanentEditor                         *mPermanentEditor;
    
    EditorMenuPathControl                       *mMenuControls;
    EditorMenuPath                              *mMenuPaths;
    EditorMenuFormationGrid                     *mMenuGrid;
    
    
    void                                        Close();
    
    void                                        SetUp(LevelWaveBlueprint *pWave);
    void                                        SetUp(LevelSectionPermanentBlueprint *pPerm);
    
    void                                        SetUpPath(LevelPathBlueprint *pPath);
    
    
    
    
    
    LevelPathBlueprint                          *mPath;
    LevelWaveBlueprint                          *mWave;
    LevelSectionPermanentBlueprint              *mPerm;
    
};

#endif /* GamePathEditor_hpp */
