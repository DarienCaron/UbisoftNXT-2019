#pragma once
#include "Event.h"
#include "Vector.h"


class InputEvent : public Event
{
public:
    InputEvent() {};
    InputEvent(Vector2Int direction) { m_EventType = Event::EventTypes::InputEvent; InputDirection = direction; }
    ~InputEvent() {}


    Vector2Int InputDirection;

};