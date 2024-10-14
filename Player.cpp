#include "Global.h"
#include "player.h"
#include "raycast.h"
#include "rayRender.h"

player PlayerData(Vector2 playerPos)
{
    Vector2 playerPosition = { playerPos.x, playerPos.y };

    player result = {
        playerPos
    };

    return result;
}

void drawPlayer( Vector2 playerPos ) 
{
    player playerDrawData = PlayerData(playerPos);

    DrawRectangleV(
        { playerPos.x, playerPos.y },
        { playerSize, playerSize },
        RED
    );     //This is our player...
}
