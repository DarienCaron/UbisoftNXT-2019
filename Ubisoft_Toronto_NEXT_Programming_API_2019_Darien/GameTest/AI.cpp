#include "stdafx.h"
#include "AI.h"

#include "stdafx.h"
#include "GameObject.h"
#include "App/app.h"
#include "App/InputEvent.h"
#include "App/PauseEvent.h"


AI::AI()
{

}

AI::AI(Scene* sceneref, std::string name) : GameObject(sceneref, name)
{

    m_SceneIBelongTo = sceneref;

    Init(name);







}

AI::AI(Scene* sceneref, std::string name, ObjectTransform transform) : GameObject(sceneref, name, transform)
{
    Init(name, transform);

    m_SceneIBelongTo = sceneref;




}


AI::~AI()
{
    delete m_Collider;
    delete m_PathFinder;
}

void AI::Init(std::string name)
{

    m_Name = name;

    m_Transform = ObjectTransform();

    m_Collider = new Collider();
    m_Collider->SetHalfDimensions(Vector2(32, 32));
    CSimpleTileMap* s = &m_SceneIBelongTo->GetTileMap();
    m_PathFinder = new Pathfinder(s, 16,16);

    Vector2Int Destination = m_SceneIBelongTo->GetTileMap().GetTilePosForWorldPos(Vector2(500, 500));
    m_FinalTileDestination = Destination;
    SetNextDestination();
}

void AI::Init(std::string name, ObjectTransform& t)
{
    m_Name = name;
    m_Transform = t;

    m_Collider = new Collider();
    m_Collider->SetHalfDimensions(Vector2(32, 32));
    CSimpleTileMap* s = &m_SceneIBelongTo->GetTileMap();
    m_PathFinder = new Pathfinder(s, 16,16 );
    int bp = 0;

    Vector2Int Destination = m_SceneIBelongTo->GetTileMap().GetTilePosForWorldPos(Vector2(1024 / 2, 768 / 2));
    m_FinalTileDestination = Destination;

    SetNextDestination();
   
}


void AI::Update(float deltatime)
{
    m_FinalTileDestination =  m_SceneIBelongTo->GetTileMap().GetTilePosForWorldPos(Vector2(0, 0));
  

   

    Vector2Int direction = Vector2Int(0, 0);

    if (m_Destination.x > m_Transform.Position.x)
    {
        direction = Vector2Int().Right();
        if (direction.x > (m_Destination.x - m_Transform.Position.x))
            direction.x = m_Destination.x - m_Transform.Position.x;
    }
    else if (m_Destination.x < m_Transform.Position.x)
    {
        direction = Vector2Int().Left();
        if (direction.x < (m_Destination.x - m_Transform.Position.x))
            direction.x = m_Destination.x - m_Transform.Position.x;
    }
    else if (m_Destination.y > m_Transform.Position.y)
    {
        direction = Vector2Int().Up();
        if (direction.y > (m_Destination.x - m_Transform.Position.y))
            direction.y = m_Destination.y - m_Transform.Position.y;
    }
    else if (m_Destination.y < m_Transform.Position.y)
    {
        direction = Vector2Int().Down();
        if (direction.y < (m_Destination.x - m_Transform.Position.y))
            direction.y = m_Destination.y - m_Transform.Position.y;
    
    }


    m_MoveDirection = direction;

    m_Collider->CalculateCollider(m_Transform.Position, m_MoveDirection);

    if (m_Collider->CheckCollisions(m_SceneIBelongTo->GetTileMap()))
    {
        m_Collider->ResolveCollision(m_MoveDirection);
    }

    m_Transform.Position += m_MoveDirection * deltatime / 5;

    
    
}

void AI::Render()
{

    Vector2Int LeftPos = m_Transform.Position - 32;
    Vector2Int RightPos = m_Transform.Position + 32;
    //App::DrawQuad((float)LeftPos.x, (float)LeftPos.y, (float)RightPos.x, (float)RightPos.y, 0.5f, 0.5f, 0.5f);
    App::DrawQuad(LeftPos, RightPos, Vector3(1, 0, 0));
    m_Collider->DebugDrawCollider();

    
}

void AI::OnEvent(Event * sEvent)
{
   

}

void AI::SetPosition(Vector2 pos)
{
}

bool AI::IsAtDestination()
{
    // If close to destination, pick a new destination.
    float distanceFromDestination = (m_Destination - m_Transform.Position).GetLength();
    if (distanceFromDestination < 0.1f)
    {
        return true;
    }

    return false;
}

void AI::SetNextDestination()
{
    m_Destination = m_Transform.Position;

    int currentileIndex = -1;
    int nextTileIndex = -1;

    Vector2Int currentTilePos = m_SceneIBelongTo->GetTileMap().GetTilePosForWorldPos(Vector2(m_Destination.x, m_Destination.y));


    bool pathFound = m_PathFinder->FindPath(currentTilePos.x, currentTilePos.y, m_FinalTileDestination.x, m_FinalTileDestination.y);
    int bp = 0;

    if (pathFound)
    {
        int path[255];
        int length = m_PathFinder->GetPath(path, 255, m_FinalTileDestination.x, m_FinalTileDestination.y);

        if (length > 1)
        {
            currentileIndex = path[length - 1];
            nextTileIndex = path[length - 2];

            m_Destination = m_SceneIBelongTo->GetTileMap().GetWorldPosForTileIndex(nextTileIndex);
        }
        {
            m_Destination = Vector2Int(m_SceneIBelongTo->GetTileMap().GetWorldPosForTilePos(currentTilePos).x, m_SceneIBelongTo->GetTileMap().GetWorldPosForTilePos(currentTilePos).y);
            m_FinalTileDestination = currentTilePos;
        }
    }
}
