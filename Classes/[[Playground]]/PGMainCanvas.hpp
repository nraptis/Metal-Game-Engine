//
//  PGMainCanvas.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/2/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef PGMainCanvas_hpp
#define PGMainCanvas_hpp

#include "FCanvas.hpp"
#include "DragableCanvas.hpp"
#include "FDrawQuad.hpp"
#include "ToolMenu.hpp"
#include "PGMainToolbar.hpp"

class UIImagePicker;
class PGPathEditor;
class PGMainCanvas : public FCanvas {
public:
    PGMainCanvas();
    virtual ~PGMainCanvas();

    virtual void                            Update();
    virtual void                            Draw();

    virtual void                            Layout();

    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();

    virtual void                            MouseDown(float pX, float pY, int pButton);
    virtual void                            MouseMove(float pX, float pY);
    virtual void                            MouseUp(float pX, float pY, int pButton);
    virtual void                            MouseWheel(int pDirection);

    virtual void                            KeyDown(int pKey);
    virtual void                            KeyUp(int pKey);

    virtual void                            Notify(void *pSender, const char *pNotification);

    bool                                    IsModal(FCanvas *pCanvas);
    void                                    PushModal(FCanvas *pCanvas);
    void                                    PopModal(FCanvas *pCanvas);
    void                                    PopModal();
    void                                    RefreshModalStack();

    FList                                   mModalList;
    FList                                   mModalUnderlayList;


    void                                    SetBackgroundDark();
    void                                    SetBackgroundGray();
    void                                    SetBackgroundLight();
    
    PGMainToolbar                           *mMainToolbar;

    PGPathEditor                            *ShowPathEditor(FCanvas *pObserver);
    PGPathEditor                            *mPathEditor;

    UIImagePicker                           *ShowImagePicker(FCanvas *pObserver);
    UIImagePicker                           *mImagePicker;

    FDrawQuad                               mBackQuad;
};

extern PGMainCanvas *gTool;

#endif

