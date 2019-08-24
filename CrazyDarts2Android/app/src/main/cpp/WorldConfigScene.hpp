//
//  WorldConfigScene.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/9/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef WorldConfigScene_hpp
#define WorldConfigScene_hpp

#include "FCanvas.hpp"
#include "PhongLightMenu.hpp"
#include "SimpleSpotLightMenu.hpp"
#include "DiffuseLightMenu.hpp"
#include "CameraMenu.hpp"
#include "FloatingCamera.hpp"
#include "FModelDataPacked.hpp"
#include "FUniforms.hpp"
#include "PhongConfiguration.hpp"
#include "DiffuseConfiguration.hpp"
#include "SpotLightSimpleConfiguration.hpp"


class WorldConfigScene : public FCanvas {
public:
    WorldConfigScene();
    virtual ~WorldConfigScene();
    
    virtual void                                Layout() override;
    virtual void                                Update() override;
    virtual void                                Draw() override;
    void                                        Draw3D();
    
    virtual void                                TouchDown(float pX, float pY, void *pData) override;
    virtual void                                TouchMove(float pX, float pY, void *pData) override;
    virtual void                                TouchUp(float pX, float pY, void *pData) override;
    virtual void                                TouchFlush() override;
    
    virtual void                                KeyDown(int pKey) override;
    virtual void                                KeyUp(int pKey) override;
    
    virtual void                                Notify(void *pSender, const char *pNotification) override;
    
    PhongConfiguration                          mPhong;
    SpotLightSimpleConfiguration                mSpotlight;
    DiffuseConfiguration                        mDiffuse;
    
    FloatingCamera                              mCamera;
    
    float                                       mCenterX;
    float                                       mCenterY;
    
    float                                       mDummyRot1;
    float                                       mDummyRot2;
    
    float                                       mDummyObjectX;
    float                                       mDummyObjectY;
    float                                       mDummyObjectZ;
    
    bool                                        mDisableLight;
    
    PhongLightMenu                              *mPhongLightMenu;
    DiffuseLightMenu                            *mDiffuseLightMenu;
    SimpleSpotLightMenu                         *mSpotlightMenu;
    
    
    
    CameraMenu                                  *mCameraMenu;
    
    int                                         mType;
    
    
    
    float                                       mEllipseX;
    float                                       mEllipseY;
    
    float                                       mEllipseAxisH;
    float                                       mEllipseAxisV;
    float                                       mEllipseRotation;
    
};

extern WorldConfigScene *gWorldScene;

#endif /* WorldConfigScene_hpp */
