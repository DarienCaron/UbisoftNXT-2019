#pragma once
class Mesh;
#include "App/Vector.h"
class IMeshBuilder
{
public:

    Vector2 Origin;

    virtual Mesh* GetResult() = 0;
};