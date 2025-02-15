/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2024 Ramon Santamaria (@raysan5)
*   
*   
*   The simplest possible build command
*   
*   cc game.c -lraylib -lGL -lm -lpthread -ldl -lrt
*
********************************************************************************************/

#include <stdio.h>
#include "raylib.h"

#define CUTE_TILED_IMPLEMENTATION
#include "cute_tiled.h"

//#define NULL (void *)0

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 400;

    InitWindow(screenWidth, screenHeight, "Runner - Game");

    cute_tiled_map_t* map = cute_tiled_load_map_from_file("test_cute_tiled/test_cute_tiled.json", NULL);

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

    Texture2D skyBGTexture = LoadTexture("graphics/Sky.png");        // Texture loading
    Texture2D groungBGTexture = LoadTexture("graphics/ground.png");
    Texture2D snail = LoadTexture("graphics/snail/snail1.png");
    Texture2D player = LoadTexture("graphics/Player/player_walk_1.png");

    float snailXPos = 600.f;

    // Source rectangle (part of the texture to use for drawing)
    Rectangle sourceRec_skyBGTexture = { 0.0f, 0.0f, (float)skyBGTexture.width, (float)skyBGTexture.height };
    // Destination rectangle (screen rectangle where drawing part of texture)
    Rectangle destRec_skyBGTexture = { 0.0f, 0.0f, (float)skyBGTexture.width, (float)skyBGTexture.height };
    // Origin of the texture (rotation/scale point), it's relative to destination rectangle size
    Vector2 origin_skyBGTexture = { 0.f, 0.f };

    Rectangle sourceRec_groungBGTexture = { 0.f, 0.f, (float)groungBGTexture.width, (float)groungBGTexture.height };
    Rectangle destRec_groungBGTexture = { 0.f, (float)skyBGTexture.height, (float)groungBGTexture.width, (float)groungBGTexture.height };
    Vector2 origin_groungBGTexture = { 0.f, 0.f };

    Rectangle sourceRec_snail = { 0.f, 0.f, (float)snail.width, (float)snail.height };
    Rectangle destRec_snail = { snailXPos, (float)(destRec_groungBGTexture.y - snail.height), (float)snail.width, (float)snail.height };
    Vector2 origin_snail = { 0.f, 0.f };

    Rectangle sourceRec_player = { 0.f, 0.f, (float)player.width, (float)player.height };
    Rectangle destRec_player = { 30.f, ((float)destRec_groungBGTexture.y - player.height), (float)player.width, (float)player.height };
    //Vector2 origin_player = { (float)player.width/2, (float)player.height };
    Vector2 origin_player = { 0.f, 0.f };



    Font testFont = LoadFont("font/Pixeltype.ttf");
    char * scoreText = "Congrats! You created your first window!";
    Vector2 fontPos = {screenWidth/2.f - MeasureTextEx(testFont, scoreText, 20.f, 1.f).x / 2.f, 50};

    bool collision = false;
    Vector2 mousePos = {0.f, 0.f};


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        collision = false;
        mousePos = GetMousePosition();

        destRec_snail.x = snailXPos;
        snailXPos -= 4.f;

        if ((snailXPos + snail.width) < 0) {
            snailXPos = screenWidth;
        }

        if (CheckCollisionPointRec(mousePos, destRec_player)) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                collision = true;
            }
        } else if (CheckCollisionRecs(destRec_player, destRec_snail)) {
            collision = true;
        }
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // NOTE: Using DrawTexturePro() we can easily rotate and scale the part of the texture we draw
            // sourceRec defines the part of the texture we use for drawing
            // destRec defines the rectangle where our texture part will fit (scaling it to fit)
            // origin defines the point of the texture used as reference for rotation and scaling
            // rotation defines the texture rotation (using origin as rotation point)
            DrawTexturePro(skyBGTexture, sourceRec_skyBGTexture, destRec_skyBGTexture, origin_skyBGTexture, 0.f, WHITE);
            DrawTexturePro(groungBGTexture, sourceRec_groungBGTexture, destRec_groungBGTexture, origin_groungBGTexture, 0.f, WHITE);
            DrawTexturePro(snail, sourceRec_snail, destRec_snail, origin_snail, 0.f, WHITE);
            DrawTexturePro(player, sourceRec_player, destRec_player, origin_player, 0.f, WHITE);

            if (collision) {
                DrawTextEx(testFont, "Congrats! You created your first window!", fontPos, 20.f, 1.f, LIGHTGRAY);
            }



        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(skyBGTexture);
    UnloadTexture(groungBGTexture);
    UnloadTexture(snail);
    UnloadTexture(player);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}