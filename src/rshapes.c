#include <raylib.h>
#include <citro2d.h>

RLAPI void DrawCircle(int centerX, int centerY, float radius, Color color) {
    u32 _color = C2D_Color32(color.r, color.g, color.b, color.a);
    
    C2D_DrawCircleSolid(centerX, centerY, 0, radius, _color);
}
RLAPI void DrawCircleV(Vector2 center, float radius, Color color) {
    return DrawCircle(center.x, center.y, radius, color);
}

RLAPI void DrawPixel(int posX, int posY, Color color) {
    u32 _color = C2D_Color32(color.r, color.g, color.b, color.a);

    C2D_DrawRectSolid(posX, posX, 0, 1, 1, _color);
}
RLAPI void DrawPixelV(Vector2 position, Color color) {
    return DrawPixel(position.x, position.y, color);
}

RLAPI void DrawLineEx(Vector2 startPos, Vector2 endPos, float thick, Color color) {
    u32 _color = C2D_Color32(color.r, color.g, color.b, color.a);

    C2D_DrawLine(startPos.x, startPos.y, _color, endPos.x, endPos.y, _color, thick, 1);
}
RLAPI void DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color) {
    return DrawLineEx((Vector2){startPosX, startPosY}, (Vector2){endPosX, endPosY}, 1, color);
}
RLAPI void DrawLineV(Vector2 startPos, Vector2 endPos, Color color) {
    return DrawLineEx(startPos, endPos, 1, color);
}
RLAPI void DrawLineStrip(Vector2 *points, int pointCount, Color color) {
    if (pointCount < 2) return;

    for (int i = 0; i < pointCount - 1; i++) {
        DrawLineV(points[i], points[i + 1], color);
    }
}
RLAPI void DrawLineBezier(Vector2 startPos, Vector2 endPos, float thick, Color color) {
    // WIP

    return;
}

RLAPI void DrawEllipse(int centerX, int centerY, float radiusH, float radiusV, Color color) {
    u32 _color = C2D_Color32(color.r, color.g, color.b, color.a);

    C2D_DrawEllipseSolid(centerX, centerY, 0, radiusH, radiusV, _color);
}

RLAPI void DrawRectangle(int posX, int posY, int width, int height, Color color) {
    u32 _color = C2D_Color32(color.r, color.g, color.b, color.a);

    C2D_DrawRectSolid(posX, posY, 0, width, height, _color);
}
RLAPI void DrawRectangleV(Vector2 position, Vector2 size, Color color) {
    return DrawRectangle(position.x, position.y, size.x, size.y, color);
}
RLAPI void DrawRectangleRec(Rectangle rec, Color color) {
    return DrawRectangle(rec.x, rec.y, rec.width, rec.height, color);
}
RLAPI void DrawRectangleGradientV(int posX, int posY, int width, int height, Color color1, Color color2) {
    u32 _color1 = C2D_Color32(color1.r, color1.g, color1.b, color1.a);
    u32 _color2 = C2D_Color32(color2.r, color2.g, color2.b, color2.a);
    
    C2D_DrawRectangle(posX, posY, 0, width, height, _color1, _color1, _color2, _color2);
}
RLAPI void DrawRectangleGradientH(int posX, int posY, int width, int height, Color color1, Color color2) {
    u32 _color1 = C2D_Color32(color1.r, color1.g, color1.b, color1.a);
    u32 _color2 = C2D_Color32(color2.r, color2.g, color2.b, color2.a);
    
    C2D_DrawRectangle(posX, posY, 0, width, height, _color1, _color2, _color1, _color2);
}
RLAPI void DrawRectangleGradientEx(Rectangle rec, Color col1, Color col2, Color col3, Color col4) {
    u32 _col1 = C2D_Color32(col1.r, col1.g, col1.b, col1.a);
    u32 _col2 = C2D_Color32(col2.r, col2.g, col2.b, col2.a);
    u32 _col3 = C2D_Color32(col3.r, col3.g, col3.b, col3.a);
    u32 _col4 = C2D_Color32(col4.r, col4.g, col4.b, col4.a);

    C2D_DrawRectangle(rec.x, rec.y, 0, rec.width, rec.height, _col1, _col2, _col3, _col4);
}
RLAPI void DrawTriangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color) {
    u32 _color = C2D_Color32(color.r, color.g, color.b, color.a);
    
    C2D_DrawTriangle(v1.x, v1.y, _color, v2.x, v2.y, _color, v3.x, v3.y, _color, 1);
}



//----------------------------------------------------------------------------------
// Module Functions Definition - Collision Detection functions
//----------------------------------------------------------------------------------

// Check if point is inside rectangle
bool CheckCollisionPointRec(Vector2 point, Rectangle rec)
{
    bool collision = false;

    if ((point.x >= rec.x) && (point.x < (rec.x + rec.width)) && (point.y >= rec.y) && (point.y < (rec.y + rec.height))) collision = true;

    return collision;
}

// Check if point is inside circle
bool CheckCollisionPointCircle(Vector2 point, Vector2 center, float radius)
{
    bool collision = false;

    collision = CheckCollisionCircles(point, 0, center, radius);

    return collision;
}

// Check if point is inside a triangle defined by three points (p1, p2, p3)
bool CheckCollisionPointTriangle(Vector2 point, Vector2 p1, Vector2 p2, Vector2 p3)
{
    bool collision = false;

    float alpha = ((p2.y - p3.y)*(point.x - p3.x) + (p3.x - p2.x)*(point.y - p3.y)) /
                  ((p2.y - p3.y)*(p1.x - p3.x) + (p3.x - p2.x)*(p1.y - p3.y));

    float beta = ((p3.y - p1.y)*(point.x - p3.x) + (p1.x - p3.x)*(point.y - p3.y)) /
                 ((p2.y - p3.y)*(p1.x - p3.x) + (p3.x - p2.x)*(p1.y - p3.y));

    float gamma = 1.0f - alpha - beta;

    if ((alpha > 0) && (beta > 0) && (gamma > 0)) collision = true;

    return collision;
}

// Check if point is within a polygon described by array of vertices
// NOTE: Based on http://jeffreythompson.org/collision-detection/poly-point.php
bool CheckCollisionPointPoly(Vector2 point, Vector2 *points, int pointCount)
{
    bool inside = false;

    if (pointCount > 2)
    {
        for (int i = 0, j = pointCount - 1; i < pointCount; j = i++)
        {
            if ((points[i].y > point.y) != (points[j].y > point.y) &&
                (point.x < (points[j].x - points[i].x) * (point.y - points[i].y) / (points[j].y - points[i].y) + points[i].x))
            {
                inside = !inside;
            }
        }
    }

    return inside;
}

// Check collision between two rectangles
bool CheckCollisionRecs(Rectangle rec1, Rectangle rec2)
{
    bool collision = false;

    if ((rec1.x < (rec2.x + rec2.width) && (rec1.x + rec1.width) > rec2.x) &&
        (rec1.y < (rec2.y + rec2.height) && (rec1.y + rec1.height) > rec2.y)) collision = true;

    return collision;
}

// Check collision between two circles
bool CheckCollisionCircles(Vector2 center1, float radius1, Vector2 center2, float radius2)
{
    bool collision = false;

    float dx = center2.x - center1.x;      // X distance between centers
    float dy = center2.y - center1.y;      // Y distance between centers

    float distance = sqrtf(dx*dx + dy*dy); // Distance between centers

    if (distance <= (radius1 + radius2)) collision = true;

    return collision;
}

// Check collision between circle and rectangle
// NOTE: Reviewed version to take into account corner limit case
bool CheckCollisionCircleRec(Vector2 center, float radius, Rectangle rec)
{
    bool collision = false;

    float recCenterX = rec.x + rec.width/2.0f;
    float recCenterY = rec.y + rec.height/2.0f;

    float dx = fabsf(center.x - recCenterX);
    float dy = fabsf(center.y - recCenterY);

    if (dx > (rec.width/2.0f + radius)) { return false; }
    if (dy > (rec.height/2.0f + radius)) { return false; }

    if (dx <= (rec.width/2.0f)) { return true; }
    if (dy <= (rec.height/2.0f)) { return true; }

    float cornerDistanceSq = (dx - rec.width/2.0f)*(dx - rec.width/2.0f) +
                             (dy - rec.height/2.0f)*(dy - rec.height/2.0f);

    collision = (cornerDistanceSq <= (radius*radius));

    return collision;
}

// Check the collision between two lines defined by two points each, returns collision point by reference
bool CheckCollisionLines(Vector2 startPos1, Vector2 endPos1, Vector2 startPos2, Vector2 endPos2, Vector2 *collisionPoint)
{
    bool collision = false;

    float div = (endPos2.y - startPos2.y)*(endPos1.x - startPos1.x) - (endPos2.x - startPos2.x)*(endPos1.y - startPos1.y);

    if (fabsf(div) >= FLT_EPSILON)
    {
        collision = true;

        float xi = ((startPos2.x - endPos2.x)*(startPos1.x*endPos1.y - startPos1.y*endPos1.x) - (startPos1.x - endPos1.x)*(startPos2.x*endPos2.y - startPos2.y*endPos2.x))/div;
        float yi = ((startPos2.y - endPos2.y)*(startPos1.x*endPos1.y - startPos1.y*endPos1.x) - (startPos1.y - endPos1.y)*(startPos2.x*endPos2.y - startPos2.y*endPos2.x))/div;

        if (((fabsf(startPos1.x - endPos1.x) > FLT_EPSILON) && (xi < fminf(startPos1.x, endPos1.x) || (xi > fmaxf(startPos1.x, endPos1.x)))) ||
            ((fabsf(startPos2.x - endPos2.x) > FLT_EPSILON) && (xi < fminf(startPos2.x, endPos2.x) || (xi > fmaxf(startPos2.x, endPos2.x)))) ||
            ((fabsf(startPos1.y - endPos1.y) > FLT_EPSILON) && (yi < fminf(startPos1.y, endPos1.y) || (yi > fmaxf(startPos1.y, endPos1.y)))) ||
            ((fabsf(startPos2.y - endPos2.y) > FLT_EPSILON) && (yi < fminf(startPos2.y, endPos2.y) || (yi > fmaxf(startPos2.y, endPos2.y))))) collision = false;

        if (collision && (collisionPoint != 0))
        {
            collisionPoint->x = xi;
            collisionPoint->y = yi;
        }
    }

    return collision;
}

// Check if point belongs to line created between two points [p1] and [p2] with defined margin in pixels [threshold]
bool CheckCollisionPointLine(Vector2 point, Vector2 p1, Vector2 p2, int threshold)
{
    bool collision = false;

    float dxc = point.x - p1.x;
    float dyc = point.y - p1.y;
    float dxl = p2.x - p1.x;
    float dyl = p2.y - p1.y;
    float cross = dxc*dyl - dyc*dxl;

    if (fabsf(cross) < (threshold*fmaxf(fabsf(dxl), fabsf(dyl))))
    {
        if (fabsf(dxl) >= fabsf(dyl)) collision = (dxl > 0)? ((p1.x <= point.x) && (point.x <= p2.x)) : ((p2.x <= point.x) && (point.x <= p1.x));
        else collision = (dyl > 0)? ((p1.y <= point.y) && (point.y <= p2.y)) : ((p2.y <= point.y) && (point.y <= p1.y));
    }

    return collision;
}

// Get collision rectangle for two rectangles collision
Rectangle GetCollisionRec(Rectangle rec1, Rectangle rec2)
{
    Rectangle overlap = { 0 };

    float left = (rec1.x > rec2.x)? rec1.x : rec2.x;
    float right1 = rec1.x + rec1.width;
    float right2 = rec2.x + rec2.width;
    float right = (right1 < right2)? right1 : right2;
    float top = (rec1.y > rec2.y)? rec1.y : rec2.y;
    float bottom1 = rec1.y + rec1.height;
    float bottom2 = rec2.y + rec2.height;
    float bottom = (bottom1 < bottom2)? bottom1 : bottom2;

    if ((left < right) && (top < bottom))
    {
        overlap.x = left;
        overlap.y = top;
        overlap.width = right - left;
        overlap.height = bottom - top;
    }

    return overlap;
}