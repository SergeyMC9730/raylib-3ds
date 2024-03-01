#include <raylib.h>
#include <citro2d.h>

RLAPI void DrawFPS(int posX, int posY) {
    Color color = LIME;                         // Good FPS
    int fps = GetFPS();

    char textbuf[32] = {};
    snprintf(textbuf, 32, "%2i FPS", fps);

    if ((fps < 30) && (fps >= 15)) color = ORANGE;  // Warning FPS
    else if (fps < 15) color = RED;             // Low FPS

    DrawText(textbuf, posX, posY, 20, color);
}
RLAPI void DrawText(const char *text, int posX, int posY, int fontSize, Color color) {
    C2D_Text t;
    t.buf = C2D_TextBufNew(strlen(text) + 64);
    
    C2D_TextParse(&t, t.buf, text);
    
    float baseline = 25;
    float scale_factor = (float)fontSize / baseline;

    C2D_DrawText(&t, 0, posX, posY, 0, scale_factor, scale_factor);

    C2D_TextBufDelete(t.buf);


}