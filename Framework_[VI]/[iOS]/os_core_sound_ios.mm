//
//  os_core_sound.cpp
//  Ghibli
//
//  Created by Nick Raptis on 2/21/14.
//  Copyright (c) 2014 Union AdWorks LLC. All rights reserved.
//

#include "os_core_sound.h"
#include "os_core_outlets.h"

#import <AVFoundation/AVFoundation.h>
#import <AudioToolbox/AudioToolbox.h>
#import <QuartzCore/QuartzCore.h>
#import <CoreFoundation/CoreFoundation.h>

#include "os_core_outlets.h"
#include "core_includes.h"
#include "OSMusicPlayer.h"




#include "openal/al.h"
#include "OpenAL/alc.h"

#include "FSound.h"

OSMusicPlayer *gMusicPlayer = NULL;

FSoundInstanceIOS::FSoundInstanceIOS()
{
    
}

FSoundInstanceIOS::~FSoundInstanceIOS()
{
    
}

//unsigned int                    mIndexOpenAL;



FSoundDataIOS::FSoundDataIOS()
{
    mInstanceID = 0;
    mData = 0;
    mSourceBuffer = new float[16];
    
}

FSoundDataIOS::~FSoundDataIOS()
{
    mData = 0;
    mInstanceID = 0;
    
    if(mSourceBuffer)
    {
        delete [] mSourceBuffer;
        mSourceBuffer = 0;
    }
}


ALCcontext *gAudioContext = NULL;
ALCdevice *gAudioDevice = NULL;

void interruptionListener( void *inUserData, UInt32 inInterruption)
{
    printf("Session interrupted! --- %s ---\n", inInterruption == kAudioSessionBeginInterruption ? "Begin Interruption" : "End Interruption");
    
    if ( inInterruption == kAudioSessionBeginInterruption ) {
        printf("Audio interrupted.\n" );
        //iphonePauseMusic();
        core_sound_musicPause();
        alcMakeContextCurrent( NULL );
        //AudioSessionSetActive( false );
        
    } else if ( inInterruption == kAudioSessionEndInterruption ) {
        printf("Audio restored.\n" );
        
        OSStatus r = AudioSessionSetActive( true );
        if ( r != kAudioSessionNoError ) {
            printf( "AudioSessionSetActive( true ) failed: 0x%x\n", r );
        } else {
            printf( "AudioSessionSetActive( true ) succeeded.\n" );
        }
        alcMakeContextCurrent(gAudioContext);
        if( alcGetError(gAudioDevice) != ALC_NO_ERROR ) {
            printf("Failed to alcMakeContextCurrent\n");
            
        }
        //iphoneResumeMusic();
        core_sound_musicResume();
    }
}

int otherAudioIsPlaying;

void core_sound_initialize()
{
    
    /*
     OSStatus status = 0;
     status = AudioSessionInitialize(NULL, NULL, interruptionListener, NULL);    // else "couldn't initialize audio session"
     
     // if there is iPod music playing in the background, we want to use
     // the AmbientSound catagory, otherwise we will leave it at the default.
     // If we always set it to AmbientSound, then the mp3 background music
     // playback goes to software on 3.0 for a huge slowdown.
     UInt32  propOtherAudioIsPlaying = 'othr'; // kAudioSessionProperty_OtherAudioIsPlaying
     UInt32  size = sizeof( otherAudioIsPlaying );
     AudioSessionGetProperty( propOtherAudioIsPlaying, &size, &otherAudioIsPlaying );
     printf("OtherAudioIsPlaying = %d\n", otherAudioIsPlaying );
     
     if ( otherAudioIsPlaying ) {
     UInt32 audioCategory = kAudioSessionCategory_AmbientSound;
     status = AudioSessionSetProperty(kAudioSessionProperty_AudioCategory, sizeof(audioCategory), &audioCategory);
     }
     
     status = AudioSessionSetActive(true);                                       // else "couldn't set audio session active\n"
     */
    
    gAudioDevice = alcOpenDevice( NULL );
    if( gAudioDevice == NULL ) {
        printf( "Failed to alcOpenDevice\n" );
    }
    
    gAudioContext = alcCreateContext( gAudioDevice, NULL );
    if( gAudioContext == NULL ) {
        printf("Failed to create audio context\n");
        return;
    }
    
    // Set active context
    alcGetError(gAudioDevice);
    alcMakeContextCurrent(gAudioContext);
    if( alcGetError(gAudioDevice) != ALC_NO_ERROR ) {
        printf("Failed to alcMakeContextCurrent\n" );
        return;
    }
    
    ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };
    ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };
    ALfloat ListenerOri[] = { 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 };
    
    alListenerfv(AL_POSITION, ListenerPos);
    alListenerfv(AL_VELOCITY, ListenerVel);
    alListenerfv(AL_ORIENTATION, ListenerOri);
    
    gMusicPlayer = [[OSMusicPlayer alloc] init];
}

void *sound_load_ios(const char *theFilename, int *theDataSize, int *theDataFormat, int* theSampleRate) {
    NSString *aPath=[NSString stringWithUTF8String: theFilename];
    NSURL *aUrl=[NSURL fileURLWithPath:aPath];
    
    CFURLRef						aFileURL=(__bridge CFURLRef)aUrl;
    OSStatus						aResult = noErr;
    SInt64							aFileLengthInFrames = 0;
    AudioStreamBasicDescription		aFileFormat;
    UInt32							aPropertySize = sizeof(aFileFormat);
    ExtAudioFileRef					aExtRef = NULL;
    unsigned int*					aData = NULL;
    AudioStreamBasicDescription		aOutputFormat;
    
    for (;;) {
        aResult = ExtAudioFileOpenURL(aFileURL, &aExtRef);
        if (aResult) {
            break;
        }
        
        aResult = ExtAudioFileGetProperty(aExtRef, kExtAudioFileProperty_FileDataFormat, &aPropertySize, &aFileFormat);
        
        if (aResult) {
            break;
        }
        
        if (aFileFormat.mChannelsPerFrame > 2) {
            break;
        }
        
        
        aOutputFormat.mSampleRate=aFileFormat.mSampleRate;
        aOutputFormat.mChannelsPerFrame=aFileFormat.mChannelsPerFrame;
        
        
        aOutputFormat.mFormatID=kAudioFormatLinearPCM;
        aOutputFormat.mBytesPerPacket=2*aOutputFormat.mChannelsPerFrame;
        aOutputFormat.mFramesPerPacket=1;
        aOutputFormat.mBytesPerFrame=2*aOutputFormat.mChannelsPerFrame;
        aOutputFormat.mBitsPerChannel=16;
        aOutputFormat.mFormatFlags=kAudioFormatFlagsNativeEndian | kAudioFormatFlagIsPacked | kAudioFormatFlagIsSignedInteger;
        
        aResult=ExtAudioFileSetProperty(aExtRef, kExtAudioFileProperty_ClientDataFormat,sizeof(aOutputFormat),&aOutputFormat);
        if (aResult) {
            break;
        }
        
        aPropertySize=sizeof(aFileLengthInFrames);
        aResult=ExtAudioFileGetProperty(aExtRef, kExtAudioFileProperty_FileLengthFrames, &aPropertySize, &aFileLengthInFrames);
        if (aResult) {
            break;
        }
        
        unsigned int aDataSize = (unsigned int)(aFileLengthInFrames*aOutputFormat.mBytesPerFrame);
        
        aData = (unsigned int*)malloc(aDataSize);
        
        if (aData) {
            AudioBufferList		aDataBuffer;
            aDataBuffer.mNumberBuffers = 1;
            aDataBuffer.mBuffers[0].mDataByteSize=aDataSize;
            aDataBuffer.mBuffers[0].mNumberChannels=aOutputFormat.mChannelsPerFrame;
            aDataBuffer.mBuffers[0].mData=aData;
            
            aResult=ExtAudioFileRead(aExtRef, (UInt32*)&aFileLengthInFrames, &aDataBuffer);
            if (aResult == noErr) {
                *theDataSize = (int)aDataSize;
                *theDataFormat = aOutputFormat.mChannelsPerFrame;
                *theSampleRate = (int)aOutputFormat.mSampleRate;
            } else {
                free(aData);
                aData=NULL;
            }
        }
        break;
    }
    
    //Dispose the ExtAudioFileRef, it is no longer needed
    if (aExtRef) {
        ExtAudioFileDispose(aExtRef);
    }
    
    return aData;
}

bool core_sound_load(FSound *pSound, const char *pFileName, int pInstanceCount) {
    bool aReturn = false;
    if ((pSound != 0) && (pFileName != 0)) {
        if (pSound->mSoundData != 0) {
            FSoundDataIOS *aSoundData = ((FSoundDataIOS *)pSound->mSoundData);
            if (os_fileExists(pFileName)) {
                int aLoadDataSize;
                int aLoadDataFormat;
                int aLoadSampleRate;
                
                ALsizei aDataSize;
                ALenum aDataFormat;
                ALsizei aSampleRate;
                
                void *aData = sound_load_ios(pFileName,&aLoadDataSize,&aLoadDataFormat,&aLoadSampleRate);
                if (aData) {
                    aDataSize=aLoadDataSize;
                    aDataFormat = (aLoadDataFormat>1) ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
                    aSampleRate=aLoadSampleRate;
                    
                    aSoundData->mData = new ALuint(aDataSize);
                    
                    bool aFail = false;
                    
                    alGenBuffers(1, aSoundData->mData);
                    
                    if(alGetError()!=AL_NO_ERROR)
                    {
                        Log("Could not load Sound (alGenBuffers Failed): %s\n", pFileName);
                        
                        aFail = true;
                    }
                    
                    if(aFail == false)
                    {
                        alBufferData(aSoundData->mData[0],aDataFormat,aData,aDataSize,aSampleRate);
                        
                        if(alGetError()!=AL_NO_ERROR)
                        {
                            Log("Could not load Sound (alBufferData Failed): %s\n", pFileName);
                            
                            aFail = true;
                        }
                    }
                    
                    
                    if(aFail == false)
                    {
                        aSoundData->mInstanceID = new ALuint[pInstanceCount];
                        alGenSources(pInstanceCount, aSoundData->mInstanceID);
                        
                        if(alGetError() != AL_NO_ERROR)
                        {
                            aFail = true;
                            Log("Could not load Sound (alGenSources Failed): %s\n", pFileName);
                        }
                    }
                    
                    if(aFail == false)
                    {
                        for(int aCount=0;aCount<pInstanceCount;aCount++)
                        {
                            alSourcei(aSoundData->mInstanceID[aCount],AL_BUFFER,aSoundData->mData[0]);
                            
                            FSoundInstanceIOS *aInstance = new FSoundInstanceIOS();// (aSoundData->mInstanceID[aCount]);
                            aInstance->mIndexOpenAL = aSoundData->mInstanceID[aCount];
                            aInstance->mDidLoad = true;
                            pSound->mInstances+=aInstance;
                        }
                    }
                    
                    if (aData) {
                        free(aData);
                    }
                    if (aFail == false) {
                        aReturn = true;
                    }
                }
            }
        }
    }
    
    return aReturn;
}

void core_sound_play(FSound *pSound)
{
    core_sound_play(pSound, 1.0f);
}

void core_sound_play(FSound *pSound, float pVolume) {
    if (pSound) {
        FSoundInstanceIOS *aAvailable = 0;
        EnumList (FSoundInstanceIOS, aInstance, pSound->mInstances) {
            if (aInstance->mDidLoad == true) {
                if (core_sound_instance_isPlaying(aInstance) == false) {
                    aAvailable = aInstance;
                    break;
                }
            }
        }
        if (aAvailable) {
            if (aAvailable->mDidLoad) {
                aAvailable->ResetPitch();
                aAvailable->Play(pVolume);
            }
        }
    }
}

void core_sound_playPitched(FSound *pSound, float pPitch, float pVolume) {
    if (pSound) {
        FSoundInstanceIOS *aAvailable = 0;
        EnumList (FSoundInstanceIOS, aInstance, pSound->mInstances) {
            if (aInstance->mDidLoad) {
                if (core_sound_instance_isPlaying(aInstance) == false) {
                    aAvailable=aInstance;
                    break;
                }
            }
        }
        
        if(aAvailable)
        {
            aAvailable->SetPitch(pPitch);
            aAvailable->Play(pVolume);
        }
    }
}

void core_sound_stop(FSound *pSound)
{
    if(pSound)
    {
        EnumList(FSoundInstanceIOS, aInstance, pSound->mInstances)
        {
            aInstance->Stop();
        }
    }
}

void core_sound_clear(FSound *pSound) {
    if (pSound) {
        FSoundDataIOS *aSoundData = ((FSoundDataIOS *)pSound->mSoundData);
        if (aSoundData) {
            alDeleteBuffers(pSound->mInstances.mCount, aSoundData->mData);
            
            delete [] aSoundData->mData;
            delete [] aSoundData->mInstanceID;
            
            aSoundData->mData = 0;
            aSoundData->mInstanceID = 0;
        }
    }
}

bool core_sound_isPlaying(FSound *pSound)
{
    bool aReturn = false;
    
    if(pSound)
    {
        EnumList(FSoundInstanceIOS, aInstance, pSound->mInstances)
        {
            if(core_sound_instance_isPlaying(aInstance))
            {
                aReturn = true;
                break;
            }
        }
    }
    
    return aReturn;
}

bool core_sound_didLoad(FSound *pSound)
{
    bool aReturn = false;
    
    if(pSound)
    {
        
        EnumList(FSoundInstanceIOS, aInstance, pSound->mInstances)
        {
            if(aInstance->mDidLoad == true)
            {
                aReturn = true;
            }
        }
    }
    
    return aReturn;
}

void core_sound_setVolume(float pVolume)
{
    gVolumeSound = pVolume;
}

float core_sound_getVolume()
{
    return gVolumeSound;
}









void core_sound_instance_resetPitch(FSoundInstance *pInstance)
{
    FSoundInstanceIOS *aInstance = (FSoundInstanceIOS *)pInstance;
    if(aInstance)alSourcef(aInstance->mIndexOpenAL,AL_PITCH,1.0f);
}

void core_sound_instance_setPitch(FSoundInstance *pInstance, float pPitch)
{
    FSoundInstanceIOS *aInstance = (FSoundInstanceIOS *)pInstance;
    if(aInstance)alSourcef(aInstance->mIndexOpenAL, AL_PITCH, pPitch);
}

void core_sound_instance_setVolume(FSoundInstance *pInstance, float pVolume)
{
    FSoundInstanceIOS *aInstance = (FSoundInstanceIOS *)pInstance;
    if(aInstance)alSourcef(aInstance->mIndexOpenAL, AL_GAIN, pVolume);
}

void core_sound_instance_play(FSoundInstance *pInstance, float pVolume)
{
    FSoundInstanceIOS *aInstance = (FSoundInstanceIOS *)pInstance;
    if(aInstance)
    {
        core_sound_instance_setVolume(pInstance, pVolume);
        alSourcei(aInstance->mIndexOpenAL,AL_LOOPING,false);
        alSourcePlay(aInstance->mIndexOpenAL);
        pInstance->mIsLooping = false;
    }
}

void core_sound_instance_pause(FSoundInstance *pInstance)
{
    FSoundInstanceIOS *aInstance = (FSoundInstanceIOS *)pInstance;
    if(aInstance)
    {
        if(pInstance->mIsPaused == false)
        {
            pInstance->mIsPaused = true;
            alSourcePause(aInstance->mIndexOpenAL);
        }
    }
}

void core_sound_instance_unpause(FSoundInstance *pInstance)
{
    FSoundInstanceIOS *aInstance = (FSoundInstanceIOS *)pInstance;
    if(aInstance)
    {
        if(pInstance->mIsPaused == true)
        {
            pInstance->mIsPaused = false;
            alSourcePlay(aInstance->mIndexOpenAL);
        }
    }
}


void core_sound_instance_loop(FSoundInstance *pInstance, float pVolume)
{
    FSoundInstanceIOS *aInstance = (FSoundInstanceIOS *)pInstance;
    if(aInstance)
    {
        core_sound_instance_setVolume(pInstance, pVolume);
        alSourcei(aInstance->mIndexOpenAL, AL_LOOPING, true);
        alSourcePlay(aInstance->mIndexOpenAL);
    }
    
}

void core_sound_instance_stop(FSoundInstance *pInstance)
{
    FSoundInstanceIOS *aInstance = (FSoundInstanceIOS *)pInstance;
    if(aInstance)alSourceStop(aInstance->mIndexOpenAL);
}

bool core_sound_instance_isPlaying(FSoundInstance *pInstance) {
    ALint aResult = 0;
    FSoundInstanceIOS *aInstance = (FSoundInstanceIOS *)pInstance;
    if(aInstance)
        alGetSourcei(aInstance->mIndexOpenAL, AL_SOURCE_STATE, &aResult);
    return (aResult==AL_PLAYING);
}

void core_sound_instance_destroy(FSoundInstance *pInstance) {
    
}

void core_sound_musicPlay(const char *pFilePath, bool pLoop) {
   FString aFilePath = gDirBundle + pFilePath;
    
    if (os_fileExists(aFilePath)) {
        [gMusicPlayer musicPlay: [NSString stringWithUTF8String: aFilePath.c()] withLoop: pLoop];
    }
    
}

void core_sound_musicCrossFade(const char *pFilePath, int pDurationTicks, bool pLoop) {
    FString aFilePath = gDirBundle + pFilePath;
    if (os_fileExists(aFilePath)) {
        [gMusicPlayer musicCrossFadeWithPath:[NSString stringWithUTF8String: aFilePath.c()] withDurationTicks: pDurationTicks withLoop: pLoop];
    }
}

void core_sound_musicFadeOut(int pDurationTicks) {
    [gMusicPlayer musicFadeOutWithDurationTicks: pDurationTicks];
}

void core_sound_musicStop() {
    [gMusicPlayer musicStop];
}

bool core_sound_musicIsPlaying() {
    bool aResult = false;
    
    aResult = [gMusicPlayer musicIsPlaying];
    
    return aResult;
}

void core_sound_musicSetVolume(float pVolume) {
    gVolumeMusic = pVolume;
}

float core_sound_musicGetVolume() {
    return gVolumeMusic;
}

void core_sound_musicResume() {
    
}

void core_sound_musicPause() {
    
}

void core_sound_stopAll() {
    core_sound_stopAllEffects();
    core_sound_musicPause();
}

void core_sound_stopAllEffects() {
    
}

FSoundData *core_sound_spawn_data() {
    return new FSoundDataIOS();
}

void core_sound_unloadEffects() {
    
}

void core_sound_reloadEffects() {
    
}

void core_sound_update() {
    [gMusicPlayer updateFade];
}

void core_sound_active() {
    
}

void core_sound_inactive() {
    
}



