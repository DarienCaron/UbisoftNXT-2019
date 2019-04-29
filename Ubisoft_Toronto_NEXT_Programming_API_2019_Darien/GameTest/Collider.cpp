#include "stdafx.h"
#include "Collider.h"
#include "App/MathHelper.h"
#include "App/app.h"


Collider::Collider()
{
}


Collider::~Collider()
{
}

void Collider::CalculateCollider(Vector2Int position, Vector2Int direction)
{

    // Calculates a movement vector to offset it to the front of the object.
    Vector2Int MovingDirection = position + direction ;
    // Calcualte the extremities.
    Vector2 TopLeft = Vector2((float)MovingDirection.x - m_Dimensions.x, (float)MovingDirection.y + m_Dimensions.y);
    Vector2 BottomLeft = Vector2((float)MovingDirection.x - m_Dimensions.x, (float)MovingDirection.y - m_Dimensions.y);
    Vector2 TopRight = Vector2((float)MovingDirection.x + m_Dimensions.x, (float)MovingDirection.y + m_Dimensions.y);
    Vector2 BottomRight = Vector2((float)MovingDirection.x + m_Dimensions.x, (float)MovingDirection.y - m_Dimensions.y);

    m_TopLeft = TopLeft; // Store them/
    m_TopRight = TopRight;
    m_BottomRight = BottomRight;
    m_BottomLeft = BottomLeft;



}

bool Collider::CheckCollisions(CSimpleTileMap & map)
{
    // Bool compares to see which ones are touching and set the collision normal.
    if (map.GetTileMapValue(m_TopLeft.x, m_TopLeft.y) != EMapValue::FLOOR && map.GetTileMapValue(m_BottomLeft.x, m_BottomLeft.y) != EMapValue::FLOOR)
    {
        m_CollisionNormal = CollisionLeft;
       
    }
    else if (map.GetTileMapValue(m_TopRight.x, m_TopRight.y) != EMapValue::FLOOR && map.GetTileMapValue(m_BottomRight.x, m_BottomRight.y) != EMapValue::FLOOR )
    {
        m_CollisionNormal = CollisionRight;
        
    }
    else if (map.GetTileMapValue(m_BottomLeft.x, m_BottomLeft.y) != EMapValue::FLOOR && map.GetTileMapValue(m_BottomRight.x, m_BottomRight.y) != EMapValue::FLOOR)
    {
        m_CollisionNormal = CollisionDown;
       
    }
    else if (map.GetTileMapValue(m_TopRight.x, m_TopRight.y) != EMapValue::FLOOR && map.GetTileMapValue(m_TopLeft.x, m_TopLeft.y) != EMapValue::FLOOR)
    {
        m_CollisionNormal = CollisionUp;
     
    }
    else if (map.GetTileMapValue(m_TopRight.x, m_TopRight.y) != EMapValue::FLOOR)
    {
        m_CollisionNormal = CollisionTopRight;
    }
    else if (map.GetTileMapValue(m_TopLeft.x, m_TopLeft.y) != EMapValue::FLOOR)
    {
        m_CollisionNormal = CollisionTopLeft;
    }
    else if (map.GetTileMapValue(m_BottomRight.x, m_BottomRight.y) != EMapValue::FLOOR)
    {
        m_CollisionNormal = CollisionBottomRight;
    }
    else if (map.GetTileMapValue(m_BottomLeft.x, m_BottomLeft.y) != EMapValue::FLOOR)
    {
        m_CollisionNormal = CollisionBottomLeft;
    }
    else
    {
        m_CollisionNormal = CollisionNone;

    }

    if (m_CollisionNormal != CollisionNone)
    {
        return true;
    }

    return false;
}

void Collider::ResolveCollision(Vector2Int & direction)
{
    // Check the collision normal and clamp the direction reference accordingly.

    if (m_CollisionNormal == Collider::CollisionLeft)
    {
        Clamp(direction.x, 0, 1);
    }
    if (m_CollisionNormal == Collider::CollisionRight)
    {
        Clamp(direction.x, -1, 0);
    }
    if (m_CollisionNormal == Collider::CollisionUp || Collider::CollisionTopRight || Collider::CollisionTopLeft)
    {
        Clamp(direction.y, -1, 0);
    }
    if (m_CollisionNormal == Collider::CollisionDown || Collider::CollisionBottomRight || Collider::CollisionBottomLeft)
    {
        Clamp(direction.y, 0, 1);
    }
   
}

void Collider::DebugDrawCollider()
{
        Vector3 color = Vector3(0.4f, 0.8f, 0.7f);

    App::DrawLine(m_TopLeft, m_TopRight, color);
    App::DrawLine(m_BottomRight, m_TopRight, color);
    App::DrawLine(m_TopLeft, m_BottomLeft, color);
    App::DrawLine(m_BottomRight, m_BottomLeft, color);
 
}

