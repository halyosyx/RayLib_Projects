#include "raylib.h"
#include <cstdio>
#include "stdlib.h"

const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 640;
const char *TITLE = "Raylib Tutorial 1";

bool CheckCollisionBetweenObjects(Vector2 obj1, int obj1Radius, Vector2 obj2, int obj2Radius)
{

    // player Collider
    int l_circle_x = obj1.x - obj1Radius;
    int r_circle_x = obj1.x + obj1Radius;
    int u_circle_y = obj1.y - obj1Radius;
    int b_circle_y = obj1.y + obj1Radius;

    int l_box_x = obj2.x;
    int r_box_x = obj2.x + obj2Radius;
    int u_box_y = obj2.y;
    int b_box_y = obj2.y + obj2Radius;

    if (b_box_y >= u_circle_y && u_box_y <= b_circle_y && l_box_x <= r_circle_x && r_box_x >= l_circle_x)
    {
        return true;
    }
    
    return false;    
}

int main()
{
    InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,TITLE);
    SetTargetFPS(60);

    bool collisionWithAxe = false;

    Vector2 playerPosition;
    playerPosition.x = SCREEN_WIDTH / 2;
    playerPosition.y = SCREEN_HEIGHT - 100;
    float playerRadius = 25;
    float playerSpeed = 5;

    Vector2 EnemyPos;
    EnemyPos.x = 0;
    EnemyPos.y = 250;

    float axeLength = 50;
    float enemySpeed = 5;


    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(GRAY);

        if (collisionWithAxe)
        {
            DrawText("Game Over", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 30, RED);
        }
        else
        {
            collisionWithAxe = CheckCollisionBetweenObjects(playerPosition, playerRadius, EnemyPos, axeLength);

            DrawCircle(playerPosition.x,playerPosition.y, playerRadius, BLUE);
            DrawRectangle(EnemyPos.x,EnemyPos.y,axeLength,axeLength,RED);

            if (IsKeyDown(KEY_D) && playerPosition.x <= SCREEN_WIDTH)
            {
                playerPosition.x += playerSpeed;
            }
            else if (IsKeyDown(KEY_A) && playerPosition.x >= 0)
            {
                playerPosition.x -= playerSpeed;
            }

            if (IsKeyDown(KEY_W) && playerPosition.y >= 0)
            {
                playerPosition.y -= playerSpeed;
            }
            else if (IsKeyDown(KEY_S) && playerPosition.y <= SCREEN_HEIGHT)
            {
                playerPosition.y += playerSpeed;
            }

            EnemyPos.x += enemySpeed;

            if (EnemyPos.x > SCREEN_WIDTH || EnemyPos.x < 0)
            {
                enemySpeed = -enemySpeed;
            }
        }
        
        EndDrawing();
    }
    
}

