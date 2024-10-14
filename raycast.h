#pragma once

struct hitInfo {
	bool wasHit;
	Vector2 hitPos;
	float distance;
};

hitInfo ray(Vector2 startPos, Vector2 endPos, int* tilemap);					// Primitatve Raycast

hitInfo ray(Vector2 startPos, float angle, float distance, int* tilemap);		// Proper Raycast