#include "Global.h"
#include "raycast.h"

void setRayTarget( Vector2 rayStartPos, Vector2 rayEndPos, int tilemap[mapX][mapY])
{
	hitInfo rayTarget = ray(rayStartPos, rayEndPos, tilemap);
}

void rayRender( Vector2 startPos, Vector2 endPos, int tilemap[mapX][mapY])
{
	hitInfo hit = ray(startPos, endPos, tilemap);

	if (hit.wasHit == true) {
		DrawLineEx(startPos, hit.hitPos, 3, GREEN);

		DrawLineV(endPos, hit.hitPos, YELLOW);
	}

	else {
		DrawLineV(startPos, endPos, RED);
	}
}

void rayHitRender(Vector2 startPos, Vector2 endPos, int tilemap[mapX][mapY])
{
	hitInfo hitRender = ray(startPos, endPos, tilemap);

	if (hitRender.wasHit == true)
	{
		DrawCircle(hitRender.hitPos.x, hitRender.hitPos.y, 5, PURPLE);
	}

	else
	{
		DrawCircle(hitRender.hitPos.x, hitRender.hitPos.y, 5, GRAY);
	}
}

#ifndef rayFOV
	void rayFOV(Vector2 startPos, float viewAngle, int tilemap[mapX][mapY])
	{
		const float FOV = 90.0f;							// Field of Vision
		const float DPP = FOV / RayRenderOutputWidth;		// Degrees Per-Pixel
		const float VA = viewAngle;							// View Angle
		const float VL = VA + FOV / 2.0f;					// View Left
		const float VR = VA - FOV / 2.0f;					// View Right

		for (int x = 0; x < RayRenderOutputWidth; x++)
		{
			const float PA = VL - x * DPP;										// Current Pixel Angle
			const float RPA = VA - PA;											// Reletive Pixel Angle

			const hitInfo hit = ray(startPos, PA, 1000.0f, tilemap);			// the Raycasts that will be used to draw the floors, walls and ceilings
			const float ratio = hit.distance / RaycasterMaxFogDistance;			// Fog distance away from the Player in Pixels
			const float correctedDistance = hit.distance * cos(toRad(RPA));		// fish eye lens effect fix

			if (hit.distance == 0) 
			{
				continue;
			}

			const float midPoint = lerp(RayRenderOutputHeight / 2, RayRenderOutputHeight, 50 / correctedDistance);		// middle and the horizon line the rendered output
			const float midPointClamped = clamp(RayRenderOutputHeight / 2.0f, RayRenderOutputHeight, midPoint);			// prevent the walls from going too far down
			const float midPointCeiling = RayRenderOutputHeight - midPointClamped;										// middle point for the ceiling because it was too low ...

			Vector2 lineStart { RayRenderOutputX + x, RayRenderOutputHeight };
			Vector2 lineMiddle{ RayRenderOutputX + x, midPointClamped };
			Vector2 lineMiddleCeiling{ RayRenderOutputX + x, midPointCeiling };
			Vector2 lineEnd{ RayRenderOutputX + x, 0 };

			Color wallColor = grayScale(1 - clamp(0, 1, ratio));		// This is what's Used to create the fog effect on the walls
			Color floorColor = DARKGREEN;
			Color ceilingColor = DARKBLUE;

			DrawLineV(lineMiddle, lineStart, floorColor);				// Draw the Floor
			DrawLineV(lineMiddle, lineEnd, wallColor);					// Draw the Walls
			DrawLineV(lineMiddleCeiling, lineEnd, ceilingColor);		// Draw the ceiling
		}

#ifndef DEBUG
		// Debug Lines
		DrawLineV(startPos, startPos + directionVector(VL) * RaycasterMaxFogDistance, GREEN);
		DrawLineV(startPos, startPos + directionVector(VR) * RaycasterMaxFogDistance, RED);
		DrawLineV(startPos, startPos + directionVector(VA) * RaycasterMaxFogDistance, BLUE);
#endif // DEBUG
	}
#endif // rayFOV