//
//  OSSoundBuffer.h
//  Space Whore
//
//  Created by Nick Raptis on 03/27/2019.
//  Copyright (c) 2019
//

#ifndef FRAMEWORK_MUSIC_PLAYER_ANDROID_H
#define FRAMEWORK_MUSIC_PLAYER_ANDROID_H

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>



class OSMusicPlayer {

public:
    OSMusicPlayer();
    ~OSMusicPlayer();


};

extern OSMusicPlayer gMusicPlayer;

#endif


