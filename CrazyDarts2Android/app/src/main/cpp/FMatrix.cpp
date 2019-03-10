//
//  FMatrix.cpp
//  CoreDemo
//
//  Created by Nick Raptis on 10/6/13.
//  Copyright (c) 2013 Nick Raptis. All rights reserved.
//

#include "FMatrix.h"
#include "core_includes.h"

FMatrix::FMatrix() {
    m[0] = 1.0f;m[1] = 0.0f;m[2] = 0.0f;m[3] = 0.0f;
	m[4] = 0.0f;m[5] = 1.0f;m[6] = 0.0f;m[7] = 0.0f;
	m[8] = 0.0f;m[9] = 0.0f;m[10]= 1.0f;m[11]= 0.0f;
	m[12]= 0.0f;m[13]= 0.0f;m[14]= 0.0f;m[15]= 1.0f;
}

FMatrix::FMatrix(float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33) {
    m[0]=m00;m[1]=m01;m[2]=m02;m[3]=m03;
	m[4]=m10;m[5]=m11;m[6]=m12;m[7]=m13;
	m[8]=m20;m[9]=m21;m[10]=m22;m[11]=m23;
	m[12]=m30;m[13]=m31;m[14]=m32;m[15]=m33;
}

FMatrix::~FMatrix()
{
    
}

void FMatrix::Reset() {
    m[0] = 1.0f;m[1] = 0.0f;m[2] = 0.0f;m[3] = 0.0f;
    m[4] = 0.0f;m[5] = 1.0f;m[6] = 0.0f;m[7] = 0.0f;
    m[8] = 0.0f;m[9] = 0.0f;m[10]= 1.0f;m[11]= 0.0f;
    m[12]= 0.0f;m[13]= 0.0f;m[14]= 0.0f;m[15]= 1.0f;
    
    /*
    m[0]=1.0f;m[1]=0.0f;m[2]=0.0f;m[3]=0.0f;
    m[4]=0.0f;m[5]=1.0f;m[6]=0.0f;m[7]=0.0f;
    m[8]=0.0f;m[9]=0.0f;m[10]=1.0f;m[11]=0.0f;
    m[12]=0.0f;m[13]=0.0f;m[14]=0.0f;m[15]=1.0f;
    */
}

void FMatrix::Set(FMatrix &pMatrix) {
    float *aData = pMatrix.m;
    m[0]  = aData[0] ;m[1]  = aData[1] ;m[2]  = aData[2] ;m[3]  = aData[3];
    m[4]  = aData[4] ;m[5]  = aData[5] ;m[6]  = aData[6] ;m[7]  = aData[7];
    m[8]  = aData[8] ;m[9]  = aData[9] ;m[10] = aData[10];m[11] = aData[11];
    m[12] = aData[12];m[13] = aData[13];m[14] = aData[14];m[15] = aData[15];
}

void FMatrix::Set(int pRow, int pCol, float pValue) {
    int aIndex = pCol * 4 + pRow;
    if((aIndex >= 0) && (aIndex < 16)) {
        m[aIndex] = pValue;
    }
}

void FMatrix::Multiply(FMatrix &pMatrix) {
    *this = FMatrixMultiply(*this, pMatrix);
}

void FMatrix::Add(FMatrix &pMatrix) {
    *this = FMatrixAdd(*this, pMatrix);
}

void FMatrix::Subtract(FMatrix &pMatrix) {
    *this = FMatrixSubtract(*this, pMatrix);
}

void FMatrix::Rotate(float pDegrees, float pAxisX, float pAxisY, float pAxisZ) {
    *this = FMatrixRotate(*this, DEGREES_TO_RADIANS(pDegrees), pAxisX, pAxisY, pAxisZ);
}

void FMatrix::RotateX(float pDegrees) {
    if (pDegrees != 0.0f) {
        *this = FMatrixRotateX(*this, DEGREES_TO_RADIANS(pDegrees));
    }
}

void FMatrix::RotateY(float pDegrees) {
    if (pDegrees != 0.0f) {
        *this = FMatrixRotateY(*this, DEGREES_TO_RADIANS(pDegrees));
    }
}

void FMatrix::RotateZ(float pDegrees) {
    if (pDegrees != 0.0f) {
        *this = FMatrixRotateZ(*this, DEGREES_TO_RADIANS(pDegrees));
    }
}

void FMatrix::Translate(float pX, float pY) {
    if ((pX != 0.0f) || (pY != 0.0f)) {
        *this = FMatrixTranslate(*this, pX, pY, 0.0f);
    }
}

void FMatrix::Translate(float pX, float pY, float pZ) {
    if ((pX != 0.0f) || (pY != 0.0f) || (pZ != 0.0f)) {
        *this = FMatrixTranslate(*this, pX, pY, pZ);
    }
}

FVec2 FMatrix::ProcessVec2(FVec2 pVec) {
    FVec3 aResult = ProcessVec3(FVec3(pVec.mX, pVec.mY, 0.0f));
    return FVec2(aResult.mX, aResult.mY);
}

FVec3 FMatrix::ProcessVec3(FVec3 pVec) {
    Log("VecIn[%f %f %f]\n", pVec.mX, pVec.mY, pVec.mZ);
    
    //float aX = m[0] * pVec.mX + m[4] * pVec.mY + m[8] * pVec.mZ;
    //float aY = m[1] * pVec.mX + m[5] * pVec.mY + m[9] * pVec.mZ;
    //float aZ = m[2] * pVec.mX + m[6] * pVec.mY + m[10] * pVec.mZ;
    //float aW = m[3] * pVec.mX + m[7] * pVec.mY + m[11] * pVec.mZ;
    
    float aX = m[0] * pVec.mX + m[4] * pVec.mY + m[8] * pVec.mZ + m[12];
    float aY = m[1] * pVec.mX + m[5] * pVec.mY + m[9] * pVec.mZ + m[13];
    float aZ = m[2] * pVec.mX + m[6] * pVec.mY + m[10] * pVec.mZ + m[14];
    float aW = m[3] * pVec.mX + m[7] * pVec.mY + m[11] * pVec.mZ + m[15];
    
    Log("TX[%f] TY[%f] TZ[%f] TW[%f]\n", aX, aY, aZ, aW);
    
    float aScale = 1 / aW;
    
    return FVec3(aX * aScale, aY * aScale, aZ * aScale);
    //return FVec3(aX, aY, aZ);
}

/*
GLK_INLINE GLKFVec3 GLKMatrix4MultiplyAndProjectFVec3(GLKMatrix4 matrixLeft, GLKFVec3 vectorRight)
{
    GLKVector4 v4 = GLKMatrix4MultiplyVector4(matrixLeft, GLKVector4Make(vectorRight.v[0], vectorRight.v[1], vectorRight.v[2], 1.0f));
    return GLKFVec3MultiplyScalar(GLKFVec3Make(v4.v[0], v4.v[1], v4.v[2]), 1.0f / v4.v[3]);
}


GLK_INLINE GLKVector4 GLKMatrix4MultiplyVector4(GLKMatrix4 matrixLeft, GLKVector4 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x4x4_t iMatrix = *(float32x4x4_t *)&matrixLeft;
    float32x4_t v;
    
    iMatrix.val[0] = vmulq_n_f32(iMatrix.val[0], (float32_t)vectorRight.v[0]);
    iMatrix.val[1] = vmulq_n_f32(iMatrix.val[1], (float32_t)vectorRight.v[1]);
    iMatrix.val[2] = vmulq_n_f32(iMatrix.val[2], (float32_t)vectorRight.v[2]);
    iMatrix.val[3] = vmulq_n_f32(iMatrix.val[3], (float32_t)vectorRight.v[3]);
    
    iMatrix.val[0] = vaddq_f32(iMatrix.val[0], iMatrix.val[1]);
    iMatrix.val[2] = vaddq_f32(iMatrix.val[2], iMatrix.val[3]);
    
    v = vaddq_f32(iMatrix.val[0], iMatrix.val[2]);
    
    return *(GLKVector4 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
	const __m128 v = _mm_load_ps(&vectorRight.v[0]);
    
	const __m128 r = _mm_load_ps(&matrixLeft.m[0])  * _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 0, 0))
    + _mm_load_ps(&matrixLeft.m[4])  * _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1))
    + _mm_load_ps(&matrixLeft.m[8])  * _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2))
    + _mm_load_ps(&matrixLeft.m[12]) * _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 3, 3, 3));
    
	GLKVector4 ret;
	*(__m128*)&ret = r;
    return ret;
#else
    GLKVector4 v = { matrixLeft.m[0] * vectorRight.v[0] + matrixLeft.m[4] * vectorRight.v[1] + matrixLeft.m[8] * vectorRight.v[2] + matrixLeft.m[12] * vectorRight.v[3],
        matrixLeft.m[1] * vectorRight.v[0] + matrixLeft.m[5] * vectorRight.v[1] + matrixLeft.m[9] * vectorRight.v[2] + matrixLeft.m[13] * vectorRight.v[3],
        matrixLeft.m[2] * vectorRight.v[0] + matrixLeft.m[6] * vectorRight.v[1] + matrixLeft.m[10] * vectorRight.v[2] + matrixLeft.m[14] * vectorRight.v[3],
        matrixLeft.m[3] * vectorRight.v[0] + matrixLeft.m[7] * vectorRight.v[1] + matrixLeft.m[11] * vectorRight.v[2] + matrixLeft.m[15] * vectorRight.v[3] };
    return v;
#endif
}


GLK_INLINE GLKFVec3 GLKFVec3MultiplyScalar(GLKFVec3 vector, float value)
{
    GLKFVec3 v = { vector.v[0] * value,
        vector.v[1] * value,
        vector.v[2] * value };
    return v;
}
*/


void FMatrix::Scale(float pScale) {
    m[0] *= pScale;
    m[1] *= pScale;
    m[2] *= pScale;
    m[3] *= pScale;
    m[4] *= pScale;
    m[5] *= pScale;
    m[6] *= pScale;
    m[7] *= pScale;
    m[8] *= pScale;
    m[9] *= pScale;
    m[10] *= pScale;
    m[11] *= pScale;
}

void FMatrix::Scale(float pScaleX, float pScaleY, float pScaleZ) {
    m[0] *= pScaleX;
    m[1] *= pScaleX;
    m[2] *= pScaleX;
    m[3] *= pScaleX;
    m[4] *= pScaleY;
    m[5] *= pScaleY;
    m[6] *= pScaleY;
    m[7] *= pScaleY;
    m[8] *= pScaleZ;
    m[9] *= pScaleZ;
    m[10] *= pScaleZ;
    m[11] *= pScaleZ;
}


void FMatrix::Invert() {
	m[0]=m[6]*m[11]*m[13]-m[7]*m[10]*m[13]+m[7]*m[9]*m[14]-m[5]*m[11]*m[14]-m[6]*m[9]*m[15]+m[5]*m[10]*m[15];
	m[1]=m[3]*m[10]*m[13]-m[2]*m[11]*m[13]-m[3]*m[9]*m[14]+m[1]*m[11]*m[14]+m[2]*m[9]*m[15]-m[1]*m[10]*m[15];
	m[2]=m[2]*m[7]*m[13]-m[3]*m[6]*m[13]+m[3]*m[5]*m[14]-m[1]*m[7]*m[14]-m[2]*m[5]*m[15]+m[1]*m[6]*m[15];
	m[3]=m[3]*m[6]*m[9]-m[2]*m[7]*m[9]-m[3]*m[5]*m[10]+m[1]*m[7]*m[10]+m[2]*m[5]*m[11]-m[1]*m[6]*m[11];
	m[4]=m[7]*m[10]*m[12]-m[6]*m[11]*m[12]-m[7]*m[8]*m[14]+m[4]*m[11]*m[14]+m[6]*m[8]*m[15]-m[4]*m[10]*m[15];
	m[5]=m[2]*m[11]*m[12]-m[3]*m[10]*m[12]+m[3]*m[8]*m[14]-m[0]*m[11]*m[14]-m[2]*m[8]*m[15]+m[0]*m[10]*m[15];
	m[6]=m[3]*m[6]*m[12]-m[2]*m[7]*m[12]-m[3]*m[4]*m[14]+m[0]*m[7]*m[14]+m[2]*m[4]*m[15]-m[0]*m[6]*m[15];
	m[7]=m[2]*m[7]*m[8]-m[3]*m[6]*m[8]+m[3]*m[4]*m[10]-m[0]*m[7]*m[10]-m[2]*m[4]*m[11]+m[0]*m[6]*m[11];
	m[8]=m[5]*m[11]*m[12]-m[7]*m[9]*m[12]+m[7]*m[8]*m[13]-m[4]*m[11]*m[13]-m[5]*m[8]*m[15]+m[4]*m[9]*m[15];
	m[9]=m[3]*m[9]*m[12]-m[1]*m[11]*m[12]-m[3]*m[8]*m[13]+m[0]*m[11]*m[13]+m[1]*m[8]*m[15]-m[0]*m[9]*m[15];
	m[10]=m[1]*m[7]*m[12]-m[3]*m[5]*m[12]+m[3]*m[4]*m[13]-m[0]*m[7]*m[13]-m[1]*m[4]*m[15]+m[0]*m[5]*m[15];
	m[11]=m[3]*m[5]*m[8]-m[1]*m[7]*m[8]-m[3]*m[4]*m[9]+m[0]*m[7]*m[9]+m[1]*m[4]*m[11]-m[0]*m[5]*m[11];
	m[12]=m[6]*m[9]*m[12]-m[5]*m[10]*m[12]-m[6]*m[8]*m[13]+m[4]*m[10]*m[13]+m[5]*m[8]*m[14]-m[4]*m[9]*m[14];
	m[13]=m[1]*m[10]*m[12]-m[2]*m[9]*m[12]+m[2]*m[8]*m[13]-m[0]*m[10]*m[13]-m[1]*m[8]*m[14]+m[0]*m[9]*m[14];
	m[14]=m[2]*m[5]*m[12]-m[1]*m[6]*m[12]-m[2]*m[4]*m[13]+m[0]*m[6]*m[13]+m[1]*m[4]*m[14]-m[0]*m[5]*m[14];
	m[15]=m[1]*m[6]*m[8]-m[2]*m[5]*m[8]+m[2]*m[4]*m[9]-m[0]*m[6]*m[9]-m[1]*m[4]*m[10]+m[0]*m[5]*m[10];
	Scale(1/Determinant());
}

float FMatrix::Determinant() {
	float aValue;
	aValue =
    m[3] * m[6] * m[9] * m[12]-m[2] * m[7] * m[9] * m[12]-m[3] * m[5] * m[10] * m[12]+m[1] * m[7] * m[10] * m[12]+
    m[2] * m[5] * m[11] * m[12]-m[1] * m[6] * m[11] * m[12]-m[3] * m[6] * m[8] * m[13]+m[2] * m[7] * m[8] * m[13]+
    m[3] * m[4] * m[10] * m[13]-m[0] * m[7] * m[10] * m[13]-m[2] * m[4] * m[11] * m[13]+m[0] * m[6] * m[11] * m[13]+
    m[3] * m[5] * m[8] * m[14]-m[1] * m[7] * m[8] * m[14]-m[3] * m[4] * m[9] * m[14]+m[0] * m[7] * m[9] * m[14]+
    m[1] * m[4] * m[11] * m[14]-m[0] * m[5] * m[11] * m[14]-m[2] * m[5] * m[8] * m[15]+m[1] * m[6] * m[8] * m[15]+
    m[2] * m[4] * m[9] * m[15]-m[0] * m[6] * m[9] * m[15]-m[1] * m[4] * m[10] * m[15]+m[0] * m[5] * m[10] * m[15];
	return aValue;
}

void FMatrix::OffsetPerspectiveCenter(float pOffsetX, float pOffsetY) {
    m[8] = pOffsetX / gDeviceWidth2;
    m[9] = -pOffsetY / gDeviceHeight2;
}

void FMatrix::Print() {
    int aIndex = 0;
    for (int n=0;n<4;n++) {
        printf("M[%d-%d] [%.2f %.2f %.2f %.2f]\n", 100, n, m[aIndex + 0], m[aIndex + 1], m[aIndex + 2], m[aIndex + 3]);
        aIndex += 4;
    }
}

/*

FMatrix FMatrixCreate(float m00, float m01, float m02, float m03,
                                     float m10, float m11, float m12, float m13,
                                     float m20, float m21, float m22, float m23,
                                     float m30, float m31, float m32, float m33)
{
    FMatrix m = { m00, m01, m02, m03,
        m10, m11, m12, m13,
        m20, m21, m22, m23,
        m30, m31, m32, m33 };
    return m;
}

FMatrix FMatrixCreateAndTranspose(float m00, float m01, float m02, float m03,
                                                 float m10, float m11, float m12, float m13,
                                                 float m20, float m21, float m22, float m23,
                                                 float m30, float m31, float m32, float m33)
{
    FMatrix m = { m00, m10, m20, m30,
        m01, m11, m21, m31,
        m02, m12, m22, m32,
        m03, m13, m23, m33 };
    return m;
}

FMatrix FMatrixCreateWithArray(float values[16])
{
    FMatrix m = { values[0], values[1], values[2], values[3],
        values[4], values[5], values[6], values[7],
        values[8], values[9], values[10], values[11],
        values[12], values[13], values[14], values[15] };
    return m;
}

FMatrix FMatrixCreateTranslation(float tx, float ty, float tz)
{
    FMatrix m;
    m.m[12] = tx;
    m.m[13] = ty;
    m.m[14] = tz;
    return m;
}

FMatrix FMatrixCreateScale(float sx, float sy, float sz)
{
    FMatrix m;
    m.m[0] = sx;
    m.m[5] = sy;
    m.m[10] = sz;
    return m;
}

FMatrix FMatrixCreateRotation(float radians, float x, float y, float z)
{
    float cos = cosf(radians);
    float cosp = 1.0f - cos;
    float sin = sinf(radians);
    
    float aDist = x * x + y * y + z * z;
    
    if(aDist > 0.01f)
    {
        aDist = sqrtf(aDist);
        x /= aDist;
        y /= aDist;
        z /= aDist;
    }
    
    FMatrix m = { cos + cosp * x * x,
        cosp * x * y + z * sin,
        cosp * x * z - y * sin,
        0.0f,
        cosp * x * y - z * sin,
        cos + cosp * y * y,
        cosp * y * z + x * sin,
        0.0f,
        cosp * x * z + y * sin,
        cosp * y * z - x * sin,
        cos + cosp * z * z,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        1.0f };
    
    return m;
}

FMatrix FMatrixCreateXRotation(float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);
    
    FMatrix m = { 1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, cos, sin, 0.0f,
        0.0f, -sin, cos, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f };
    
    return m;
}

FMatrix FMatrixCreateYRotation(float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);
    
    FMatrix m = { cos, 0.0f, -sin, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        sin, 0.0f, cos, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f };
    
    return m;
}

FMatrix FMatrixCreateZRotation(float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);
    
    FMatrix m = { cos, sin, 0.0f, 0.0f,
        -sin, cos, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f };
    
    return m;
}

FMatrix FMatrixCreatePerspective(float fovyRadians, float aspect, float nearZ, float farZ)
{
    float cotan = 1.0f / tanf(fovyRadians / 2.0f);
    
    FMatrix m = { cotan / aspect, 0.0f, 0.0f, 0.0f,
        0.0f, cotan, 0.0f, 0.0f,
        0.0f, 0.0f, (farZ + nearZ) / (nearZ - farZ), -1.0f,
        0.0f, 0.0f, (2.0f * farZ * nearZ) / (nearZ - farZ), 0.0f };
    
    return m;
}

FMatrix FMatrixCreateFrustum(float left, float right, float bottom, float top, float nearZ, float farZ)
{
    float ral = right + left;
    float rsl = right - left;
    float tsb = top - bottom;
    float tab = top + bottom;
    float fan = farZ + nearZ;
    float fsn = farZ - nearZ;
    
    FMatrix m = { 2.0f * nearZ / rsl, 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f * nearZ / tsb, 0.0f, 0.0f,
        ral / rsl, tab / tsb, -fan / fsn, -1.0f,
        0.0f, 0.0f, (-2.0f * farZ * nearZ) / fsn, 0.0f };
    
    return m;
}

FMatrix FMatrixCreateOrtho(float left, float right, float bottom, float top, float nearZ, float farZ)
{
    float ral = right + left;
    float rsl = right - left;
    float tab = top + bottom;
    float tsb = top - bottom;
    float fan = farZ + nearZ;
    float fsn = farZ - nearZ;
    
    FMatrix m = { 2.0f / rsl, 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f / tsb, 0.0f, 0.0f,
        0.0f, 0.0f, -2.0f / fsn, 0.0f,
        -ral / rsl, -tab / tsb, -fan / fsn, 1.0f };
    
    return m;
}

FMatrix FMatrixCreateLookAt(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ)
{
    float aNX = eyeX - centerX;
    float aNY = eyeY - centerY;
    float aNZ = eyeZ - centerZ;
    
    float aDist = aNX * aNX + aNY * aNY + aNZ * aNZ;
    
    if(aDist > 0.01f)
    {
        aDist = sqrtf(aDist);
        aNX /= aDist;
        aNY /= aDist;
        aNZ /= aDist;
    }
    
    float aUX = upY * aNZ - upZ * aNY;
    float aUY = upZ * aNX - upX * aNZ;
    float aUZ = upX * aNY - upY * aNX;
    
    aDist = aUX * aUX + aUY * aUY + aUZ * aUZ;
    if(aDist > 0.01f)
    {
        aDist = sqrtf(aDist);
        aUX /= aDist;
        aUY /= aDist;
        aUZ /= aDist;
    }
    
    float aVX = aNY * aUZ - aNZ * aUY;
    float aVY = aNZ * aUX - aNX * aUZ;
    float aVZ = aNX * aUY - aNY * aUX;
    
    FMatrix m = {aUX, aVX, aNX, 0.0f,
        aUY, aVY, aNY, 0.0f,
        aUZ, aVZ, aNZ, 0.0f,
        -aUX * eyeX + -aUY * eyeY + -aUZ * eyeZ,
        -aVX * eyeX + -aVY * eyeY + -aVZ * eyeZ,
        -aNX * eyeX + -aNY * eyeY + -aNZ * eyeZ,
        1.0f };
    
    return m;
}

FMatrix FMatrixTranspose(FMatrix matrix)
{
    FMatrix m = { matrix.m[0], matrix.m[4], matrix.m[8], matrix.m[12],
        matrix.m[1], matrix.m[5], matrix.m[9], matrix.m[13],
        matrix.m[2], matrix.m[6], matrix.m[10], matrix.m[14],
        matrix.m[3], matrix.m[7], matrix.m[11], matrix.m[15] };
    return m;
}

FMatrix FMatrixMultiply(FMatrix matrixLeft, FMatrix matrixRight)
{
    FMatrix m;
    
    m.m[0]  = matrixLeft.m[0] * matrixRight.m[0]  + matrixLeft.m[4] * matrixRight.m[1]  + matrixLeft.m[8] * matrixRight.m[2]   + matrixLeft.m[12] * matrixRight.m[3];
	m.m[4]  = matrixLeft.m[0] * matrixRight.m[4]  + matrixLeft.m[4] * matrixRight.m[5]  + matrixLeft.m[8] * matrixRight.m[6]   + matrixLeft.m[12] * matrixRight.m[7];
	m.m[8]  = matrixLeft.m[0] * matrixRight.m[8]  + matrixLeft.m[4] * matrixRight.m[9]  + matrixLeft.m[8] * matrixRight.m[10]  + matrixLeft.m[12] * matrixRight.m[11];
	m.m[12] = matrixLeft.m[0] * matrixRight.m[12] + matrixLeft.m[4] * matrixRight.m[13] + matrixLeft.m[8] * matrixRight.m[14]  + matrixLeft.m[12] * matrixRight.m[15];
    
	m.m[1]  = matrixLeft.m[1] * matrixRight.m[0]  + matrixLeft.m[5] * matrixRight.m[1]  + matrixLeft.m[9] * matrixRight.m[2]   + matrixLeft.m[13] * matrixRight.m[3];
	m.m[5]  = matrixLeft.m[1] * matrixRight.m[4]  + matrixLeft.m[5] * matrixRight.m[5]  + matrixLeft.m[9] * matrixRight.m[6]   + matrixLeft.m[13] * matrixRight.m[7];
	m.m[9]  = matrixLeft.m[1] * matrixRight.m[8]  + matrixLeft.m[5] * matrixRight.m[9]  + matrixLeft.m[9] * matrixRight.m[10]  + matrixLeft.m[13] * matrixRight.m[11];
	m.m[13] = matrixLeft.m[1] * matrixRight.m[12] + matrixLeft.m[5] * matrixRight.m[13] + matrixLeft.m[9] * matrixRight.m[14]  + matrixLeft.m[13] * matrixRight.m[15];
    
	m.m[2]  = matrixLeft.m[2] * matrixRight.m[0]  + matrixLeft.m[6] * matrixRight.m[1]  + matrixLeft.m[10] * matrixRight.m[2]  + matrixLeft.m[14] * matrixRight.m[3];
	m.m[6]  = matrixLeft.m[2] * matrixRight.m[4]  + matrixLeft.m[6] * matrixRight.m[5]  + matrixLeft.m[10] * matrixRight.m[6]  + matrixLeft.m[14] * matrixRight.m[7];
	m.m[10] = matrixLeft.m[2] * matrixRight.m[8]  + matrixLeft.m[6] * matrixRight.m[9]  + matrixLeft.m[10] * matrixRight.m[10] + matrixLeft.m[14] * matrixRight.m[11];
	m.m[14] = matrixLeft.m[2] * matrixRight.m[12] + matrixLeft.m[6] * matrixRight.m[13] + matrixLeft.m[10] * matrixRight.m[14] + matrixLeft.m[14] * matrixRight.m[15];
    
	m.m[3]  = matrixLeft.m[3] * matrixRight.m[0]  + matrixLeft.m[7] * matrixRight.m[1]  + matrixLeft.m[11] * matrixRight.m[2]  + matrixLeft.m[15] * matrixRight.m[3];
	m.m[7]  = matrixLeft.m[3] * matrixRight.m[4]  + matrixLeft.m[7] * matrixRight.m[5]  + matrixLeft.m[11] * matrixRight.m[6]  + matrixLeft.m[15] * matrixRight.m[7];
	m.m[11] = matrixLeft.m[3] * matrixRight.m[8]  + matrixLeft.m[7] * matrixRight.m[9]  + matrixLeft.m[11] * matrixRight.m[10] + matrixLeft.m[15] * matrixRight.m[11];
	m.m[15] = matrixLeft.m[3] * matrixRight.m[12] + matrixLeft.m[7] * matrixRight.m[13] + matrixLeft.m[11] * matrixRight.m[14] + matrixLeft.m[15] * matrixRight.m[15];
    
    return m;
}

FMatrix FMatrixAdd(FMatrix matrixLeft, FMatrix matrixRight)
{
    FMatrix m;
    
    m.m[0] = matrixLeft.m[0] + matrixRight.m[0];
    m.m[1] = matrixLeft.m[1] + matrixRight.m[1];
    m.m[2] = matrixLeft.m[2] + matrixRight.m[2];
    m.m[3] = matrixLeft.m[3] + matrixRight.m[3];
    
    m.m[4] = matrixLeft.m[4] + matrixRight.m[4];
    m.m[5] = matrixLeft.m[5] + matrixRight.m[5];
    m.m[6] = matrixLeft.m[6] + matrixRight.m[6];
    m.m[7] = matrixLeft.m[7] + matrixRight.m[7];
    
    m.m[8] = matrixLeft.m[8] + matrixRight.m[8];
    m.m[9] = matrixLeft.m[9] + matrixRight.m[9];
    m.m[10] = matrixLeft.m[10] + matrixRight.m[10];
    m.m[11] = matrixLeft.m[11] + matrixRight.m[11];
    
    m.m[12] = matrixLeft.m[12] + matrixRight.m[12];
    m.m[13] = matrixLeft.m[13] + matrixRight.m[13];
    m.m[14] = matrixLeft.m[14] + matrixRight.m[14];
    m.m[15] = matrixLeft.m[15] + matrixRight.m[15];
    
    return m;
}

FMatrix FMatrixSubtract(FMatrix matrixLeft, FMatrix matrixRight)
{
    FMatrix m;
    
    m.m[0] = matrixLeft.m[0] - matrixRight.m[0];
    m.m[1] = matrixLeft.m[1] - matrixRight.m[1];
    m.m[2] = matrixLeft.m[2] - matrixRight.m[2];
    m.m[3] = matrixLeft.m[3] - matrixRight.m[3];
    
    m.m[4] = matrixLeft.m[4] - matrixRight.m[4];
    m.m[5] = matrixLeft.m[5] - matrixRight.m[5];
    m.m[6] = matrixLeft.m[6] - matrixRight.m[6];
    m.m[7] = matrixLeft.m[7] - matrixRight.m[7];
    
    m.m[8] = matrixLeft.m[8] - matrixRight.m[8];
    m.m[9] = matrixLeft.m[9] - matrixRight.m[9];
    m.m[10] = matrixLeft.m[10] - matrixRight.m[10];
    m.m[11] = matrixLeft.m[11] - matrixRight.m[11];
    
    m.m[12] = matrixLeft.m[12] - matrixRight.m[12];
    m.m[13] = matrixLeft.m[13] - matrixRight.m[13];
    m.m[14] = matrixLeft.m[14] - matrixRight.m[14];
    m.m[15] = matrixLeft.m[15] - matrixRight.m[15];
    
    return m;
}

FMatrix FMatrixTranslate(FMatrix matrix, float tx, float ty, float tz)
{
    FMatrix m = { matrix.m[0], matrix.m[1], matrix.m[2], matrix.m[3],
        matrix.m[4], matrix.m[5], matrix.m[6], matrix.m[7],
        matrix.m[8], matrix.m[9], matrix.m[10], matrix.m[11],
        matrix.m[0] * tx + matrix.m[4] * ty + matrix.m[8] * tz + matrix.m[12],
        matrix.m[1] * tx + matrix.m[5] * ty + matrix.m[9] * tz + matrix.m[13],
        matrix.m[2] * tx + matrix.m[6] * ty + matrix.m[10] * tz + matrix.m[14],
        matrix.m[15] };
    return m;
}

FMatrix FMatrixScale(FMatrix matrix, float sx, float sy, float sz)
{
    FMatrix m = { matrix.m[0] * sx, matrix.m[1] * sx, matrix.m[2] * sx, matrix.m[3] * sx,
        matrix.m[4] * sy, matrix.m[5] * sy, matrix.m[6] * sy, matrix.m[7] * sy,
        matrix.m[8] * sz, matrix.m[9] * sz, matrix.m[10] * sz, matrix.m[11] * sz,
        matrix.m[12], matrix.m[13], matrix.m[14], matrix.m[15] };
    return m;
}

FMatrix FMatrixRotate(FMatrix matrix, float radians, float x, float y, float z)
{
    FMatrix rm = FMatrixCreateRotation(radians, x, y, z);
    return FMatrixMultiply(matrix, rm);
}

FMatrix FMatrixRotateX(FMatrix matrix, float radians)
{
    FMatrix rm = FMatrixCreateXRotation(radians);
    return FMatrixMultiply(matrix, rm);
}

FMatrix FMatrixRotateY(FMatrix matrix, float radians)
{
    FMatrix rm = FMatrixCreateYRotation(radians);
    return FMatrixMultiply(matrix, rm);
}

FMatrix FMatrixRotateZ(FMatrix matrix, float radians)
{
    FMatrix rm = FMatrixCreateZRotation(radians);
    return FMatrixMultiply(matrix, rm);
}
 
*/











FMatrix FMatrixCreate(float m00, float m01, float m02, float m03,
                      float m10, float m11, float m12, float m13,
                      float m20, float m21, float m22, float m23,
                      float m30, float m31, float m32, float m33)
{
    FMatrix m;
    
    
    m.m[0 ] = m00;
    m.m[1 ] = m01;
    m.m[2 ] = m02;
    m.m[3 ] = m03;
    
    m.m[4 ] = m10;
    m.m[5 ] = m11;
    m.m[6 ] = m12;
    m.m[7 ] = m13;
    
    m.m[8 ] = m20;
    m.m[9 ] = m21;
    m.m[10] = m22;
    m.m[11] = m23;
    
    m.m[12] = m30;
    m.m[13] = m31;
    m.m[14] = m32;
    m.m[15] = m33;
    
    return m;
}

FMatrix FMatrixCreateAndTranspose(float m00, float m01, float m02, float m03,
                                  float m10, float m11, float m12, float m13,
                                  float m20, float m21, float m22, float m23,
                                  float m30, float m31, float m32, float m33)
{
    FMatrix m;
    
    m.m[0 ] = m00;
    m.m[1 ] = m10;
    m.m[2 ] = m20;
    m.m[3 ] = m30;
    
    m.m[4 ] = m01;
    m.m[5 ] = m11;
    m.m[6 ] = m21;
    m.m[7 ] = m31;
    
    m.m[8 ] = m02;
    m.m[9 ] = m12;
    m.m[10] = m22;
    m.m[11] = m32;
    
    m.m[12] = m03;
    m.m[13] = m13;
    m.m[14] = m23;
    m.m[15] = m33;
    
    return m;
}


FMatrix FMatrixCreateWithArray(float values[16])
{
    FMatrix m;
    
    m.m[0 ] = values[0 ];
    m.m[1 ] = values[1 ];
    m.m[2 ] = values[2 ];
    m.m[3 ] = values[3 ];
    
    m.m[4 ] = values[4 ];
    m.m[5 ] = values[5 ];
    m.m[6 ] = values[6 ];
    m.m[7 ] = values[7 ];
    
    m.m[8 ] = values[8 ];
    m.m[9 ] = values[9 ];
    m.m[10] = values[10];
    m.m[11] = values[11];
    
    m.m[12] = values[12];
    m.m[13] = values[13];
    m.m[14] = values[14];
    m.m[15] = values[15];
    
    return m;
}

FMatrix FMatrixCreateTranslation(float tx, float ty, float tz)
{
    FMatrix m;
    m.m[12] = tx;
    m.m[13] = ty;
    m.m[14] = tz;
    return m;
}

FMatrix FMatrixCreateScale(float sx, float sy, float sz)
{
    FMatrix m;
    m.m[0] = sx;
    m.m[5] = sy;
    m.m[10] = sz;
    return m;
}

FMatrix FMatrixCreateRotation(float radians, float x, float y, float z)
{
    float cos = cosf(radians);
    float cosp = 1.0f - cos;
    float sin = sinf(radians);
    
    float aDist = x * x + y * y + z * z;
    
    if(aDist > 0.01f)
    {
        aDist = sqrtf(aDist);
        x /= aDist;
        y /= aDist;
        z /= aDist;
    }
    
    FMatrix m = FMatrixCreate(cos + cosp * x * x,
                              cosp * x * y + z * sin,
                              cosp * x * z - y * sin,
                              0.0f,
                              cosp * x * y - z * sin,
                              cos + cosp * y * y,
                              cosp * y * z + x * sin,
                              0.0f,
                              cosp * x * z + y * sin,
                              cosp * y * z - x * sin,
                              cos + cosp * z * z,
                              0.0f,
                              0.0f,
                              0.0f,
                              0.0f,
                              1.0f );
    
    return m;
}

FMatrix FMatrixCreateXRotation(float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);
    
    FMatrix m = FMatrixCreate(1.0f, 0.0f, 0.0f, 0.0f,
                              0.0f, cos, sin, 0.0f,
                              0.0f, -sin, cos, 0.0f,
                              0.0f, 0.0f, 0.0f, 1.0f );
    
    return m;
}

FMatrix FMatrixCreateYRotation(float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);
    
    FMatrix m = FMatrixCreate(cos, 0.0f, -sin, 0.0f,
                              0.0f, 1.0f, 0.0f, 0.0f,
                              sin, 0.0f, cos, 0.0f,
                              0.0f, 0.0f, 0.0f, 1.0f );
    
    return m;
}

FMatrix FMatrixCreateZRotation(float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);
    
    
    FMatrix m = FMatrixCreate(cos, sin, 0.0f, 0.0f,
                              -sin, cos, 0.0f, 0.0f,
                              0.0f, 0.0f, 1.0f, 0.0f,
                              0.0f, 0.0f, 0.0f, 1.0f);
    
    return m;
}

FMatrix FMatrixCreatePerspective(float fovyRadians, float aspect, float nearZ, float farZ)
{
    float cotan = 1.0f / tanf(fovyRadians / 2.0f);
    
    FMatrix m = FMatrixCreate(cotan / aspect, 0.0f, 0.0f, 0.0f,
                              0.0f, cotan, 0.0f, 0.0f,
                              0.0f, 0.0f, (farZ + nearZ) / (nearZ - farZ), -1.0f,
                              0.0f, 0.0f, (2.0f * farZ * nearZ) / (nearZ - farZ), 0.0f );
    
    
    return m;
}

FMatrix FMatrixCreateFrustum(float left, float right, float bottom, float top, float nearZ, float farZ)
{
    float ral = right + left;
    float rsl = right - left;
    float tsb = top - bottom;
    float tab = top + bottom;
    float fan = farZ + nearZ;
    float fsn = farZ - nearZ;
    
    FMatrix m = FMatrixCreate(2.0f * nearZ / rsl, 0.0f, 0.0f, 0.0f,
                              0.0f, 2.0f * nearZ / tsb, 0.0f, 0.0f,
                              ral / rsl, tab / tsb, -fan / fsn, -1.0f,
                              0.0f, 0.0f, (-2.0f * farZ * nearZ) / fsn, 0.0f);
    
    
    return m;
}

FMatrix FMatrixCreateOrtho(float left, float right, float bottom, float top, float nearZ, float farZ) {
    float ral = right + left;
    float rsl = right - left;
    float tab = top + bottom;
    float tsb = top - bottom;
    float fan = farZ + nearZ;
    float fsn = farZ - nearZ;
    FMatrix m = FMatrixCreate(2.0f / rsl, 0.0f, 0.0f, 0.0f,
                              0.0f, 2.0f / tsb, 0.0f, 0.0f,
                              0.0f, 0.0f, -2.0f / fsn, 0.0f,
                              -ral / rsl, -tab / tsb, -fan / fsn, 1.0f);
    return m;
}

FMatrix FMatrixCreateLookAt(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float aCenterZ, float pUpX, float pUpY, float pUpZ) {
    float aNX = eyeX - centerX;
    float aNY = eyeY - centerY;
    float aNZ = eyeZ - aCenterZ;
    float aDist = aNX * aNX + aNY * aNY + aNZ * aNZ;
    if (aDist > 0.01f) {
        aDist = sqrtf(aDist);
        aNX /= aDist;
        aNY /= aDist;
        aNZ /= aDist;
    }
    //float aUX = upY * aNZ - pUpZ * aNY;
    //float aUY = upZ * aNX - aUpX * aNZ;
    //float aUZ = aUpX * aNY - pUpY * aNX;
    

    //Left-Handed...
    float aUX = pUpY * aNZ - pUpZ * aNY;
    float aUY = pUpZ * aNX - pUpX * aNZ;
    float aUZ = pUpX * aNY - pUpY * aNX;
    
    //Right-Handed
    //float aUX = pUpY * aNZ - pUpZ * aNY;
    //float aUY = pUpX * aNZ - pUpZ * aNX;
    //float aUZ = pUpX * aNY - pUpY * aNX;
    
    aDist = aUX * aUX + aUY * aUY + aUZ * aUZ;
    if (aDist > 0.01f) {
        aDist = sqrtf(aDist);
        aUX /= aDist;
        aUY /= aDist;
        aUZ /= aDist;
    }
    
    float aVX = aNY * aUZ - aNZ * aUY;
    float aVY = aNZ * aUX - aNX * aUZ;
    float aVZ = aNX * aUY - aNY * aUX;
    
    /*
    vec3 zaxis = normal(eye - target);    // The "forward" vector.
    vec3 xaxis = normal(cross(up, zaxis));// The "right" vector.
    vec3 yaxis = cross(zaxis, xaxis);     // The "up" vector.
    
    // Create a 4x4 orientation matrix from the right, up, and forward vectors
    // This is transposed which is equivalent to performing an inverse
    // if the matrix is orthonormalized (in this case, it is).
    mat4 orientation = {
        vec4( xaxis.x, yaxis.x, zaxis.x, 0 ),
        vec4( xaxis.y, yaxis.y, zaxis.y, 0 ),
        vec4( xaxis.z, yaxis.z, zaxis.z, 0 ),
        vec4(   0,       0,       0,     1 )
    };
    
    // Create a 4x4 translation matrix.
    // The eye position is negated which is equivalent
    // to the inverse of the translation matrix.
    // T(v)^-1 == T(-v)
    mat4 translation = {
        vec4(   1,      0,      0,   0 ),
        vec4(   0,      1,      0,   0 ),
        vec4(   0,      0,      1,   0 ),
        vec4(-eye.x, -eye.y, -eye.z, 1 )
    };
    
    // Combine the orientation and translation to compute
    // the final view matrix. Note that the order of
    // multiplication is reversed because the matrices
    // are already inverted.
    return ( orientation * translation );
    */
    
    
    FMatrix m = FMatrixCreate(aUX, aVX, aNX, 0.0f,
                              aUY, aVY, aNY, 0.0f,
                              aUZ, aVZ, aNZ, 0.0f,
                              -aUX * eyeX + -aUY * eyeY + -aUZ * eyeZ,
                              -aVX * eyeX + -aVY * eyeY + -aVZ * eyeZ,
                              -aNX * eyeX + -aNY * eyeY + -aNZ * eyeZ,
                              1.0f );
    
    return m;
}

FMatrix FMatrixTranspose(FMatrix matrix)
{
    
    FMatrix m = FMatrixCreate(matrix.m[0], matrix.m[4], matrix.m[8], matrix.m[12],
                              matrix.m[1], matrix.m[5], matrix.m[9], matrix.m[13],
                              matrix.m[2], matrix.m[6], matrix.m[10], matrix.m[14],
                              matrix.m[3], matrix.m[7], matrix.m[11], matrix.m[15]);
    return m;
}

FMatrix FMatrixMultiply(FMatrix matrixLeft, FMatrix matrixRight)
{
    
    /*
     #if defined(__ARM_NEON__)
     
     float32x4x4_t iMatrixRight =
     {{
     {matrixRight.m[0], matrixRight.m[1], matrixRight.m[2], matrixRight.m[3]},
     {matrixRight.m[4], matrixRight.m[5], matrixRight.m[6], matrixRight.m[7]},
     {matrixRight.m[8], matrixRight.m[9], matrixRight.m[10], matrixRight.m[11]},
     {matrixRight.m[12], matrixRight.m[13], matrixRight.m[14], matrixRight.m[15]}
     }};
     
     float32x4x4_t iMatrixLeft =
     {{
     {matrixLeft.m[0], matrixLeft.m[1], matrixLeft.m[2], matrixLeft.m[3]},
     {matrixLeft.m[4], matrixLeft.m[5], matrixLeft.m[6], matrixLeft.m[7]},
     {matrixLeft.m[8], matrixLeft.m[9], matrixLeft.m[10], matrixLeft.m[11]},
     {matrixLeft.m[12], matrixLeft.m[13], matrixLeft.m[14], matrixLeft.m[15]}
     }};
     
     float32x4x4_t m;
     
     m.val[0] = vmulq_n_f32(iMatrixLeft.val[0], vgetq_lane_f32(iMatrixRight.val[0], 0));
     m.val[1] = vmulq_n_f32(iMatrixLeft.val[0], vgetq_lane_f32(iMatrixRight.val[1], 0));
     m.val[2] = vmulq_n_f32(iMatrixLeft.val[0], vgetq_lane_f32(iMatrixRight.val[2], 0));
     m.val[3] = vmulq_n_f32(iMatrixLeft.val[0], vgetq_lane_f32(iMatrixRight.val[3], 0));
     
     m.val[0] = vmlaq_n_f32(m.val[0], iMatrixLeft.val[1], vgetq_lane_f32(iMatrixRight.val[0], 1));
     m.val[1] = vmlaq_n_f32(m.val[1], iMatrixLeft.val[1], vgetq_lane_f32(iMatrixRight.val[1], 1));
     m.val[2] = vmlaq_n_f32(m.val[2], iMatrixLeft.val[1], vgetq_lane_f32(iMatrixRight.val[2], 1));
     m.val[3] = vmlaq_n_f32(m.val[3], iMatrixLeft.val[1], vgetq_lane_f32(iMatrixRight.val[3], 1));
     
     m.val[0] = vmlaq_n_f32(m.val[0], iMatrixLeft.val[2], vgetq_lane_f32(iMatrixRight.val[0], 2));
     m.val[1] = vmlaq_n_f32(m.val[1], iMatrixLeft.val[2], vgetq_lane_f32(iMatrixRight.val[1], 2));
     m.val[2] = vmlaq_n_f32(m.val[2], iMatrixLeft.val[2], vgetq_lane_f32(iMatrixRight.val[2], 2));
     m.val[3] = vmlaq_n_f32(m.val[3], iMatrixLeft.val[2], vgetq_lane_f32(iMatrixRight.val[3], 2));
     
     m.val[0] = vmlaq_n_f32(m.val[0], iMatrixLeft.val[3], vgetq_lane_f32(iMatrixRight.val[0], 3));
     m.val[1] = vmlaq_n_f32(m.val[1], iMatrixLeft.val[3], vgetq_lane_f32(iMatrixRight.val[1], 3));
     m.val[2] = vmlaq_n_f32(m.val[2], iMatrixLeft.val[3], vgetq_lane_f32(iMatrixRight.val[2], 3));
     m.val[3] = vmlaq_n_f32(m.val[3], iMatrixLeft.val[3], vgetq_lane_f32(iMatrixRight.val[3], 3));
     
     return *(FMatrix *)&(m);
     
     #else
     */
    
    
    FMatrix aMatrix;
    
    aMatrix.m[0]  = matrixLeft.m[0] * matrixRight.m[0]  + matrixLeft.m[4] * matrixRight.m[1]  + matrixLeft.m[8] * matrixRight.m[2]   + matrixLeft.m[12] * matrixRight.m[3];
	aMatrix.m[4]  = matrixLeft.m[0] * matrixRight.m[4]  + matrixLeft.m[4] * matrixRight.m[5]  + matrixLeft.m[8] * matrixRight.m[6]   + matrixLeft.m[12] * matrixRight.m[7];
	aMatrix.m[8]  = matrixLeft.m[0] * matrixRight.m[8]  + matrixLeft.m[4] * matrixRight.m[9]  + matrixLeft.m[8] * matrixRight.m[10]  + matrixLeft.m[12] * matrixRight.m[11];
	aMatrix.m[12] = matrixLeft.m[0] * matrixRight.m[12] + matrixLeft.m[4] * matrixRight.m[13] + matrixLeft.m[8] * matrixRight.m[14]  + matrixLeft.m[12] * matrixRight.m[15];
    
	aMatrix.m[1]  = matrixLeft.m[1] * matrixRight.m[0]  + matrixLeft.m[5] * matrixRight.m[1]  + matrixLeft.m[9] * matrixRight.m[2]   + matrixLeft.m[13] * matrixRight.m[3];
	aMatrix.m[5]  = matrixLeft.m[1] * matrixRight.m[4]  + matrixLeft.m[5] * matrixRight.m[5]  + matrixLeft.m[9] * matrixRight.m[6]   + matrixLeft.m[13] * matrixRight.m[7];
	aMatrix.m[9]  = matrixLeft.m[1] * matrixRight.m[8]  + matrixLeft.m[5] * matrixRight.m[9]  + matrixLeft.m[9] * matrixRight.m[10]  + matrixLeft.m[13] * matrixRight.m[11];
	aMatrix.m[13] = matrixLeft.m[1] * matrixRight.m[12] + matrixLeft.m[5] * matrixRight.m[13] + matrixLeft.m[9] * matrixRight.m[14]  + matrixLeft.m[13] * matrixRight.m[15];
    
	aMatrix.m[2]  = matrixLeft.m[2] * matrixRight.m[0]  + matrixLeft.m[6] * matrixRight.m[1]  + matrixLeft.m[10] * matrixRight.m[2]  + matrixLeft.m[14] * matrixRight.m[3];
	aMatrix.m[6]  = matrixLeft.m[2] * matrixRight.m[4]  + matrixLeft.m[6] * matrixRight.m[5]  + matrixLeft.m[10] * matrixRight.m[6]  + matrixLeft.m[14] * matrixRight.m[7];
	aMatrix.m[10] = matrixLeft.m[2] * matrixRight.m[8]  + matrixLeft.m[6] * matrixRight.m[9]  + matrixLeft.m[10] * matrixRight.m[10] + matrixLeft.m[14] * matrixRight.m[11];
	aMatrix.m[14] = matrixLeft.m[2] * matrixRight.m[12] + matrixLeft.m[6] * matrixRight.m[13] + matrixLeft.m[10] * matrixRight.m[14] + matrixLeft.m[14] * matrixRight.m[15];
    
	aMatrix.m[3]  = matrixLeft.m[3] * matrixRight.m[0]  + matrixLeft.m[7] * matrixRight.m[1]  + matrixLeft.m[11] * matrixRight.m[2]  + matrixLeft.m[15] * matrixRight.m[3];
	aMatrix.m[7]  = matrixLeft.m[3] * matrixRight.m[4]  + matrixLeft.m[7] * matrixRight.m[5]  + matrixLeft.m[11] * matrixRight.m[6]  + matrixLeft.m[15] * matrixRight.m[7];
	aMatrix.m[11] = matrixLeft.m[3] * matrixRight.m[8]  + matrixLeft.m[7] * matrixRight.m[9]  + matrixLeft.m[11] * matrixRight.m[10] + matrixLeft.m[15] * matrixRight.m[11];
	aMatrix.m[15] = matrixLeft.m[3] * matrixRight.m[12] + matrixLeft.m[7] * matrixRight.m[13] + matrixLeft.m[11] * matrixRight.m[14] + matrixLeft.m[15] * matrixRight.m[15];
    
    return aMatrix;
    
    //#endif
    
}

FMatrix FMatrixAdd(FMatrix matrixLeft, FMatrix matrixRight)
{
    FMatrix m;
    
    m.m[0] = matrixLeft.m[0] + matrixRight.m[0];
    m.m[1] = matrixLeft.m[1] + matrixRight.m[1];
    m.m[2] = matrixLeft.m[2] + matrixRight.m[2];
    m.m[3] = matrixLeft.m[3] + matrixRight.m[3];
    
    m.m[4] = matrixLeft.m[4] + matrixRight.m[4];
    m.m[5] = matrixLeft.m[5] + matrixRight.m[5];
    m.m[6] = matrixLeft.m[6] + matrixRight.m[6];
    m.m[7] = matrixLeft.m[7] + matrixRight.m[7];
    
    m.m[8] = matrixLeft.m[8] + matrixRight.m[8];
    m.m[9] = matrixLeft.m[9] + matrixRight.m[9];
    m.m[10] = matrixLeft.m[10] + matrixRight.m[10];
    m.m[11] = matrixLeft.m[11] + matrixRight.m[11];
    
    m.m[12] = matrixLeft.m[12] + matrixRight.m[12];
    m.m[13] = matrixLeft.m[13] + matrixRight.m[13];
    m.m[14] = matrixLeft.m[14] + matrixRight.m[14];
    m.m[15] = matrixLeft.m[15] + matrixRight.m[15];
    
    return m;
}

FMatrix FMatrixSubtract(FMatrix matrixLeft, FMatrix matrixRight)
{
    FMatrix m;
    
    m.m[0] = matrixLeft.m[0] - matrixRight.m[0];
    m.m[1] = matrixLeft.m[1] - matrixRight.m[1];
    m.m[2] = matrixLeft.m[2] - matrixRight.m[2];
    m.m[3] = matrixLeft.m[3] - matrixRight.m[3];
    
    m.m[4] = matrixLeft.m[4] - matrixRight.m[4];
    m.m[5] = matrixLeft.m[5] - matrixRight.m[5];
    m.m[6] = matrixLeft.m[6] - matrixRight.m[6];
    m.m[7] = matrixLeft.m[7] - matrixRight.m[7];
    
    m.m[8] = matrixLeft.m[8] - matrixRight.m[8];
    m.m[9] = matrixLeft.m[9] - matrixRight.m[9];
    m.m[10] = matrixLeft.m[10] - matrixRight.m[10];
    m.m[11] = matrixLeft.m[11] - matrixRight.m[11];
    
    m.m[12] = matrixLeft.m[12] - matrixRight.m[12];
    m.m[13] = matrixLeft.m[13] - matrixRight.m[13];
    m.m[14] = matrixLeft.m[14] - matrixRight.m[14];
    m.m[15] = matrixLeft.m[15] - matrixRight.m[15];
    
    return m;
}

FMatrix FMatrixTranslate(FMatrix matrix, float tx, float ty, float tz)
{
    FMatrix m = FMatrixCreate(matrix.m[0], matrix.m[1], matrix.m[2], matrix.m[3],
                              matrix.m[4], matrix.m[5], matrix.m[6], matrix.m[7],
                              matrix.m[8], matrix.m[9], matrix.m[10], matrix.m[11],
                              matrix.m[0] * tx + matrix.m[4] * ty + matrix.m[8] * tz + matrix.m[12],
                              matrix.m[1] * tx + matrix.m[5] * ty + matrix.m[9] * tz + matrix.m[13],
                              matrix.m[2] * tx + matrix.m[6] * ty + matrix.m[10] * tz + matrix.m[14],
                              matrix.m[15]);
    return m;
}

FMatrix FMatrixScale(FMatrix matrix, float sx, float sy, float sz)
{
    FMatrix m = FMatrixCreate(matrix.m[0] * sx, matrix.m[1] * sx, matrix.m[2] * sx, matrix.m[3] * sx,
                              matrix.m[4] * sy, matrix.m[5] * sy, matrix.m[6] * sy, matrix.m[7] * sy,
                              matrix.m[8] * sz, matrix.m[9] * sz, matrix.m[10] * sz, matrix.m[11] * sz,
                              matrix.m[12], matrix.m[13], matrix.m[14], matrix.m[15]);
    return m;
}

FMatrix FMatrixRotate(FMatrix matrix, float radians, float x, float y, float z)
{
    FMatrix rm = FMatrixCreateRotation(radians, x, y, z);
    return FMatrixMultiply(matrix, rm);
}

FMatrix FMatrixRotateX(FMatrix matrix, float radians)
{
    FMatrix rm = FMatrixCreateXRotation(radians);
    return FMatrixMultiply(matrix, rm);
}

FMatrix FMatrixRotateY(FMatrix matrix, float radians)
{
    FMatrix rm = FMatrixCreateYRotation(radians);
    return FMatrixMultiply(matrix, rm);
}

FMatrix FMatrixRotateZ(FMatrix matrix, float radians)
{
    FMatrix rm = FMatrixCreateZRotation(radians);
    return FMatrixMultiply(matrix, rm);
}



