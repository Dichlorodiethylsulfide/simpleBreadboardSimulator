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
 * Note: CPU & Output are also components
 *
 * --> Component -> Component -> Component ------>
 * |                                             |
 * CPU -> Component -> Component -->             |
 * |                               |             |
 * --> Component -> Component --> Component -> Component -> Output
 * |                                             |
 * --> Component -> Component -> Component ------>
 *
 *
 *
 * CPU sends signal
 * Component receives signal
 *
 * Component handles signal
 *
 * Component sends signal
 * Other Component receives signal
 *
 *
 * Sending signal will send all the OUT pins
 * Receives signal will ping all IN pins
 * Handling signal uses those IN pins and creates the OUT pin signal
 * Loop send, receive and handle
 *
 *
 * void Send(component) => component.Receive(OutPins)
 * void Receive() => this.setInPins
 * void Handle() => this.useInPins, this.setOutPins
 * Send -> Receive -> Handle -> Send to next component in chain
 *
 */

#endif //CLIONUNTITLED_PARTOBJECT_H
