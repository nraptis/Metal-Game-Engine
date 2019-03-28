//
//  OSSoundBuffer.cpp
//  Space Whore
//
//  Created by Nick Raptis on 03/27/2019.
//  Copyright (c) 2019
//

#include <assert.h>
#include "os_core_music.h"
#include "OSMusicBuffer.h"
#include "OSMusicPlayer.h"
#include "os_core_sound.h"
#include "os_core_includes.h"
#include "core_includes.h"

OSMusicBuffer::OSMusicBuffer() {
    uriPlayerObject = NULL;
    uriPlayerPlay = NULL;
    uriPlayerSeek = NULL;
    uriPlayerMuteSolo = NULL;
    uriPlayerVolume = NULL;

    mDidFail = false;
}

OSMusicBuffer::~OSMusicBuffer() {

    Log("DEALLOC::OSMusicBuffer(%s)\n\n", mFileName.c());

    TearDown();
}

void OSMusicBuffer::SetUp(const char *pFilePath, bool pLoop) {

    mFileName = pFilePath;
    mDidFail = false;


    off_t aStartIndex, aLength;
    int aFileDescriptor = MUSIC_GetFileDescriptor(pFilePath, aStartIndex, aLength);

    if (aFileDescriptor == -1) {
        Log("***---\nFAILED PLAY MUSIC!! [%s]\n***---\n", pFilePath);


        mDidFail = true;
        return;
    }

    Log("Music FD: %d [%s]\n", aFileDescriptor, pFilePath);


    SLDataSource audioSrc;
    SLDataLocator_AndroidFD loc_fd = {SL_DATALOCATOR_ANDROIDFD, aFileDescriptor, aStartIndex, aLength};
    SLDataFormat_MIME format_mime = {SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED};
    audioSrc.pLocator = &loc_fd;
    audioSrc.pFormat = &format_mime;

    SLresult aResult;

    // configure audio sink
    SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, outputMixObject};
    SLDataSink audioSnk = {&loc_outmix, NULL};

    // create audio player
    const SLInterfaceID ids[3] = {SL_IID_SEEK, SL_IID_MUTESOLO, SL_IID_VOLUME};
    const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
    aResult = (*engineEngine)->CreateAudioPlayer(engineEngine, &uriPlayerObject, &audioSrc, &audioSnk, 3, ids, req);
    // note that an invalid URI is not detected here, but during prepare/prefetch on Android,
    // or possibly during Realize on other platforms
    if (aResult != SL_RESULT_SUCCESS) {
        Log("Music Player Failed: CreateAudioPlayer()\n");

        mDidFail = true;
        TearDown();
        return;;
    }
    
    // realize the player
    aResult = (*uriPlayerObject)->Realize(uriPlayerObject, SL_BOOLEAN_FALSE);
    if (aResult != SL_RESULT_SUCCESS) {
        Log("Music Player Failed: Realize()\n");

        mDidFail = true;
        TearDown();
        return;;
    }

    // get the play interface
    aResult = (*uriPlayerObject)->GetInterface(uriPlayerObject, SL_IID_PLAY, &uriPlayerPlay);
    if (aResult != SL_RESULT_SUCCESS) {
        Log("Music Player Failed: GetInterface(SL_IID_PLAY)\n");

        mDidFail = true;
        TearDown();
        return;;
    }

    // get the seek interface
    aResult = (*uriPlayerObject)->GetInterface(uriPlayerObject, SL_IID_SEEK, &uriPlayerSeek);
    if (aResult != SL_RESULT_SUCCESS) {
        Log("Music Player Failed: GetInterface(SL_IID_SEEK)\n");

        mDidFail = true;
        TearDown();
        return;;
    }

    // get the mute/solo interface
    aResult = (*uriPlayerObject)->GetInterface(uriPlayerObject, SL_IID_MUTESOLO, &uriPlayerMuteSolo);
    if (aResult != SL_RESULT_SUCCESS) {
        Log("Music Player Failed: GetInterface(SL_IID_MUTESOLO)\n");

        mDidFail = true;
        TearDown();
        return;;
    }

    // get the volume interface
    aResult = (*uriPlayerObject)->GetInterface(uriPlayerObject, SL_IID_VOLUME, &uriPlayerVolume);
    if (aResult != SL_RESULT_SUCCESS) {
        Log("Music Player Failed: GetInterface(SL_IID_VOLUME)\n");

        mDidFail = true;
        TearDown();
        return;;
    }

    Log("Music Setup Complete\n\n");

    if (uriPlayerSeek != NULL) {

        // set the looping state
        aResult = (*uriPlayerSeek)->SetLoop(uriPlayerSeek, (SLboolean)pLoop, 0, SL_TIME_UNKNOWN);
        if (aResult != SL_RESULT_SUCCESS) {
            Log("Music Player Failed: SetLoop()\n");

            mDidFail = true;
            TearDown();
            return;;
        }
    }

    if (NULL != uriPlayerPlay) {
        aResult = (*uriPlayerPlay)->SetPlayState(uriPlayerPlay, SL_PLAYSTATE_PLAYING);
        if (aResult != SL_RESULT_SUCCESS) {
            Log("Music Player Failed: SetPlayState()\n");

            mDidFail = true;
            TearDown();
            return;;
        }

        //SL_PLAYSTATE_PAUSED
    }

}

void OSMusicBuffer::TearDown() {
    if (uriPlayerObject != NULL) {
        (*uriPlayerObject)->Destroy(uriPlayerObject);
        uriPlayerObject = NULL;
        uriPlayerPlay = NULL;
        uriPlayerSeek = NULL;
        uriPlayerMuteSolo = NULL;
        uriPlayerVolume = NULL;
    }
}

void OSMusicBuffer::Pause() {

}

void OSMusicBuffer::Resume() {

}
