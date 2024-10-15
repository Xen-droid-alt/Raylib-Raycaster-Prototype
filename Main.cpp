#include "Global.h"
#include "raycast.h"
#include "rayRender.h"
#include "player.h"

#ifndef worldMap

int worldMap[mapX][mapY]=         //Map Tiles (now a 2D Array after refactoring. Thx Lancy~ x3)
{
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,
    1,0,0,0,1,0,0,1,1,0,1,0,1,0,1,1,1,0,1,1,
    1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,
    1,0,0,1,1,0,0,1,1,0,0,0,0,0,1,1,0,0,0,1,
    1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,
    1,0,0,0,1,0,0,1,1,0,0,0,0,0,1,1,0,0,0,1,
    1,1,0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,
    1,1,0,0,1,0,0,1,1,0,0,0,0,0,1,1,0,0,0,1,
    1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,0,0,0,0,0,1,1,0,1,1,0,0,1,1,0,1,1,
    1,0,1,0,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,1,
    1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,1,1,0,1,1,1,0,0,0,1,1,1,1,0,0,0,1,
    1,0,1,0,0,0,0,0,1,1,0,1,1,0,0,1,1,0,1,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};
#endif

void drawMap2D()
{
    int x, y;
    for (x = 0; x < mapX; x++)
    {
        for (y = 0; y < mapY; y++)
        {
            DrawRectangle(
                x * mapS,
                y * mapS,
                mapS,
                mapS,
                (worldMap[x][y] == 1) ? WHITE : Fade(BLACK, 0.9f)
            );

            DrawRectangleLines(
                x * mapS,
                y * mapS,
                mapS,
                mapS,
                Fade(GRAY, 0.5f)
            );
        }
    }
}

Vector2 playerStartPosition = { playerStartXPos, playerStartYPos };
float playerAngle = 40.0f;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = resWidth;
    const int screenHeight = resHeight;

    InitWindow(screenWidth, screenHeight, "raylib raycaster prototype [Alpha Version: 0.00 Ceiling Update]");

    int playerTileX = 0;
    int playerTileY = 0;

    int mouseTileX = 0;
    int mouseTileY = 0;

    int rayTileX = 0;
    int rayTileY = 0;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

#ifndef Update
        //----------------------------------------------------------------------------------
        // 
        //---------------------------------------------------------------------------------- 
        // 
        // Player Movement
        //----------------------------------------------------------------------------------
        const Vector2 viewDirection = directionVector(playerAngle);
        const Vector2 viewDirectionSide = directionVector(playerAngle + 90.0f);

        // Strafe Left
        if (IsKeyDown(KEY_A))
        {
            playerStartPosition = playerStartPosition + viewDirectionSide * playerSpeed;
        }

        // Strafe Right
        if (IsKeyDown(KEY_D))
        {
            playerStartPosition = playerStartPosition - viewDirectionSide * playerSpeed;
        }

        // Move Forward
        if (IsKeyDown(KEY_W))
        {
            playerStartPosition = playerStartPosition + viewDirection * playerSpeed;
        }

        // Backpedal
        if (IsKeyDown(KEY_S))
        {
            playerStartPosition = playerStartPosition - viewDirection * playerSpeed;
        }

        // Look Left
        if (IsKeyDown(KEY_LEFT))
        {
            playerAngle += playerTurnSpeed;
        }

        // Look Right
        if (IsKeyDown(KEY_RIGHT))
        {
            playerAngle -= playerTurnSpeed;
        }
        //----------------------------------------------------------------------------------

        //
        // Player and Mouse Tile Position
        //----------------------------------------------------------------------------------
        playerTileX = (int)((playerStartPosition.x + mapS) / mapS);
        playerTileY = (int)((playerStartPosition.y + mapS) / mapS);

        Vector2 mousePosition = { float(GetMouseX()), float(GetMouseY()) };
        mouseTileX = (int)((mousePosition.x + mapS) / mapS);
        mouseTileY = (int)((mousePosition.y + mapS) / mapS);
        //----------------------------------------------------------------------------------

        // Raycasting for Tile Position
        //----------------------------------------------------------------------------------
        hitInfo rayCastHitPos = ray(playerStartPosition, mousePosition, worldMap);

        rayTileX = (int)((rayCastHitPos.hitPos.x + mapS) / mapS);
        rayTileY = (int)((rayCastHitPos.hitPos.y + mapS) / mapS);
        //----------------------------------------------------------------------------------

#endif // !Update

#ifndef Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(DARKGRAY);

            DrawText("Raycaster Prototype", 
                GetScreenWidth() - 250, 
                30, 
                20, 
                LIGHTGRAY);

            DrawText(TextFormat("Player Speed: %i", playerSpeed), 
                GetScreenWidth() - 250, 
                70, 
                20, 
                LIGHTGRAY);

            DrawText(TextFormat("Current Player Tile: [%i,%i]", playerTileX, playerTileY),
                GetScreenWidth() - 300, 
                100, 
                20, 
                LIGHTGRAY);

            DrawText(TextFormat("Current Mouse Tile: [%i,%i]", mouseTileX, mouseTileY), 
                GetScreenWidth() - 300, 
                140, 
                20, 
                LIGHTGRAY);

            DrawText(TextFormat(
                "Current Ray Tile: [%i,%i]", rayTileX, rayTileY),
                GetScreenWidth() - 300, 
                180, 
                20, 
                LIGHTGRAY);

            DrawText(
                "The Green Line: players Left-most view angle",
                GetScreenWidth() - 500,
                220,
                20,
                GREEN);

            DrawText(
                "The Red Line: players Right-most view angle",
                GetScreenWidth() - 500,
                260,
                20,
                RED);

            DrawText(
                "The Blue Line: players current view angle",
                GetScreenWidth() - 500,
                300,
                20,
                BLUE);

            DrawFPS(GetScreenWidth() - 95, 10);

            DrawRectangle(
                RayRenderOutputX, 
                RaycasterOutputY,
                RayRenderOutputWidth,
                RayRenderOutputHeight, 
                BLACK);     // This box represents the boundaries of the Raycast Renderer.

            DrawText("TODO: Add Sudo-3D here",  RayRenderOutputX * 2, 20, 20, GRAY);
            DrawText("whenever the Raycaster",  RayRenderOutputX * 2, 40, 20, GRAY);
            DrawText("Renderer is made",        RayRenderOutputX * 2, 60, 20, GRAY);

            DrawText("Current Raycasting System Progress:",     RayRenderOutputX * 2, 100, 20, LIGHTGRAY);
            DrawText("  * Rays have a start and End Pos",       RayRenderOutputX * 2, 120, 20, LIGHTGRAY);
            DrawText("  * Rays check for collsion",             RayRenderOutputX * 2, 140, 20, LIGHTGRAY);
            DrawText("  * Rays calculate distance from",        RayRenderOutputX * 2, 160, 20, LIGHTGRAY);
            DrawText("     their start to end Position",        RayRenderOutputX * 2, 180, 20, LIGHTGRAY);
            DrawText("  * Rays check if their source are",      RayRenderOutputX * 2, 200, 20, LIGHTGRAY);
            DrawText("     in bounds of the Tile Map",          RayRenderOutputX * 2, 220, 20, LIGHTGRAY);

#ifdef RenderTestRayCasts
            rayRender({ 10 * mapS, 10 * mapS }, playerStartPosition, worldMap);
            rayRender({ 11 * mapS, 10 * mapS }, playerStartPosition, worldMap);
            rayRender({ 12 * mapS, 10 * mapS }, playerStartPosition, worldMap);

            rayRender({ 10 * mapS, 11 * mapS }, playerStartPosition, worldMap);
            rayRender({ 11 * mapS, 11 * mapS }, playerStartPosition, worldMap);
            rayRender({ 12 * mapS, 11 * mapS }, playerStartPosition, worldMap);

            rayRender({ 10 * mapS, 12 * mapS }, playerStartPosition, worldMap);
            rayRender({ 11 * mapS, 12 * mapS }, playerStartPosition, worldMap);
            rayRender({ 12 * mapS, 12 * mapS }, playerStartPosition, worldMap);
#endif // RenderTestRayCasts

            drawMap2D();

            rayRender(playerStartPosition, mousePosition, worldMap);

            rayHitRender(playerStartPosition, mousePosition, worldMap);

            rayFOV(playerStartPosition, playerAngle, worldMap);

            drawPlayer(playerStartPosition);  //This is our player...

        EndDrawing();
    }
    //----------------------------------------------------------------------------------
#endif // !Draw

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL content
    //--------------------------------------------------------------------------------------

    return 0;
}