#include "DDRenderer.h"

class DDEngine
{
    private:
    DDRenderer _renderer;

    public:
    DDEngine();

    int Init();
    void Run();
    void Shutdown();
};
