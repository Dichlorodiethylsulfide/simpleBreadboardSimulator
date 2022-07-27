//
// Created by riki on 7/26/22.
//

#include "PartObject.h"

/////////// PartObject

PartObject::PartObject(const Texture &spriteTexture) {
    this->drawableSprite = Sprite(spriteTexture);
}

void PartObject::draw(RenderTarget &target, RenderStates states) const {
    target.draw(drawableSprite, states);
}

void PartObject::SetOrigin(float x, float y) {
    auto size = (Vector2f)this->drawableSprite.getTexture()->getSize();
    this->drawableSprite.setOrigin(x * size.x, y * size.y);
}

void PartObject::SetPosition(float x, float y) {
    this->drawableSprite.setPosition(x, y);
}

void PartObject::SetScale(float x, float y) {
    this->drawableSprite.setScale(x, y);
}

void PartObject::SetRotation(float r) {
    this->drawableSprite.setRotation(r);
}

void PartObject::SetPosition(const Vector2f& position) {
    this->SetPosition(position.x, position.y);
}

void PartObject::SetOrigin(const Vector2f &origin) {
    this->SetOrigin(origin.x, origin.y);
}

void PartObject::SetScale(const Vector2f &scale) {
    this->SetScale(scale.x, scale.y);
}

void PartObject::SetColor(const Color& color) {
    this->drawableSprite.setColor(color);
}

PartObject::PartObject() = default;

/////////// PartObject
/////////// Component
Component::Component(const string & texture_name) : PartObject(ResourceManager::Resources->GetTexture(texture_name)) {
    this->SetOrigin(0.5, 0.5);
    this->receivedSignal = false;
}

void Component::Update() {
    if(this->receivedSignal)
    {
        this->Handle();
        this->receivedSignal = false;
    }
}

void Component::Send() {
    for(auto comp : connectedComponents)
    {
        comp->Receive(this->OutPins);
    }
}

void Component::Receive(const vector<Pin> &outPinData) {
    assert(outPinData.size() <= this->InPins.size());
    this->receivedSignal = true;
    //this->InPins = outPinData;
    for(int i = 0; i < outPinData.size(); i++)
    {
        this->InPins[i] = outPinData[i];
    }
}

void Component::ConnectComponent(Component *comp) {
    this->connectedComponents.push_back(comp);
}

void Component::Handle() {
    this->Send();
}

/////////// Component
/////////// CPU

CPU::CPU() : Component("cpu") {
    canPulse = false;
    pulseRate = Milliseconds(1000);
    lastPulse = NOW;
    this->OutPins.push_back(0);
}

void CPU::Update() {
    if(this->canPulse)
    {
        OutPins[0] = 1;
        this->canPulse = false;
        lastPulse = HR_Clock::now();
    } else {
        OutPins[0] = 0;
    }
    this->receivedSignal = true;
    if(chrono::duration_cast<Milliseconds>(NOW - lastPulse) > pulseRate)
    {
        this->canPulse = true;
    }
    Component::Update();
}

void CPU::Handle() {
    Component::Handle();
}

/////////// CPU
/////////// LightBulb

LightBulb::LightBulb() : Component("light") {
    InPins.push_back(0);
    OutPins.push_back(0);
}

void LightBulb::Update() {
    Component::Update();
    if(InPins[0])
    {
        this->SetColor(Color::Yellow);
    }
    else
    {
        this->SetColor(Color::White);
    }
}

void LightBulb::Handle() {
    OutPins[0] = InPins[0];
    Component::Handle();
}

/////////// LightBulb
/////////// NOT Gate

NotLogicGate::NotLogicGate() : Component("inverter") {
    InPins.push_back(0);
    OutPins.push_back(0);
}

void NotLogicGate::Update() {
    Component::Update();
}

void NotLogicGate::Handle() {
    OutPins[0] = !InPins[0];
    Component::Handle();
}

/////////// NOT Gate