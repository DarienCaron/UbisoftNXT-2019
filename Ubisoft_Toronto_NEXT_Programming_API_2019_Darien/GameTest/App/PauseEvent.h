#pragma once
#include "Event.h"


class PauseEvent : public Event
{
public:

    PauseEvent() { m_EventType = Event::EventTypes::PauseEvent;}
    ~PauseEvent() {}


};