#include "../include/Sound.hpp"

Sound::Sound()
{
    sndResult = ma_engine_init(NULL, &sndEngine);
    if (sndResult != MA_SUCCESS)
    {
        std::cout << "Failed to initialize audio engine.\n";
        //do something here later to throw error?
    }
}

Sound::~Sound()
{
    ma_engine_uninit(&sndEngine);
}

void Sound::Play(const char* file)
{
    ma_engine_play_sound(&sndEngine, file, NULL);
}