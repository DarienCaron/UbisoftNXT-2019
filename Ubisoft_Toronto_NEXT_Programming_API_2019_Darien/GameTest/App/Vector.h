#pragma once
// Vector Helper class to help deal with game logic.
// Vector2 deals in floats
#include "MathHelper.h"


class Vector2
{
public:
    float x;
    float y;

public:


    Vector2() {}
    Vector2(float tx, float ty) { x = tx;  y = ty; }
    Vector2(float xy) { x = xy;  y = xy; }

    inline void SetVector(float tx, float ty) { x = tx; y = ty; }
    inline float GetLengthSquared() const { return ((x * x) + (y * y)); }
    inline float GetLength() const { float len = GetLengthSquared(); return sqrt(len); }

    inline bool operator ==(const Vector2& o) const { return abs(this->x - o.x) <= EPSILON && abs(this->y - o.y) <= EPSILON; } // EPSILON is found in the MyMathHelper header.
    inline bool operator !=(const Vector2& o) const { return !abs(this->x - o.x) <= EPSILON || !abs(this->y - o.y) <= EPSILON; }

    inline Vector2 GetNormalized() const { float len = GetLength();  if (abs(len - 0) <= EPSILON) return Vector2(x, y); len = 1.0f / len; return Vector2(x * len, y * len); }
    inline Vector2 Normalize() { float len = GetLength(); if (!abs(len - 0) <= EPSILON) { this->x /= len; this->y /= len; } return *this; }

    inline Vector2 operator -() const { return Vector2(-this->x, -this->y); }

    inline Vector2 operator *(const float o) const { return Vector2(this->x * o, this->y * o); }
    inline Vector2 operator -(const float o) const { return Vector2(this->x - o, this->y - o); }
    inline Vector2 operator /(const float o) const { return Vector2(this->x / o, this->y / o); }
    inline Vector2 operator +(const float o) const { return Vector2(this->x + o, this->y + o); }


    inline Vector2 operator *(const Vector2& o) const { return Vector2(this->x * o.x, this->y * o.y); }
    inline Vector2 operator -(const Vector2& o) const { return Vector2(this->x - o.x, this->y - o.y); }
    inline Vector2 operator /(const Vector2& o) const { return Vector2(this->x / o.x, this->y / o.y); }
    inline Vector2 operator +(const Vector2& o) const { return Vector2(this->x + o.x, this->y + o.y); }

    inline Vector2 operator -=(const Vector2& o) { this->x -= o.x; this->y -= o.y; return *this; }
    inline Vector2 operator +=(const Vector2& o) { this->x += o.x; this->y += o.y; return *this; }
    inline Vector2 operator /=(const Vector2& o) { this->x /= o.x; this->y /= o.y; return *this; }
    inline Vector2 operator *=(const Vector2& o) { this->x *= o.x; this->y *= o.y; return *this; }

    inline Vector2 operator -=(const float o) { this->x -= o; this->y -= o; return *this; }
    inline Vector2 operator +=(const float o) { this->x += o; this->y += o; return *this; }
    inline Vector2 operator /=(const float o) { this->x /= o; this->y /= o; return *this; }
    inline Vector2 operator *=(const float o) { this->x *= o; this->y *= o; return *this; }


    inline Vector2 Left() const { return Vector2(-1, 0); }
    inline Vector2 Right() const { return Vector2(1, 0); }
    inline Vector2 Up() const { return Vector2(0, 1); }
    inline Vector2 Down() const { return Vector2(0, -1); }
    inline Vector2 Zero() const { return Vector2(0, 0); }


    inline float DotProduct(const Vector2& o) const { return this->x * o.x + this->y * o.y; }







};




// Vector2Int
// This will be used for game logic seeing as it is grid based movement.
class Vector2Int
{
public:
    int x;
    int y;

public:


    Vector2Int() {}
    Vector2Int(int tx, int ty) { x = tx;  y = ty; }
    Vector2Int(int xy) { x = xy;  y = xy; }

    inline void SetVector(int tx, int ty) { x = tx; y = ty; }
    inline float GetLengthSquared() const { return ((x * x) + (y * y)); }
    inline float GetLength() const { float len = GetLengthSquared(); return sqrt(len); }

    inline bool operator ==(const Vector2Int& o) const { return this->x == o.x && this->y == o.y; }
    inline bool operator !=(const Vector2Int& o) const { return this->x != o.x || this->y != o.y; }

    inline Vector2Int GetNormalized() const { float len = GetLength();  if (abs(len - 0) <= EPSILON) return Vector2Int(x, y); len = 1.0f / len; return Vector2Int(x * len, y * len); }
    inline Vector2Int Normalize() { float len = GetLength(); if (!abs(len - 0) <= EPSILON) { this->x /= len; this->y /= len; } return *this; }

    inline Vector2Int operator -() const { return Vector2Int(-this->x, -this->y); }

    inline Vector2Int operator *(const int o) const { return Vector2Int(this->x * o, this->y * o); }
    inline Vector2Int operator -(const int o) const { return Vector2Int(this->x - o, this->y - o); }
    inline Vector2Int operator /(const int o) const { return Vector2Int(this->x / o, this->y / o); }
    inline Vector2Int operator +(const int o) const { return Vector2Int(this->x + o, this->y + o); }


    inline Vector2Int operator *(const Vector2Int& o) const { return Vector2Int(this->x * o.x, this->y * o.y); }
    inline Vector2Int operator -(const Vector2Int& o) const { return Vector2Int(this->x - o.x, this->y - o.y); }
    inline Vector2Int operator /(const Vector2Int& o) const { return Vector2Int(this->x / o.x, this->y / o.y); }
    inline Vector2Int operator +(const Vector2Int& o) const { return Vector2Int(this->x + o.x, this->y + o.y); }

    inline Vector2Int operator -=(const Vector2Int& o) { this->x -= o.x; this->y -= o.y; return *this; }
    inline Vector2Int operator +=(const Vector2Int& o) { this->x += o.x; this->y += o.y; return *this; }
    inline Vector2Int operator /=(const Vector2Int& o) { this->x /= o.x; this->y /= o.y; return *this; }
    inline Vector2Int operator *=(const Vector2Int& o) { this->x *= o.x; this->y *= o.y; return *this; }

    inline Vector2Int operator -=(const int o) { this->x -= o; this->y -= o; return *this; }
    inline Vector2Int operator +=(const int o) { this->x += o; this->y += o; return *this; }
    inline Vector2Int operator /=(const int o) { this->x /= o; this->y /= o; return *this; }
    inline Vector2Int operator *=(const int o) { this->x *= o; this->y *= o; return *this; }


    inline Vector2Int Left() const { return Vector2Int(-1, 0); }
    inline Vector2Int Right() const { return Vector2Int(1, 0); }
    inline Vector2Int Up() const { return Vector2Int(0, 1); }
    inline Vector2Int Down() const { return Vector2Int(0, -1); }
    inline Vector2Int Zero() const { return Vector2Int(0, 0); }


    inline float DotProduct(const Vector2Int& o) const { return (float)this->x * o.x + this->y * o.y; }







};


class Vector3
{
public:
    float x;
    float y;
    float z;

public:
    Vector3() {}
    Vector3(float tx, float ty, float tz) { x = tx;  y = ty; z = tz; }
    Vector3(float xyz) { x = xyz;  y = xyz; z = xyz; }


};