#include "core_includes.h"
#include "os_core_graphics.h"
#include "core_includes.h"
#include "FApp.hpp"
#include "PlatformGraphicsInterface.hpp"
#include "RootViewController.h"
#include "FFloatBufferCache.hpp"
#include "FIndexBufferCache.hpp"
#include "FFileTable.hpp"
#include "OpenGLViewController.h"
#include "ShaderProgram.hpp"

#if defined(WIN_32_ENV) || defined(MAC_ENVIRONMENT)
//

//
#endif

#ifndef glOrthof
#define glOrthof glOrtho
#endif

//
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE GL_CLAMP
//
#endif


static int                                  cArrayBufferDataOffset = -1;
static int                                  cArrayBufferPositionsOffset = -1;
static int                                  cArrayBufferTextureCoordsOffset = -1;
static int                                  cArrayBufferNormalsOffset = -1;
static int                                  cArrayBufferTangentsOffset = -1;

static int                                  gGraphicsThread = -1;

static int                                  cCurrentRenderPass = -1;

static int                                  cBufferIndexUniforms = 2;
static int                                  cBufferIndexPositions = 0;
static int                                  cBufferIndexTextureCoords = 1;
static int                                  cBufferIndexNormals = -1;
static int                                  cBufferIndexUNormals = -1;
static int                                  cBufferIndexTangents = -1;
static int                                  cBufferIndexData = 0;
static int                                  cBufferIndexTextures = 0;

static float                                cClipRectBase[4];
static bool                                 cClipEnabled = false;


ShaderProgram                               *cShaderProgram = NULL;

FMatrix                                     cMatrixProjection;
FMatrix                                     cMatrixModelView;

FMatrix                                     cMatrixOrtho;
FTextureRect                                cTileRect;

//When we create buffers, we add them to this thing...
//VideoBuffer

FUniforms                                   cUniform;
FFloatBufferCacheByteAligned256             cVertexCache;
FIndexBufferCache                           cIndexCache;

FIntMap                                     cTextureBindMap;
int                                         cTextureBindCreateIndex = 0;
NSMutableSet                                *cTextureSet = [[NSMutableSet alloc] init];
//
//
FIntMap                                     cBufferBindMap;
int                                         cBufferBindCreateIndex = 0;
NSMutableSet                                *cBufferSet = [[NSMutableSet alloc] init];

static FColor                               cColor;
static float                                cRectBuffer[12];

volatile static bool                        cGraphicsThreadLocked = false;

Graphics::Graphics() {
    
}

Graphics::~Graphics()
{
    
}

void Graphics::Flush() {
    
}

void Graphics::Initialize() {
    
}

void Graphics::SetDeviceSize(float pWidth, float pHeight) {
    FMatrix aOrtho = FMatrixCreateOrtho(0.0f, pWidth, pHeight, 0.0f, -2048.0f, 2048.0f);
    cMatrixOrtho.Set(aOrtho);
    Graphics::ViewportSet(0.0f, 0.0f, pWidth, pHeight);
    Graphics::ClipSetAppFrame(0.0f, 0.0f, pWidth, pHeight);
    cTileRect.SetRect(0.0f, 0.0f, pWidth, pHeight);
}

void Graphics::PreRender() {
    cVertexCache.Reset();
    cIndexCache.Reset();
    cCurrentRenderPass = -1;
    cShaderProgram = NULL;
    
    cArrayBufferDataOffset = -999;
    cArrayBufferPositionsOffset = -999;
    cArrayBufferTextureCoordsOffset = -999;
    cArrayBufferNormalsOffset = -999;
    cArrayBufferTangentsOffset = -999;
}

void Graphics::PostRender() {
    cCurrentRenderPass = -1;
}

bool Graphics::ThreadIsLocked() {
    return cGraphicsThreadLocked;
}

void Graphics::ThreadLock() {
    if (os_thread_lock_exists(gGraphicsThread) == false) {
        gGraphicsThread = os_create_thread_lock();
    }
    
    while (cGraphicsThreadLocked) {
        printf("GFX Sleeping...\n");
        usleep(256);
    }
    
    cGraphicsThreadLocked = true;
    os_lock_graphics_thread(gGraphicsThread);
    if (gGraphicsInterface) {
        gGraphicsInterface->SetContext();
    }
}

void Graphics::ThreadUnlock() {
    os_unlock_graphics_thread(gGraphicsThread);
    cGraphicsThreadLocked = false;
}

void Graphics::DrawQuad(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4) {
    cRectBuffer[0] = pX1;
    cRectBuffer[1] = pY1;
    cRectBuffer[2] = pX2;
    cRectBuffer[3] = pY2;
    cRectBuffer[4] = pX3;
    cRectBuffer[5] = pY3;
    cRectBuffer[6] = pX4;
    cRectBuffer[7] = pY4;
    
    cVertexCache.Get(sizeof(float) * 8);
    if (cVertexCache.mResult.mSuccess) {
        int aPositionsBufferIndex = cVertexCache.mResult.mBufferIndex;
        int aPositionsBufferOffset = cVertexCache.mResult.mBufferOffset;
        
        BufferArrayWrite(aPositionsBufferIndex, cRectBuffer, aPositionsBufferOffset, sizeof(float) * 8);
        ArrayBufferPositions(aPositionsBufferIndex, aPositionsBufferOffset);
    }
    //
    //
    //
    UniformBind();
    DrawTriangleStrips(4);
    //
    //
    //
}

void Graphics::DrawQuad(float x1, float y1, float z1, float x2, float y2, float z2,
                        float x3, float y3, float z3, float x4, float y4, float z4) {
    cRectBuffer[0]=x1;
    cRectBuffer[1]=y1;
    cRectBuffer[2]=z1;
    
    cRectBuffer[3]=x2;
    cRectBuffer[4]=y2;
    cRectBuffer[5]=z2;
    
    cRectBuffer[6]=x3;
    cRectBuffer[7]=y3;
    cRectBuffer[8]=z3;
    
    cRectBuffer[9]=x4;
    cRectBuffer[10]=y4;
    cRectBuffer[11]=z4;
    
    cVertexCache.Get(sizeof(float) * 12);
    if (cVertexCache.mResult.mSuccess) {
        int aPositionsBufferIndex = cVertexCache.mResult.mBufferIndex;
        int aPositionsBufferOffset = cVertexCache.mResult.mBufferOffset;
        BufferArrayWrite(aPositionsBufferIndex, cRectBuffer, aPositionsBufferOffset, sizeof(float) * 12);
        ArrayBufferPositions(aPositionsBufferIndex, aPositionsBufferOffset);
    }
    
    //TODO: Bind Uni?
    //This will MESS UP menu ??
    //UniformBind();
    DrawTriangleStrips(4);
}


void Graphics::SetColor(float pRed, float pGreen, float pBlue, float pAlpha) {
    cColor.mRed = pRed;
    cColor.mGreen = pGreen;
    cColor.mBlue = pBlue;
    cColor.mAlpha = pAlpha;
}

void Graphics::SetColor(float pRed, float pGreen, float pBlue){Graphics::SetColor(pRed,pGreen,pBlue,1);}
void Graphics::SetColor(float pIntensity){Graphics::SetColor(1,1,1,pIntensity);}
void Graphics::SetColor(){Graphics::SetColor(1,1,1,1);}
void Graphics::SetColor(FColor pColor){Graphics::SetColor(pColor.mRed,pColor.mGreen,pColor.mBlue,pColor.mAlpha);}




void Graphics::SetColorHex(int pRed, int pGreen, int pBlue, int pAlpha) {
    Graphics::SetColor((float)pRed/255.0f, (float)pGreen/255.0f, (float)pBlue/255.0f, (float)pAlpha/255.0f);
}

void Graphics::SetColorHex(int pRed, int pGreen, int pBlue) {
    SetColorHex(pRed, pGreen, pBlue, 255);
}

void Graphics::SetColorHex(int pAlpha) {
    SetColorHex(255,255,255,pAlpha);
}

void Graphics::DrawTriangle2D(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3) {
    //
    cRectBuffer[0] = pX1;
    cRectBuffer[1] = pY1;
    cRectBuffer[2] = pX2;
    cRectBuffer[3] = pY2;
    cRectBuffer[4] = pX3;
    cRectBuffer[5] = pY3;
    //
    cVertexCache.Get(sizeof(float) * 6);
    if (cVertexCache.mResult.mSuccess) {
        int aPositionsBufferIndex = cVertexCache.mResult.mBufferIndex;
        int aPositionsBufferOffset = cVertexCache.mResult.mBufferOffset;
        
        BufferArrayWrite(aPositionsBufferIndex, cRectBuffer, aPositionsBufferOffset, sizeof(float) * 6);
        ArrayBufferPositions(aPositionsBufferIndex, aPositionsBufferOffset);
    }
    //
    UniformBind();
    DrawTriangles(3);
}

void Graphics::DrawRect(float pX, float pY, float pWidth, float pHeight) {
    DrawQuad(pX, pY, pX + pWidth, pY, pX, pY + pHeight, pX + pWidth, pY + pHeight);
}

void Graphics::OutlineRect(float pX, float pY, float pWidth, float pHeight, float pThickness) {
    DrawRect(pX-pThickness, pY-pThickness, pWidth + pThickness * 2, pThickness);
    DrawRect(pX-pThickness, pY+pHeight, pWidth + pThickness * 2, pThickness);
    DrawRect(pX-pThickness, pY, pThickness, pHeight);
    DrawRect(pX+pWidth, pY, pThickness, pHeight);
}

void Graphics::OutlineRectInside(float pX, float pY, float pWidth, float pHeight, float pThickness) {
    OutlineRect(pX + pThickness, pY + pThickness, pWidth - pThickness * 2, pHeight - pThickness * 2, pThickness);
}

void Graphics::OutlineRect(FRect pRect, float pThickness) {
    OutlineRect(pRect.mX, pRect.mY, pRect.mWidth, pRect.mHeight, pThickness);
}

void Graphics::OutlineRectInside(FRect pRect, float pThickness) {
    OutlineRectInside(pRect.mX, pRect.mY, pRect.mWidth, pRect.mHeight, pThickness);
}

void Graphics::SetColorSwatch(int pSwatchIndex, float pAlpha) {
    bool aSign = pSwatchIndex < 0;
    
    if (aSign) {
        pSwatchIndex = (-pSwatchIndex);
    }
    
    if (pSwatchIndex >= 8) {
        pSwatchIndex = (pSwatchIndex % 8);
    }
    
    if (aSign) {
        pSwatchIndex = (8 - pSwatchIndex);
    }
    
    if (pSwatchIndex==0) {
        Graphics::SetColor(1,0,0, pAlpha);
    } else if(pSwatchIndex == 1) {
        Graphics::SetColor(0,1,0, pAlpha);
    } else if(pSwatchIndex == 2) {
        Graphics::SetColor(0,0,1, pAlpha);
    } else if(pSwatchIndex == 3) {
        Graphics::SetColor(0.5f,1,1, pAlpha);
    } else if(pSwatchIndex == 4) {
        Graphics::SetColor(1,0.5f,1, pAlpha);
    } else if(pSwatchIndex==5) {
        Graphics::SetColor(1,1,0.5, pAlpha);
    } else if(pSwatchIndex==6) {
        Graphics::SetColor(1,0.5f,0.5, pAlpha);
    } else if(pSwatchIndex==7) {
        Graphics::SetColor(0.5f,1,0.5, pAlpha);
    } else {
        Graphics::SetColor(0.5f,0.5f,1, pAlpha);
    }
}

void Graphics::SetColorSwatch(int pSwatchIndex) {
    SetColorSwatch(pSwatchIndex, 1.0f);
}

void Graphics::DrawLine(float pX1, float pY1, float pX2, float pY2) {
    DrawLine(pX1, pY1, pX2, pY2, 1.0f);
}

void Graphics::DrawLine(float pX1, float pY1, float pX2, float pY2, float pThickness) {
    float aDirX = pX2 - pX1;
    float aDirY = pY2 - pY1;
    float aDist = sqrtf((aDirX * aDirX) + (aDirY * aDirY));

    aDirX /= aDist;
    aDirY /= aDist;

    float aHold = aDirX;
    
    aDirX=-aDirY;
    aDirY=aHold;
    aDirX*=pThickness;
    aDirY*=pThickness;

    DrawQuad(pX2-aDirX, pY2-aDirY, pX2+aDirX, pY2+aDirY, pX1-aDirX, pY1-aDirY, pX1+aDirX, pY1+aDirY);
}

void Graphics::DrawPoint(float pX, float pY, float pSize) {
    DrawRect(pX-pSize/2, pY-pSize/2, pSize, pSize);
}

void Graphics::DrawArrow(float pStartX, float pStartY, float pEndX, float pEndY, float pHeadLength, float pThickness) {
    DrawLine(pStartX, pStartY, pEndX, pEndY, pThickness);
    
    float aDiffX = pStartX - pEndX;
    float aDiffY = pStartY - pEndY;
    
    float aAngle = RADIANS_TO_DEGREES(atan2f(aDiffX, aDiffY));
    
    float aAngle1 = aAngle + 35;
    float aAngle2 = aAngle - 35;
    
    DrawLine(pEndX, pEndY, pEndX + Sin(aAngle1) * pHeadLength, pEndY + Cos(aAngle1) * pHeadLength, pThickness);
    DrawLine(pEndX, pEndY, pEndX + Sin(aAngle2) * pHeadLength, pEndY + Cos(aAngle2) * pHeadLength, pThickness);
}


void Graphics::DrawBox(float x1, float y1, float z1, float x2, float y2, float z2, float pSize, float pRotation) {
    float aDirX = x2 - x1;
    float aDirY = y2 - y1;
    float aDirZ = z2 - z1;
    
    float aLength = aDirX * aDirX + aDirY * aDirY + aDirZ * aDirZ;
    
    if (aLength < SQRT_EPSILON) {
        aDirX = 0.0f;
        aDirY = 0.0f;
        aDirZ = 1.0f;
    } else {
        aLength = (float)sqrtf(aLength);
        aDirX /= aLength;
        aDirY /= aLength;
        aDirZ /= aLength;
    }
    
    Graphics::CullFacesSetDisabled();
    
    
    
    FVec3 aReference = FVec3(aDirX, aDirY, aDirZ);
    FVec3 aAxis = FVec3(aDirX, aDirY, aDirZ);
    
    //Pick the "optimal" orthogonal...
    float aFactorX = fabsf(aReference.mX);
    float aFactorY = fabsf(aReference.mY);
    float aFactorZ = fabsf(aReference.mZ);
    
    // (1, 1, 1)
    //   Ortho (-1, 1, 1)
    
    if (aFactorX < 0.00025f) {
        
        if (aFactorY < 0.00025f) {
            
            //Z only, go straight up or left...
            aReference = FVec3(0.0f, 1.0f, 0.0f);
            
        } else {
            //Y and Z only, flip them...
            aReference = FVec3(0.0f, -aReference.mZ, aReference.mY);
        }
        
        //aReference = FVec3(1.0f, 0.0f, 0.0f);
        
        
    } else if (aFactorY < 0.00025f) {
        
        if (aFactorZ < 0.00025f) {
            //X only, go straight up or in...
            aReference = FVec3(0.0f, -1.0f, 0.0f);
        } else {
            //X and Z only, flip them...
            aReference = FVec3(-aReference.mZ, 0.0f, aReference.mX);
        }
    } else if (aFactorZ < 0.00025f) {
        //X and Y only, flip them...
        aReference = FVec3(-aReference.mY, aReference.mX, 0.0f);
    } else {
        aReference = FVec3(1.0f, 1.0f, -((aAxis.mX + aAxis.mY) / aAxis.mZ));
    }
    
    aReference.Normalize();
    
    FVec3 aPerp1 = Rotate3DNormalized(aReference, aAxis, 0.0f + pRotation);
    FVec3 aPerp2 = Rotate3DNormalized(aReference, aAxis, 90.0f + pRotation);
    FVec3 aPerp3 = Rotate3DNormalized(aReference, aAxis, 180.0f + pRotation);
    FVec3 aPerp4 = Rotate3DNormalized(aReference, aAxis, 270.0f + pRotation);
    
    static float aCornerX1[4];
    static float aCornerY1[4];
    static float aCornerZ1[4];
    
    static float aCornerX2[4];
    static float aCornerY2[4];
    static float aCornerZ2[4];
    
    float aSize = (pSize / 2.0f);
    aPerp1 *= aSize; aPerp2 *= aSize; aPerp3 *= aSize; aPerp4 *= aSize;
    
    aCornerX1[0] = x1 + aPerp1.mX; aCornerY1[0] = y1 + aPerp1.mY; aCornerZ1[0] = z1 + aPerp1.mZ;
    aCornerX1[1] = x1 + aPerp2.mX; aCornerY1[1] = y1 + aPerp2.mY; aCornerZ1[1] = z1 + aPerp2.mZ;
    aCornerX1[2] = x1 + aPerp3.mX; aCornerY1[2] = y1 + aPerp3.mY; aCornerZ1[2] = z1 + aPerp3.mZ;
    aCornerX1[3] = x1 + aPerp4.mX; aCornerY1[3] = y1 + aPerp4.mY; aCornerZ1[3] = z1 + aPerp4.mZ;
    //          //
    //          //
    // // // // //
    //          //
    //          //
    aCornerX2[0] = x2 + aPerp1.mX; aCornerY2[0] = y2 + aPerp1.mY; aCornerZ2[0] = z2 + aPerp1.mZ;
    aCornerX2[1] = x2 + aPerp2.mX; aCornerY2[1] = y2 + aPerp2.mY; aCornerZ2[1] = z2 + aPerp2.mZ;
    aCornerX2[2] = x2 + aPerp3.mX; aCornerY2[2] = y2 + aPerp3.mY; aCornerZ2[2] = z2 + aPerp3.mZ;
    aCornerX2[3] = x2 + aPerp4.mX; aCornerY2[3] = y2 + aPerp4.mY; aCornerZ2[3] = z2 + aPerp4.mZ;
    
    //TODO: Do we want this?
    UniformBind();
    
    DrawQuad(aCornerX1[0], aCornerY1[0], aCornerZ1[0], aCornerX2[0], aCornerY2[0], aCornerZ2[0],
             aCornerX1[1], aCornerY1[1], aCornerZ1[1], aCornerX2[1], aCornerY2[1], aCornerZ2[1]);
    DrawQuad(aCornerX1[1], aCornerY1[1], aCornerZ1[1], aCornerX2[1], aCornerY2[1], aCornerZ2[1],
             aCornerX1[2], aCornerY1[2], aCornerZ1[2], aCornerX2[2], aCornerY2[2], aCornerZ2[2]);
    DrawQuad(aCornerX1[2], aCornerY1[2], aCornerZ1[2], aCornerX2[2], aCornerY2[2], aCornerZ2[2],
             aCornerX1[3], aCornerY1[3], aCornerZ1[3], aCornerX2[3], aCornerY2[3], aCornerZ2[3]);
    DrawQuad(aCornerX1[3], aCornerY1[3], aCornerZ1[3], aCornerX2[3], aCornerY2[3], aCornerZ2[3],
             aCornerX1[0], aCornerY1[0], aCornerZ1[0], aCornerX2[0], aCornerY2[0], aCornerZ2[0]);
    
    //
    // Cap ends...
    //
    DrawQuad(aCornerX1[0], aCornerY1[0], aCornerZ1[0], aCornerX1[3], aCornerY1[3], aCornerZ1[3],
             aCornerX1[1], aCornerY1[1], aCornerZ1[1], aCornerX1[2], aCornerY1[2], aCornerZ1[2]);
    DrawQuad(aCornerX2[0], aCornerY2[0], aCornerZ2[0], aCornerX2[1], aCornerY2[1], aCornerZ2[1],
             aCornerX2[3], aCornerY2[3], aCornerZ2[3], aCornerX2[2], aCornerY2[2], aCornerZ2[2]);
    
}

void Graphics::DepthEnable() {
    
}

void Graphics::DepthDisable() {
    
}

void Graphics::DepthClear() {
    
}

void Graphics::Clear(float pRed, float pGreen, float pBlue, float pAlpha) {
    // ... This is handled by Metal
    glClearColor(pRed, pGreen, pBlue, pAlpha);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Graphics::Clear(float pRed, float pGreen, float pBlue) {
    Clear(pRed, pGreen, pBlue, 1.0f);
}

void Graphics::Clear() {
    Clear(0.0f, 0.0f, 0.0f, 1.0f);
}

void Graphics::TextureSetWrap() {
    
}

void Graphics::TextureSetClamp() {
    
}

void Graphics::TextureSetFilterMipMap() {
    
}

void Graphics::TextureSetFilterLinear() {
    
}

void Graphics::TextureSetFilterNearest() {
    
}

void Graphics::ArrayBufferData(int pIndex) {
    ArrayBufferData(pIndex, 0);
}

void Graphics::ArrayBufferData(int pIndex, int pOffset) {
    
}

void Graphics::ArrayBufferPositions(int pIndex) {
    ArrayBufferPositions(pIndex, 0);
}

void Graphics::ArrayBufferPositions(int pIndex, int pOffset) {
    
    if (cShaderProgram == NULL) {
        Log("ArrayBufferPositionsS Fails...\n");
        return;
    }
    
    cShaderProgram->ArrayBufferPositions(pIndex, pOffset);

    //virtual void                ArrayBufferData(int pIndex, int pSize, int pOffset);
    //virtual void                ArrayBufferPositions(int pIndex, int pSize,int pOffset);
    //virtual void                ArrayBufferTextureCoords(int pIndex, int pSize,int pOffset);
    //virtual void                ArrayBufferNormals(int pIndex, int pSize,int pOffset);
    
}

void Graphics::ArrayBufferTextureCoords(int pIndex) {
    ArrayBufferTextureCoords(pIndex, 0);
}

void Graphics::ArrayBufferTextureCoords(int pIndex, int pOffset) {
    
    if (cShaderProgram == NULL) {
        Log("ArrayBufferTextureCoordsS Fails...\n");
        return;
    }
    
    cShaderProgram->ArrayBufferTextureCoords(pIndex, pOffset);
}

void Graphics::ArrayBufferNormals(int pIndex) {
    ArrayBufferNormals(pIndex, 0);
}

void Graphics::ArrayBufferNormals(int pIndex, int pOffset) {
    
}

void Graphics::ArrayBufferTangents(int pIndex) {
    ArrayBufferTangents(pIndex, 0);
}

void Graphics::ArrayBufferTangents(int pIndex, int pOffset) {
    
}



void Graphics::ArrayWriteData(void *pData, int pCount) {
    if (pCount > 0) {
        cVertexCache.Get(pCount);
        if (cVertexCache.mResult.mSuccess) {
            int aPositionsBufferIndex = cVertexCache.mResult.mBufferIndex;
            int aPositionsBufferOffset = cVertexCache.mResult.mBufferOffset;
            
            BufferArrayWrite(aPositionsBufferIndex, pData, aPositionsBufferOffset, pCount);
            ArrayBufferPositions(aPositionsBufferIndex, aPositionsBufferOffset);
        }
    }
}

void Graphics::UniformBind() {
    cUniform.mProjection.Set(cMatrixProjection);
    cUniform.mModelView.Set(cMatrixModelView);
    cUniform.mColor = cColor;
    UniformBind(&cUniform);
}

void Graphics::UniformBind(FUniforms *pUniforms) {
    if (cShaderProgram != NULL && pUniforms != NULL) {
        cShaderProgram->BindUniform(pUniforms);
    } else {
        printf("** Illegally Trying To Bind [%x] [%x]\n", cShaderProgram, pUniforms);
    }
}

int Graphics::TextureGenerate(unsigned int *pData, int pWidth, int pHeight) {
    int aBindIndex = -1;
    glGenTextures(1, (GLuint*)(&aBindIndex));
    if (aBindIndex == -1) {
        printf("Error Binding Texture [%d x %d]\n", pWidth, pHeight);
    } else {
        TextureSetData(aBindIndex, pData, pWidth, pHeight);
    }
    return aBindIndex;
}

void Graphics::TextureDelete(int pIndex) {
    if (pIndex != -1) {
        glDeleteTextures(1, (GLuint*)(&(pIndex)));
    }
}

bool Graphics::TextureValid(FTexture *pTexture) {
    bool aResult = false;
    if (pTexture) {
        if (pTexture->IsValid()) {
            aResult = true;
        }
    }
    return aResult;
}

void Graphics::TextureSetData(int pIndex, unsigned int *pData, int pWidth, int pHeight) {
    TextureBind(pIndex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pWidth, pHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pData);
}

void Graphics::TextureBind(int pIndex) {
    glBindTexture(GL_TEXTURE_2D, pIndex);
}

void Graphics::TextureBind(FTexture *pTexture) {
    if (pTexture) {
        TextureBind(pTexture->mBindIndex);
    }
}



 
int Graphics::BufferArrayGenerate(int pLength) {
    unsigned int aBindIndex = 0;
    if (pLength > 0) {
        glGenBuffers(1, &aBindIndex);
        if (aBindIndex != 0) {
            printf("Create Buffer [%d] Sized[%d]\n", aBindIndex, pLength);
            glBindBuffer(GL_ARRAY_BUFFER, aBindIndex);
            glBufferData(GL_ARRAY_BUFFER, pLength, 0, GL_DYNAMIC_DRAW);
        } else {
            GLenum aError = glGetError();
            
            printf("Failed To Make Buffer[%d] Err[%d]\n", pLength, aError);
        }
    } else {
        printf("Creating Invalid Sized Buffer... [%d]\n", pLength);
    }
    
    
    
    return aBindIndex;
    
    
    //glBindBuffer(GL_ARRAY_BUFFER, pBufferIndex);
    //glBufferData(GL_ARRAY_BUFFER, pSize * 4, pData, GL_STATIC_DRAW);
    
    //GL_ELEMENT_ARRAY_BUFFER
    
    //
    
}

int Graphics::BufferArrayGenerate(void *pData, int pLength) {
    int aBindIndex = BufferArrayGenerate(pLength);
    if (aBindIndex != -1) {
        BufferArrayWrite(aBindIndex, pData, pLength);
    } else {
        printf("Failed To Make Buffer[%d]\n", pLength);
    }
    return aBindIndex;
}

void Graphics::BufferArrayWrite(int pIndex, void *pData, int pLength) {
    BufferArrayWrite(pIndex, pData, 0, pLength);
}

void Graphics::BufferArrayWrite(int pIndex, void *pData, int pOffset, int pLength) {
    glBindBuffer(GL_ARRAY_BUFFER, pIndex);
    glBufferSubData(GL_ARRAY_BUFFER, pOffset, pLength, pData);
    
    //glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
    
}

void Graphics::BufferArrayDelete(int pIndex) {
    if (pIndex != -1) {
        glDeleteBuffers(1, (unsigned int *)(&(pIndex)));
    }
}


int Graphics::BufferElementGenerate(int pLength) {
    unsigned int aBindIndex = -1;
    if (pLength > 0) {
        glGenBuffers(1, &aBindIndex);
        if (aBindIndex != -1) {
            printf("Create Element Buffer [%d] Sized[%d]\n", aBindIndex, pLength);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, pLength, 0, GL_DYNAMIC_DRAW);
        } else {
            printf("Failed To Make Element Buffer[%d]\n", pLength);
        }
    } else {
        printf("Creating Invalid Sized Element Buffer... [%d]\n", pLength);
    }
    
    
    
    return aBindIndex;
}

int Graphics::BufferElementGenerate(void *pData, int pLength) {
    int aBindIndex = BufferElementGenerate(pLength);
    if (aBindIndex != -1) {
        BufferElementWrite(aBindIndex, pData, pLength);
    } else {
        printf("Failed To Make Element Buffer[%d]\n", pLength);
    }
    return aBindIndex;
}

void Graphics::BufferElementWrite(int pIndex, void *pData, int pLength) {
    BufferElementWrite(pIndex, pData, 0, pLength);
}

void Graphics::BufferElementWrite(int pIndex, void *pData, int pOffset, int pLength) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pIndex);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, pOffset, pLength, pData);
}

void Graphics::BufferElementDelete(int pIndex) {
    if (pIndex != -1) {
        glDeleteBuffers(1, (unsigned int *)(&(pIndex)));
    }
}

void Graphics::BufferSetUniformsIndex(int pIndex) {
    cBufferIndexUniforms = pIndex;
}

void Graphics::BufferSetPositionsIndex(int pIndex) {
    cBufferIndexPositions = pIndex;
}

void Graphics::BufferSetTextureCoordsIndex(int pIndex) {
    cBufferIndexTextureCoords = pIndex;
}

void Graphics::BufferSetNormalsIndex(int pIndex) {
    cBufferIndexNormals = pIndex;
}

void Graphics::BufferSetTangentsIndex(int pIndex) {
    cBufferIndexTangents = pIndex;
}

void Graphics::BufferSetUNormalsIndex(int pIndex) {
    cBufferIndexUNormals = pIndex;
}

void Graphics::BufferSetDataIndex(int pIndex) {
    cBufferIndexData = pIndex;
}

void Graphics::BufferSetTexturesIndex(int pIndex) {
    cBufferIndexTextures = pIndex;
}

void Graphics::BufferSetIndicesShape() {
    Graphics::BufferSetPositionsIndex(GFX_BUFFER_INDEX_POSITIONS_SHAPE);
    Graphics::BufferSetTextureCoordsIndex(-1);
    Graphics::BufferSetNormalsIndex(-1);
    Graphics::BufferSetTangentsIndex(-1);
    Graphics::BufferSetUNormalsIndex(-1);
    Graphics::BufferSetDataIndex(-1);
    Graphics::BufferSetUniformsIndex(GFX_BUFFER_INDEX_UNIFORMS_SHAPE);
}

void Graphics::BufferSetIndicesShapeNode() {
    Graphics::BufferSetPositionsIndex(GFX_BUFFER_INDEX_DATA_SHAPE_NODE);
    Graphics::BufferSetTextureCoordsIndex(-1);
    Graphics::BufferSetNormalsIndex(-1);
    Graphics::BufferSetTangentsIndex(-1);
    Graphics::BufferSetUNormalsIndex(-1);
    Graphics::BufferSetDataIndex(-1);
    Graphics::BufferSetUniformsIndex(GFX_BUFFER_INDEX_UNIFORMS_SHAPE_NODE);
}

void Graphics::BufferSetIndicesSprite() {
    Graphics::BufferSetPositionsIndex(GFX_BUFFER_INDEX_POSITIONS_SPRITE);
    Graphics::BufferSetTextureCoordsIndex(GFX_BUFFER_INDEX_TEXTURE_COORDS_SPRITE);
    Graphics::BufferSetNormalsIndex(-1);
    Graphics::BufferSetTangentsIndex(-1);
    Graphics::BufferSetUNormalsIndex(-1);
    Graphics::BufferSetDataIndex(-1);
    Graphics::BufferSetUniformsIndex(GFX_BUFFER_INDEX_UNIFORMS_SPRITE);
}

void Graphics::BufferSetIndicesSimpleModel() {
    Graphics::BufferSetPositionsIndex(GFX_BUFFER_INDEX_POSITIONS_SIMPLE_MODEL);
    Graphics::BufferSetTextureCoordsIndex(GFX_BUFFER_INDEX_TEXTURE_COORDS_SIMPLE_MODEL);
    Graphics::BufferSetNormalsIndex(-1);
    Graphics::BufferSetTangentsIndex(-1);
    Graphics::BufferSetUNormalsIndex(-1);
    Graphics::BufferSetDataIndex(-1);
    Graphics::BufferSetUniformsIndex(GFX_BUFFER_INDEX_UNIFORMS_SIMPLE_MODEL);
}

void Graphics::BufferSetIndicesSimpleModelIndexed() {
    Graphics::BufferSetPositionsIndex(-1);
    Graphics::BufferSetTextureCoordsIndex(-1);
    Graphics::BufferSetNormalsIndex(-1);
    Graphics::BufferSetTangentsIndex(-1);
    Graphics::BufferSetUNormalsIndex(-1);
    Graphics::BufferSetDataIndex(GFX_BUFFER_INDEX_DATA_INDEXED_SIMPLE_MODEL);
    Graphics::BufferSetUniformsIndex(GFX_BUFFER_INDEX_UNIFORMS_INDEXED_SIMPLE_MODEL);
}

void Graphics::BufferSetIndicesModelIndexed() {
    Graphics::BufferSetPositionsIndex(-1);
    Graphics::BufferSetTextureCoordsIndex(-1);
    Graphics::BufferSetNormalsIndex(-1);
    Graphics::BufferSetTangentsIndex(-1);
    Graphics::BufferSetUNormalsIndex(-1);
    Graphics::BufferSetDataIndex(GFX_BUFFER_INDEX_DATA_INDEXED_MODEL);
    Graphics::BufferSetUniformsIndex(GFX_BUFFER_INDEX_UNIFORMS_INDEXED_MODEL);
}

void Graphics::ClipEnable() {
    if (cClipEnabled == false) {
        cClipEnabled = true;
        
    }
}

void Graphics::ClipDisable() {
    //if (cClipEnabled) {
    cClipEnabled = false;
    //Clip(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    
}



//static double cClipPlane[4][4] = { { 0.0f, 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f, 512.0f }, { 0.0f, -1.0f, 0.0f, 512.0f } };

void Graphics::Clip(float pX, float pY, float pWidth, float pHeight) {
    int aMaxX = gDeviceWidth * gOpenGLView.screenScale;
    int aMaxY = gDeviceHeight * gOpenGLView.screenScale;
    int aLeft = roundf(pX);
    int aTop = roundf(pY);
    int aWidth = (int)(pWidth + 0.5f);
    int aHeight = (int)(pHeight + 0.5f);
    
    aLeft *= gOpenGLView.screenScale;
    aTop *= gOpenGLView.screenScale;
    aWidth *= gOpenGLView.screenScale;
    aHeight *= gOpenGLView.screenScale;
    
    if (aLeft < 0) {
        aWidth += aLeft;
        aLeft = 0;
    }
    if (aTop < 0) {
        aHeight += aTop;
        aTop = 0;
    }
    int aRight = aLeft + aWidth;
    if (aRight > aMaxX) { aWidth -= (aRight - aMaxX); }
    int aBottom = aTop + aHeight;
    if (aBottom > aMaxY) { aHeight -= (aBottom - aMaxY); }
    if (aWidth < 0) { return; }
    if (aHeight < 0) { return; }
    
    /*
    cScissorRect.x = NSUInteger(aLeft);
    cScissorRect.y = NSUInteger(aTop);
    cScissorRect.width = NSUInteger(aWidth);
    cScissorRect.height = NSUInteger(aHeight);
    [gMetalEngine.renderCommandEncoder setScissorRect: cScissorRect];
    */
}

void Graphics::ClipSetAppFrame(float pX, float pY, float pWidth, float pHeight) {
    cClipRectBase[0] = pX;
    cClipRectBase[1] = pY;
    cClipRectBase[2] = pWidth;
    cClipRectBase[3] = pHeight;
}

void Graphics::ViewportSet(float pX, float pY, float pWidth, float pHeight) {
    glViewport(pX, pY, pWidth, pHeight);
}

void Graphics::DrawModelEfficientSetup(float *pPositions, float *pTextureCoords, float *pNormals, FTexture *pTexture) {
    
}

void Graphics::DrawModelIndexedEfficientSetup(float *pPositions, float *pTextureCoords, float *pNormals, FTexture *pTexture) {
    
}

void Graphics::DrawModelIndexed(float *pPositions, int pPositionsCount, float *pTextureCoords, int pTextureCoordsCount, float *pNormals, int pNormalsCount, GFX_MODEL_INDEX_TYPE *pIndex, int pCount, FTexture *pTexture) {
    
    if (pTexture == NULL || pTexture->mBindIndex == -1) {
        return;
    }
    
    if (pPositions != NULL && cBufferIndexPositions != -1 && pPositionsCount > 0) {
        cVertexCache.Get(sizeof(float) * pPositionsCount * 3);
        if (cVertexCache.mResult.mSuccess) {
            int aPositionsBufferIndex = cVertexCache.mResult.mBufferIndex;
            int aPositionsBufferOffset = cVertexCache.mResult.mBufferOffset;
            BufferArrayWrite(aPositionsBufferIndex, pPositions, aPositionsBufferOffset, sizeof(float) * pPositionsCount * 3);
            ArrayBufferPositions(aPositionsBufferIndex, aPositionsBufferOffset);
        }
    }
    
    if (pTextureCoords != NULL && cBufferIndexTextureCoords != -1 && pTextureCoordsCount > 0) {
        cVertexCache.Get(sizeof(float) * pTextureCoordsCount * 3);
        if (cVertexCache.mResult.mSuccess) {
            int aTextureCoordsBufferIndex = cVertexCache.mResult.mBufferIndex;
            int aTextureCoordsBufferOffset = cVertexCache.mResult.mBufferOffset;
            
            BufferArrayWrite(aTextureCoordsBufferIndex, pTextureCoords, aTextureCoordsBufferOffset, sizeof(float) * pTextureCoordsCount * 3);
            ArrayBufferTextureCoords(aTextureCoordsBufferIndex, aTextureCoordsBufferOffset);
        }
    }
    
    if (pNormals != NULL && cBufferIndexNormals != -1 && pNormalsCount > 0) {
        cVertexCache.Get(sizeof(float) * pNormalsCount * 3);
        if (cVertexCache.mResult.mSuccess) {
            int aNormalsBufferIndex = cVertexCache.mResult.mBufferIndex;
            int aNormalsBufferOffset = cVertexCache.mResult.mBufferOffset;
            BufferArrayWrite(aNormalsBufferIndex, pTextureCoords, aNormalsBufferOffset, sizeof(float) * pNormalsCount * 3);
            ArrayBufferNormals(aNormalsBufferIndex, aNormalsBufferOffset);
        }
    }
    
    /////////////////////
    //
    TextureBind(pTexture);
    UniformBind();
    //
    //DrawTriangles(pCount);
    
    
    DrawTrianglesIndexed(pIndex, pCount / 3);
}

void Graphics::DrawModelIndexed(float *pPositions, int pPositionsCount, float *pTextureCoords, int pTextureCoordsCount, float *pNormals, int pNormalsCount, GFX_MODEL_INDEX_TYPE *pIndex, FTexture *pTexture, int pStartIndex, int pEndIndex) {
    DrawModelIndexed(pPositions, pPositionsCount, pTextureCoords, pTextureCoordsCount, pNormals, pNormalsCount, pIndex + pStartIndex, (pEndIndex - pStartIndex) + 1, pTexture);
}

void Graphics::DrawModel(float *pPositions, float *pTextureCoords, float *pNormals, int pCount, FTexture *pTexture) {
    if (pTexture == NULL || pTexture->mBindIndex == -1) {
        return;
    }
    
    if (pPositions != NULL && cBufferIndexPositions != -1) {
    cVertexCache.Get(sizeof(float) * pCount * 3);
    if (cVertexCache.mResult.mSuccess) {
        int aPositionsBufferIndex = cVertexCache.mResult.mBufferIndex;
        int aPositionsBufferOffset = cVertexCache.mResult.mBufferOffset;
        BufferArrayWrite(aPositionsBufferIndex, pPositions, aPositionsBufferOffset, sizeof(float) * pCount * 3);
        ArrayBufferPositions(aPositionsBufferIndex, aPositionsBufferOffset);
    }
    }
    
    if (pTextureCoords != NULL && cBufferIndexTextureCoords != -1) {
        cVertexCache.Get(sizeof(float) * pCount * 3);
        if (cVertexCache.mResult.mSuccess) {
            int aTextureCoordsBufferIndex = cVertexCache.mResult.mBufferIndex;
            int aTextureCoordsBufferOffset = cVertexCache.mResult.mBufferOffset;
            BufferArrayWrite(aTextureCoordsBufferIndex, pTextureCoords, aTextureCoordsBufferOffset, sizeof(float) * pCount * 3);
            ArrayBufferTextureCoords(aTextureCoordsBufferIndex, aTextureCoordsBufferOffset);
        }
    }
    
    if (pNormals != NULL && cBufferIndexNormals != -1) {
        cVertexCache.Get(sizeof(float) * pCount * 3);
        if (cVertexCache.mResult.mSuccess) {
            int aNormalsBufferIndex = cVertexCache.mResult.mBufferIndex;
            int aNormalsBufferOffset = cVertexCache.mResult.mBufferOffset;
            
            BufferArrayWrite(aNormalsBufferIndex, pTextureCoords, aNormalsBufferOffset, sizeof(float) * pCount * 3);
            ArrayBufferNormals(aNormalsBufferIndex, aNormalsBufferOffset);
        }
    }
    //
    TextureBind(pTexture);
    DrawTriangles(pCount);
}

void Graphics::DrawTriangles(int pCount, float *pPositions, float *pTextureCoords, float *pNormals) {
    
}

void Graphics::DrawTriangles(int pCount) {
    glDrawArrays(GL_TRIANGLES, 0, pCount);
}

void Graphics::DrawTriangleStrips(int pCount) {
    glDrawArrays(GL_TRIANGLE_STRIP, 0, pCount);
}

void Graphics::DrawTrianglesIndexed(GFX_MODEL_INDEX_TYPE *pIndices, int pCount) {
    if (pIndices != NULL && pCount > 0) {
        cIndexCache.Get(sizeof(GFX_MODEL_INDEX_TYPE) * pCount);
        if (cIndexCache.mResult.mSuccess) {
            int aIndexBufferIndex = cIndexCache.mResult.mBufferIndex;
            int aIndexBufferOffset = cIndexCache.mResult.mBufferOffset;
            
            /*
            BufferBindingWrapper *aWrapper = (__bridge BufferBindingWrapper *)cBufferBindMap.Get(aIndexBufferIndex);
            if (aWrapper != NULL) {
                if (aWrapper.buffer) {
                    unsigned char *aAddress = (unsigned char *)aWrapper.buffer.contents;
                    aAddress = &(aAddress[aIndexBufferOffset]);
                    memcpy(aAddress, pIndices, pCount * sizeof(GFX_MODEL_INDEX_TYPE));
                    [gMetalEngine.renderCommandEncoder drawIndexedPrimitives: MTLPrimitiveTypeTriangle indexCount: pCount indexType: MTLIndexTypeUInt16 indexBuffer: aWrapper.buffer indexBufferOffset: aIndexBufferOffset];
                }
            }
            */
        }
    }
}

void Graphics::DrawTrianglesIndexedFromPackedBuffers(int pVertexBuffer, int pVertexBufferOffset,
                                                                              int pIndexBuffer , int pIndexBufferOffset,
                                                     int pCount, FTexture *pTexture) {
    
    Graphics::TextureBind(pTexture);
    
    /*
    BufferBindingWrapper *aWrapperVertex = (__bridge BufferBindingWrapper *)cBufferBindMap.Get(pVertexBuffer);
    BufferBindingWrapper *aWrapperIndex = (__bridge BufferBindingWrapper *)cBufferBindMap.Get(pIndexBuffer);
    
    if (aWrapperVertex == NULL || aWrapperIndex == NULL) {
        return;
    }
    
    if (aWrapperVertex.buffer == NULL || aWrapperIndex.buffer == NULL) {
        return;
    }
    
    //unsigned char *aAddressVertex = (unsigned char *)aWrapperVertex.buffer.contents;
    //aAddressVertex = &(aAddressVertex[pVertexBufferOffset]);
    
    //unsigned char *aAddressIndex = (unsigned char *)aWrapperIndex.buffer.contents;
    //aAddressIndex = &(aAddressIndex[pIndexBufferOffset]);
    
    [gMetalEngine.renderCommandEncoder setVertexBuffer: aWrapperVertex.buffer offset: pVertexBufferOffset atIndex: cBufferIndexData];
    [gMetalEngine.renderCommandEncoder drawIndexedPrimitives: MTLPrimitiveTypeTriangle indexCount: pCount indexType: MTLIndexTypeUInt16 indexBuffer: aWrapperIndex.buffer indexBufferOffset: pIndexBufferOffset];
     
    */
    
}



void Graphics::DrawTriangleStripsIndexed(GFX_MODEL_INDEX_TYPE *pIndices, int pCount) {
    if (pIndices != NULL && pCount > 0) {
        cIndexCache.Get(sizeof(GFX_MODEL_INDEX_TYPE) * pCount);
        if (cIndexCache.mResult.mSuccess) {
            int aIndexBufferIndex = cIndexCache.mResult.mBufferIndex;
            int aIndexBufferOffset = cIndexCache.mResult.mBufferOffset;
            
            /*
            BufferBindingWrapper *aWrapper = (__bridge BufferBindingWrapper *)cBufferBindMap.Get(aIndexBufferIndex);
            if (aWrapper != NULL) {
                if (aWrapper.buffer) {
                    unsigned char *aAddress = (unsigned char *)aWrapper.buffer.contents;
                    aAddress = &(aAddress[aIndexBufferOffset]);
                    memcpy(aAddress, pIndices, pCount * sizeof(GFX_MODEL_INDEX_TYPE));
                    [gMetalEngine.renderCommandEncoder drawIndexedPrimitives: MTLPrimitiveTypeTriangleStrip indexCount: pCount indexType: MTLIndexTypeUInt16 indexBuffer: aWrapper.buffer indexBufferOffset: aIndexBufferOffset];
                }
            }
            */
        }
    }
}

void Graphics::MatrixProjectionSet(FMatrix &pMatrix) {
    cMatrixProjection.Set(pMatrix);
}

void Graphics::MatrixModelViewSet(FMatrix &pMatrix) {
    cMatrixModelView.Set(pMatrix);
}

void Graphics::MatrixProjectionReset() {
    cMatrixProjection.Reset();
}

void Graphics::MatrixModelViewReset() {
    cMatrixModelView.Reset();
}

void Graphics::MatrixProjectionResetOrtho() {
    Graphics::MatrixProjectionSet(cMatrixOrtho);
}

FMatrix Graphics::MatrixProjectionGet() {
    FMatrix aResult;
    aResult.Set(cMatrixProjection);
    return aResult;
}

FMatrix Graphics::MatrixModelViewGet() {
    FMatrix aResult;
    aResult.Set(cMatrixModelView);
    return aResult;
}

void Graphics::CullFacesSetFront() {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
}

void Graphics::CullFacesSetBack() {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void Graphics::CullFacesSetDisabled() {
    glDisable(GL_CULL_FACE);
}

void Graphics::RenderQuad(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4, FTexture *pTexture) {
    RenderQuad(pX1, pY1, pX2, pY2, pX3, pY3, pX4, pY4, 0, 0, 0, 1, 1, 0, 1, 1, pTexture);
}

static float cRenderQuadBufferPositions[9];
static float cRenderQuadBufferUV[9];

void Graphics::RenderQuad(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4, float pU1, float pV1, float pU2, float pV2, float pU3, float pV3, float pU4, float pV4, FTexture *pTexture) {
    cRenderQuadBufferPositions[0] = pX1;
    cRenderQuadBufferPositions[1] = pY1;
    cRenderQuadBufferPositions[2] = pX2;
    cRenderQuadBufferPositions[3] = pY2;
    cRenderQuadBufferPositions[4] = pX3;
    cRenderQuadBufferPositions[5] = pY3;
    cRenderQuadBufferPositions[6] = pX4;
    cRenderQuadBufferPositions[7] = pY4;
    cRenderQuadBufferUV[0] = pU1;
    cRenderQuadBufferUV[1] = pV1;
    cRenderQuadBufferUV[2] = pU2;
    cRenderQuadBufferUV[3] = pV2;
    cRenderQuadBufferUV[4] = pU3;
    cRenderQuadBufferUV[5] = pV3;
    cRenderQuadBufferUV[6] = pU4;
    cRenderQuadBufferUV[7] = pV4;
    
    DrawSprite(cRenderQuadBufferPositions, cRenderQuadBufferUV, pTexture);
}

//void Graphics::RenderQuadPushed(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4,
//float pU1, float pV1, float pU2, float pV2, float pU3, float pV3, float pU4, //float pV4, FTexture *pTexture, float pPush)

void Graphics::RenderQuadScaled(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4, float pU1, float pV1, float pU2, float pV2, float pU3, float pV3, float pU4, float pV4, FTexture *pTexture, float pScale)
{
    float aRangeX = (pX2 - pX1);
    float aRangeY = (pY3 - pY1);
    
    float aCenterX = pX1 + aRangeX / 2.0f;
    float aCenterY = pY1 + aRangeY / 2.0f;
    
    aRangeX *= pScale;
    aRangeY *= pScale;
    
    aRangeX /= 2.0f;
    aRangeY /= 2.0f;
    
    pX1 = aCenterX - aRangeX;
    pX2 = aCenterX + aRangeX;
    
    pY1 = aCenterY - aRangeY;
    pY3 = aCenterY + aRangeY;
    
    pX3 = pX1;
    pX4 = pX2;
    pY2 = pY1;
    pY4 = pY3;
    
    cRenderQuadBufferPositions[0] = pX1;
    cRenderQuadBufferPositions[1] = pY1;
    
    cRenderQuadBufferPositions[2] = pX2;
    cRenderQuadBufferPositions[3] = pY2;
    
    cRenderQuadBufferPositions[4] = pX3;
    cRenderQuadBufferPositions[5] = pY3;
    
    cRenderQuadBufferPositions[6] = pX4;
    cRenderQuadBufferPositions[7] = pY4;
    
    cRenderQuadBufferUV[0] = pU1;
    cRenderQuadBufferUV[1] = pV1;
    
    cRenderQuadBufferUV[2] = pU2;
    cRenderQuadBufferUV[3] = pV2;
    
    cRenderQuadBufferUV[4] = pU3;
    cRenderQuadBufferUV[5] = pV3;
    
    cRenderQuadBufferUV[6] = pU4;
    cRenderQuadBufferUV[7] = pV4;
    
    DrawSprite(cRenderQuadBufferPositions, cRenderQuadBufferUV, pTexture);
}


void Graphics::RenderQuadScaled(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4, float pU1, float pV1, float pU2, float pV2, float pU3, float pV3, float pU4, float pV4, FTexture *pTexture, float pScale, float pCenterX, float pCenterY)
{
    pX1 = pCenterX - (pCenterX - pX1) * pScale;
    pX2 = pCenterX - (pX2 - pCenterX) * pScale;
    
    pY1 = pCenterY - (pCenterY - pY1) * pScale;
    pY3 = pCenterY - (pY2 - pCenterY) * pScale;
    
    pX3 = pX1;
    pX4 = pX2;
    pY2 = pY1;
    pY4 = pY3;
    
    //pX1 -= pPush;
    //pX2 += pPush;
    
    cRenderQuadBufferPositions[0] = pX1;
    cRenderQuadBufferPositions[1] = pY1;
    
    cRenderQuadBufferPositions[2] = pX2;
    cRenderQuadBufferPositions[3] = pY2;
    
    cRenderQuadBufferPositions[4] = pX3;
    cRenderQuadBufferPositions[5] = pY3;
    
    cRenderQuadBufferPositions[6] = pX4;
    cRenderQuadBufferPositions[7] = pY4;
    
    cRenderQuadBufferUV[0] = pU1;
    cRenderQuadBufferUV[1] = pV1;
    
    cRenderQuadBufferUV[2] = pU2;
    cRenderQuadBufferUV[3] = pV2;
    
    cRenderQuadBufferUV[4] = pU3;
    cRenderQuadBufferUV[5] = pV3;
    
    cRenderQuadBufferUV[6] = pU4;
    cRenderQuadBufferUV[7] = pV4;
    
    DrawSprite(cRenderQuadBufferPositions, cRenderQuadBufferUV, pTexture);
}

void Graphics::RenderTriangle(float pX1, float pY1, float pZ1, float pX2, float pY2, float pZ2, float pX3, float pY3, float pZ3) {
    cRenderQuadBufferPositions[0] = pX1;
    cRenderQuadBufferPositions[1] = pY1;
    cRenderQuadBufferPositions[2] = pZ1;
    
    cRenderQuadBufferPositions[3] = pX2;
    cRenderQuadBufferPositions[4] = pY2;
    cRenderQuadBufferPositions[5] = pZ2;
    
    cRenderQuadBufferPositions[6] = pX3;
    cRenderQuadBufferPositions[7] = pY3;
    cRenderQuadBufferPositions[8] = pZ3;
    
    
}

void Graphics::RenderTriangle(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3) {
    RenderTriangle(pX1, pY1, 0.0f, pX2, pY2, 0.0f, pX3, pY3, 0.0f);
}

void Graphics::DrawSpriteSetup(float *pPositions, float *pTextureCoords) {
    cVertexCache.Get(sizeof(float) * 8);
    if (cVertexCache.mResult.mSuccess) {
        int aPositionsBufferIndex = cVertexCache.mResult.mBufferIndex;
        int aPositionsBufferOffset = cVertexCache.mResult.mBufferOffset;
        BufferArrayWrite(aPositionsBufferIndex, pPositions, aPositionsBufferOffset, sizeof(float) * 8);
        ArrayBufferPositions(aPositionsBufferIndex, aPositionsBufferOffset);
    }
    
    cVertexCache.Get(sizeof(float) * 8);
    if (cVertexCache.mResult.mSuccess) {
        int aTextureCoordsBufferIndex = cVertexCache.mResult.mBufferIndex;
        int aTextureCoordsBufferOffset = cVertexCache.mResult.mBufferOffset;
        BufferArrayWrite(aTextureCoordsBufferIndex, pTextureCoords, aTextureCoordsBufferOffset, sizeof(float) * 8);
        ArrayBufferTextureCoords(aTextureCoordsBufferIndex, aTextureCoordsBufferOffset);
    }
}

void Graphics::DrawSprite(float *pPositions, float *pTextureCoords, FTexture *pTexture) {
    
    if (pTexture == NULL || pTexture->mBindIndex == -1) {
        return;
    }
    
    DrawSpriteSetup(pPositions, pTextureCoords);
    
    
    //
    TextureBind(pTexture);
    UniformBind();
    //
    DrawTriangleStrips(4);
}

void Graphics::DrawSprite(float pX, float pY, float pScaleX, float pScaleY, float pScaleZ, float pRotation, float *pPositions, float *pTextureCoords, FTexture *pTexture) {
    FMatrix aHold = cMatrixModelView;
    FMatrix aModelView = cMatrixModelView;
    
    if (pX != 0.0f || pY != 0.0f) {
        aModelView.Translate(pX, pY);
    }
    if (pScaleX != 1.0f || pScaleY != 1.0f || pScaleZ != 1.0f) {
        aModelView.Scale(pScaleX, pScaleY, pScaleZ);
    }
    if (pRotation != 0.0f) {
        aModelView.Rotate(pRotation);
    }
    MatrixModelViewSet(aModelView);
    
    DrawSprite(pPositions, pTextureCoords, pTexture);
    
    MatrixModelViewSet(aHold);
}

void Graphics::DrawSpriteTriangle(float pX, float pY, float pScaleX, float pScaleY, float pScaleZ, float pRotation, float *pPositions, float *pTextureCoords, FTexture *pTexture) {
    
    FMatrix aHold = cMatrixModelView;
    FMatrix aModelView = cMatrixModelView;
    aModelView.Translate(pX, pY);
    aModelView.Scale(pScaleX, pScaleY, pScaleZ);
    aModelView.Rotate(pRotation);
    MatrixModelViewSet(aModelView);
    
    
    DrawSpriteTriangle(pPositions, pTextureCoords, pTexture);
    
    MatrixModelViewSet(aHold);
}

void Graphics::DrawSpriteTriangleSetup(float *pPositions, float *pTextureCoords) {
    cVertexCache.Get(sizeof(float) * 6);
    if (cVertexCache.mResult.mSuccess) {
        int aPositionsBufferIndex = cVertexCache.mResult.mBufferIndex;
        int aPositionsBufferOffset = cVertexCache.mResult.mBufferOffset;
        BufferArrayWrite(aPositionsBufferIndex, pPositions, aPositionsBufferOffset, sizeof(float) * 6);
        ArrayBufferPositions(aPositionsBufferIndex, aPositionsBufferOffset);
    }
    //
    cVertexCache.Get(sizeof(float) * 6);
    if (cVertexCache.mResult.mSuccess) {
        int aTextureCoordsBufferIndex = cVertexCache.mResult.mBufferIndex;
        int aTextureCoordsBufferOffset = cVertexCache.mResult.mBufferOffset;
        BufferArrayWrite(aTextureCoordsBufferIndex, pTextureCoords, aTextureCoordsBufferOffset, sizeof(float) * 6);
        ArrayBufferTextureCoords(aTextureCoordsBufferIndex, aTextureCoordsBufferOffset);
    }
}

void Graphics::DrawSpriteTriangle(float *pPositions, float *pTextureCoords, FTexture *pTexture) {
    
    if (pTexture == NULL || pTexture->mBindIndex == -1) {
        return;
    }
    
    DrawSpriteTriangleSetup(pPositions, pTextureCoords);
    //
    TextureBind(pTexture);
    UniformBind();
    //
    DrawTriangleStrips(3);
}

void Graphics::DrawCurrentTile() {
    PipelineStateSetSpriteNoBlending();
    MatrixProjectionResetOrtho();
    MatrixModelViewReset();
    UniformBind();
    DrawSpriteSetup(cTileRect.mVertex, cTileRect.mTextureCoord);
    DrawTriangleStrips(4);
    
    /*
    cTileRect.SetRect(0.0f, 0.0f, gDeviceWidth2, gDeviceHeight2);
    UniformBind();
    DrawSpriteSetup(cTileRect.mVertex, cTileRect.mTextureCoord);
    DrawTriangleStrips(4);
    
    
    cTileRect.SetRect(gDeviceWidth2, 0.0f, gDeviceWidth2, gDeviceHeight2);
    UniformBind();
    DrawSpriteSetup(cTileRect.mVertex, cTileRect.mTextureCoord);
    DrawTriangleStrips(4);
    
    cTileRect.SetRect(0.0f, gDeviceHeight2, gDeviceWidth2, gDeviceHeight2);
    UniformBind();
    DrawSpriteSetup(cTileRect.mVertex, cTileRect.mTextureCoord);
    DrawTriangleStrips(4);
    
    cTileRect.SetRect(gDeviceWidth2, gDeviceHeight2, gDeviceWidth2, gDeviceHeight2);
    UniformBind();
    DrawSpriteSetup(cTileRect.mVertex, cTileRect.mTextureCoord);
    DrawTriangleStrips(4);
    */
    
}

void Graphics::Ortho2D(float pLeft, float pRight, float pBottom, float pTop) {
    //glOrthof(pLeft, pRight, pBottom, pTop, -1024.0f, 1024.0f);
    //glOrthof
    
}

void Graphics::Ortho2D() {
    //Ortho2D(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    
}



void Graphics::PipelineStateSetShape2DNoBlending() {
    if (gOpenGLEngine) {
        BlendDisable();
        gOpenGLEngine->UseProgramShape2D();
    }
}

void Graphics::PipelineStateSetShape2DAlphaBlending() {
    if (gOpenGLEngine) {
        BlendEnable();
        BlendSetAlpha();
        gOpenGLEngine->UseProgramShape2D();
    }
}

void Graphics::PipelineStateSetShape2DAdditiveBlending() {
    if (gOpenGLEngine) {
        BlendEnable();
        BlendSetAdditive();
        gOpenGLEngine->UseProgramShape2D();
    }
}

void Graphics::PipelineStateSetShape3DNoBlending() {
    if (gOpenGLEngine) {
        BlendDisable();
        gOpenGLEngine->UseProgramShape3D();
    }
}

void Graphics::PipelineStateSetShape3DAlphaBlending() {
    if (gOpenGLEngine) {
        BlendEnable();
        BlendSetAlpha();
        gOpenGLEngine->UseProgramShape3D();
    }
}

void Graphics::PipelineStateSetShape3DAdditiveBlending() {
    if (gOpenGLEngine) {
        BlendEnable();
        BlendSetAdditive();
        gOpenGLEngine->UseProgramShape3D();
    }
}

void Graphics::PipelineStateSetSpriteNoBlending() {
    if (gOpenGLEngine) {
        //UseProgramShape()
        BlendDisable();
        gOpenGLEngine->UseProgramSprite();
    }
}

void Graphics::PipelineStateSetSpriteAlphaBlending() {
    if (gOpenGLEngine) {
        BlendEnable();
        BlendSetAlpha();
        gOpenGLEngine->UseProgramSprite();
    }
}

void Graphics::PipelineStateSetSpriteAdditiveBlending() {
    if (gOpenGLEngine) {
        
        BlendEnable();
        BlendSetAdditive();
        gOpenGLEngine->UseProgramSprite();
    }
}

void Graphics::PipelineStateSetSpritePremultipliedBlending() {
    if (gOpenGLEngine) {
        BlendEnable();
        BlendSetPremultiplied();
        gOpenGLEngine->UseProgramSprite();
    }
}

void Graphics::PipelineStateSetSpriteWhiteBlending() {
    if (gOpenGLEngine) {
        BlendEnable();
        BlendSetAlpha();
        gOpenGLEngine->UseProgramSpriteWhite();
    }
}


void Graphics::PipelineStateSetModelIndexedLightedPhongNoBlending() {
    Graphics::BufferSetIndicesModelIndexed();
    //[gMetalPipeline pipelineStateSetModelIndexedLightedPhongNoBlending];
    
    
}

void Graphics::PipelineStateSetModelIndexedLightedPhongAlphaBlending() {
    Graphics::BufferSetIndicesModelIndexed();
    //[gMetalPipeline pipelineStateSetModelIndexedLightedPhongAlphaBlending];
    
    
}

void Graphics::PipelineStateSetModelIndexedLightedAmbientDiffuseNoBlending() {
    Graphics::BufferSetIndicesModelIndexed();
    //[gMetalPipeline pipelineStateSetModelIndexedLightedAmbientDiffuseNoBlending];
    
}

void Graphics::PipelineStateSetModelIndexedLightedAmbientDiffuseAlphaBlending() {
    Graphics::BufferSetIndicesModelIndexed();
    //[gMetalPipeline pipelineStateSetModelIndexedLightedAmbientDiffuseAlphaBlending];
    
    
}

void Graphics::PipelineStateSetModelIndexedLightedAmbientNoBlending() {
    Graphics::BufferSetIndicesModelIndexed();
    //[gMetalPipeline pipelineStateSetModelIndexedLightedAmbientNoBlending];
    
}

void Graphics::PipelineStateSetModelIndexedLightedAmbientAlphaBlending() {
    Graphics::BufferSetIndicesModelIndexed();
    //[gMetalPipeline pipelineStateSetModelIndexedLightedAmbientAlphaBlending];
    
}

void Graphics::PipelineStateSetModelIndexedNoBlending() {
    Graphics::BufferSetIndicesModelIndexed();
    //[gMetalPipeline pipelineStateSetModelIndexedNoBlending];
    
}

void Graphics::PipelineStateSetModelIndexedAlphaBlending() {
    Graphics::BufferSetIndicesModelIndexed();
    //[gMetalPipeline pipelineStateSetModelIndexedAlphaBlending];
    
}

void Graphics::PipelineStateSetSimpleModelIndexedNoBlending() {
    Graphics::BufferSetIndicesSimpleModelIndexed();
    //[gMetalPipeline pipelineStateSetSimpleModelIndexedNoBlending];
    
}

void Graphics::PipelineStateSetSimpleModelIndexedAlphaBlending() {
    Graphics::BufferSetIndicesSimpleModelIndexed();
    //[gMetalPipeline pipelineStateSetSimpleModelAlphaBlending];
    
}

void Graphics::PipelineStateSetSimpleModelNoBlending() {
    Graphics::BufferSetIndicesSimpleModel();
    //[gMetalPipeline pipelineStateSetSimpleModelNoBlending];
    
}

void Graphics::PipelineStateSetSimpleModelAlphaBlending() {
    Graphics::BufferSetIndicesSimpleModel();
    //[gMetalPipeline pipelineStateSetSimpleModelAlphaBlending];
    
}





void Graphics::PipelineStateSetShapeNodeNoBlending() {
    Graphics::BufferSetIndicesShapeNode();
    
    //[gMetalPipeline pipelineStateSetShapeNodeNoBlending];
    
}

void Graphics::PipelineStateSetShapeNodeAlphaBlending() {
    Graphics::BufferSetIndicesShapeNode();
    
    //[gMetalPipeline pipelineStateSetShapeNodeAlphaBlending];
    
}

void Graphics::PipelineStateSetShapeNodeAdditiveBlending() {
    Graphics::BufferSetIndicesShapeNode();
    
    //[gMetalPipeline pipelineStateSetShapeNodeAdditiveBlending];
    
}

int Graphics::RenderPass() {
    return cCurrentRenderPass;
}

void Graphics::RenderPassBegin(int pRenderPass, bool pClearColor, bool pClearDepth) {
    cCurrentRenderPass = pRenderPass;
    //[gMetalEngine startRenderPass:pRenderPass clearingColor: pClearColor clearingDepth: pClearDepth];
    
}

void Graphics::SetShaderProgram(ShaderProgram *pShaderProgram) {
    cShaderProgram = pShaderProgram;
}

void Graphics::BlendEnable() {
    glEnable(GL_BLEND);
}

void Graphics::BlendDisable() {
    glDisable(GL_BLEND);
}

void Graphics::BlendSetAlpha() {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Graphics::BlendSetAdditive() {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
}

void Graphics::BlendSetPremultiplied() {
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
}

