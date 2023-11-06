#include <cstdio>
#include <math.h>
#include "raylib.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 450;
const char* TITLE_NAME = "Warrior Runner";

// const int recWidth = 50;
// const int recHeight = 100;
// int recPosY = SCREEN_HEIGHT - recHeight;
const float gravity = 980.0;
const float jumpForce = -300.0;
const float updateTime = 1.0 / 12.0;

float velocity = 0;
float scale = 2;
float runTime = 0;
bool isGrounded;

Texture2D player;
Rectangle playerRect;
Vector2 playerPosition;

Texture2D enemy;
Rectangle enemyRect;
Vector2 enemyPosition;

float enemyVel = -400;

void DrawCharacterTexture(Texture2D texture, Rectangle source, Vector2 position, float textureScale, Color tint);
void RunAnimation(int *frame);

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE_NAME);
    SetTargetFPS(60);
    int frame = 0;
    player = LoadTexture("textures/WarriorRun.png");

    playerRect.width =  ((player.width) / 8);
    playerRect.height = player.height;
    playerRect.x = 0;
    playerRect.y = 0;

    playerPosition.x = (SCREEN_WIDTH / 2 - playerRect.width / 2) / 6;
    playerPosition.y = (SCREEN_HEIGHT - (playerRect.height * scale));


    enemy = LoadTexture("textures/Slime.png");
    enemyRect.width = enemy.width / 4;
    enemyRect.height = enemy.height;
    enemyRect.x = 0;
    enemyRect.y = 0;

    enemyPosition.x = (SCREEN_WIDTH / 2 - enemyRect.width / 2);
    enemyPosition.y = SCREEN_HEIGHT - (enemyRect.height * scale);

    while (!WindowShouldClose())
    {
        const float deltaTime = GetFrameTime();

        BeginDrawing();
        ClearBackground(GRAY);

        DrawCharacterTexture(player, playerRect, playerPosition, scale, WHITE);
        DrawCharacterTexture(enemy, enemyRect, enemyPosition, scale, WHITE);

        isGrounded = playerPosition.y >= (SCREEN_HEIGHT - (playerRect.height * scale));
        velocity = isGrounded ? 0 : velocity + (gravity * deltaTime);

        if (IsKeyPressed(KEY_SPACE) && isGrounded)
        {
            velocity += jumpForce;    
        }

        playerPosition.y += (velocity * deltaTime);
        enemyPosition.x += enemyVel * deltaTime;

        runTime += deltaTime;

        if (isGrounded)
        {
            if (runTime >= updateTime)
            {
                runTime = 0.0;

                playerRect.x = frame * playerRect.width;
                frame++;

                if (frame > 7)
                {
                    frame = 0;
                }
            }
        }
        else
        {
            
        }
        
        
        EndDrawing();
    }

    UnloadTexture(player); 
    UnloadTexture(enemy);
    CloseWindow();
    
}

void DrawCharacterTexture(Texture2D texture, Rectangle source, Vector2 position, float textureScale, Color tint)
{
    Rectangle dest = { position.x, position.y, fabsf(source.width * textureScale), fabsf(source.height * textureScale) };
    Vector2 origin = { 0.0f, 0.0f };

    DrawTexturePro(texture, source, dest, origin, 0.0f, tint);
}
