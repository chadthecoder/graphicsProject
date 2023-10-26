#include <iostream>

#include <chrono>
#include <ctime>    




int main()
{
    clock_t current_ticks, delta_ticks;
clock_t fps = 0;

    while(1)
    {
        current_ticks = clock();

    render();

    delta_ticks = clock() - current_ticks; //the time, in ms, that took to render the scene
    if(delta_ticks > 0)
        fps = CLOCKS_PER_SEC / delta_ticks;
    std::cout << fps << std::endl;
}
    

    return 0;
}