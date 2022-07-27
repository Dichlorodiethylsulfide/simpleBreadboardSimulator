//
// Created by riki on 7/25/22.
//

#include "WindowMouse.h"

WindowMouse* WindowMouse::Mouse = nullptr;

Vector2i WindowMouse::GetCurrentMousePosition() {
    return Mouse::getPosition(*relativeTo);
}

bool WindowMouse::IsClicking() {
    return this->clickState == ClickState::IsClicking;
}

bool WindowMouse::DidClick() {
    return this->clickState == ClickState::Clicked;
}

void WindowMouse::SetClickState(ClickState e) {
    this->clickState = e;
}

void WindowMouse::ResetMouse(bool clearWindow) {
    this->clickState = ClickState::NoClick;
}

WindowMouse::WindowMouse(RenderWindow *window) {
    this->relativeTo = window;
    this->clickState = ClickState::NoClick;
}
