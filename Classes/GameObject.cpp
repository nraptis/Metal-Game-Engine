//
//  GameObject.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 2/28/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "GameObject.hpp"
#include "Game.hpp"

GameObject::GameObject() {
    
    mUniform = NULL;
    mModel = NULL;
    mSprite = NULL;
}

GameObject::~GameObject() {
    
}

void GameObject::Update() {
    
    
}

void GameObject::Draw() {
    
}

void GameObject::Draw3D() {
    
    if (mModel != NULL && mSprite != NULL) {
        
        if (mUniform != NULL) {
            gGame->Convert2DTransformTo3D(&mTransform, &mTransform3D);
            
            mModelView.Reset();
            
            //We start by translation...?
            
            mModelView.Translate(mTransform3D.mX, mTransform3D.mY, mTransform3D.mZ);
            
            //All of our models are exported with X 90 degrees wrong...
            mModelView.RotateX(90.0f);
            
            if (mTransform3D.mRotationX != 0.0f) {
                mModelView.RotateX(mTransform3D.mRotationX);
            }
            
            if (mTransform3D.mRotationZ != 0.0f) {
                mModelView.RotateZ(mTransform3D.mRotationZ);
            }
            
            //Now we do a 2-D rotation...
            if (mTransform3D.mRotation2D != 0.0f) {
                mModelView.RotateY(mTransform3D.mRotation2D);
            }
            
            //Now we spin around the Y axis...
            if (mTransform3D.mSpin != 0.0f) {
                mModelView.RotateZ(mTransform3D.mSpin);
            }
            
            //Now we scale down...
            mModelView.Scale(mTransform3D.mScaleX * mTransform3D.mScale, mTransform3D.mScaleY * mTransform3D.mScale, mTransform3D.mScaleZ * mTransform3D.mScale);
            
            mNormal.SetNormalMatrix(mModelView);
            
            
            //Assign the model view to the uniform...
            mUniform->mModelView.Set(mModelView);
            
            if (mUniform->GetType() == UNIFORM_TYPE_LIGHT_DIFFUSE) {
                FUniformsLightDiffuse *aUniform = (FUniformsLightDiffuse *)(mUniform);
                aUniform->mNormal.Set(mNormal);
            }
            
            if (mUniform->GetType() == UNIFORM_TYPE_LIGHT_PHONG) {
                FUniformsLightPhong *aUniform = (FUniformsLightPhong *)(mUniform);
                aUniform->mNormal.Set(mNormal);
            }
            
            if (mUniform->GetType() == UNIFORM_TYPE_LIGHT_SIMPLE_SPOTLIGHT) {
                FUniformsLightSimpleSpotlight *aUniform = (FUniformsLightSimpleSpotlight *)(mUniform);
                aUniform->mNormal.Set(mNormal);
            }
            
            
            //aNormal.SetNormalMatrix(aModelView);
            
            
            mUniform->mColor.mRed = mColor.mRed;
            mUniform->mColor.mGreen = mColor.mGreen;
            mUniform->mColor.mBlue = mColor.mBlue;
            mUniform->mColor.mAlpha = mColor.mAlpha;
            
            //Then bind the uniform...
            Graphics::UniformBind(mUniform);
        }
        
        Graphics::DrawTrianglesIndexedWithPackedBuffers(mModel->mBuffer, 0, mModel->mIndex, mModel->mIndexCount, mSprite->mTexture);
        
        
        //Graphics::DrawTrianglesIndexedFromPackedBuffers(mModel->mBufferVertex, mModel->mBufferVertexOffset, <#int pIndexBuffer#>, <#int pIndexBufferOffset#>, <#int pCount#>, <#FTexture *pTexture#>)
        
        /*
        Graphics::TextureBind(mSprite->mTexture);
        
        
        Graphics::ArrayBufferData(mModel->mBufferVertex, mModel->mBufferVertexOffset);
        Graphics::ArrayBufferPositions(-1, 0);
        Graphics::ArrayBufferTextureCoords(-1, sizeof(float) * 3);
        Graphics::ArrayBufferNormals(-1, sizeof(float) * 6);
        
        */
        
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mModel->mBufferIndex);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, mModel->mIndexCount * sizeof(unsigned short), mModel->mIndex, GL_STATIC_DRAW);
        
        
        //glDrawElements(GL_TRIANGLES, 0, GL_UNSIGNED_SHORT, 0);
        
        
        /*
        class func bufferIndexSetData(bufferIndex:BufferIndex?, data:inout [IndexBufferType], size:Int) {
            if let checkIndex = bufferIndex {
                glBindBuffer(GLenum(GL_ELEMENT_ARRAY_BUFFER), GLuint(checkIndex))
                glBufferData(GLenum(GL_ELEMENT_ARRAY_BUFFER), size * MemoryLayout<IndexBufferType>.size, &data, GLenum(GL_STATIC_DRAW))
            }
        }
        
        class func drawElementsTriangle(count:Int, offset:Int) {
            let ptr = UnsafeRawPointer(bitPattern: (offset << 1))
            glDrawElements(GLenum(GL_TRIANGLES), GLsizei(count), GLenum(GL_UNSIGNED_SHORT), ptr)
        }
        */
        
        
        /*
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mModel->mBufferIndex);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mModel->mIndexCount * sizeof(GFX_MODEL_INDEX_GL_TYPE), mModel->mIndex, GL_DYNAMIC_DRAW);
        
        
        glDrawElements(GL_TRIANGLES, 0, GFX_MODEL_INDEX_GL_TYPE, 0);
        */
        
        /*
        //
        
        unsigned char *aOffset = NULL;
        aOffset = &(aOffset[mModel->mBufferIndexOffset]);
        
        
        //mModel->mIndexCount
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mModel->mBufferIndex);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, <#GLsizeiptr size#>, <#const GLvoid *data#>, <#GLenum usage#>)
        
        Graphics::BufferElementWrite(mModel->mBufferIndex, mModel->mIndex, mModel->mBufferIndexOffset, mModel->mIndexCount);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, mModel->mIndexCount, mModel->mIndex, GL_DYNAMIC_DRAW);
        
        
        //glDrawElements(GL_TRIANGLES, 100, GFX_MODEL_INDEX_GL_TYPE, aOffset);
        */
        
        //glDrawArraysInstancedEXT(GL_TRIANGLES, pIndexBufferOffset, <#GLsizei count#>, pCount)
        
        //Graphics::DrawTrianglesIndexed(mMonolith.mIndex, mMonolith.mIndexCount);
        
        
        //Graphics::DrawTrianglesIndexed(mModel->mIndex, mModel->mIndexCount);
        
        /*
        Graphics::DrawTrianglesIndexedFromPackedBuffers(mModel->mBufferVertex,
                                                        mModel->mBufferVertexOffset,
                                                        mModel->mBufferIndex,
                                                        mModel->mBufferIndexOffset,
                                                        mModel->mIndexCount,
                                                        mSprite->mTexture);
        */
    }
}

void GameObject::Kill() {
    FObject::Kill();
}





