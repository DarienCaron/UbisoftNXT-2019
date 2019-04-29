#pragma once
#include "IMeshBuilder.h"
#include "Mesh.h"
class PacManMeshBuilder :
    public IMeshBuilder
{
public:
    PacManMeshBuilder();
    ~PacManMeshBuilder();

    // Inherited via IMeshBuilder
    virtual Mesh* GetResult() override;
};

