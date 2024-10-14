#pragma once

#include "Global.h"

void rayRender(Vector2 startPos, Vector2 endPos, int* tilemap);

void rayHitRender(Vector2 startPos, Vector2 endPos, int* tilemap);

void setRayTarget(Vector2 rayStartPos, Vector2 rayEndPos, int* tilemap);

void rayFOV(Vector2 startPos, float viewAngle, int* tilemap);