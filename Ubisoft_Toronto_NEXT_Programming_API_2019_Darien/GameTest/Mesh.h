#pragma once
#include "App/Vector.h"
class Mesh
{
public:
    Mesh();
    ~Mesh();

private:
    std::vector<Vector2> m_Points;
};

