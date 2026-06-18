// clang cube.c -o cube -I/opt/homebrew/include -L/opt/homebrew/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

#include <raylib.h>
#include <stdio.h>

#define WIDTH 900
#define HEIGHT 600

int main(int argc, char* argv[])
{
    InitWindow(WIDTH, HEIGHT, "3D Cube");
    SetTargetFPS(60);
    
    Vector3 pos = {10, 0, 0};
    Vector3 target = {0, 0, 0};
    Vector3 up = {0, 0, 1};
    float fovy = 90;
    Camera3D cam = {pos, target, up, fovy, CAMERA_PERSPECTIVE};
    while (!WindowShouldClose())
    {
        UpdateCamera(&cam, CAMERA_FREE);
        BeginDrawing();
        BeginMode3D(cam);

        Vector3 origin = {0, 0, 0};
        DrawCube(origin, 1, 1, 1, RED);

        EndMode3D();
        EndDrawing();
    }
    EndMode3D();
    return 0;
}