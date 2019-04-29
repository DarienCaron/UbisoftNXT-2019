#pragma once
#include "Vector.h"
#include "Event.h"


// Interface for Game logic items.
class IGameElement
{
public:

    virtual void Update(float deltatime) = 0;
    virtual void Render() = 0;
    virtual void OnEvent(Event* event) = 0;

};







