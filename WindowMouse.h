//
// Created by riki on 7/25/22.
//

#ifndef CLIONUNTITLED_WINDOWMOUSE_H
#define CLIONUNTITLED_WINDOWMOUSE_H

#include "includes.h"
#include <chrono>

enum ClickState
{
    NoClick,
    IsClicking,
    Clicked,
};

class WindowMouse {
public:
    Vector2i  GetCurrentMousePosition();
    bool IsClicking();
    bool DidClick();
    void SetClickState(ClickState e);
    void ResetMouse(bool clearWindow = false);
    explicit WindowMouse(RenderWindow* window);
    static WindowMouse* Mouse;
private:
    RenderWindow* relativeTo;
    ClickState clickState;
};

/*
enum ClickEnum
{
    Start,
    End,
    Difference,
};

struct PartialClickData
{
    Vector2i clickPosition;
    chrono::system_clock::time_point  clickTime;

    PartialClickData();
    explicit PartialClickData(Vector2i pos);
    PartialClickData& operator-(PartialClickData right);
};

struct ClickData
{
    PartialClickData startClickData;
    PartialClickData endClickData;
    ClickState clickState = NoClick;
};

class WindowMouse {
public:
    WindowMouse();
    Vector2i GetMousePosition();
    void SetMousePosition(Int32 x, Int32 y);

    bool IsClicking();
    ClickData GetPreviousClick();
    PartialClickData GetPreviousPartialClickData(ClickEnum clickE);
    void SetClickData(ClickEnum clickE, Vector2i position);
    bool ClickedLastFrame() const;
    void ResetMouse();

private:
    Vector2i mousePosition;
    bool isClicking;
    ClickData mouseClickData;
};
*/

#endif //CLIONUNTITLED_WINDOWMOUSE_H
