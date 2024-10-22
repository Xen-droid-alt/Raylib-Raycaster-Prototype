#pragma once

#include "raylib.h"
#include "raymath.h"

#include <math.h>

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//#include <tuple>
//#include <utility>
//#include <memory>
#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <cmath>

#define resWidth	1800
#define resHeight	900

// Map related Definitions
//------------------------------------------------------------------------------------
#define mapX	40
#define mapY	40
#define mapS	16
//------------------------------------------------------------------------------------

// Raycaster Definitions
//------------------------------------------------------------------------------------
#define RayRenderOutputWidth		640
#define RayRenderOutputHeight		480
#define RayRenderOutputX			mapS*mapX+60
#define RaycasterOutputY			0

#define RaycasterMaxFogDistance		400.0f
//------------------------------------------------------------------------------------

// Player related Definitions
//------------------------------------------------------------------------------------
#define playerStartXPos		26 * mapS
#define playerStartYPos		36 * mapS
#define playerSize			10
#define playerSpeed			2
#define playerTurnSpeed		2.5f
//------------------------------------------------------------------------------------

// Item related Definitions
//------------------------------------------------------------------------------------
#define itemXPos			8 * mapS
#define itemYPos			11 * mapS
#define itemSize			10
//------------------------------------------------------------------------------------

// Enemy related Definitions
//------------------------------------------------------------------------------------
#define enemyXPos			15 * mapS
#define enemyYPos			27 * mapS
#define enemySize			20
#define enemySpeed			2
//------------------------------------------------------------------------------------

// Math operators
//------------------------------------------------------------------------------------
#define PI 3.1415926535
#define P2 PI/2
#define P3 3*PI/2

// Directions
//------------------------------------------------------------------------------------
#define North 0.f
#define Northeast 45.f
#define East 90.f
#define Southeast 135.f
#define South 180.f
#define Southwest 225.f
#define West 270.f
#define Northwest 315.f

inline Vector2 operator/ (Vector2 v, float divide)		//special operator that adds division to Vector 2
{
	Vector2 result; 
	result.x = v.x / divide;
	result.y = v.y / divide;
	return result;
}

inline Vector2 operator+ (Vector2 v, Vector2 add)		//special operator that adds addition to Vector 2
{
	Vector2 result;
	result.x = v.x + add.x;
	result.y = v.y + add.y;
	return result;
}

inline Vector2 operator- (Vector2 v, Vector2 subtract)		//special operator that adds subtraction to Vector 2
{
	Vector2 result;
	result.x = v.x - subtract.x;
	result.y = v.y - subtract.y;
	return result;
}

inline Vector2 operator* (Vector2 v, float Multiply)		//special operator that adds Multiplcation to Vector 2
{
	Vector2 result;
	result.x = v.x * Multiply;
	result.y = v.y * Multiply;
	return result;
}

inline float vectorLength(Vector2 v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

inline Vector2 normalizedVector(Vector2 v)
{
	// normalized vector = any value between -1 and 1.
	if (v.x == 0 && v.y == 0)
	{
		return v;
	}

	const float length = vectorLength(v);

	Vector2 result;
	result.x = v.x / length;
	result.y = v.y / length;
	return result;
}

inline float toRad(float degrees)			// Degrees to Radians 
{
	return (degrees / 180.0f) * PI;
}
inline float toDeg(float radians)			// Radians to Degrees
{
	return (radians / PI) * 180.0f;
}

inline Vector2 directionVector(float angle)
{
	Vector2 result;

	const float angleInRadians = toRad(angle);

	result.x = cos(angleInRadians);
	result.y = -sin(angleInRadians);

	return result;
}

template < class T >
inline T lerp(T a, T b, float alpha)
{
	return a * (1 - alpha) + b * alpha;
}

inline Color grayScale(float value) 
{
	unsigned char byteValue = value * 255;

	return { byteValue, byteValue, byteValue, 255};
}

#ifdef colorScale
inline Color colorScale(float value1, float value2, float value3, float transparancy)
{
	unsigned char byteValue1 = value1 * 255;
	unsigned char byteValue2 = value2 * 255;
	unsigned char byteValue3 = value3 * 255;
	unsigned char byteValue4 = brightness * 255;

	return { byteValue1, byteValue2, byteValue3, byteValue4 };
}
#endif // !colorScale

inline Vector2 renderFlipped(Vector2 value)
{
	value.y = mapY * mapS - value.y;

	return value;
}

inline float clamp(float minimum, float maximum, float value)
{
	if (value > maximum)
	{
		return maximum;
	}

	if (value < minimum)
	{
		return minimum;
	}

	return value;
}

inline float dot(Vector2 v1, Vector2 v2)	// Dot Product
{
	return v1.x * v2.x + v1.y * v2.y;
}

inline float remap(float minimum, float maximum, float value, float Rmin, float Rmax)
{
	const float range = maximum - minimum;
	const float nValue = 1 - ((maximum - value) / range);

	return lerp(Rmin, Rmax, nValue);
}
//------------------------------------------------------------------------------------
