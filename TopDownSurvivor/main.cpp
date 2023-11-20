#include "raylib.h"
#include "raymath.h"

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

const char* TITLE = "RogueLikeDown";

Camera2D camera;
float deltaTime;

struct Tilemap
{
    Texture2D texture;
    Vector2 position;
};

struct Player
{
    Vector2 position;
    Rectangle rec;
};



int main()
{
    InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,TITLE);
    SetTargetFPS(60);
    //Rectangle player = Rectangle{ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 100, 100 };
    Player player {{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2},{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 100, 100}};

    //Set Fullscreen
    //SCREEN_WIDTH = GetMonitorWidth(0);
    //SCREEN_HEIGHT = GetMonitorHeight(0);
    //SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    //ToggleFullscreen();
    
    Tilemap tilemap
    {
        {LoadTexture("Tileset/WorldMap.png")},
        {0.0,0.0}
    };

    camera.offset = Vector2{player.position.x, player.position.y}; //use this to center it on the player if you need to.

    camera.rotation = 0; 

    camera.zoom = 1; //Zoom defaults to zero and this is probably why you can't see anything under BeginMode2D.

    while (!WindowShouldClose())
    {
        deltaTime = GetFrameTime();
        Vector2 direction = {};
        
        if (IsKeyDown(KEY_W)) {
            direction.y -= 1.0;
        }
        if (IsKeyDown(KEY_A)) {
            direction.x -= 1.0;
        }
        if (IsKeyDown(KEY_S)) {
            direction.y += 1.0;
        }
        if (IsKeyDown(KEY_D)) {
            direction.x += 1.0;
        }

        if (Vector2Length(direction) != 0.0)
        {
            player.position = Vector2Add(player.position, Vector2Scale(Vector2Normalize(direction), 2));
        }

        camera.target = Vector2{ player.position.x + player.rec.width / 2, player.position.y + player.rec.height / 2 };
        BeginDrawing();
        ClearBackground(WHITE);
        BeginMode2D(camera);

        DrawTextureEx(tilemap.texture, tilemap.position, 0.0, 1.5, WHITE);
        DrawRectangle(player.position.x, player.position.y, player.rec.width, player.rec.height, Color{ 255, 0, 0, 255 });

        EndMode2D();
        EndDrawing();
    }
    
    UnloadTexture(tilemap.texture);
    CloseWindow();
}