#pragma once

#include "Global.h"

void rayRender(Vector2 startPos, Vector2 endPos, int tilemap[mapX][mapY]);

void rayHitRender(Vector2 startPos, Vector2 endPos, int tilemap[mapX][mapY]);

void setRayTarget(Vector2 rayStartPos, Vector2 rayEndPos, int tilemap[mapX][mapY]);

void rayFOV(Vector2 startPos, float viewAngle, int tilemap[mapX][mapY]);

// Mini Dev Log Part 1
// By: Nebula
// Date: 10/21/2024
// Type int and state bool are disanbled until sprite rendering prototyping is complete.
// What's currently being tested is drawing a green square to the rendered output, based on the position of the item entity in the tile map.
// the Update void will be used later on to detetced the Emeny's angle to decided 1 out od the 8 rotational sprite. 
// (Side note: Items could also have rotational sprites?)

#ifndef sprite data
struct sprite {
	//int type;													// Enemy, Item, Key ect
	//bool state;												// should the sorite be rendered or not
	Vector3 position{ position.x, position.y, position.z };		// Sprites position within the sudo-3D renderer

	inline Vector2 getPosition2D() {
		return Vector2{ position.x, position.y };
	}

	void Update();

	sprite(Vector3 pos);
};
#endif // !sprite data