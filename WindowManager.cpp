//
// Created by riki on 7/24/22.
//

#include "WindowManager.h"

WindowManager* WindowManager::Window = nullptr;

void WindowManager::IsValidWindow(RenderWindow* window)
{
    if(!window)
    {
        printf("Cannot destroy window. Invalid window pointer.\n");
        fflush(stdout);
        exit(EXIT_FAILURE);
    }
}

RenderWindow* WindowManager::CreateWindow(Uint32 x, Uint32 y, const String& title, Uint32 frame_rate)
{
    auto window = new RenderWindow(VideoMode(x, y), title);
    IsValidWindow(window);
    window->setFramerateLimit(frame_rate);
    return window;
}

void WindowManager::DestroyWindow(RenderWindow* window)
{
    IsValidWindow(window);
    delete window;
}

WindowManager::WindowManager(Uint32 x, Uint32 y, const String &title, Uint32 frame_rate)
{
    this->windowImpl = CreateWindow(x, y, title, frame_rate);
    this->frontBuffer = RenderBuffer();
    this->activeBuffer = &this->frontBuffer;
    this->clearColor = Color(125, 125, 125);
}

WindowManager::~WindowManager()
{
    DestroyWindow(this->windowImpl);
}

void WindowManager::Update()
{
    this->HandleEvents();
    for(auto & part : this->activeBuffer->onScreenParts)
    {
        part->Update();
        this->windowImpl->draw(*part);
    }
    for(auto & text : this->activeBuffer->onScreenText)
    {
        this->windowImpl->draw(*text);
    }
    this->windowImpl->display();
    this->windowImpl->clear(this->clearColor);
}

bool WindowManager::IsOpen()
{
    IsValidWindow(this->windowImpl);
    return this->windowImpl->isOpen();
}


void WindowManager::AddText(const string & text_string)
{
    Text* text = new Text();
    text->setFont(ResourceManager::Resources->GetFont());
    text->setString(text_string);
    text->setCharacterSize(24);
    text->setFillColor(Color::Black);
    text->setStyle(Text::Style::Regular);
    this->activeBuffer->onScreenText.push_back(text);
}

void WindowManager::HandleEvents()
{
    IsValidWindow(this->windowImpl);
    auto mouse = WindowMouse::Mouse;
    if(!mouse->IsClicking())
        mouse->ResetMouse();
    Event event{};
    while(this->windowImpl->pollEvent(event))
    {
        switch(event.type)
        {
            case Event::Closed:
                this->windowImpl->close();
                break;
            case Event::MouseButtonPressed:
                mouse->SetClickState(ClickState::IsClicking);
                break;
            case Event::MouseButtonReleased:
                mouse->SetClickState(ClickState::Clicked);
                break;
            default:
                break;
        }
    }
}

void WindowManager::Init(Uint32 x, Uint32 y, const String &title, Uint32 frame_rate) {
    Window = new WindowManager(x, y, title, frame_rate);
    ResourceManager::Resources = new ResourceManager("../Resources/Arial.ttf");
    WindowMouse::Mouse = new WindowMouse(Window->windowImpl);

    ResourceManager::Resources->AddNewTexture("light", "../Resources/lightbulb.png");
    ResourceManager::Resources->AddNewTexture("cpu", "../Resources/cpu.png");
    ResourceManager::Resources->AddNewTexture("555", "../Resources/555_timer.png");
    ResourceManager::Resources->AddNewTexture("inverter", "../Resources/inverter_single.png");
}

void WindowManager::Kill() {
    delete Window;
    delete ResourceManager::Resources;
}


