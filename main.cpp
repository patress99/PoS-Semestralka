
#include <iostream>
#include "Game.h"
#include "Menu.h"
#include "heap_monitor.h"


int main()
{

    initHeapMonitor();

    std::srand(static_cast<unsigned>(time(NULL)));

    Menu menu;



    return 0;
}



