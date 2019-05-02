//
//  EditorMenuFormationPicker.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/30/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef EditorMenuFormationPicker_hpp
#define EditorMenuFormationPicker_hpp

#include "ToolMenu.hpp"
#include "EditorMenuFormationPickerCell.hpp"
#include "FGestureCanvas.hpp"
#include "ToolMenu.hpp"
#include "FDrawQuad.hpp"
#include "ToolMenuSection.hpp"


//gNotify.Register(this, aFormationPicker, "formation_selected");
//gNotify.Register(this, aFormationPicker, "formation_canceled");



class GameEditor;
class EditorMenuFormationPickerCell;
class EditorMenuFormationPickerScrollContent : public FGestureCanvas {
public:
    
    EditorMenuFormationPickerScrollContent();
    virtual ~EditorMenuFormationPickerScrollContent();
    
    virtual void                                Layout();
    
    virtual void                                Update();
    virtual void                                Draw();
    
    virtual void                                TouchDown(float pX, float pY, void *pData);
    
    void                                        AddCell(EditorMenuFormationPickerCell *pCell);
    
    void                                        ClearAll();
    
    virtual void                                PanBegin(float pX, float pY);
    virtual void                                Pan(float pX, float pY);
    virtual void                                PanEnd(float pX, float pY, float pSpeedX, float pSpeedY);
    
    void                                        SetUp();
    
    FList                                       mCellList;
    EditorMenuFormationPickerCell               ***mCellGrid;
    
    int                                         mScreenGridWidth;
    int                                         mMaxRows;
    
    int                                         mColCount;
    int                                         mRowCount;
    
    float                                       mScrollSpeedX;
    float                                       mScrollSpeedY;
    float                                       mScrollFlingSpeed;
    
    float                                       mScrollOffsetX;
    float                                       mScrollOffsetY;
    
    int                                         mGridOffsetX;
    int                                         mGridOffsetY;
    
    float                                       mCellSpacingH;
    float                                       mCellSpacingV;
    
    float                                       mCellWidth;
    float                                       mCellHeight;
    
    float                                       mStartOffsetX;
    float                                       mStartOffsetY;
};

class EditorMenuFormationPicker : public ToolMenu {
public:
    EditorMenuFormationPicker();
    virtual ~EditorMenuFormationPicker();
    
    virtual void                                Layout();
    virtual void                                Update();
    virtual void                                Draw();
    
    virtual void                                Notify(void *pSender, const char *pNotification);
    
    
    ToolMenuSectionRow                          *mFilterRow1;
    UIButton                                    *mButtonApplyFilter;
    UITextBox                                   *mTextBoxFilter;
    
    ToolMenuSectionRow                          *mFilterRow2;
    UICheckBox                                  *mCheckBoxBalloonsOnly;
    UICheckBox                                  *mCheckBoxMixedOnly;
    UICheckBox                                  *mCheckBoxTracersOnly;
    UICheckBox                                  *mCheckBoxNoTracersOnly;
    
    void                                        ApplyFilter();
    
    
    EditorMenuFormationPickerScrollContent      *mScrollContent;
    ToolMenuSection                             *mSection;
    
    FSprite                                     *mSelectedSprite;
    FSpriteSequence                             *mSelectedSpriteSequence;
    
    void                                        AddAllFormations();
    void                                        AddFormation(LevelFormation *pFormation);
    
    FList                                       mFormationList;
    FList                                       mFormationListFiltered;
    
    
    bool                                        mDidSetUp;
};

extern LevelFormation *gSelectedFormation;

#endif /* EditorMenuFormationPicker_hpp */
