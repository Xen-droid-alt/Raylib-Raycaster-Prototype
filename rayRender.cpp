#include "Global.h"
#include "rayRender.h"
#include "raycast.h"
#include "Entity.h"

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

#ifndef sprite code
sprite::sprite(Vector3 position) : position(position)
{
	// Sprite Struct
}

Vector3 itemPos = { 
	itemPos.x = itemXPos,
	itemPos.y = itemYPos,
	itemPos.z = 0 };		// Sprite x, y and z position 

sprite itemSprite{ itemPos };		// Sprite Entity
#endif // !sprite code

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
#ifndef wallSegment

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
#endif // !wallSegment
		}

#ifndef sprite draw
		// Mini Dev Log Part 2
		// By: Nebula
		// Date: 10/21/2024
		// Refactor time! Part 2!
		// New Sprite rendering code will use Dot Products! x3
		// The old code was not very good. I hated it.

		const float spriteDist = vectorLength(itemSprite.getPosition2D() - startPos);		// Hacky Sprite Distance...

		const Vector2 vecVS = normalizedVector(itemSprite.getPosition2D() - startPos);		// View Sprite
		const Vector2 vecVAP = directionVector(viewAngle + 90.0f);							// Rotate View Angle by 90 Degrees...
		const Vector2 vecVA = directionVector(viewAngle);							
		const Vector2 vecVL = directionVector(VL);

		// Dot Products
		const float DS = dot(vecVAP, vecVS);		// Dot Sprite Direction Horizontal
		const float DSF = dot(vecVA, vecVS);		// Dot View Sprite Forward
		const float DL = dot(vecVAP, vecVL);		// Dot View Left
		const float DR = -DL;						// Dot View Right

		if (DSF > 0 && DS < DL && DS > DR)			// Occlusion Culling for Sprites. Only draw the srpite if it's within range of the sudo-3D rendered Output.
		{
			const float pixelX = remap(DL, DR, DS, 0, RayRenderOutputWidth);

			DrawRectangleV(
				{ RayRenderOutputX + pixelX, RayRenderOutputHeight / 2 },
				{2000 / spriteDist, 2000 / spriteDist},
				GREEN
			);
		}
#endif	

#ifndef DEBUG
		// Debug Lines
		DrawLineV(startPos, startPos + directionVector(VL) * RaycasterMaxFogDistance, GREEN);
		DrawLineV(startPos, startPos + directionVector(VR) * RaycasterMaxFogDistance, RED);
		DrawLineV(startPos, startPos + directionVector(VA) * RaycasterMaxFogDistance, BLUE);
#endif // DEBUG
	}
#endif // rayFOV

