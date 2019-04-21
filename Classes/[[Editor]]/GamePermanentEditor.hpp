//
//  GamePermanentEditor.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/6/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef GamePermanentEditor_hpp
#define GamePermanentEditor_hpp

#include "GFXApp.hpp"
#include "Game.hpp"
#include "EditorMenuPermanentUtils.hpp"
#include "EditorMenuPermanent.hpp"
#include "LevelSectionPermanentBlueprint.hpp"
#include "LevelSectionPermanent.hpp"
#include "GamePathEditor.hpp"

#define PERMANENT_MODE_ADD 0
#define PERMANENT_MODE_MOVE 1
#define PERMANENT_MODE_SELECT 2

class GameEditor;
class GamePermanentEditor : public FCanvas {
public:
    GamePermanentEditor(GameEditor *pEditor);
    virtual ~GamePermanentEditor();
    
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
    EditorMenuPermanentUtils                    *mMenuUtils;
    EditorMenuPermanent                         *mMenuPerm;
    
    void                                        SetOverlay(FCanvas *pCanvas);
    FCanvas                                     *mOverlay;
    FCanvas                                     *mToolContainer;
    GamePathEditor                              *mPathEditor;
    
    void                                        OpenPathEditor();
    void                                        ClosePathEditor();
    
    
    
    
    void                                        AddPath();
    void                                        DeletePath();
    void                                        DeletePermanent();
    
    
    LevelSectionPermanentBlueprint              *GetPerm();
    
    bool                                        mSnapsEnabled;
    
    int                                         mPermMode;
    
    bool                                        mMarkersDisplay;
    
    void                                        *mSelectedTouch;
    
    float                                       mSelectNodeStartX;
    float                                       mSelectNodeStartY;
    
    float                                       mSelectTouchStartX;
    float                                       mSelectTouchStartY;
    
    void                                        Close();
    
    void                                        ResetSelected();
    
    
    void                                        Refresh();
    
    void                                        PickDefaultModes();
    
    void                                        SetUp();
    
    
    void                                        BreakConstraintX();
    void                                        BreakConstraintY();
    
    
    void                                        ResetOffsetX();
    void                                        ResetOffsetY();

    
    
    
    
    
    //if (pSender == mButtonDeletePermanent) { mEditor->BreakConstraintY(); }
    //if (pSender == mButtonEditPermanentPaths) { mEditor->BreakConstraintY(); }
    //if (pSender == mButtonAddPath) { mEditor->BreakConstraintY(); }
    //if (pSender == mButtonDeletePath) { mEditor->BreakConstraintY(); }
    
    
    
    
    
    
    float                                       mGameAreaTop;
    float                                       mGameAreaRight;
    float                                       mGameAreaBottom;
    float                                       mGameAreaLeft;
};

extern GamePermanentEditor *gPermEditor;

#endif
