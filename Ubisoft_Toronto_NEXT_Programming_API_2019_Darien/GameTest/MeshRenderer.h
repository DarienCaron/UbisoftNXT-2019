#pragma once
#include "App/app.h"

#include "IMeshBuilder.h"
#include "Mesh.h"
class MeshRenderer
{
public:
    MeshRenderer();
    ~MeshRenderer();
    MeshRenderer(IMeshBuilder* builder);

    void Draw();

private:
    Mesh * m_Mesh;
};

