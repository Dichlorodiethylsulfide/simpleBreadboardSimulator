//
// Created by riki on 7/24/22.
//

#ifndef CLIONUNTITLED_WINDOWMANAGER_H
#define CLIONUNTITLED_WINDOWMANAGER_H

#include "includes.h"

#include "ResourceManager.h"
#include "WindowMouse.h"

#include "PartObject.h"

struct RenderBuffer
{
    vector<Text*> onScreenText;
    vector<PartObject*> onScreenParts;
};

class WindowManager {
public:
    WindowManager() = delete;
    ~WindowManager();
    WindowManager(Uint32 x, Uint32 y, const String& title, Uint32 frame_rate = 60);
    void Update();
    bool IsOpen();

    void AddText(const string& text_string);
    template<typename Part> Part& AddPart(float x = 0, float y = 0)
    {
        static_assert(std::is_base_of<PartObject, Part>::value, "Part must inherit from PartObject");
        auto part = new Part();
        this->activeBuffer->onScreenParts.push_back(part);
        ((PartObject*)part)->SetPosition(x, y);
        return *part;
    }

    static void Init(Uint32 x, Uint32 y, const String &title, Uint32 frame_rate = 60);
    static void Kill();

    static WindowManager* Window;

private:
    RenderBuffer frontBuffer;
    //RenderBuffer backBuffer;

    RenderBuffer* activeBuffer;

    Color clearColor;

    void HandleEvents();

    RenderWindow* windowImpl;
    static RenderWindow* CreateWindow(Uint32 x, Uint32 y, const String& title, Uint32 frame_rate = 60);
    static void DestroyWindow(RenderWindow* window);
    static void IsValidWindow(RenderWindow* window);
};


#endif //CLIONUNTITLED_WINDOWMANAGER_H
