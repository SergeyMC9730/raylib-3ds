#include <string.h>
#include <stdio.h>
#include <3ds.h>
#include <raylib.h>
#include <citro2d.h>
#include <math.h>
#include <stdlib.h>

#ifndef RAND_MAX
#define RAND_MAX 0xFFFF
#endif


typedef struct CoreData {
    struct {
        const char *title;                  // Window text title const pointer
        unsigned int flags;                 // Configuration flags (bit based), keeps window state
        bool ready;                         // Check if window has been initialized successfully
        bool fullscreen;                    // Check if fullscreen mode is enabled
        bool shouldClose;                   // Check if window set for closing
        bool resizedLastFrame;              // Check if window has been resized last frame
        bool eventWaiting;                  // Wait for events before ending frame
        bool usingFbo;                      // Using FBO (RenderTexture) for rendering instead of default framebuffer
        const char *clipboardData;          // Clipboard data
        C3D_RenderTarget* top;              // Top 3DS screen
        C3D_RenderTarget* bottom;           // Bottom 3DS screen
        gfxScreen_t screen;                 // Rendered 3DS screen

        // Point position;                     // Window position (required on fullscreen toggle)
        // Point previousPosition;             // Window previous position (required on borderless windowed toggle)
        // Size display;                       // Display width and height (monitor, device-screen, LCD, ...)
        // Size screen;                        // Screen width and height (used render area)
        // Size previousScreen;                // Screen previous width and height (required on borderless windowed toggle)
        // Size currentFbo;                    // Current render width and height (depends on active fbo)
        // Size render;                        // Framebuffer width and height (render area, including black bars if required)
        // Point renderOffset;                 // Offset from render area (must be divided by 2)
        // Size screenMin;                     // Screen minimum width and height (for resizable window)
        // Size screenMax;                     // Screen maximum width and height (for resizable window)
        // Matrix screenScale;                 // Matrix to scale screen (framebuffer rendering)

        // char **dropFilepaths;               // Store dropped files paths pointers (provided by GLFW)
        // unsigned int dropFileCount;         // Count dropped files strings

    } Window;

    struct {
        double current;                     // Current time measure
        double previous;                    // Previous time measure
        double update;                      // Time measure for frame update
        double draw;                        // Time measure for frame draw
        double frame;                       // Time measure for one frame
        double target;                      // Desired time for one frame, if 0 not applied
        unsigned long long int base;        // Base time measure for hi-res timer (PLATFORM_ANDROID, PLATFORM_DRM)
        unsigned int frameCounter;          // Frame counter

    } Time;
} CoreData;

CoreData CORE = { 0 };               // Global CORE state context

RLAPI void InitWindow(int width, int height, const char *title) {
    // init gfx
    gfxInitDefault();

    // init citro3d
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);

    // init citro2d
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();

    // init citro3d renderer targets
    CORE.Window.top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    CORE.Window.bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

    CORE.Window.screen = GFX_TOP;

    CORE.Window.fullscreen = true;
    CORE.Window.title = title;

    CORE.Window.ready = true;
}

RLAPI void InitConsole(void) {
    consoleInit(GFX_BOTTOM, NULL);
    consoleClear();
}

RLAPI void CloseWindow(void) {
    // unload citro2d
    C2D_Fini();

    // unload citro3d
	C3D_Fini();

    // unload gfx
	gfxExit();
}

RLAPI bool WindowShouldClose(void) {
    CORE.Window.shouldClose = aptShouldClose();
    
    return !aptMainLoop();
}
RLAPI bool IsWindowReady(void) {
    return CORE.Window.ready;
}

RLAPI bool IsWindowFullscreen(void) {
    return CORE.Window.fullscreen;
}
RLAPI bool IsWindowHidden(void) {
    return false;
}
RLAPI bool IsWindowMinimized(void) {
    return false;
}
RLAPI bool IsWindowMaximized(void) {
    return true;
}
RLAPI bool IsWindowFocused(void) {
    return true;
}
RLAPI bool IsWindowResized(void) {
    return false;
}

RLAPI bool IsWindowState(unsigned int flag) {
    // WIP
    return false;
}
RLAPI void SetWindowState(unsigned int flags) {
    // WIP
    return;
}
RLAPI void ClearWindowState(unsigned int flags) {
    // WIP
    return;
}

RLAPI void ToggleFullscreen(void) {
    return;
}
RLAPI void ToggleBorderlessWindowed(void) {
    return;
}
RLAPI void MaximizeWindow(void) {
    return;
}

RLAPI void MinimizeWindow(void) {
    return;
}
RLAPI void RestoreWindow(void) {
    return;
}

RLAPI void SetWindowIcon(Image image) {
    return;
}
RLAPI void SetWindowIcons(Image *images, int count) {
    return;
}
RLAPI void SetWindowTitle(const char *title) {
    CORE.Window.title = title;
}
RLAPI void SetWindowPosition(int x, int y) {
    return;
}

RLAPI void SetWindowMonitor(int monitor) {
    return;
}

RLAPI void SetWindowMinSize(int width, int height) {
    return;
}
RLAPI void SetWindowMaxSize(int width, int height) {
    return;
}
RLAPI void SetWindowSize(int width, int height) {
    return;
}

RLAPI void SetWindowOpacity(float opacity) {
    return;
}

RLAPI void SetWindowFocused(void) {
    return;
}

RLAPI void *GetWindowHandle(void) {
    if (CORE.Window.screen == GFX_TOP) {
        return CORE.Window.top;
    }

    return CORE.Window.bottom;
}

RLAPI int GetScreenWidth(void) {
    return GetMonitorWidth(CORE.Window.screen);
}
RLAPI int GetScreenHeight(void) {
    return GetMonitorHeight(CORE.Window.screen);
}

RLAPI int GetRenderWidth(void) {
    return GetScreenWidth();
}
RLAPI int GetRenderHeight(void) {
    return GetScreenHeight();
}

RLAPI int GetMonitorCount(void) {
    // two screens
    return 2;
}

RLAPI int GetCurrentMonitor(void) {
    return 0;
}

RLAPI Vector2 GetMonitorPosition(int monitor) {
    switch (monitor) {
        default:
        case 0: {
            return (Vector2){0, 0};
        }
        case 1: {
            return (Vector2){
                0, GetScreenHeight()
            };
        }
    }
}

RLAPI int GetMonitorWidth(int monitor) {
    switch (monitor) {
        default:
        case 0: {
            return 400;
        }
        case 1: {
            return 320;
        }
    }
}
RLAPI int GetMonitorHeight(int monitor) {
    return 240;
}

RLAPI int GetMonitorPhysicalWidth(int monitor) {
    return 0;
}
RLAPI int GetMonitorPhysicalHeight(int monitor) {
    return 0;
}

RLAPI int GetMonitorRefreshRate(int monitor) {
    return 60;
}

RLAPI Vector2 GetWindowPosition(void) {
    return (Vector2){0, 0};
}
RLAPI Vector2 GetWindowScaleDPI(void) {
    return (Vector2){1, 1};
}

RLAPI const char *GetMonitorName(int monitor) {
    return "TN LCD";
}

RLAPI void SetClipboardText(const char *text) {
    CORE.Window.clipboardData = text;
}
RLAPI const char *GetClipboardText(void) {
    return CORE.Window.clipboardData;
}

RLAPI void EnableEventWaiting(void) {
    CORE.Window.eventWaiting = true;
}
RLAPI void DisableEventWaiting(void) {
    CORE.Window.eventWaiting = false;
}

RLAPI void ShowCursor(void) {}
RLAPI void HideCursor(void) {}
RLAPI bool IsCursorHidden(void) { return true; }
RLAPI void EnableCursor(void) {}
RLAPI void DisableCursor(void) {}
RLAPI bool IsCursorOnScreen(void) { return false; }

RLAPI void SwitchScreen(int screen) {
    CORE.Window.screen = screen % 2;

    C2D_SceneBegin(GetWindowHandle());
}

RLAPI void ClearBackground(Color color) {
    C3D_RenderTarget *target = GetWindowHandle();

    u32 _color = C2D_Color32(color.r, color.g, color.b, color.a);

    C2D_TargetClear(target, _color);
}

RLAPI void BeginDrawing(void) {
    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
    C2D_SceneBegin(GetWindowHandle());

    CORE.Time.frameCounter++;
}

RLAPI void EndDrawing(void) {
    SwitchScreen(GFX_TOP);

    CORE.Time.frame = C3D_FrameRate(0);
    CORE.Time.draw = C3D_GetDrawingTime();
    CORE.Time.update = C3D_GetProcessingTime();

    SwapScreenBuffer();

    C3D_FrameEnd(0);

    PollInputEvents();
}

RLAPI void SetTargetFPS(int fps) {
    C3D_FrameRate(fps);
}

RLAPI void SwapScreenBuffer(void) {
    return;
}

RLAPI void PollInputEvents(void) {
    return hidScanInput();
}

RLAPI void WaitTime(double seconds) {
    u64 ms = seconds * 1000;

    svcSleepThread(1000000ULL * ms);
}

//----------------------------------------------------------------------------------
// Module Functions Definition: Misc
//----------------------------------------------------------------------------------

// NOTE: Functions with a platform-specific implementation on rcore_<platform>.c
//void OpenURL(const char *url)

// Set the seed for the random number generator
void SetRandomSeed(unsigned int seed)
{
#if defined(SUPPORT_RPRAND_GENERATOR)
    rprand_set_seed(seed);
#else
    srand(seed);
#endif
}

// Get a random value between min and max included
int GetRandomValue(int min, int max)
{
    int value = 0;

    if (min > max)
    {
        int tmp = max;
        max = min;
        min = tmp;
    }

#if defined(SUPPORT_RPRAND_GENERATOR)
    value = rprand_get_value(min, max);
#else
    // WARNING: Ranges higher than RAND_MAX will return invalid results
    // More specifically, if (max - min) > INT_MAX there will be an overflow,
    // and otherwise if (max - min) > RAND_MAX the random value will incorrectly never exceed a certain threshold
    // NOTE: Depending on the library it can be as low as 32767
    if ((unsigned int)(max - min) > (unsigned int)RAND_MAX)
    {
        // TRACELOG(LOG_WARNING, "Invalid GetRandomValue() arguments, range should not be higher than %i", RAND_MAX);
    }

    value = (rand()%(abs(max - min) + 1) + min);
#endif
    return value;
}

RLAPI bool IsKeyPressed(int key) {
    return false;
}
RLAPI bool IsKeyPressedRepeat(int key) {
    return false;
}
RLAPI bool IsKeyDown(int key) {
    return false;
}
RLAPI bool IsKeyReleased(int key) {
    return false;
}
RLAPI bool IsKeyUp(int key) {
    return false;
}
RLAPI int GetKeyPressed(void) {
    return 0;
}
RLAPI int GetCharPressed(void) {
    return 0;
}
RLAPI void SetExitKey(int key) {
    return;
}

RLAPI bool IsGamepadAvailable(int gamepad) {
    if (gamepad == 0) return true;

    return false;
}
RLAPI const char *GetGamepadName(int gamepad) {
    return "Nintendo 3DS";
}
RLAPI bool IsGamepadButtonPressed(int gamepad, int button) {
    if (gamepad != 0) return false;

    u32 kDown = hidKeysDown();

    return kDown & button;
}
RLAPI bool IsGamepadButtonDown(int gamepad, int button) {
    if (gamepad != 0) return false;

    u32 kHeld = hidKeysHeld();
    
    return kHeld & button;
}
RLAPI bool IsGamepadButtonReleased(int gamepad, int button) {
    if (gamepad != 0) return false;

    u32 kReleased = hidKeysUp();

    return kReleased & button;
}
RLAPI bool IsGamepadButtonUp(int gamepad, int button) {
    return !IsGamepadButtonPressed(gamepad, button);
}
RLAPI int GetGamepadButtonPressed(void) {
    u32 kDown = hidKeysDown();

    if (kDown & KEY_A) return KEY_A;
    if (kDown & KEY_B) return KEY_B;
    if (kDown & KEY_SELECT) return KEY_SELECT;
    if (kDown & KEY_START) return KEY_START;
    if (kDown & KEY_DRIGHT) return KEY_DRIGHT;
    if (kDown & KEY_DLEFT) return KEY_DLEFT;
    if (kDown & KEY_DUP) return KEY_DUP;
    if (kDown & KEY_DDOWN) return KEY_DDOWN;
    if (kDown & KEY_R) return KEY_R;
    if (kDown & KEY_L) return KEY_L;
    if (kDown & KEY_X) return KEY_X;
    if (kDown & KEY_Y) return KEY_Y;
    if (kDown & KEY_ZL) return KEY_ZL;
    if (kDown & KEY_ZR) return KEY_ZR;
    if (kDown & KEY_CSTICK_RIGHT) return KEY_CSTICK_RIGHT;
    if (kDown & KEY_CSTICK_LEFT) return KEY_CSTICK_LEFT;
    if (kDown & KEY_CSTICK_UP) return KEY_CSTICK_UP;
    if (kDown & KEY_CSTICK_DOWN) return KEY_CSTICK_DOWN;
    if (kDown & KEY_UP) return KEY_UP;
    if (kDown & KEY_DOWN) return KEY_DOWN;
    if (kDown & KEY_LEFT) return KEY_LEFT;
    if (kDown & KEY_RIGHT) return KEY_RIGHT;

    return 0;
}

RLAPI int GetGamepadAxisCount(int gamepad) {
    if (gamepad != 0) return 0;

    return 2;
}
RLAPI float GetGamepadAxisMovement(int gamepad, int axis) {
    return 0.f;
}
RLAPI int SetGamepadMappings(const char *mappings) {
    return 0;
}

RLAPI float GetFrameTime(void) {
    return 1.f / CORE.Time.frame;
}
RLAPI double GetTime(void) {
    return (long double)CORE.Time.frameCounter * (1.f / CORE.Time.frame);
}
RLAPI int GetFPS(void) {
    return CORE.Time.frame;
}