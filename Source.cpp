#include <iostream>
#include "raylib.h"

int main(void){
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "mandel but shader");
    Shader shader = LoadShader(0, TextFormat("./shader.fs", 330));

    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);

    float offset[2] = { .0f, .0f};
    float zoom = 1.0f;

    Vector2 offsetSpeed = { 0.0f, 0.0f };

    int zoomLoc = GetShaderLocation(shader, "zoom");
    int offsetLoc = GetShaderLocation(shader, "offset");

    float screenDims[2] = { (float)screenWidth, (float)screenHeight };
    SetShaderValue(shader, GetShaderLocation(shader, "screenDims"), screenDims, SHADER_UNIFORM_VEC2);

    SetShaderValue(shader, zoomLoc, &zoom, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, offsetLoc, offset, SHADER_UNIFORM_VEC2);

    while (!WindowShouldClose()) {

        if (GetMouseWheelMove() > 0) zoom *= 1 + 0.2f;
        if (GetMouseWheelMove() < 0) zoom *= 1 - 0.2f;

        Vector2 mousePos = GetMousePosition();

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            offset[0] -= GetMouseDelta().x / screenWidth / zoom;
            offset[1] -= GetMouseDelta().y / screenHeight / zoom;
        }

        SetShaderValue(shader, zoomLoc, &zoom, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, offsetLoc, offset, SHADER_UNIFORM_VEC2);

        BeginTextureMode(target);
        ClearBackground(BLACK);
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
        EndTextureMode();

        BeginDrawing();
        ClearBackground(BLACK);
        BeginShaderMode(shader);
        Vector2 fix = { 0.0f, 0.0f };
        DrawTextureEx(target.texture, fix, 0.0f, 1.0f, WHITE);
        EndShaderMode();

        //DrawFPS(10, 10);

        EndDrawing();
    }

    UnloadShader(shader);
    UnloadRenderTexture(target);

    CloseWindow();

    return 0;
}