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
#include "EditorMenuFormationSpawnPicker.hpp"
#include "EditorMenuFormationGrid.hpp"

#include "LevelFormationBlueprint.hpp"
#include "LevelFormation.hpp"
#include "FPointList.hpp"

#define FORMATION_MODE_ADD_POINT 0
#define FORMATION_MODE_MOVE_POINT 1
#define FORMATION_MODE_SELECT_POINT 2


#define FORMATION_GRID_TYPE_RECT 0
#define FORMATION_GRID_TYPE_CIRCLE 1
#define FORMATION_GRID_TYPE_STAR 2
#define FORMATION_GRID_TYPE_TRIANGLE 3
#define FORMATION_GRID_TYPE_NGON1 4
#define FORMATION_GRID_TYPE_NGON2 5


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
    EditorMenuFormationSpawnPicker              *mMenuSpawn;
    EditorMenuFormationGrid                     *mMenuGrid;
    
    
    //Speed Classes...
    int                                         mFormationRotationSpeedClassIndex;
    int                                         mTracerSpeedClassIndex;
    
    
    int                                         mFormationMode;
    
    bool                                        mTracerEnabled;
    int                                         mTracerMode;
    
    
    bool                                        mGridEnabled;
    bool                                        mMarkersDisplay;
    
    int                                         mGridType;
    
    int                                         mGridRectWidth;
    int                                         mGridRectHeight;
    int                                         mGridRectSpacing;
    
    int                                         mGridCircleRingSpacing;
    int                                         mGridCircleRingCount;
    int                                         mGridCircleRadialCount;
    
    int                                         mGridNGON1Sides;
    int                                         mGridNGON1RingSpacing;
    int                                         mGridNGON1RingCount;
    int                                         mGridNGON1PointSpacing;
    int                                         mGridNGON1StartRotation;
    
    FPointList                                  mGridList;
    
    void                                        *mSelectedTouch;
    
    float                                       mSelectNodeStartX;
    float                                       mSelectNodeStartY;
    
    
    float                                       mSelectTouchStartX;
    float                                       mSelectTouchStartY;
    
    void                                        Close();
    void                                        Clear();
    
    
    void                                        RefreshTracerSpeed();
    void                                        RefreshRotationSpeed();
    void                                        Refresh();
    
    void                                        Save();
    void                                        Load();
    void                                        Print();
    void                                        PickDefaultModes();
    
    void                                        BuildGrid();
    
    void                                        BuildRectGrid();
    void                                        BuildCircleGrid();
    void                                        BuildStarGrid();
    void                                        BuildNGON1Grid();
    void                                        BuildNGON2Grid();
    
    
    void                                        SetUp(LevelFormationBlueprint *pFormation);
    LevelFormationBlueprint                     mFormation;
    
    void                                        DeleteNode();
    void                                        DeleteTracer();
    
    
    void                                        SpawnSelect(int pIndex);
    int                                         SpawnIndex();
    LevelFormationNodeBlueprint                 *SpawnGet();
    //int                                         mSelectedSpawnIndex; // Not on tracer...
    //int                                         mSelectedTracerSpawnIndex; // Not on tracer...
    void                                        SpawnPickBalloon();
    void                                        SpawnPickBrickHead();
    
    
    LevelFormationTracerBlueprint               *TracerGet();
    
    
    void                                        GridSnap(float *pX, float *pY);
    
    float                                       mGameAreaTop;
    float                                       mGameAreaRight;
    float                                       mGameAreaBottom;
    float                                       mGameAreaLeft;
    
    float                                       mCenterX;
    float                                       mCenterY;
    
    LevelFormation                              mEditorFormation;
    
    void                                        SaveGridState();
    void                                        LoadGridState();
    int                                         mSaveGridTimer;
    
    
    
    FString                                     GetShortNameForGameObjectType(int pGameObjectType);
    FString                                     GetPathSpeedName(int pSpeedClass);
    FString                                     GetObjectListName(FIntList *pList);
    FString                                     GenerateTracerName(LevelFormationTracerBlueprint *pTracer);
    
    FString                                     GenerateGridName();
    FString                                     GenerateNodesName();
    
    
    FString                                     GenerateName();
    
    
};

extern GameFormationEditor *gFormationEditor;

#endif /* GameFormationEditor_hpp */
