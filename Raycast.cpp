#include "Global.h"
#include "raycast.h"

// Raycast code from YouTuber javidx9
// Source: https://www.youtube.com/watch?v=NbSee-XM7WA&t=1421s
// Modifications: 
//				 *	Raycast algorithm checks to see if the source of the raycast itself is in bounds of the tilemap  

bool IsInBounds(Vector2 position)
{
	return position.x >= 0.0f
		&& position.x < mapX
		&& position.y >= 0.0f
		&& position.y < mapY;
}

int GetCellType(Vector2 position, int* tilemap)
{
	if (!IsInBounds(position))
	{
		return 1;
	}

	return tilemap[int(position.y) * mapX + int(position.x)];
}

hitInfo ray(Vector2 startPos, float angle, float distance, int* tilemap)
{
	Vector2 endPos = startPos + directionVector(angle) * distance;

	return ray(startPos, endPos, tilemap);
}

hitInfo ray( Vector2 startPos, Vector2 endPos, int* tilemap)
{

	Vector2 vMouseCell = endPos / float(mapS);

	// Form ray cast from it's source into scene
	Vector2 vRayStart = startPos / float(mapS);
	Vector2 vRayDir = Vector2Normalize(vMouseCell - vRayStart);

	if (GetCellType(vRayStart, tilemap) == 1)
	{
		hitInfo result = {
			false,
			startPos,
			0.0f,
		};

		return result;
	}

	Vector2 vRayUnitStepSize = {
	sqrt(
			 1 + (vRayDir.y / vRayDir.x) * (vRayDir.y / vRayDir.x)),
		sqrt(1 + (vRayDir.x / vRayDir.y) * (vRayDir.x / vRayDir.y))
	};
	Vector2 vMapCheck = { int(vRayStart.x), int(vRayStart.y) };
	Vector2 vRayLength1D;
	Vector2 vStep;

	// Establish Starting Conditions
	if (vRayDir.x < 0)
	{
		vStep.x = -1;
		vRayLength1D.x = (vRayStart.x - float(vMapCheck.x)) * vRayUnitStepSize.x;
	}
	else
	{
		vStep.x = 1;
		vRayLength1D.x = (float(vMapCheck.x + 1) - vRayStart.x) * vRayUnitStepSize.x;
	}

	if (vRayDir.y < 0)
	{
		vStep.y = -1;
		vRayLength1D.y = (vRayStart.y - float(vMapCheck.y)) * vRayUnitStepSize.y;
	}
	else
	{
		vStep.y = 1;
		vRayLength1D.y = (float(vMapCheck.y + 1) - vRayStart.y) * vRayUnitStepSize.y;
	}

	// Perform "Walk" until collision or range check
	bool bTileFound = false;
	float fMaxDistance = 100.0f;
	float fDistance = 0.0f;
	while (!bTileFound && fDistance < fMaxDistance)
	{
		// Walk along shortest path
		if (vRayLength1D.x < vRayLength1D.y)
		{
			vMapCheck.x += vStep.x;
			fDistance = vRayLength1D.x;
			vRayLength1D.x += vRayUnitStepSize.x;
		}
		else
		{
			vMapCheck.y += vStep.y;
			fDistance = vRayLength1D.y;
			vRayLength1D.y += vRayUnitStepSize.y;
		}

		// Test tile at new test point
		if (IsInBounds(vMapCheck))
		{
			if (GetCellType(vMapCheck, tilemap) == 1)
			{
				bTileFound = true;
			}
		}
	}

	// Calculate intersection location
	Vector2 vIntersection = {0,0};
	if (bTileFound)
	{
		vIntersection = vRayStart + vRayDir * fDistance;
	}

	hitInfo result = {
		bTileFound,
		vIntersection * mapS,
		fDistance * mapS, 
	};

	return result;
}