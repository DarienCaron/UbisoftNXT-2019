#pragma once
#include "App/Vector.h"
#include "App/MathHelper.h"
#include "SimpleTileMap.h"
class Collider
{
public:
    Collider();
    
    ~Collider();

    void CalculateCollider(Vector2Int position, Vector2Int direction);

    bool CheckCollisions(CSimpleTileMap& map);


    void SetHalfDimensions(Vector2 dimensions) { m_Dimensions = dimensions; }

    void ResolveCollision(Vector2Int& direction);

    void DebugDrawCollider();

    enum CollisionNormal
    {
        CollisionUp,
        CollisionDown,
        CollisionLeft,
        CollisionRight,
        CollisionTopRight,
        CollisionTopLeft,
        CollisionBottomLeft,
        CollisionBottomRight,
        CollisionNone
      
    };

    CollisionNormal GetCollisionNormal() { return m_CollisionNormal; }
private:
   
    Vector2 m_Dimensions;

    CollisionNormal m_CollisionNormal;


    Vector2 m_TopRight, m_TopLeft, m_BottomLeft, m_BottomRight;


};

