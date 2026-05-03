#include "DDEngine.h"

DDEngine::DDEngine() : _renderer()
{

}

int DDEngine::Init()
{
    if (_renderer.Init() != 0) return -1;
    return 0;
}

void DDEngine::Run()
{
    _renderer.Run();
}

void DDEngine::Shutdown()
{
    _renderer.Shutdown();
}
