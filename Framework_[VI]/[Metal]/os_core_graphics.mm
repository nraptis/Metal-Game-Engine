#include "core_includes.h"
#include "os_core_graphics.h"
#include "core_includes.h"
#include "FApp.hpp"
#include "PlatformGraphicsInterface.hpp"
#include "RootViewController.h"
#include "FFloatBufferCache.hpp"
#include "FIndexBufferCache.hpp"

//#import "ShaderTypes.h"
#import "MetalView.h"
#import "MetalViewController.h"
#import "FFileTable.hpp"

#ifdef MAC_ENVIRONMENT
#import <Cocoa/Cocoa.h>
#else
#import <UIKit/UIKit.h>
#endif

#import "TextureBindingWrapper.h"
#import "BufferBindingWrapper.h"

#define GRAPHICS_CLIP_STACK_COUNT 256

#if defined(WIN_32_ENV) || defined(MAC_ENVIRONMENT)
//
#ifndef glOrthof
#define glOrthof glOrtho
#endif
//
#endif
//
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE GL_CLAMP
//
#endif

static int                  gGraphicsThread = -1;

//Used for "clear depth" - we have 3 depth buffers.

static int                  cCurrentRenderPass = -1;

static int                  cBufferIndexUniforms = 2;
static int                  cBufferIndexPositions = 0;
static int                  cBufferIndexTextureCoords = 1;
static int                  cBufferIndexColors = -1;
static int                  cBufferIndexNormals = -1;
static int                  cBufferIndexUNormals = -1;
static int                  cBufferIndexTangents = -1;
static int                  cBufferIndexData = 0;
static int                  cBufferIndexTextures = 0;

static float                cClipRect[4];
static float                cClipRectBase[4];
static bool                 cClipEnabled = false;

static float                cEnvironmentColor[4];

static float                cFogColor[4];
static float                cFogDensity;
static float                cFogStart;
static float                cFogEnd;

FMatrix                     cMatrixProjection;
FMatrix                     cMatrixModelView;

FMatrix                     cMatrixOrtho;
FTextureRect                cTileRect;

//static FMatrix              cProjectionMatrixStack[GRAPHICS_MATRIX_STACK_COUNT];
//static int                  cProjectionMatrixStackCount = 0;

//static FMatrix              cModelViewMatrixStack[GRAPHICS_MATRIX_STACK_COUNT];
//static int                  cModelViewMatrixStackCount = 0 ghh


FUniforms                                   cUniform;

FFloatBufferCacheByteAligned256             cUniformCache;
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

static float                                cDeviceScale = 1.0f;

Graphics::Graphics() {
    //cTextureBindIndex=-1;
    //MaterialSetDefault();
    //LightSetDefault();
    
}

Graphics::~Graphics()
{
    
}

void Graphics::Flush() {
    
}

void Graphics::Initialize() {
    
}

// When we get a new content, we SET UP.
void Graphics::SetUp() {
    
}

void Graphics::TearDown() {
    
}

void Graphics::SetDeviceScale(float pScale) {
    cDeviceScale = pScale;
}

void Graphics::SetDeviceSize(float pWidth, float pHeight) {
 
    FMatrix aOrtho = FMatrixCreateOrtho(0.0f, pWidth, pHeight, 0.0f, -2048.0f, 2048.0f);
    cMatrixOrtho.Set(aOrtho);
    
    //Graphics::ViewportSet(0.0f, 0.0f, pWidth, pHeight);
    Graphics::ClipSetAppFrame(0.0f, 0.0f, pWidth, pHeight);
    
    cTileRect.SetRect(0.0f, 0.0f, pWidth, pHeight);
    
}

void Graphics::PreRender() {
    cUniformCache.Reset();
    cVertexCache.Reset();
    cIndexCache.Reset();
    cCurrentRenderPass = -1;
}

void Graphics::PostRender() {

    cCurrentRenderPass = -1;
    
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
        FBuffer *aPositionsBuffer = cVertexCache.mResult.mBuffer;
        int aPositionsBufferOffset = cVertexCache.mResult.mBufferOffset;
        BufferArrayWrite(aPositionsBuffer, cRectBuffer, aPositionsBufferOffset, sizeof(float) * 8);
        ArrayBufferPositions(aPositionsBuffer, aPositionsBufferOffset);
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
        FBuffer *aPositionsBuffer = cVertexCache.mResult.mBuffer;
        int aPositionsBufferOffset = cVertexCache.mResult.mBufferOffset;
        BufferArrayWrite(aPositionsBuffer, cRectBuffer, aPositionsBufferOffset, sizeof(float) * 12);
        ArrayBufferPositions(aPositionsBuffer, aPositionsBufferOffset);
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
        FBuffer *aPositionsBuffer = cVertexCache.mResult.mBuffer;
        int aPositionsBufferOffset = cVertexCache.mResult.mBufferOffset;
        BufferArrayWrite(aPositionsBuffer, cRectBuffer, aPositionsBufferOffset, sizeof(float) * 6);
        ArrayBufferPositions(aPositionsBuffer, aPositionsBufferOffset);
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
    
    if(aSign)
    {
        pSwatchIndex = (-pSwatchIndex);
    }
    
    if(pSwatchIndex >= 8)
    {
        pSwatchIndex = (pSwatchIndex % 8);
    }
    
    if(aSign)
    {
        pSwatchIndex = (8 - pSwatchIndex);
    }
    
    if(pSwatchIndex==0)
    {
        Graphics::SetColor(1,0,0, pAlpha);
    }
    else if(pSwatchIndex==1)
    {
        Graphics::SetColor(0,1,0, pAlpha);
    }
    else if(pSwatchIndex==2)
    {
        Graphics::SetColor(0,0,1, pAlpha);
    }
    else if(pSwatchIndex==3)
    {
        Graphics::SetColor(0.5f,1,1, pAlpha);
    }
    else if(pSwatchIndex==4)
    {
        Graphics::SetColor(1,0.5f,1, pAlpha);
    }
    else if(pSwatchIndex==5)
    {
        Graphics::SetColor(1,1,0.5, pAlpha);
    }
    else if(pSwatchIndex==6)
    {
        Graphics::SetColor(1,0.5f,0.5, pAlpha);
    }
    else if(pSwatchIndex==7)
    {
        Graphics::SetColor(0.5f,1,0.5, pAlpha);
    }
    else
    {
        Graphics::SetColor(0.5f,0.5f,1, pAlpha);
    }
}

void Graphics::SetColorSwatch(int pSwatchIndex)
{
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
    
    /*
    if v.x == 0:
        return Vector(1, 0, 0)
        if v.y == 0:
            return Vector(0, 1, 0)
            if v.z == 0:
                return Vector(0, 0, 1)
                
# arbitrarily set a = b = 1
# then the equation simplifies to
#     c = -(x + y)/z
                return Vector(1, 1, -1.0 * (v.x + v.y) / v.z)
    */
    
    /*
    if (aFactorX > aFactorZ && aFactorY > aFactorZ) {
        //Z is the smallest...
        aReference = FVec3(-aReference.mY, aReference.mX, 0.0f);
        
        
    } else if (aFactorX > aFactorY && aFactorZ > aFactorY) {
        //Y is the smallest...
        
        aReference = FVec3(-aReference.mZ, 0.0f, aReference.mX);
        
        
    } else {
        //X is the smallest...
        aReference = FVec3(0.0f, aReference.mZ, -aReference.mY);
    }
    */
    
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
    
    //printf("Dir[%.2f, %.2f, %.2f] Perp1[%.2f, %.2f, %.2f]\nPerp2[%.2f, %.2f, %.2f]\nPerp3[%.2f, %.2f, %.2f]\nPerp4[%.2f, %.2f, %.2f]\n", aAxis.mX, aAxis.mY, aAxis.mZ, aPerp1.mX, aPerp1.mY, aPerp1.mZ, aPerp2.mX, aPerp2.mY, aPerp2.mZ, aPerp3.mX, aPerp3.mY, aPerp3.mZ, aPerp4.mX, aPerp4.mY, aPerp4.mZ);
    
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
    [gMetalEngine.renderCommandEncoder setDepthStencilState: gMetalEngine.depthState];
}

void Graphics::DepthDisable() {
    [gMetalEngine.renderCommandEncoder setDepthStencilState: gMetalEngine.depthStateDisabled];
    //[gMetalEngine.renderCommandEncoder setDepthStencilState: NULL];
}

void Graphics::DepthClear() {
    
    
}

void Graphics::Clear(float pRed, float pGreen, float pBlue, float pAlpha) {
    // ... This is handled by Metal
}

void Graphics::Clear(float pRed, float pGreen, float pBlue) {
    Clear(pRed, pGreen, pBlue, 1.0f);
}

void Graphics::Clear() {
    Clear(0.0f, 0.0f, 0.0f, 1.0f);
}

void Graphics::TextureSetWrap() {
    [gMetalEngine.renderCommandEncoder setFragmentSamplerState: gMetalEngine.samplerStateLinearRepeat atIndex: SamplerIndexColor];
}

void Graphics::TextureSetClamp() {
    [gMetalEngine.renderCommandEncoder setFragmentSamplerState: gMetalEngine.samplerStateLinearClamp atIndex: SamplerIndexColor];
}

void Graphics::TextureSetFilterMipMap() {
    
}

void Graphics::TextureSetFilterLinear() {
    
}

void Graphics::TextureSetFilterNearest() {
    
}

void Graphics::ArrayBufferData(FBuffer *pBuffer) {
    ArrayBufferData(pBuffer, 0);
}

void Graphics::ArrayBufferData(FBuffer *pBuffer, int pOffset) {
    if (pBuffer == NULL) return;
    if (pBuffer->mBindIndex == -1) { return; }
    BufferBindingWrapper *aWrapper = (__bridge BufferBindingWrapper *)cBufferBindMap.Get(pBuffer->mBindIndex);
    if (aWrapper != NULL && aWrapper.buffer != NULL) {
        [gMetalEngine.renderCommandEncoder setVertexBuffer: aWrapper.buffer offset: pOffset atIndex: cBufferIndexData];
    }
}

void Graphics::ArrayBufferPositions(FBuffer *pBuffer) {
    ArrayBufferPositions(pBuffer, 0);
}

void Graphics::ArrayBufferPositions(FBuffer *pBuffer, int pOffset) {
    if (pBuffer == NULL) return;
    BufferBindingWrapper *aWrapper = (__bridge BufferBindingWrapper *)cBufferBindMap.Get(pBuffer->mBindIndex);
    if (aWrapper != NULL && aWrapper.buffer != NULL) {
        [gMetalEngine.renderCommandEncoder setVertexBuffer: aWrapper.buffer offset: pOffset atIndex: cBufferIndexPositions];
    }
}

void Graphics::ArrayBufferTextureCoords(FBuffer *pBuffer) {
    ArrayBufferTextureCoords(pBuffer, 0);
}

void Graphics::ArrayBufferTextureCoords(FBuffer *pBuffer, int pOffset) {
    if (pBuffer == NULL) return;
    BufferBindingWrapper *aWrapper = (__bridge BufferBindingWrapper *)cBufferBindMap.Get(pBuffer->mBindIndex);
    if (aWrapper != NULL && aWrapper.buffer != NULL) {
        [gMetalEngine.renderCommandEncoder setVertexBuffer: aWrapper.buffer offset: pOffset atIndex: cBufferIndexTextureCoords];
    }
}

void Graphics::ArrayBufferColors(FBuffer *pBuffer) {
    ArrayBufferColors(pBuffer, 0);
}

void Graphics::ArrayBufferColors(FBuffer *pBuffer, int pOffset) {
    if (pBuffer == NULL) return;
    BufferBindingWrapper *aWrapper = (__bridge BufferBindingWrapper *)cBufferBindMap.Get(pBuffer->mBindIndex);
    if (aWrapper != NULL && aWrapper.buffer != NULL) {
        [gMetalEngine.renderCommandEncoder setVertexBuffer: aWrapper.buffer offset: pOffset atIndex: cBufferIndexColors];
    }
}

void Graphics::ArrayBufferNormals(FBuffer *pBuffer) {
    ArrayBufferNormals(pBuffer, 0);
}

void Graphics::ArrayBufferNormals(FBuffer *pBuffer, int pOffset) {
    if (pBuffer == NULL) return;
    BufferBindingWrapper *aWrapper = (__bridge BufferBindingWrapper *)cBufferBindMap.Get(pBuffer->mBindIndex);
    if (aWrapper != NULL && aWrapper.buffer != NULL) {
        [gMetalEngine.renderCommandEncoder setVertexBuffer: aWrapper.buffer offset: pOffset atIndex: cBufferIndexNormals];
    }
}

void Graphics::ArrayBufferTangents(FBuffer *pBuffer) {
    ArrayBufferTangents(pBuffer, 0);
}

void Graphics::ArrayBufferTangents(FBuffer *pBuffer, int pOffset) {
    if (pBuffer == NULL) return;
    BufferBindingWrapper *aWrapper = (__bridge BufferBindingWrapper *)cBufferBindMap.Get(pBuffer->mBindIndex);
    if (aWrapper != NULL && aWrapper.buffer != NULL) {
        [gMetalEngine.renderCommandEncoder setVertexBuffer: aWrapper.buffer offset: pOffset atIndex: cBufferIndexTangents];
    }
}

FBuffer *Graphics::ArrayWriteData(void *pData, int pCount) {
    if (pCount > 0) {
        cVertexCache.Get(pCount);
        if (cVertexCache.mResult.mSuccess) {
            FBuffer *aDataBuffer = cVertexCache.mResult.mBuffer;
            int aPositionsBufferOffset = cVertexCache.mResult.mBufferOffset;
            BufferArrayWrite(aDataBuffer, pData, aPositionsBufferOffset, pCount);
            ArrayBufferPositions(aDataBuffer, aPositionsBufferOffset);
            //TODO:
            ArrayBufferData(NULL, -10000);
            
            return aDataBuffer;
            
        }
    }
    return NULL;
}




void Graphics::UniformBind() {
    cUniform.mProjection.Set(cMatrixProjection);
    cUniform.mModelView.Set(cMatrixModelView);
    cUniform.mColor = cColor;
    UniformBind(&cUniform);
}

void Graphics::UniformBind(FUniforms *pUniforms) {
    
    FBuffer *aBufferVertex = NULL;
    int aBufferOffsetVertex = -1;
    FBuffer *aBufferFragment = NULL;
    int aBufferOffsetFragment = -1;
    
    cUniformCache.Get(pUniforms->GetVertexSize());
    if (cUniformCache.mResult.mSuccess) {
        aBufferVertex = cUniformCache.mResult.mBuffer;
        aBufferOffsetVertex = cUniformCache.mResult.mBufferOffset;
    }
    
    if (aBufferVertex == NULL) { return; }
    
    cUniformCache.Get(pUniforms->GetFragmentSize());
    if (cUniformCache.mResult.mSuccess) {
        aBufferFragment = cUniformCache.mResult.mBuffer;
        aBufferOffsetFragment = cUniformCache.mResult.mBufferOffset;
    }
    
    if (aBufferFragment == NULL) { return; }
    
    BufferBindingWrapper *aWrapperVertex = (__bridge BufferBindingWrapper *)cBufferBindMap.Get(aBufferVertex->mBindIndex);
    BufferBindingWrapper *aWrapperFragment = (__bridge BufferBindingWrapper *)cBufferBindMap.Get(aBufferFragment->mBindIndex);
    
    if (aWrapperVertex != NULL && aWrapperFragment != NULL) {
        if (aWrapperVertex.buffer != NULL && aWrapperFragment != NULL) {
            pUniforms->WriteVertexToBuffer(aWrapperVertex.buffer.contents, aBufferOffsetVertex);
            [gMetalEngine.renderCommandEncoder setVertexBuffer: aWrapperVertex.buffer offset: aBufferOffsetVertex atIndex: cBufferIndexUniforms];
            
            pUniforms->WriteFragmentToBuffer(aWrapperFragment.buffer.contents, aBufferOffsetFragment);
            [gMetalEngine.renderCommandEncoder setFragmentBuffer: aWrapperFragment.buffer offset: aBufferOffsetFragment atIndex: cBufferIndexUniforms];
        }
    }
}

int Graphics::TextureGenerate(unsigned int *pData, int pWidth, int pHeight) {
    int aBindIndex =- 1;
    //MTLTextureDescriptor *aDescriptor = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat: MTLPixelFormatRGBA8Unorm width: pWidth height: pHeight mipmapped: NO];
    MTLTextureDescriptor *aDescriptor = [[MTLTextureDescriptor alloc] init];
    [aDescriptor setPixelFormat: MTLPixelFormatRGBA8Unorm];
    [aDescriptor setWidth: pWidth];
    [aDescriptor setHeight: pHeight];
    [aDescriptor setMipmapLevelCount: 1];
    //[aDescriptor setTextureType: MTLTextureType2DMultisample];
    //[aDescriptor setUsage: MTLTextureUsageRenderTarget | MTLTextureUsageShaderRead];
    //[aDescriptor setSampleCount: 4];
    
    id <MTLTexture> aMetalTexture = [gMetalEngine.device newTextureWithDescriptor: aDescriptor];
    if (aMetalTexture != NULL) {
        TextureBindingWrapper *aWrapper = [[TextureBindingWrapper alloc] init];
        [cTextureSet addObject: aWrapper];
        
        aWrapper.texture = aMetalTexture;
        
        MTLRegion aRegion = {
            { 0, 0, 0 },
            {static_cast<NSUInteger>(pWidth), static_cast<NSUInteger>(pHeight), 1}
        };
        int aBytesPerRow = pWidth * 4;
        [aMetalTexture replaceRegion: aRegion mipmapLevel: 0 withBytes: pData bytesPerRow: aBytesPerRow];
        
        cTextureBindMap.Add(cTextureBindCreateIndex, (__bridge void *)aWrapper);
        aBindIndex = cTextureBindCreateIndex;
        if (++cTextureBindCreateIndex < 0) { cTextureBindCreateIndex = 0; }
        
    } else {
        printf("Metal Texture DOESN'T Exists!\n");
        
    }
    
    return aBindIndex;
}

void Graphics::TextureDelete(int pIndex) {
    if (pIndex != -1) {
        TextureBindingWrapper *aWrapper = (__bridge TextureBindingWrapper *)cTextureBindMap.Get(pIndex);
        if (aWrapper != NULL) {
            cTextureBindMap.Remove(pIndex);
            //TODO: Do we need to clean up METAL textures more? ARC will solve this...
            aWrapper.texture = NULL;
            [cTextureSet removeObject: aWrapper];
        }
    }
}

void Graphics::TextureSetData(int pIndex, unsigned int *pData, int pWidth, int pHeight) {
    TextureBindingWrapper *aWrapper = (__bridge TextureBindingWrapper *)cTextureBindMap.Get(pIndex);
    if (aWrapper != NULL) {
        if (aWrapper.texture) {
            MTLRegion aRegion = {
                { 0, 0, 0 },
                {static_cast<NSUInteger>(pWidth), static_cast<NSUInteger>(pHeight), 1}
            };
            int aBytesPerRow = pWidth * 4;
            [aWrapper.texture replaceRegion: aRegion mipmapLevel: 0 withBytes: pData bytesPerRow: aBytesPerRow];
        }
    }
}

void Graphics::TextureBind(int pIndex) {
    TextureBindingWrapper *aWrapper = (__bridge TextureBindingWrapper *)cTextureBindMap.Get(pIndex);
    if (aWrapper != NULL) {
        if (aWrapper.texture) {
            [gMetalEngine.renderCommandEncoder setFragmentTexture: aWrapper.texture atIndex: cBufferIndexTextures];
        }
    }
}

void Graphics::TextureBind(FTexture *pTexture) {
    if (pTexture) {
        TextureBind(pTexture->mBindIndex);
    }
}

int Graphics::BufferArrayGenerate(int pLength) {
    int aBindIndex =- 1;
    id <MTLBuffer> aMetalBuffer = [gMetalEngine.device newBufferWithLength: pLength options: MTLResourceStorageModeShared];
    if (aMetalBuffer != NULL) {
        BufferBindingWrapper *aWrapper = [[BufferBindingWrapper alloc] init];
        aWrapper.buffer = aMetalBuffer;
        [cBufferSet addObject: aWrapper];
        //
        cBufferBindMap.Add(cBufferBindCreateIndex, (__bridge void *)aWrapper);
        aBindIndex = cBufferBindCreateIndex;
        if (++cBufferBindCreateIndex < 0) { cBufferBindCreateIndex = 0; }
    }
    return aBindIndex;
}

void Graphics::BufferArrayWrite(FBuffer *pBuffer, void *pData, int pLength) {
    BufferArrayWrite(pBuffer, pData, 0, pLength);
}

void Graphics::BufferArrayWrite(FBuffer *pBuffer, void *pData, int pOffset, int pLength) {
    if (pBuffer == NULL) { return; }
    BufferBindingWrapper *aWrapper = (__bridge BufferBindingWrapper *)cBufferBindMap.Get(pBuffer->mBindIndex);
    if (aWrapper != NULL) {
        if (aWrapper.buffer) {
            unsigned char *aAddress = (unsigned char *)aWrapper.buffer.contents;
            aAddress = &(aAddress[pOffset]);
            memcpy(aAddress, pData, pLength);
        }
    } else {
        printf("Missed Bind: %d\n", pBuffer->mBindIndex);
    }
}

void Graphics::BufferArrayDelete(int pIndex) {
        BufferBindingWrapper *aWrapper = (__bridge BufferBindingWrapper *)cBufferBindMap.Get(pIndex);
        if (aWrapper != NULL) {
            aWrapper.buffer = NULL;
            cBufferBindMap.Remove(pIndex);
            [cBufferSet removeObject: aWrapper];
        }
}

int Graphics::BufferElementGenerate(int pLength) {
    return BufferArrayGenerate(pLength);
}

void Graphics::BufferElementWrite(FBuffer *pBuffer, void *pData, int pLength) {
    BufferElementWrite(pBuffer, pData, 0, pLength);
}

void Graphics::BufferElementWrite(FBuffer *pBuffer, void *pData, int pOffset, int pLength) {
    BufferArrayWrite(pBuffer, pData, pOffset, pLength);
}

void Graphics::BufferElementDelete(int pIndex) {
    BufferArrayDelete(pIndex);
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

void Graphics::BufferSetColorsIndex(int pIndex) {
    cBufferIndexColors = pIndex;
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
    Graphics::BufferSetColorsIndex(-1);
    Graphics::BufferSetNormalsIndex(-1);
    Graphics::BufferSetTangentsIndex(-1);
    Graphics::BufferSetUNormalsIndex(-1);
    Graphics::BufferSetDataIndex(-1);
    Graphics::BufferSetUniformsIndex(GFX_BUFFER_INDEX_UNIFORMS_SHAPE);
}

void Graphics::BufferSetIndicesShapeNode() {
    Graphics::BufferSetPositionsIndex(GFX_BUFFER_INDEX_DATA_SHAPE_NODE);
    Graphics::BufferSetTextureCoordsIndex(-1);
    Graphics::BufferSetColorsIndex(-1);
    Graphics::BufferSetNormalsIndex(-1);
    Graphics::BufferSetTangentsIndex(-1);
    Graphics::BufferSetUNormalsIndex(-1);
    Graphics::BufferSetDataIndex(-1);
    Graphics::BufferSetUniformsIndex(GFX_BUFFER_INDEX_UNIFORMS_SHAPE_NODE);
}

void Graphics::BufferSetIndicesSprite() {
    Graphics::BufferSetPositionsIndex(GFX_BUFFER_INDEX_POSITIONS_SPRITE);
    Graphics::BufferSetTextureCoordsIndex(GFX_BUFFER_INDEX_TEXTURE_COORDS_SPRITE);
    Graphics::BufferSetColorsIndex(-1);
    Graphics::BufferSetNormalsIndex(-1);
    Graphics::BufferSetTangentsIndex(-1);
    Graphics::BufferSetUNormalsIndex(-1);
    Graphics::BufferSetDataIndex(-1);
    Graphics::BufferSetUniformsIndex(GFX_BUFFER_INDEX_UNIFORMS_SPRITE);
}

void Graphics::BufferSetIndicesSimpleModel() {
    Graphics::BufferSetPositionsIndex(GFX_BUFFER_INDEX_POSITIONS_SIMPLE_MODEL);
    Graphics::BufferSetTextureCoordsIndex(GFX_BUFFER_INDEX_TEXTURE_COORDS_SIMPLE_MODEL);
    Graphics::BufferSetColorsIndex(-1);
    Graphics::BufferSetNormalsIndex(-1);
    Graphics::BufferSetTangentsIndex(-1);
    Graphics::BufferSetUNormalsIndex(-1);
    Graphics::BufferSetDataIndex(-1);
    Graphics::BufferSetUniformsIndex(GFX_BUFFER_INDEX_UNIFORMS_SIMPLE_MODEL);
}

void Graphics::BufferSetIndicesSimpleModelIndexed() {
    Graphics::BufferSetPositionsIndex(-1);
    Graphics::BufferSetTextureCoordsIndex(-1);
    Graphics::BufferSetColorsIndex(-1);
    Graphics::BufferSetNormalsIndex(-1);
    Graphics::BufferSetTangentsIndex(-1);
    Graphics::BufferSetUNormalsIndex(-1);
    Graphics::BufferSetDataIndex(GFX_BUFFER_INDEX_DATA_INDEXED_SIMPLE_MODEL);
    Graphics::BufferSetUniformsIndex(GFX_BUFFER_INDEX_UNIFORMS_INDEXED_SIMPLE_MODEL);
}

void Graphics::BufferSetIndicesModelIndexed() {
    Graphics::BufferSetPositionsIndex(-1);
    Graphics::BufferSetTextureCoordsIndex(-1);
    Graphics::BufferSetColorsIndex(-1);
    Graphics::BufferSetNormalsIndex(-1);
    Graphics::BufferSetTangentsIndex(-1);
    Graphics::BufferSetUNormalsIndex(-1);
    Graphics::BufferSetDataIndex(GFX_BUFFER_INDEX_DATA_INDEXED_MODEL);
    Graphics::BufferSetUniformsIndex(GFX_BUFFER_INDEX_UNIFORMS_INDEXED_MODEL);
}

void Graphics::ClipEnable() {
    if (cClipEnabled == false) {
        cClipEnabled = true;
        //glEnable(GL_SCISSOR_TEST);
        //glEnable(GL_CLIP_PLANE0);
        //glEnable(GL_CLIP_PLANE1);
        //glEnable(GL_CLIP_PLANE2);
        //glEnable(GL_CLIP_PLANE3);
        
        
        //[gMetalEngine.renderCommandEncoder setScissorRect:<#(MTLScissorRect)#>]
        //MTLDepthClipModeClip = 0,
        //MTLDepthClipModeClamp = 1,
        
        //MTLDepthClipMode
        
    }
}

void Graphics::ClipDisable() {
    //if (cClipEnabled) {
    cClipEnabled = false;
    Clip(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
}



//static double cClipPlane[4][4] = { { 0.0f, 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f, 512.0f }, { 0.0f, -1.0f, 0.0f, 512.0f } };

static MTLScissorRect cScissorRect;
void Graphics::Clip(float pX, float pY, float pWidth, float pHeight) {
    int aMaxX = gDeviceWidth * gMetalEngine.screenScale;
    int aMaxY = gDeviceHeight * gMetalEngine.screenScale;
    int aLeft = roundf(pX);
    int aTop = roundf(pY);
    int aWidth = (int)(pWidth + 0.5f);
    int aHeight = (int)(pHeight + 0.5f);
    
    aLeft *= gMetalEngine.screenScale;
    aTop *= gMetalEngine.screenScale;
    aWidth *= gMetalEngine.screenScale;
    aHeight *= gMetalEngine.screenScale;
    
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
    
    cScissorRect.x = NSUInteger(aLeft);
    cScissorRect.y = NSUInteger(aTop);
    cScissorRect.width = NSUInteger(aWidth);
    cScissorRect.height = NSUInteger(aHeight);
    [gMetalEngine.renderCommandEncoder setScissorRect: cScissorRect];
}

void Graphics::ClipSetAppFrame(float pX, float pY, float pWidth, float pHeight) {
    cClipRectBase[0] = pX;
    cClipRectBase[1] = pY;
    cClipRectBase[2] = pWidth;
    cClipRectBase[3] = pHeight;
}

void Graphics::ViewportSet(float pX, float pY, float pWidth, float pHeight) {
    MTLViewport aViewPort = {
        pX, pY, pWidth, pHeight, -2048.0f, 2048.0f
    };
    [gMetalEngine.renderCommandEncoder setViewport: aViewPort];
}

void Graphics::DrawModelEfficientSetup(float *pPositions, float *pTextureCoords, float *pNormals, FTexture *pTexture) {
    
    /*
    EnableVertexArray();
    ArrayVertices(pXYZ);

    if(TextureValid(pTexture) && (pUVW != 0)){TextureEnable();EnableTextureCoordinateArray();TextureBind(pTexture);ArrayCoords(pUVW);}
    else {TextureDisable();DisableTextureCoordinateArray();}
    
    if(pNormal != 0){EnableNormalArray();ArrayNormals(pNormal);}
    else {DisableNormalArray();}
    */
}

void Graphics::DrawModelIndexedEfficientSetup(float *pPositions, float *pTextureCoords, float *pNormals, FTexture *pTexture) {
    
    /*
    EnableVertexArray();
    ArrayVertices(pXYZ);
    
    if(TextureValid(pTexture) && (pUVW != 0)){TextureEnable();EnableTextureCoordinateArray();TextureBind(pTexture);ArrayCoords(pUVW);}
    else {TextureDisable();DisableTextureCoordinateArray();}
    
    if(pNormal != 0){EnableNormalArray();ArrayNormals(pNormal);}
    else {DisableNormalArray();}
    */
}


void Graphics::DrawModelIndexed(float *pPositions, int pPositionsCount, float *pTextureCoords, int pTextureCoordsCount, float *pNormals, int pNormalsCount, GFX_MODEL_INDEX_TYPE *pIndex, int pCount, FTexture *pTexture) {
    
    if (pTexture == NULL || pTexture->mBindIndex == -1) {
        return;
    }
    
    if (pPositions != NULL && cBufferIndexPositions != -1 && pPositionsCount > 0) {
        cVertexCache.Get(sizeof(float) * pPositionsCount * 3);
        if (cVertexCache.mResult.mSuccess) {
            FBuffer *aPositionsBuffer = cVertexCache.mResult.mBuffer;
            int aPositionsBufferOffset = cVertexCache.mResult.mBufferOffset;
            BufferArrayWrite(aPositionsBuffer, pPositions, aPositionsBufferOffset, sizeof(float) * pPositionsCount * 3);
            ArrayBufferPositions(aPositionsBuffer, aPositionsBufferOffset);
        }
    }
    
    if (pTextureCoords != NULL && cBufferIndexTextureCoords != -1 && pTextureCoordsCount > 0) {
        cVertexCache.Get(sizeof(float) * pTextureCoordsCount * 3);
        if (cVertexCache.mResult.mSuccess) {
            FBuffer *aTextureCoordsBuffer = cVertexCache.mResult.mBuffer;
            int aTextureCoordsBufferOffset = cVertexCache.mResult.mBufferOffset;
            BufferArrayWrite(aTextureCoordsBuffer, pTextureCoords, aTextureCoordsBufferOffset, sizeof(float) * pTextureCoordsCount * 3);
            ArrayBufferTextureCoords(aTextureCoordsBuffer, aTextureCoordsBufferOffset);
        }
    }
    
    if (pNormals != NULL && cBufferIndexNormals != -1 && pNormalsCount > 0) {
        cVertexCache.Get(sizeof(float) * pNormalsCount * 3);
        if (cVertexCache.mResult.mSuccess) {
            FBuffer *aNormalsBuffer = cVertexCache.mResult.mBuffer;
            int aNormalsBufferOffset = cVertexCache.mResult.mBufferOffset;
            BufferArrayWrite(aNormalsBuffer, pTextureCoords, aNormalsBufferOffset, sizeof(float) * pNormalsCount * 3);
            ArrayBufferNormals(aNormalsBuffer, aNormalsBufferOffset);
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
        FBuffer *aPositionsBuffer = cVertexCache.mResult.mBuffer;
        int aPositionsBufferOffset = cVertexCache.mResult.mBufferOffset;
        BufferArrayWrite(aPositionsBuffer, pPositions, aPositionsBufferOffset, sizeof(float) * pCount * 3);
        ArrayBufferPositions(aPositionsBuffer, aPositionsBufferOffset);
    }
    }
    
    if (pTextureCoords != NULL && cBufferIndexTextureCoords != -1) {
        cVertexCache.Get(sizeof(float) * pCount * 3);
        if (cVertexCache.mResult.mSuccess) {
            FBuffer *aTextureCoordsBuffer = cVertexCache.mResult.mBuffer;
            int aTextureCoordsBufferOffset = cVertexCache.mResult.mBufferOffset;
            BufferArrayWrite(aTextureCoordsBuffer, pTextureCoords, aTextureCoordsBufferOffset, sizeof(float) * pCount * 3);
            ArrayBufferTextureCoords(aTextureCoordsBuffer, aTextureCoordsBufferOffset);
        }
    }
    
    if (pNormals != NULL && cBufferIndexNormals != -1) {
        cVertexCache.Get(sizeof(float) * pCount * 3);
        if (cVertexCache.mResult.mSuccess) {
            FBuffer *aNormalsBuffer = cVertexCache.mResult.mBuffer;
            int aNormalsBufferOffset = cVertexCache.mResult.mBufferOffset;
            BufferArrayWrite(aNormalsBuffer, pTextureCoords, aNormalsBufferOffset, sizeof(float) * pCount * 3);
            ArrayBufferNormals(aNormalsBuffer, aNormalsBufferOffset);
        }
    }
    //
    TextureBind(pTexture);
    DrawTriangles(pCount);
}

void Graphics::DrawTriangles(int pCount, float *pPositions, float *pTextureCoords, float *pNormals) {
    
}

void Graphics::DrawTriangles(int pCount) {
    [gMetalEngine.renderCommandEncoder drawPrimitives: MTLPrimitiveTypeTriangle
                                        vertexStart: 0
                                        vertexCount: pCount];
}

void Graphics::DrawTriangleStrips(int pCount) {
    [gMetalEngine.renderCommandEncoder drawPrimitives: MTLPrimitiveTypeTriangleStrip
                                        vertexStart: 0
                                        vertexCount: pCount];
}

void Graphics::DrawTrianglesIndexed(GFX_MODEL_INDEX_TYPE *pIndices, int pCount) {
    if (pIndices != NULL && pCount > 0) {
        cIndexCache.Get(sizeof(GFX_MODEL_INDEX_TYPE) * pCount);
        if (cIndexCache.mResult.mSuccess) {
            FBuffer *aIndexBuffer= cIndexCache.mResult.mBuffer;
            int aIndexBufferOffset = cIndexCache.mResult.mBufferOffset;
            if (aIndexBuffer == NULL) { return; }
            BufferBindingWrapper *aWrapper = (__bridge BufferBindingWrapper *)cBufferBindMap.Get(aIndexBuffer->mBindIndex);
            if (aWrapper != NULL) {
                if (aWrapper.buffer) {
                    unsigned char *aAddress = (unsigned char *)aWrapper.buffer.contents;
                    aAddress = &(aAddress[aIndexBufferOffset]);
                    memcpy(aAddress, pIndices, pCount * sizeof(GFX_MODEL_INDEX_TYPE));
                    [gMetalEngine.renderCommandEncoder drawIndexedPrimitives: MTLPrimitiveTypeTriangle indexCount: pCount indexType: MTLIndexTypeUInt16 indexBuffer: aWrapper.buffer indexBufferOffset: aIndexBufferOffset];
                }
            }
        }
    }
}

/*
void Graphics::DrawTrianglesIndexedFromPackedBuffers(int pVertexBuffer, int pVertexBufferOffset,
                                                                              int pIndexBuffer , int pIndexBufferOffset,
                                                     int pCount, FTexture *pTexture) {
    
    Graphics::TextureBind(pTexture);
    
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
    
}
*/

void Graphics::DrawTrianglesIndexedWithPackedBuffers(FBuffer *pVertexBuffer, int pVertexBufferOffset, GFX_MODEL_INDEX_TYPE *pIndices, int pCount, FTexture *pTexture) {
    
    if (pVertexBuffer == NULL) { return; }
    
    //Graphics::TextureBind(pTexture);
    //Graphics::ArrayBufferData(pVertexBuffer, pVertexBufferOffset);
    //Graphics::ArrayBufferPositions(-1, 0);
    //Graphics::ArrayBufferTextureCoords(-1, sizeof(float) * 3);
    //Graphics::ArrayBufferNormals(-1, sizeof(float) * 6);
    //Graphics::DrawTrianglesIndexed(pIndices, pCount);
    
    
    Graphics::TextureBind(pTexture);
    
    BufferBindingWrapper *aWrapperVertex = (__bridge BufferBindingWrapper *)cBufferBindMap.Get(pVertexBuffer->mBindIndex);
    
    if (aWrapperVertex == NULL) {
        return;
    }
    if (aWrapperVertex.buffer == NULL) {
        return;
    }
    
    //unsigned char *aAddressVertex = (unsigned char *)aWrapperVertex.buffer.contents;
    //aAddressVertex = &(aAddressVertex[pVertexBufferOffset]);
    
    //unsigned char *aAddressIndex = (unsigned char *)aWrapperIndex.buffer.contents;
    //aAddressIndex = &(aAddressIndex[pIndexBufferOffset]);
    
    [gMetalEngine.renderCommandEncoder setVertexBuffer: aWrapperVertex.buffer offset: pVertexBufferOffset atIndex: cBufferIndexData];
    
    DrawTrianglesIndexed(pIndices, pCount);
    
    
    //[gMetalEngine.renderCommandEncoder drawIndexedPrimitives: MTLPrimitiveTypeTriangle indexCount: pCount indexType: MTLIndexTypeUInt16 indexBuffer: aWrapperIndex.buffer indexBufferOffset: pIndexBufferOffset];
    
    
    
}



void Graphics::DrawTriangleStripsIndexed(GFX_MODEL_INDEX_TYPE *pIndices, int pCount) {
    if (pIndices != NULL && pCount > 0) {
        cIndexCache.Get(sizeof(GFX_MODEL_INDEX_TYPE) * pCount);
        if (cIndexCache.mResult.mSuccess) {
            FBuffer *aIndexBuffer= cIndexCache.mResult.mBuffer;
            int aIndexBufferOffset = cIndexCache.mResult.mBufferOffset;
            if (aIndexBuffer == NULL) { return; }
            BufferBindingWrapper *aWrapper = (__bridge BufferBindingWrapper *)cBufferBindMap.Get(aIndexBuffer->mBindIndex);
            if (aWrapper != NULL) {
                if (aWrapper.buffer) {
                    unsigned char *aAddress = (unsigned char *)aWrapper.buffer.contents;
                    aAddress = &(aAddress[aIndexBufferOffset]);
                    memcpy(aAddress, pIndices, pCount * sizeof(GFX_MODEL_INDEX_TYPE));
                    [gMetalEngine.renderCommandEncoder drawIndexedPrimitives: MTLPrimitiveTypeTriangleStrip indexCount: pCount indexType: MTLIndexTypeUInt16 indexBuffer: aWrapper.buffer indexBufferOffset: aIndexBufferOffset];
                }
            }
        }
    }
}


    /*
    
    */

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

void Graphics::MatrixProjectionGet(FMatrix *pMatrix) {
    pMatrix->Set(cMatrixProjection);
}

FMatrix Graphics::MatrixModelViewGet() {
    FMatrix aResult;
    aResult.Set(cMatrixModelView);
    return aResult;
}

void Graphics::MatrixModelViewGet(FMatrix *pMatrix) {
    pMatrix->Set(cMatrixModelView);
}

void Graphics::CullFacesSetFront() {
    [gMetalEngine.renderCommandEncoder setCullMode: MTLCullModeFront];
}

void Graphics::CullFacesSetBack() {
    [gMetalEngine.renderCommandEncoder setCullMode: MTLCullModeBack];
}

void Graphics::CullFacesSetDisabled() {
    [gMetalEngine.renderCommandEncoder setCullMode: MTLCullModeNone];
}

void Graphics::RenderQuad(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4, FTexture *pTexture)
{
    //RenderQuad(pX1, pY1, pX2, pY2, pX3, pY3, pX4, pY4, 0, 0, 1, 0, 0, 1, 1, 1, pBindIndex);
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

void Graphics::RenderTriangle(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3)
{
    RenderTriangle(pX1, pY1, 0.0f, pX2, pY2, 0.0f, pX3, pY3, 0.0f);
}

void Graphics::DrawSpriteSetup(float *pPositions, float *pTextureCoords) {
    cVertexCache.Get(sizeof(float) * 8);
    if (cVertexCache.mResult.mSuccess) {
        FBuffer *aPositionsBuffer = cVertexCache.mResult.mBuffer;
        int aPositionsBufferOffset = cVertexCache.mResult.mBufferOffset;
        BufferArrayWrite(aPositionsBuffer, pPositions, aPositionsBufferOffset, sizeof(float) * 8);
        ArrayBufferPositions(aPositionsBuffer, aPositionsBufferOffset);
    }
    
    cVertexCache.Get(sizeof(float) * 8);
    if (cVertexCache.mResult.mSuccess) {
        FBuffer *aTextureCoordsBuffer = cVertexCache.mResult.mBuffer;
        int aTextureCoordsBufferOffset = cVertexCache.mResult.mBufferOffset;
        BufferArrayWrite(aTextureCoordsBuffer, pTextureCoords, aTextureCoordsBufferOffset, sizeof(float) * 8);
        ArrayBufferTextureCoords(aTextureCoordsBuffer, aTextureCoordsBufferOffset);
    }
}

void Graphics::DrawSprite(float *pPositions, float *pTextureCoords, FTexture *pTexture) {
    if (pTexture == NULL || pTexture->mBindIndex == -1) {
        return;
    }
    DrawSpriteSetup(pPositions, pTextureCoords);
    TextureBind(pTexture);
    UniformBind();
    DrawTriangleStrips(4);
}

void Graphics::DrawSprite(float pX, float pY, float pScaleX, float pScaleY, float pScaleZ, float pRotation, float *pPositions, float *pTextureCoords, FTexture *pTexture) {
    FMatrix aHold = cMatrixModelView;
    FMatrix aModelView = cMatrixModelView;
    aModelView.Translate(pX, pY);
    aModelView.Scale(pScaleX, pScaleY, pScaleZ);
    aModelView.Rotate(pRotation);
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
        FBuffer *aPositionsBuffer = cVertexCache.mResult.mBuffer;
        int aPositionsBufferOffset = cVertexCache.mResult.mBufferOffset;
        BufferArrayWrite(aPositionsBuffer, pPositions, aPositionsBufferOffset, sizeof(float) * 6);
        ArrayBufferPositions(aPositionsBuffer, aPositionsBufferOffset);
    }
    //
    cVertexCache.Get(sizeof(float) * 6);
    if (cVertexCache.mResult.mSuccess) {
        FBuffer *aTextureCoordsBuffer = cVertexCache.mResult.mBuffer;
        int aTextureCoordsBufferOffset = cVertexCache.mResult.mBufferOffset;
        BufferArrayWrite(aTextureCoordsBuffer, pTextureCoords, aTextureCoordsBufferOffset, sizeof(float) * 6);
        ArrayBufferTextureCoords(aTextureCoordsBuffer, aTextureCoordsBufferOffset);
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
    
    
    
    /*
    cVertexCache.Get(sizeof(float) * 6);
    if (cVertexCache.mResult.mSuccess) {
        FBuffer *aPositionsBuffer = cVertexCache.mResult.mBuffer;
        int aPositionsBufferOffset = cVertexCache.mResult.mBufferOffset;
        BufferWrite(aPositionsBufferIndex, pPositions, aPositionsBufferOffset, sizeof(float) * 6);
        ArrayBufferPositions(aPositionsBufferIndex);
    } else {
        printf("TRIANGLE - HARD-FAILURE on POSITION BUFFER FETCH...\n");
    }
    
    
    cVertexCache.Get(sizeof(float) * 6);
    if (cVertexCache.mResult.mSuccess) {
        FBuffer *aTextureCoordsBuffer = cVertexCache.mResult.mBuffer;
        int aTextureCoordsBufferOffset = cVertexCache.mResult.mBufferOffset;
        BufferWrite(aTextureCoordsBufferIndex, pTextureCoords, aTextureCoordsBufferOffset, sizeof(float) * 6);
        ArrayBufferTextureCoords(aTextureCoordsBufferIndex);
    } else {
        printf("TRIANGLE - HARD-FAILURE on TEX-COORD BUFFER FETCH...\n");
    }
    */
    
    /*
    //BufferSetPositionsIndex(GFX_BUFFER_INDEX_POSITIONS_SPRITE);
    int aPositionsBuffer = cSpriteCache.GetTriangle();
    BufferWrite(aPositionsBuffer, pPositions, sizeof(float) * 6);
    ArrayBufferPositions(aPositionsBuffer);
    
    //BufferSetTextureCoordsIndex(GFX_BUFFER_INDEX_TEXTURE_COORDS_SPRITE);
    int aTextureCoordsBuffer = cSpriteCache.GetTriangle();
    BufferWrite(aTextureCoordsBuffer, pTextureCoords, sizeof(float) * 6);
    ArrayBufferTextureCoords(aTextureCoordsBuffer);
    */
    
    //TextureBind(pTexture);
    //UniformBind();
    
    //DrawTriangles(3);
    
}

void Graphics::DrawCurrentTile() {
    PipelineStateSetSpriteNoBlending();
    MatrixProjectionResetOrtho();
    MatrixModelViewReset();
    UniformBind();
    DrawSpriteSetup(cTileRect.mPositions, cTileRect.mTextureCoords);
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

void Graphics::DrawCube() {
    static float aXYZ[72]={-0.5,0.5,-0.5,-0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,-0.5,-0.5,-0.5,-0.5,0.5,-0.5,-0.5,0.5,-0.5,0.5,-0.5,-0.5,0.5,-0.5,0.5,-0.5,0.5,0.5,-0.5,0.5,-0.5,-0.5,-0.5,-0.5,-0.5,0.5,0.5,-0.5,0.5,0.5,0.5,0.5,-0.5,0.5,0.5,-0.5,-0.5,0.5,0.5,0.5,-0.5,0.5,0.5,-0.5,-0.5,0.5,0.5,-0.5,0.5,-0.5,0.5,0.5,-0.5,0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,0.5};
    static float aUVW[72]={1.00,1.00,0.00,1.00,0.00,0.00,0.00,0.00,0.00,0.00,1.00,0.00,0.00,1.00,0.00,1.00,1.00,0.00,1.00,0.00,0.00,0.00,0.00,0.00,0.00,1.00,0.00,1.00,1.00,0.00,1.00,0.00,0.00,0.00,0.00,0.00,0.00,1.00,0.00,1.00,1.00,0.00,1.00,0.00,0.00,0.00,0.00,0.00,0.00,1.00,0.00,1.00,1.00,0.00,1.00,0.00,0.00,0.00,0.00,0.00,0.00,1.00,0.00,1.00,1.00,0.00,1.00,0.00,0.00,0.00,0.00,0.00};
    static float aNormal[72]={0.000000,1.000000,0.000000,0.000000,1.000000,0.000000,0.000000,1.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.000000,-0.000000,0.000000,-1.000000,-0.000000,0.000000,-1.000000,-0.000000,0.000000,-1.000000,-0.000000,0.000000,0.000000,-1.000000,0.000000,0.000000,-1.000000,0.000000,0.000000,-1.000000,0.000000,0.000000,-1.000000,1.000000,0.000000,0.000000,1.000000,0.000000,0.000000,1.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,-0.000000,1.000000,0.000000,-0.000000,1.000000,0.000000,-0.000000,1.000000,0.000000,-0.000000,1.000000,-1.000000,0.000000,0.000000,-1.000000,0.000000,0.000000,-1.000000,0.000000,0.000000,-1.000000,0.000000,0.000000};
    
    static GFX_MODEL_INDEX_TYPE aIndex[36]={0,1,2,2,3,0,4,5,6,6,7,4,8,9,10,10,11,8,12,13,14,14,15,12,16,17,18,18,19,16,20,21,22,22,23,20};
    
    //ArrayVertices(aXYZ);
    //ArrayCoords(aUVW);
    //ArrayNormals(aNormal);
    //DrawTriangles(aIndex, 36);
    
}

void Graphics::Ortho2D(float pLeft, float pRight, float pBottom, float pTop) {
    
}

void Graphics::Ortho2D() {
    
}


void Graphics::PipelineStateSetShape2DNoBlending() {
    Graphics::BufferSetIndicesShape();
    [gMetalPipeline pipelineStateSetShape2DNoBlending];
}

void Graphics::PipelineStateSetShape2DAlphaBlending() {
    Graphics::BufferSetIndicesShape();
    [gMetalPipeline pipelineStateSetShape2DAlphaBlending];
}

void Graphics::PipelineStateSetShape2DAdditiveBlending() {
    Graphics::BufferSetIndicesShape();
    [gMetalPipeline pipelineStateSetShape2DAdditiveBlending];
}



void Graphics::PipelineStateSetShape3DNoBlending() {
    Graphics::BufferSetIndicesShape();
    [gMetalPipeline pipelineStateSetShape3DNoBlending];
}

void Graphics::PipelineStateSetShape3DAlphaBlending() {
    Graphics::BufferSetIndicesShape();
    [gMetalPipeline pipelineStateSetShape3DAlphaBlending];
}

void Graphics::PipelineStateSetShape3DAdditiveBlending() {
    Graphics::BufferSetIndicesShape();
    [gMetalPipeline pipelineStateSetShape3DAdditiveBlending];
}


void Graphics::PipelineStateSetModelIndexedLightedPhongNoBlending() {
    Graphics::BufferSetIndicesModelIndexed();
    [gMetalPipeline pipelineStateSetModelIndexedLightedPhongNoBlending];
}

void Graphics::PipelineStateSetModelIndexedLightedPhongAlphaBlending() {
    Graphics::BufferSetIndicesModelIndexed();
    [gMetalPipeline pipelineStateSetModelIndexedLightedPhongAlphaBlending];
}

void Graphics::PipelineStateSetModelIndexedLightedAmbientDiffuseNoBlending() {
    Graphics::BufferSetIndicesModelIndexed();
    [gMetalPipeline pipelineStateSetModelIndexedLightedAmbientDiffuseNoBlending];
}

void Graphics::PipelineStateSetModelIndexedLightedAmbientDiffuseAlphaBlending() {
    Graphics::BufferSetIndicesModelIndexed();
    [gMetalPipeline pipelineStateSetModelIndexedLightedAmbientDiffuseAlphaBlending];
}

void Graphics::PipelineStateSetModelIndexedLightedAmbientNoBlending() {
    Graphics::BufferSetIndicesModelIndexed();
    [gMetalPipeline pipelineStateSetModelIndexedLightedAmbientNoBlending];
}

void Graphics::PipelineStateSetModelIndexedLightedAmbientAlphaBlending() {
    Graphics::BufferSetIndicesModelIndexed();
    [gMetalPipeline pipelineStateSetModelIndexedLightedAmbientAlphaBlending];
}

void Graphics::PipelineStateSetModelIndexedNoBlending() {
    Graphics::BufferSetIndicesModelIndexed();
    [gMetalPipeline pipelineStateSetModelIndexedNoBlending];
}

void Graphics::PipelineStateSetModelIndexedAlphaBlending() {
    Graphics::BufferSetIndicesModelIndexed();
    [gMetalPipeline pipelineStateSetModelIndexedAlphaBlending];
}

void Graphics::PipelineStateSetSimpleModelIndexedNoBlending() {
    Graphics::BufferSetIndicesSimpleModelIndexed();
    [gMetalPipeline pipelineStateSetSimpleModelIndexedNoBlending];
}

void Graphics::PipelineStateSetSimpleModelIndexedAlphaBlending() {
    Graphics::BufferSetIndicesSimpleModelIndexed();
    [gMetalPipeline pipelineStateSetSimpleModelAlphaBlending];
}

void Graphics::PipelineStateSetSimpleModelNoBlending() {
    Graphics::BufferSetIndicesSimpleModel();
    [gMetalPipeline pipelineStateSetSimpleModelNoBlending];
}

void Graphics::PipelineStateSetSimpleModelAlphaBlending() {
    Graphics::BufferSetIndicesSimpleModel();
    [gMetalPipeline pipelineStateSetSimpleModelAlphaBlending];
}

void Graphics::PipelineStateSetSpriteNoBlending() {
    Graphics::BufferSetIndicesSprite();
    [gMetalPipeline pipelineStateSetSpriteNoBlending];
    //[gMetalEngine.renderCommandEncoder setRenderPipelineState: gMetalEngine.pipelineStateSpriteNoBlending];
}

void Graphics::PipelineStateSetSpriteAlphaBlending() {
    Graphics::BufferSetIndicesSprite();
    [gMetalPipeline pipelineStateSetSpriteAlphaBlending];
}

void Graphics::PipelineStateSetSpriteAdditiveBlending() {
    Graphics::BufferSetIndicesSprite();
    [gMetalPipeline pipelineStateSetSpriteAdditiveBlending];
    //[gMetalEngine.renderCommandEncoder setRenderPipelineState: gMetalEngine.pipelineStateSpriteAdditiveBlending];
}

void Graphics::PipelineStateSetSpritePremultipliedBlending() {
    Graphics::BufferSetIndicesSprite();
    [gMetalPipeline pipelineStateSetSpritePremultipliedBlending];
    //[gMetalEngine.renderCommandEncoder setRenderPipelineState: gMetalEngine.pipelineStateSpritePremultipliedBlending];
}

void Graphics::PipelineStateSetSpriteWhiteBlending() {
    Graphics::BufferSetIndicesSprite();
    [gMetalPipeline pipelineStateSetSpriteWhiteBlending];
    //[gMetalEngine.renderCommandEncoder setRenderPipelineState: gMetalEngine.pipelineStateSpriteWhiteBlending];
}



void Graphics::PipelineStateSetShapeNodeNoBlending() {
    Graphics::BufferSetIndicesShapeNode();
    [gMetalPipeline pipelineStateSetShapeNodeNoBlending];
}

void Graphics::PipelineStateSetShapeNodeAlphaBlending() {
    Graphics::BufferSetIndicesShapeNode();
    [gMetalPipeline pipelineStateSetShapeNodeAlphaBlending];
}

void Graphics::PipelineStateSetShapeNodeAdditiveBlending() {
    Graphics::BufferSetIndicesShapeNode();
    [gMetalPipeline pipelineStateSetShapeNodeAdditiveBlending];
}

int Graphics::RenderPass() {
    return cCurrentRenderPass;
}

void Graphics::RenderPassBegin(int pRenderPass, bool pClearColor, bool pClearDepth) {
    cCurrentRenderPass = pRenderPass;
    [gMetalEngine startRenderPass:pRenderPass clearingColor: pClearColor clearingDepth: pClearDepth];
}


static float cSphere12XYZ[267]={0.0,-0.0,1.0,-0.0,0.5,0.9,-0.2,0.4,0.9,0.0,-0.0,1.0,-0.4,0.2,0.9,0.0,-0.0,1.0,-0.5,-0.0,0.9,0.0,-0.0,1.0,-0.4,-0.2,0.9,0.0,-0.0,1.0,-0.2,-0.4,0.9,0.0,-0.0,1.0,-0.0,-0.5,0.9,0.0,-0.0,1.0,0.2,-0.4,0.9,0.0,-0.0,1.0,0.4,-0.2,0.9,0.0,-0.0,1.0,0.5,-0.0,0.9,0.0,-0.0,1.0,0.4,0.2,0.9,0.0,-0.0,1.0,0.2,0.4,0.9,0.0,-0.0,1.0,-0.0,0.5,0.9,-0.0,0.9,0.5,-0.4,0.8,0.5,-0.8,0.4,0.5,-0.9,-0.0,0.5,-0.8,-0.4,0.5,-0.4,-0.8,0.5,-0.0,-0.9,0.5,0.4,-0.8,0.5,0.8,-0.4,0.5,0.9,-0.0,0.5,0.8,0.4,0.5,0.4,0.7,0.5,-0.0,0.9,0.5,-0.0,1.0,-0.0,-0.5,0.9,-0.0,-0.9,0.5,-0.0,-1.0,-0.0,-0.0,-0.9,-0.5,-0.0,-0.5,-0.9,-0.0,-0.0,-1.0,-0.0,0.5,-0.9,-0.0,0.9,-0.5,-0.0,1.0,-0.0,-0.0,0.9,0.5,-0.0,0.5,0.9,-0.0,-0.0,1.0,-0.0,-0.0,0.9,-0.5,-0.4,0.8,-0.5,-0.8,0.4,-0.5,-0.9,-0.0,-0.5,-0.8,-0.4,-0.5,-0.4,-0.8,-0.5,-0.0,-0.9,-0.5,0.4,-0.8,-0.5,0.8,-0.4,-0.5,0.9,-0.0,-0.5,0.8,0.4,-0.5,0.4,0.7,-0.5,-0.0,0.9,-0.5,-0.0,0.5,-0.9,-0.2,0.4,-0.9,-0.4,0.2,-0.9,-0.5,-0.0,-0.9,-0.4,-0.2,-0.9,-0.2,-0.4,-0.9,-0.0,-0.5,-0.9,0.2,-0.4,-0.9,0.4,-0.2,-0.9,0.5,-0.0,-0.9,0.4,0.2,-0.9,0.2,0.4,-0.9,-0.0,0.5,-0.9,0.0,-0.0,-1.0,0.0,-0.0,-1.0,0.0,-0.0,-1.0,0.0,-0.0,-1.0,0.0,-0.0,-1.0,0.0,-0.0,-1.0,0.0,-0.0,-1.0,0.0,-0.0,-1.0,0.0,-0.0,-1.0,0.0,-0.0,-1.0,0.0,-0.0,-1.0,0.0,-0.0,-1.0};

static float cSphere12UVW[267]={0.00,0.00,0.00,0.00,0.17,0.00,0.08,0.17,0.00,0.08,0.00,0.00,0.17,0.17,0.00,0.17,0.00,0.00,0.25,0.17,0.00,0.25,0.00,0.00,0.33,0.17,0.00,0.33,0.00,0.00,0.42,0.17,0.00,0.42,0.00,0.00,0.50,0.17,0.00,0.50,0.00,0.00,0.58,0.17,0.00,0.58,0.00,0.00,0.67,0.17,0.00,0.67,0.00,0.00,0.75,0.17,0.00,0.75,0.00,0.00,0.83,0.17,0.00,0.83,0.00,0.00,0.92,0.17,0.00,0.92,0.00,0.00,1.00,0.17,0.00,0.00,0.33,0.00,0.08,0.33,0.00,0.17,0.33,0.00,0.25,0.33,0.00,0.33,0.33,0.00,0.42,0.33,0.00,0.50,0.33,0.00,0.58,0.33,0.00,0.67,0.33,0.00,0.75,0.33,0.00,0.83,0.33,0.00,0.92,0.33,0.00,1.00,0.33,0.00,0.00,0.50,0.00,0.08,0.50,0.00,0.17,0.50,0.00,0.25,0.50,0.00,0.33,0.50,0.00,0.42,0.50,0.00,0.50,0.50,0.00,0.58,0.50,0.00,0.67,0.50,0.00,0.75,0.50,0.00,0.83,0.50,0.00,0.92,0.50,0.00,1.00,0.50,0.00,0.00,0.67,0.00,0.08,0.67,0.00,0.17,0.67,0.00,0.25,0.67,0.00,0.33,0.67,0.00,0.42,0.67,0.00,0.50,0.67,0.00,0.58,0.67,0.00,0.67,0.67,0.00,0.75,0.67,0.00,0.83,0.67,0.00,0.92,0.67,0.00,1.00,0.67,0.00,0.00,0.83,0.00,0.08,0.83,0.00,0.17,0.83,0.00,0.25,0.83,0.00,0.33,0.83,0.00,0.42,0.83,0.00,0.50,0.83,0.00,0.58,0.83,0.00,0.67,0.83,0.00,0.75,0.83,0.00,0.83,0.83,0.00,0.92,0.83,0.00,1.00,0.83,0.00,0.00,1.00,0.00,0.08,1.00,0.00,0.17,1.00,0.00,0.25,1.00,0.00,0.33,1.00,0.00,0.42,1.00,0.00,0.50,1.00,0.00,0.58,1.00,0.00,0.67,1.00,0.00,0.75,1.00,0.00,0.83,1.00,0.00,0.92,1.00,0.00};

static float cSphere12Normal[267]={-0.000000,-0.000000,1.000000,0.000000,0.530900,0.847435,-0.265450,0.459773,0.847435,-0.000000,-0.000000,1.000000,-0.459773,0.265450,0.847435,-0.000000,-0.000000,1.000000,-0.530900,0.000000,0.847435,-0.000000,-0.000000,1.000000,-0.459773,-0.265450,0.847435,-0.000000,-0.000000,1.000000,-0.265450,-0.459773,0.847435,-0.000000,-0.000000,1.000000,-0.000000,-0.530900,0.847435,-0.000000,-0.000000,1.000000,0.265450,-0.459773,0.847435,-0.000000,-0.000000,1.000000,0.459773,-0.265450,0.847435,-0.000000,-0.000000,1.000000,0.530900,-0.000000,0.847435,-0.000000,-0.000000,1.000000,0.459773,0.265450,0.847435,-0.000000,-0.000000,1.000000,0.265450,0.459773,0.847435,-0.000000,-0.000000,1.000000,0.000000,0.530900,0.847435,0.000000,0.875983,0.482342,-0.437992,0.758624,0.482342,-0.758624,0.437992,0.482342,-0.875983,0.000000,0.482342,-0.758624,-0.437991,0.482342,-0.437992,-0.758623,0.482342,-0.000000,-0.875983,0.482342,0.437991,-0.758624,0.482342,0.758623,-0.437992,0.482342,0.875983,-0.000001,0.482342,0.758624,0.437991,0.482342,0.437992,0.758623,0.482342,0.000000,0.875983,0.482342,0.000000,1.000000,-0.000000,-0.500000,0.866025,-0.000000,-0.866025,0.500000,-0.000000,-1.000000,0.000000,-0.000000,-0.866026,-0.500000,-0.000000,-0.500000,-0.866025,-0.000000,-0.000000,-1.000000,-0.000000,0.499999,-0.866026,-0.000000,0.866025,-0.500001,-0.000000,1.000000,-0.000001,-0.000000,0.866026,0.499999,-0.000000,0.500001,0.866025,-0.000000,0.000000,1.000000,-0.000000,0.000000,0.875983,-0.482342,-0.437992,0.758624,-0.482342,-0.758624,0.437992,-0.482342,-0.875983,0.000000,-0.482342,-0.758624,-0.437991,-0.482342,-0.437992,-0.758624,-0.482342,-0.000000,-0.875983,-0.482342,0.437991,-0.758624,-0.482342,0.758623,-0.437992,-0.482342,0.875983,-0.000001,-0.482342,0.758624,0.437991,-0.482342,0.437992,0.758623,-0.482342,0.000000,0.875983,-0.482342,0.000000,0.530900,-0.847435,-0.265450,0.459773,-0.847435,-0.459773,0.265450,-0.847435,-0.530900,0.000000,-0.847435,-0.459773,-0.265450,-0.847435,-0.265450,-0.459773,-0.847435,-0.000000,-0.530900,-0.847435,0.265450,-0.459773,-0.847435,0.459773,-0.265450,-0.847435,0.530900,-0.000000,-0.847435,0.459773,0.265450,-0.847435,0.265450,0.459773,-0.847435,0.000000,0.530900,-0.847435,-0.000000,0.000000,-1.000000,-0.000000,0.000000,-1.000000,-0.000000,0.000000,-1.000000,-0.000000,0.000000,-1.000000,-0.000000,0.000000,-1.000000,-0.000000,0.000000,-1.000000,-0.000000,0.000000,-1.000000,-0.000000,0.000000,-1.000000,-0.000000,0.000000,-1.000000,-0.000000,0.000000,-1.000000,-0.000000,0.000000,-1.000000,-0.000000,0.000000,-1.000000};

static GFX_MODEL_INDEX_TYPE cSphere12Index[360]={0,1,2,3,2,4,5,4,6,7,6,8,9,8,10,11,10,12,13,12,14,15,14,16,17,16,18,19,18,20,21,20,22,23,22,24,1,25,26,1,26,2,2,26,27,2,27,4,4,27,28,4,28,6,6,28,29,6,29,8,8,29,30,8,30,10,10,30,31,10,31,12,12,31,32,12,32,14,14,32,33,14,33,16,16,33,34,16,34,18,18,34,35,18,35,20,20,35,36,20,36,22,22,36,37,22,37,24,25,38,39,25,39,26,26,39,40,26,40,27,27,40,41,27,41,28,28,41,42,28,42,29,29,42,43,29,43,30,30,43,44,30,44,31,31,44,45,31,45,32,32,45,46,32,46,33,33,46,47,33,47,34,34,47,48,34,48,35,35,48,49,35,49,36,36,49,50,36,50,37,38,51,52,38,52,39,39,52,53,39,53,40,40,53,54,40,54,41,41,54,55,41,55,42,42,55,56,42,56,43,43,56,57,43,57,44,44,57,58,44,58,45,45,58,59,45,59,46,46,59,60,46,60,47,47,60,61,47,61,48,48,61,62,48,62,49,49,62,63,49,63,50,51,64,65,51,65,52,52,65,66,52,66,53,53,66,67,53,67,54,54,67,68,54,68,55,55,68,69,55,69,56,56,69,70,56,70,57,57,70,71,57,71,58,58,71,72,58,72,59,59,72,73,59,73,60,60,73,74,60,74,61,61,74,75,61,75,62,62,75,76,62,76,63,77,65,64,78,66,65,79,67,66,80,68,67,81,69,68,82,70,69,83,71,70,84,72,71,85,73,72,86,74,73,87,75,74,88,76,75};

void Graphics::DrawSphere12(float x, float y, float z, float pRadius)
{
    //MatrixPush();
    
    //Translate(x, y, z);
    
    //Scale(pRadius);
    
    DrawModelIndexed(cSphere12XYZ, 267, cSphere12UVW, 267, cSphere12Normal, 267, cSphere12Index, 360, 0);
    
    //MatrixPop();
}

