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
#include "EditorMenuSpawn.hpp"
#include "EditorMenuWavesPicker.hpp"
#include "EditorMenuSpawnPicker.hpp"
#include "EditorMenuAttachment.hpp"
#include "EditorMenuFormationPicker.hpp"

#include "GamePathEditor.hpp"
#include "GameFormationEditor.hpp"
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
    
    //Everything we BUILD is SECTION...
    //This is the BLUEPRINT, not the actual section...
    LevelSectionBlueprint                       mSection;
    
    void                                        RefreshPlayback();
    void                                        RefreshPlaybackSpeed();
    int                                         mSpeedClassIndex;
    
    
    void                                        RefreshSpawn();
    void                                        RefreshSpawnRotationSpeed();
    int                                         mSpawnRotationSpeedClassIndex;
    
    
    void                                        RefreshSection();
    
    void                                        SetOverlay(FCanvas *pCanvas);
    void                                        SelectClosestObject(float pX, float pY);
    
    int                                         ClosestXConstraint(float pX);
    int                                         ClosestYConstraint(float pY);
    
    int                                         NextXConstraintf(float pX);
    int                                         PrevXConstraintf(float pX);
    int                                         NextYConstraintf(float pY);
    int                                         PrevYConstraintf(float pY);
    
    int                                         NextXConstraint(int pConstraint);
    int                                         PrevXConstraint(int pConstraint);
    int                                         NextYConstraint(int pConstraint);
    int                                         PrevYConstraint(int pConstraint);
    
    void                                        WaveAdd();
    void                                        WaveRemove();
    void                                        WaveSelectNext();
    void                                        WaveSelectPrev();
    void                                        WaveDeselect();
    void                                        WaveMoveUp();
    void                                        WaveMoveDown();
    void                                        WaveSelect(int pIndex);
    int                                         WaveCount(int pIndex);
    int                                         WaveIndex();
    
    void                                        SpawnSelect(int pIndex);
    int                                         SpawnIndex();
    LevelWaveSpawnBlueprint                     *SpawnGet();
    
    int                                         SpeedConvertSegmentToType(int pSegmentIndex);
    int                                         SpeedConvertTypeToSegment(int pType);
    
    
    void                                        OpenPathEditor();
    void                                        ClosePathEditor();
    
    void                                        OpenFormationEditor(LevelWaveSpawnFormation *pFormation);
    
    void                                        CloseFormationEditor();
    
    void                                        PickFormationForFormationEditor();
    
    
    void                                        OpenSpawnMenu();
    void                                        OpenWavePickerMenu();
    void                                        OpenSpawnPickerMenu();
    void                                        OpenAttachmentMenu();
    
    
    
    void                                        Clear();
    void                                        LoadCleared();
    void                                        Autosave();
    void                                        Autoload();
    
    
    //Our current "overlay" which will be either "path editor" or "tool container" etc...
    FCanvas                                     *mOverlay;
    
    
    
    
    Game                                        *mGame;
    
    GamePathEditor                              *mPathEditor;
    GameFormationEditor                         *mFormationEditor;
    
    EditorMenuSections                          *mMenuSections;
    EditorMenuSpawn                             *mMenuSpawn;
    EditorMenuWavesPicker                       *mMenuWavesPicker;
    EditorMenuSpawnPicker                       *mMenuSpawnPicker;
    EditorMenuAttachment                        *mMenuAttachment;
    
    
    FCanvas                                     *mToolContainer;
    
    float                                       mSpawnZoneTop;
    float                                       mSpawnZoneRight;
    float                                       mSpawnZoneLeft;
    float                                       mSpawnZoneBottom;
    
    float                                       mPeekZoneTop;
    float                                       mPeekZoneRight;
    float                                       mPeekZoneLeft;
    
    float                                       mQuarterZoneTop;
    float                                       mQuarterZoneRight;
    float                                       mQuarterZoneLeft;
    float                                       mQuarterZoneBottom;
    
    float                                       mPlayZoneBottom;
    
    float                                       mExitZoneTop;
    float                                       mExitZoneRight;
    float                                       mExitZoneLeft;
    
    float                                       mGameAreaTop;
    float                                       mGameAreaRight;
    float                                       mGameAreaBottom;
    float                                       mGameAreaLeft;
    
    float                                       mCenterH;
    float                                       mCenterV;
    
    int                                         mExportIndex;
    
    void                                        SaveAt(int pIndex);
    void                                        LoadAt(int pIndex);
    
    void                                        Save(const char *pFile);
    void                                        Load(const char *pFile);
    
    void                                        SaveConfig();
    void                                        LoadConfig();
    
    int                                         mAutosaveTimer;
    int                                         mEnqueueInitialLoad;
    
    
    
    
    
    //Map to game.
    //We prefix with EDITOR because these are game control. Not editor internal.
    //Essentially, it's a fake game that we can look at with our decayed eyeballs.
    void                                        EditorRestartWave();
    void                                        EditorRestartSection();
    
    bool                                        mEditorWaveLoop;
    bool                                        mEditorSectionLoop;
    bool                                        mEditorShowReferenced;
    bool                                        mEditorPlaybackEnabled;
    bool                                        mEditorPlaybackWaveOnly;
    bool                                        mEditorPlaybackFromCurrentWave;
    
    LevelSection                                mEditorSection;
    LevelWave                                   mEditorWave;
    FList                                       mEditorObjectList;
    FList                                       mEditorObjectQueue;
    
    
};

extern GameEditor *gEditor;

#endif /* GameEditorEditor_hpp */