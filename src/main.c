#include <string.h>
#include <stdio.h>
#include <3ds.h>
#include <raylib.h>
#include <citro2d.h>
#include <stdlib.h>
#include "fudesumi.h"

void renderCircles(int x, int y) {
    DrawCircle(x, y, 50, RED);
    DrawCircle(x, y, 25, GREEN);
    DrawCircle(x, y, 12.5, BLUE);
}

int main() {
    InitWindow(0, 0, "");

    SetTargetFPS(60);

    // int limit = 64;
    
    float cx = 0;
    float cy = 0;

    float speed = 15;

    Rectangle r;
    r.width = 15;
    r.height = 15;
    r.y = 35;

    TextureSheet sheet = LoadTextureSheet("romfs:/gfx/fudesumi.t3x");

    char buf1[64] = {};

    snprintf(buf1, 64, "images: %d (0x%08X)", sheet.images, sheet.sheet);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText(buf1, 10, 60, 10, BLACK);

        DrawText("U", 130, 10, 25, BLACK);
        if (IsGamepadButtonDown(0, KEY_UP)) {
            cy -= 1 * GetFrameTime() * speed * 10;

            DrawRectangle(130, r.y, r.width, r.height, GREEN);
        } else {
            DrawRectangle(130, r.y, r.width, r.height, GRAY);
        }
        DrawText("D", 90, 10, 25, BLACK);
        if (IsGamepadButtonDown(0, KEY_DOWN)) {
            cy += 1 * GetFrameTime() * speed * 10;

            DrawRectangle(90, r.y, r.width, r.height, GREEN);
        } else {
            DrawRectangle(90, r.y, r.width, r.height, GRAY);
        }
        DrawText("R", 50, 10, 25, BLACK);
        if (IsGamepadButtonDown(0, KEY_RIGHT)) {
            cx += 1 * GetFrameTime() * speed * 10;

            DrawRectangle(50, r.y, r.width, r.height, GREEN);
        } else {
            DrawRectangle(50, r.y, r.width, r.height, GRAY);
        }
        DrawText("L", 10, 10, 25, BLACK);
        if (IsGamepadButtonDown(0, KEY_LEFT)) {
            cx -= 1 * GetFrameTime() * speed * 10;

            DrawRectangle(10, r.y, r.width, r.height, GREEN);
        } else {
            DrawRectangle(10, r.y, r.width, r.height, GRAY);
        }

        renderCircles(cx, cy);

        SwitchScreen(SCREEN_BOTTOM);

        ClearBackground(RAYWHITE);

        DrawFPS(50 + cos(GetTime() * 1) * 30, 50 + sin(GetTime() * 2) * 10);

        DrawText("Congrats!\nYou created your first\nwindow!", 50, 80, 20, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();

	return 0;
}

