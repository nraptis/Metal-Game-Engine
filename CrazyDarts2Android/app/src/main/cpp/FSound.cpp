/*
 *  FSound.cpp
 *  Drillheads
 *
 *  Created by Nick Raptis on 11/29/09.
 *  Copyright 2009 Raptisoft LLC. All rights reserved.
 *
 */

#include "FSound.h"
#include "FResource.h"
#include "core_includes.h"
#include "os_core_sound.h"

FSoundInstance::FSoundInstance()
//FSoundInstance(unsigned int  pIndex)
{
	//mIndexOpenAL = pIndex;
    //gAudio.mFSoundInstanceList+=this;
    
    mIsPaused = false;
	mIsLooping = false;
    
    mVolume = 1.0f;
    mPitch = 1.0f;
    
    mDidLoad = false;
    
    //mPlayerObject = 0;
    //mPlayerPlay = 0;
    //mPlayerMuteSolo = 0;
    //mPlayerVolume = 0;
    //mPlayerRatePitch = 0;
    //mPlayerPitch = 0;
    
}

//FSoundInstance();

FSoundInstance::~FSoundInstance()
{
    
}


FSoundData::FSoundData()
{
    mDidLoad = false;
    mSound = 0;
}

FSoundData::~FSoundData()
{
    
}


void FSoundInstance::Play(float pVolume)
{
    core_sound_instance_play(this, pVolume);
}

void FSoundInstance::Loop(float pVolume)
{
    core_sound_instance_loop(this, pVolume);
}

void FSoundInstance::ResetPitch()
{
    core_sound_instance_resetPitch(this);
}

void FSoundInstance::SetPitch(float pPitch)
{
    core_sound_instance_setPitch(this, pPitch);
}

void FSoundInstance::SetVolume(float pVolume)
{
    core_sound_instance_setVolume(this, pVolume);
}

void FSoundInstance::Pause()
{
    core_sound_instance_pause(this);
}

void FSoundInstance::Unpause()
{
    core_sound_instance_unpause(this);
}

void FSoundInstance::Stop()
{
    core_sound_instance_stop(this);
}

bool FSoundInstance::IsPlaying()
{
    return core_sound_instance_isPlaying(this);
}

void FSoundInstance::Destroy()
{
    core_sound_instance_destroy(this);
}

/*
void FSoundInstance::SetPitch()
{
	//alSourcef(mIndexOpenAL,AL_PITCH,1.0f);
}

void FSoundInstance::SetPitch(float pMultiplier)
{
	//alSourcef(mIndexOpenAL,AL_PITCH,pMultiplier);
}

void FSoundInstance::SetPitchManual(float pPitch)
{
	//alSourcef(mIndexOpenAL,AL_PITCH,pPitch);
}


void FSoundInstance::Play(float pVolume)
{
	//SetVolume(pVolume);
	//alSourcei(mIndexOpenAL,AL_LOOPING,false);
	//alSourcePlay(mIndexOpenAL);
	//mIsLooping=false;
    
}

void FSoundInstance::Pause(bool pState)
{
	if(pState)mPause++;
    if(mPause > 0)mPause--;
    else mPause = 0;
    
	if(pState)
	{
		if(mPause==1 && pState)
		{
			mSavedPlaying=IsPlaying();
			//alSourcePause(mIndexOpenAL);
		}
	}
	else
	{
		if(mSavedPlaying)
		{
			//alSourcePlay(mIndexOpenAL);
			mSavedPlaying=false;
		}
	}
}


void FSoundInstance::Loop(float pVolume)
{
	SetVolume(pVolume);
	//alSourcei(mIndexOpenAL,AL_LOOPING,true);
	//alSourcePlay(mIndexOpenAL);
	mIsLooping=true;
}

void FSoundInstance::SetVolume(float pVolume)
{
	mVolume=pVolume;
	//alSourcef(mIndexOpenAL, AL_GAIN,mVolume);
}

void FSoundInstance::Stop()
{
	//alSourceStop(mIndexOpenAL);
}

bool FSoundInstance::IsPlaying()
{
	//ALint aResult;
	//alGetSourcei(mIndexOpenAL,AL_SOURCE_STATE,&aResult) ;
	//return (aResult==AL_PLAYING);
    
    return true;
}

int FSoundInstance::GetPosition()
{
	return 0;
}

void FSoundInstance::Destroy()
{
	
}
 
*/


FSound::FSound()
{
	mSoundData = core_sound_spawn_data();
    
    mSoundData->mSound = this;
    
    mDidLoad = false;
}

FSound::~FSound(void)
{
	Clear();
    
    
}

void FSound::Clear()
{
    core_sound_clear(this);
}

void FSound::Play(float pVolume)
{
    core_sound_play(this, pVolume);
}

bool FSound::IsPlaying()
{
    return core_sound_isPlaying(this);
}

void FSound::PlayPitched(float pPitch, float pVolume)
{
    core_sound_playPitched(this, pPitch, pVolume);
}

void FSound::Stop()
{
    core_sound_stop(this);
}

void FSound::Load(const char *pFileName, int pDuplicates)
{
    bool aDidLoad = false;
    
    const char *aResourcePath = gRes.GetResourcePathSound(pFileName);
    while ((aResourcePath != 0) && (aDidLoad == false))//(mWidth <= 0) && (mHeight <= 0))
    {
        aDidLoad = core_sound_load(this, aResourcePath, pDuplicates);
        if(aDidLoad)
        {
            mFileName = pFileName;
            mDidLoad = true;
        }
        else
        {
            aResourcePath = gRes.GetNextResourcePath();
        }
    }
    
    FString aFileNameBase = FString(pFileName);
    aFileNameBase.RemoveExtension();
    
    mFileName = aFileNameBase;
    
    FString aFileName;
    
    int aExtensionCount = 8;
    FString aExtension[8];
    aExtension[0] = ".aif";
    aExtension[1] = ".aiff";
    aExtension[2] = ".caf";
    aExtension[3] = ".m4a";
    aExtension[4] = ".ogg";
    aExtension[5] = ".wav";
    aExtension[6] = ".mp3";
    aExtension[7] = ".aac";
    
    if (aDidLoad == false) {
        for (int i=0;i<aExtensionCount;i++) {
            if (aDidLoad == false) {
                aFileName = FString(aFileNameBase) + aExtension[i];
                aDidLoad = core_sound_load(this, aFileName.c(), pDuplicates);
                if (aDidLoad) {
                    mFileName = aFileName;
                }
            }
        }
    }
    if ((aDidLoad == false) && (gDirBundle.mLength > 0)) {
        for (int i=0;i<aExtensionCount;i++) {
            if (aDidLoad == false) {
                aFileName = gDirBundle + FString(aFileNameBase) + aExtension[i];
                aDidLoad = core_sound_load(this, aFileName.c(), pDuplicates);
                if (aDidLoad) {
                    mFileName = aFileName;
                }
            }
        }
    }
    if (aDidLoad) {
        sSoundList.Add(this);
        EnumList(FSoundInstance, aInstance, mInstances) {
            aInstance->mSound = this;
            sSoundInstanceList.Add(aInstance);
        }
        mDidLoad = true;
    } else {
        mDidLoad = false;
    }
}

bool FSound::DidLoad()
{
    return core_sound_didLoad(this);
}



