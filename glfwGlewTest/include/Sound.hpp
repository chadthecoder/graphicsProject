#pragma once

#include <iostream>

#include "../include/miniaudio.h"

class Sound
{
private:
    ma_result sndResult;
    ma_engine sndEngine;
public:
    Sound(/* args */);
    ~Sound();

    //takes in file to play
    void Play(const char* file);
};