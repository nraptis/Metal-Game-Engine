//
//  EditorMenuFormationPickerCell.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/2/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef EditorMenuFormationPickerCell_hpp
#define EditorMenuFormationPickerCell_hpp

#include "UIButton.hpp"
#include "LevelWaveSpawnFormation.hpp"

class EditorMenuFormationPickerCell : public UIButton {
public:
    EditorMenuFormationPickerCell(LevelWaveSpawnFormation *pFormation);
    virtual ~EditorMenuFormationPickerCell();
    virtual void                            Layout() override;
    virtual void                            Update() override;
    virtual void                            Draw() override;
    
    void                                    DrawFormationNode(LevelWaveSpawnFormationNode *pNode, float pX, float pY);
    
    
    int                                     mDisplayDelay;
    
    LevelWaveSpawnFormation                 *mFormation;
    
    bool                                    mTouchCanceled;
    float                                   mGameScale;
    FRect                                   mGameRect;
    
    float                                   mLeft;
    float                                   mRight;
    float                                   mTop;
    float                                   mBottom;
};

#endif /* EditorMenuFormationPickerCell_hpp */
