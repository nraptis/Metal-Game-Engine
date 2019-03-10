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
#include "FSprite.h"

class FModelDataPacked {
public:
    
    FModelDataPacked();
    virtual ~FModelDataPacked();
    
    void                        Free();
    
    void                        BindBuffers();
    void                        KillBuffers();
    
    void                        SetSprite(FSprite *pSprite, bool pFixUVW = true);
    void                        SetTexture(FTexture *pTexture);
    FTexture                    *mTexture;
    
    void                        FitUVW(float pStartU, float pEndU, float pStartV, float pEndV);
    
    void                        Load(const char *pFile);
    inline void                 Load(char *pFile){Load((const char *)pFile);}
    inline void                 Load(FString pFile){Load((const char *)(pFile.c()));}
    
    void                        Draw();
    void                        Draw(FTexture *pTexture);
    
    void                        Save(FFile *pFile);
    void                        Save(const char *pFile);
    
    void                        LoadData(FFile *pFile);
    void                        LoadData(const char *pFile);
    
    void                        LoadOBJ(FFile *pFile);
    void                        LoadOBJ(const char *pFile);
    
    FString                     mFileName;
    
    GFX_MODEL_INDEX_TYPE        *mIndex;
    int                         mIndexCount;
    
    float                       *mData;
    int                         mDataCount;
    
    bool                        mUseUVW;
    bool                        mUseNormals;
    bool                        mUseTangents;
    bool                        mUseUNormals;
    
    bool                        mHasXYZ;
    bool                        mHasUVW;
    bool                        mHasNormals;
    bool                        mHasTangents;
    bool                        mHasUNormals;
    
    int                         mStride;
    
    int                         mBufferVertex;
    int                         mBufferVertexOffset;
    
    int                         mBufferIndex;
    int                         mBufferIndexOffset;
    
};


#endif /* FModelDataPacked_hpp */
