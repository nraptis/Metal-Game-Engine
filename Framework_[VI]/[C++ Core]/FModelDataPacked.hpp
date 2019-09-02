//
//  FModelDataPacked.hpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/7/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#ifndef FModelDataPacked_hpp
#define FModelDataPacked_hpp

#include "os_core_graphics.h"
#include "FModelData.h"
#include "FFile.hpp"
#include "FImage.hpp"
#include "FSprite.hpp"
#include "FBuffer.hpp"

class FModelDataPacked {
public:
    
    FModelDataPacked();
    virtual ~FModelDataPacked();
    
    void                                Free();
    
    void                                BindBuffers();
    void                                KillBuffers();
    
    //void                                SetSprite(FSprite *pSprite, bool pFixUVW = true);
    //void                                SetTexture(FTexture *pTexture);
    //FTexture                            *mTexture;
    
    
    void                                FitUVW(float pStartU, float pEndU, float pStartV, float pEndV);
    
    void                                Draw();
    void                                Draw(FTexture *pTexture);
    
    void                                Save(FFile *pFile);
    void                                Save(const char *pFile);
    inline void                         Save(FString pName) { Save((const char*)pName.c()); }
    
    
    
    void                                LoadData(FFile *pFile, FSprite *pSprite);
    void                                LoadData(const char *pFile, FSprite *pSprite);
    inline void                         LoadData(FString pFile, FSprite *pSprite) { LoadData((const char*)pFile.c(), pSprite); }
    
    
    void                                LoadOBJ(FFile *pFile);
    void                                LoadOBJ(const char *pFile);
    inline void                         LoadOBJ(FString pFile) { LoadOBJ((const char*)pFile.c()); }
    
    
    void                                WriteBuffers();
    
    FString                             mFileName;
    
    
    bool                                mHasXYZ;
    bool                                mHasUVW;
    bool                                mHasNormals;
    bool                                mHasTangents;
    bool                                mHasUNormals;
    
    
    
    GFX_MODEL_INDEX_TYPE                *mIndex;
    int                                 mIndexCount;
    
    float                               *mData;
    int                                 mDataCount;
    
    
    
    
    bool                                mUseUVW;
    bool                                mUseNormals;
    bool                                mUseTangents;
    bool                                mUseUNormals;
    
    
    
    int                                 mStride;
    
    FBuffer                             *mBuffer;
    
    
};


#endif /* FModelDataPacked_hpp */
