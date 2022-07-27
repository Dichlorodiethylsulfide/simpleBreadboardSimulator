#include "WindowManager.h"

int main()
{
    WindowManager::Init(800, 600, "Window", 1);
    auto manager = WindowManager::Window;

    auto& cpu = manager->AddPart<CPU>();
    cpu.SetPosition(100, 100);

    auto& gate = manager->AddPart<NotLogicGate>(200, 100);
    cpu.ConnectComponent(&gate);

    auto& light = manager->AddPart<LightBulb>(300, 100);
    gate.ConnectComponent(&light);

    auto& otherLight = manager->AddPart<LightBulb>(200, 200);
    cpu.ConnectComponent(&otherLight);

    while(manager->IsOpen())
    {
        manager->Update();
    }

    WindowManager::Kill();
    return 0;
}