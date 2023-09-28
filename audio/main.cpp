#define MINIAUDIO_IMPLEMENTATION
#include "res/cpp/miniaudio.h"

#include <stdio.h>
#include <iostream>

int main(int argc, char **argv)
{
    ma_result result;
    ma_engine engine;

    if (argc < 2)
    {
        printf("No input file.");
        return -1;
    }

    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS)
    {
        printf("Failed to initialize audio engine.");
        return -1;
    }

    ma_engine_play_sound(&engine, argv[1], NULL);

    //printf("Write play to play the sound or quit to quit...");
    std::string ans;

    while(1)
    {
        std::cout << "Write play to play the sound or quit to quit: ";
        std::cin >> ans;
        if(ans == "play") ma_engine_play_sound(&engine, argv[1], NULL);
        else if(ans == "quit") break;
        //else do go back in loop to cin
    }

    //getchar();

    ma_engine_uninit(&engine);

    return 0;
}