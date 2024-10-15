#pragma once

#include "Global.h"

void rayRender(Vector2 startPos, Vector2 endPos, int tilemap[mapX][mapY]);

void rayHitRender(Vector2 startPos, Vector2 endPos, int tilemap[mapX][mapY]);

void setRayTarget(Vector2 rayStartPos, Vector2 rayEndPos, int tilemap[mapX][mapY]);

void rayFOV(Vector2 startPos, float viewAngle, int tilemap[mapX][mapY]);