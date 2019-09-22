//
//  GameEditorGrid.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 5/5/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef GameEditorGrid_hpp
#define GameEditorGrid_hpp

#define SNAP_GRID_TYPE_RECT 0
#define SNAP_GRID_TYPE_CIRCLE 1
#define SNAP_GRID_TYPE_STAR 2
#define SNAP_GRID_TYPE_ARC 3
#define SNAP_GRID_TYPE_NGON1 4
#define SNAP_GRID_TYPE_NGON2 5
#define SNAP_GRID_TYPE_TRAP1 6
#define SNAP_GRID_TYPE_TRAP2 7


#include "FPointList.hpp"
#include "FJSON.hpp"

class GameEditorGrid {
public:
    GameEditorGrid();
    ~GameEditorGrid();
    
    void                                        Update();
    void                                        Draw();
    
    float                                       mCenterX;
    float                                       mCenterY;
    
    int                                         mOffsetX;
    int                                         mOffsetY;
    
    
    bool                                        mGridEnabled;
    
    int                                         mSaveGridTimer;
    
    int                                         mGridType;
    
    
    
    int                                         mGridRectWidth;
    int                                         mGridRectHeight;
    int                                         mGridRectSpacingH;
    int                                         mGridRectSpacingV;
    
    int                                         mGridCircleRingSpacing;
    int                                         mGridCircleRingCount;
    int                                         mGridCircleRadialCount;
    
    int                                         mGridStarInnerRadius;
    int                                         mGridStarOuterRadius;
    int                                         mGridStarArmCount;
    int                                         mGridStarStartRotation;
    int                                         mGridStarLinePointCount;
    
    int                                         mGridNGON1Sides;
    int                                         mGridNGON1RingSpacing;
    int                                         mGridNGON1RingCount;
    int                                         mGridNGON1PointSpacing;
    int                                         mGridNGON1StartRotation;
    
    int                                         mGridNGON2Sides;
    int                                         mGridNGON2Radius;
    bool                                        mGridNGON2ScanLineStagger;
    bool                                        mGridNGON2ScanLineStaggerOdd;
    int                                         mGridNGON2ScanLineOffsetY;
    int                                         mGridNGON2ScanLineSpacingV;
    int                                         mGridNGON2ScanLineSpacingH;
    int                                         mGridNGON2StartRotation;
    
    
    int                                         mGridTRAP1TopSize;
    int                                         mGridTRAP1BottomSize;
    int                                         mGridTRAP1Height;
    int                                         mGridTRAP1CountH;
    int                                         mGridTRAP1CountV;
    int                                         mGridTRAP1StartRotation;
    
    
    FPointList                                  mGridList;
    FPointList                                  mOutlineList;
    
    
    void                                        BuildGrid();
    void                                        BuildRectGrid();
    void                                        BuildCircleGrid();
    void                                        BuildStarGrid();
    void                                        BuildNGON1Grid();
    void                                        BuildNGON2Grid();
    
    void                                        BuildTRAP1Grid();
    void                                        BuildTRAP2Grid();
    
    
    void                                        BuildScanlinePoly(FPointList *pPoly, int pOffsetY, int pSpacingH, int pSpacingV, bool pStaggerH, bool pStaggerOdd);
    
    
    void                                        GridSnap(float *pX, float *pY);
    
    void                                        SaveGridState();
    void                                        LoadGridState();
    
    FJSONNode                                   *SaveCurrentGrid();
    void                                        LoadCurrentGrid(FJSONNode *pNode);
    
    
    
};


#endif /* GameEditorGrid_hpp */
