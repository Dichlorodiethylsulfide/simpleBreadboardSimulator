//
// Created by riki on 7/26/22.
//

#ifndef CLIONUNTITLED_PARTOBJECT_H
#define CLIONUNTITLED_PARTOBJECT_H

#include "includes.h"

#include "ResourceManager.h"

class PartObject : public Drawable {
public:
    explicit PartObject(const Texture& spriteTexture);
    void draw(RenderTarget &target, RenderStates states) const override;
    virtual void Update() = 0;
    void SetOrigin(float x, float y);
    void SetPosition(float x, float y);
    void SetScale(float x, float y);
    void SetRotation(float r);
    void SetColor(const Color& color);

    void SetPosition(const Vector2f& position);
    void SetOrigin(const Vector2f& origin);
    void SetScale(const Vector2f& scale);
protected:
    PartObject();
    Sprite drawableSprite;
};

typedef bool Pin;
typedef chrono::high_resolution_clock HR_Clock;
typedef chrono::high_resolution_clock::time_point TimePoint;
typedef chrono::milliseconds Milliseconds;
#define NOW HR_Clock::now()

class Component : public PartObject {
public:
    explicit Component(const string& texture_name);
    void Update() override;
    void Send();
    void Receive(const vector<Pin>& outPinData);
    virtual void Handle();
    void ConnectComponent(Component* comp);
protected:
    bool receivedSignal;
    vector<Pin> InPins;
    vector<Pin> OutPins;
    vector<Component*> connectedComponents;
};

class CPU : public Component {
public:
    CPU();
    void Update() override;
    void Handle() override;
private:
    bool canPulse;
    Milliseconds pulseRate{};
    TimePoint lastPulse;
};

class LightBulb : public Component {
public:
    LightBulb();
    void Update() override;
    void Handle() override;
};

class NotLogicGate : public Component {
public:
    NotLogicGate();
    void Update() override;
    void Handle() override;
};

/*
#define MAX_SIGNAL_COUNT 8

#define PIN(io, index) *((io == IO::In ? (Uint8*)&this->inSignal : (Uint8*)&this->outSignal) + index)

enum IO
{
    In,
    Out
};

struct IOPin {
    Uint8 signalCount;
    bool hasSignal;
    Uint64 inSignal;
    Uint64 outSignal;

    IOPin() = delete;
    explicit IOPin(Uint8 signalCount);

    void SetPin(Uint8 index, IO io, bool value);
    bool GetPin(Uint8 index, IO io);
};

#define GET_PIN(vector_index, pin_index, io) this->ioPins[vector_index].GetPin(pin_index, io)
#define SET_PIN(vector_index, pin_index, io, value) this->ioPins[vector_index].SetPin(pin_index, io, value)

typedef chrono::high_resolution_clock HR_Clock;
typedef chrono::high_resolution_clock::time_point TimePoint;
typedef chrono::milliseconds Milliseconds;

#define NOW HR_Clock::now()

class Component : public PartObject {
public:
    void Switch(bool on_off);
protected:
    explicit Component(const string& texture_name);
    bool isOn;
    vector<IOPin> ioPins;
};

class CPU : public Component {
public:
    CPU();
    void Update() override;
    void Pulse(bool input) override;
    template<typename _Comp> void AddPartToChain(_Comp* component)
    {
        static_assert(std::is_base_of<Component, _Comp>::value, "_Comp must inherit from Component.");
        pulseChain.push_back(component);
    }
private:
    bool canPulse;
    vector<Component*> pulseChain;
    Milliseconds pulseRate;
    TimePoint lastPulse;
};

class LightBulb : public Component {
public:
    LightBulb();
    void Update() override;
    void Pulse(bool input) override;
};
*/

#endif //CLIONUNTITLED_PARTOBJECT_H
