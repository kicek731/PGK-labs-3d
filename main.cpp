#include "Engine.h"

int main() {
    Engine engine(1280, 720, "Silnik 3D");
    if (!engine.Init()) return -1;
    engine.Run();
    engine.Cleanup();
    return 0;
}
