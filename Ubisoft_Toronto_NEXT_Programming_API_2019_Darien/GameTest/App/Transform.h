#pragma once
#include "Vector.h"


// Transform class that holds and objects Position, Scale and Rotation.
class ObjectTransform
{
   


public:


    // override 
    ObjectTransform()
    {
      
        Position = Vector2Int().Zero();
        Rotation = Vector2(1, 1);
        Scale = Vector2(1, 1);
    }
    ObjectTransform( Vector2Int pos)
    {
       
        Position = pos;
        Rotation = Vector2(1, 1);
        Scale = Vector2(1, 1);
    }
    ObjectTransform(Vector2Int pos, Vector2 rot)
    {
      
        Position = pos;
        Rotation = rot;
        Scale = Vector2(1, 1);
    }
    ObjectTransform( Vector2Int pos, Vector2 rot, Vector2 scale)
    {
       
        Position = pos;
        Rotation = rot;
        Scale = scale;

    }

    Vector2Int Position;
    Vector2 Rotation;
    Vector2 Scale;
    
};