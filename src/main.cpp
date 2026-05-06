#include <iostream>
#include "DDGameEngine.h"

int main(int argc, char* argv[])
{
    DDGameEngine engine;

    std::cout << "Initializing engine..." << std::endl;
    if (engine.Init() != 0) return -1;

    std::cout << "Running engine..." << std::endl;
    engine.Run();

    std::cout << "Shutting down engine..." << std::endl;
    engine.Shutdown();

	return 0;
}
