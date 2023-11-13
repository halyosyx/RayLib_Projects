#include <cstdio>
#include <math.h>
#include "raylib.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 397;
const char* TITLE_NAME = "Warrior Runner";

const float gravity = 980.0;
const float jumpForce = -300.0;
const float updateTime = 1.0 / 12.0;
const float enemyUpdateTime = 1.0/12.0;

float velocity = 0;
float scale = 2;
float runTime = 0;
float enemyRuntime = 0;
bool isGrounded;

float enemyVel = -200;

struct CharacterData
{
    Texture2D texture;
    Rectangle characterRect;
    Vector2 position;
    int frame;
    float runningTime;
    float updateTime;
};

struct BackGroundData
{
    Texture2D background;
    Vector2 position;
    float bgSpeed;
};


void DrawCharacterTexture(Texture2D texture, Rectangle source, Vector2 position, float textureScale, Color tint);
void SlimeEnemy(Texture2D texture, Rectangle rect, Vector2 position, int frame, float deltaTime);
bool GroundCheck(CharacterData characterData);
CharacterData UpdateData(CharacterData data,int maxFrame ,float deltaTime);
BackGroundData UpdateBackground(BackGroundData data, float deltaTime);

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE_NAME);
    SetTargetFPS(60);

    CharacterData player {
        {LoadTexture("textures/WarriorRun.png")},
        {0,0,player.texture.width / 8, player.texture.height},
        {(SCREEN_WIDTH / 2 - player.characterRect.width / 2) / 6, SCREEN_HEIGHT - (player.characterRect.height * scale)},
        0, 0, 1.0 / 12.0
    };

    CharacterData enemy {
        {LoadTexture("textures/Slime.png")}, 
        {0,0, (enemy.texture.width / 4), enemy.texture.height}, 
        {(SCREEN_WIDTH - enemy.characterRect.width / 2),SCREEN_HEIGHT - (enemy.characterRect.height * scale)}
        , 0, 0, 1.0 / 12.0
    };



    const int enemySize = 6;
    CharacterData enemies[enemySize] {};

    for (int i = 0; i < enemySize; i++)
    {
        enemies[i].texture = {LoadTexture("textures/Slime.png")};
        enemies[i].characterRect.x = 0;
        enemies[i].characterRect.y = 0;
        enemies[i].characterRect.width = (enemy.texture.width / 4);
        enemies[i].characterRect.height = enemy.texture.height;
        enemies[i].position.y = SCREEN_HEIGHT - (enemy.characterRect.height * scale);
        enemies[i].frame = 0;

        enemies[i].runningTime = 0;
        enemies[i].updateTime = 1.0 / 16.0;

        enemies[i].position.x = SCREEN_WIDTH + (200 * i);
    }
    
    BackGroundData FarBackground {
    {LoadTexture("textures/FarTrees.png")}, 
    {0.0, -FarBackground.background.height / 2}, 
    {20.0}};

    BackGroundData BackTreesBackground {
    {LoadTexture("textures/BackTrees.png")}, 
    {0.0, 0.0}, 
    {40.0}};

    BackGroundData Foreground {
    {LoadTexture("textures/Trees.png")}, 
    {0.0, 0.0}, 
    {80.0}};

    Texture2D background = LoadTexture("textures/FarTrees.png");
    Texture2D backTrees = LoadTexture("textures/BackTrees.png");
    Texture2D foreGround = LoadTexture("textures/Trees.png");

    float bgX {};
    Vector2 bgPosSpawnPosition = {background.width - 100, 0.0};

    while (!WindowShouldClose())
    {
        const float deltaTime = GetFrameTime();

        BeginDrawing();
        ClearBackground(GRAY);

        //bgX -= 20 * deltaTime;

        //if (bgX <= -bgPosSpawnPosition)
        //{
        //    bgX = 0.0;
        //}
        
        FarBackground = UpdateBackground(FarBackground, deltaTime);

        //Vector2 bgPos {bgX, -background.height / 2};
        //Vector2 bgPos2 {bgPosSpawnPosition + bgX, -background.height / 2};

        DrawTextureEx(FarBackground.background, FarBackground.position, 0.0, 1.0, WHITE);
        DrawTextureEx(FarBackground.background, {bgPosSpawnPosition.x + FarBackground.position.x, FarBackground.position.y}, 0.0, 1.0, WHITE);

        //DrawTextureEx(backTrees, bgPos, 0.0, 1.0, WHITE);
        //DrawTextureEx(backTrees, bgPos2, 0.0, 1.0, WHITE);

        //DrawTextureEx(foreGround, bgPos, 0.0, 1.0, WHITE);
        //DrawTextureEx(foreGround, bgPos2, 0.0, 1.0, WHITE);


        DrawCharacterTexture(player.texture, player.characterRect, player.position, scale, WHITE);
        
        for (int i = 0; i < enemySize; i++)
        {
            SlimeEnemy(enemies[i].texture, enemies[i].characterRect,enemies[i].position, enemies[i].frame, deltaTime);
            enemies[i].position.x += enemyVel * deltaTime;
        }

        isGrounded = GroundCheck(player);
        velocity = isGrounded ? 0 : velocity + (gravity * deltaTime);

        if (IsKeyPressed(KEY_SPACE) && isGrounded)
        {
            velocity += jumpForce;    
        }

        player.position.y += (velocity * deltaTime);

        if (isGrounded)
        {
            player = UpdateData(player, 7, deltaTime);
        }
        
        for (int i = 0; i < enemySize; i++)
        {
            enemies[i] = UpdateData(enemies[i], 3, deltaTime);     
        } 

        EndDrawing();
    }

    UnloadTexture(player.texture); 
    UnloadTexture(background);
    for (int i = 0; i < enemySize; i++)
    {
        UnloadTexture(enemies[i].texture);
    }
    

    CloseWindow();   
}

void DrawCharacterTexture(Texture2D texture, Rectangle source, Vector2 position, float textureScale, Color tint)
{
    Rectangle dest = { position.x, position.y, fabsf(source.width * textureScale), fabsf(source.height * textureScale) };
    Vector2 origin = { 0.0f, 0.0f };

    DrawTexturePro(texture, source, dest, origin, 0.0f, tint);
}

void SlimeEnemy(Texture2D texture, Rectangle rect, Vector2 position,int frame, float deltaTime)
{
    DrawCharacterTexture(texture, rect, position, scale, WHITE);
}

bool GroundCheck(CharacterData characterData)
{
    return characterData.position.y >= (SCREEN_HEIGHT - (characterData.characterRect.height * scale));
}

BackGroundData UpdateBackground(BackGroundData data, float deltaTime)
{
    data.position.x -= data.bgSpeed * deltaTime;

    return data;
}

CharacterData UpdateData(CharacterData data,int maxFrame ,float deltaTime)
{
    data.runningTime += deltaTime;

    if (data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0;
        data.characterRect.x = data.frame * data.characterRect.width;
        data.frame++;
        
        if (data.frame > maxFrame)
        {
            data.frame = 0;
        }
       
    }

    return data;
}

