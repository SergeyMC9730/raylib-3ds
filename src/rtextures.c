#include <raylib.h>
#include <citro2d.h>

RLAPI TextureSheet LoadTextureSheet(const char *fileName) {
    TextureSheet sheet = {0};

    sheet.sheet = C2D_SpriteSheetLoad(fileName);

    if (true) { // sheet.sheet
        sheet.images = C2D_SpriteSheetCount(sheet.sheet);
    }

    return sheet;
}

RLAPI Texture2D LoadTextureFromSheet(TextureSheet sheet, int id) {
    if (sheet.images <= 0 || !sheet.sheet) return (Texture2D){0};

    Texture2D tex = {0};

    C2D_SpriteFromSheet(&tex.spr, sheet.sheet, id % sheet.images);

    if (tex.spr.image.tex) {
        tex.width = tex.spr.image.tex->width;
        tex.height = tex.spr.image.tex->height;
    }

    return tex;
}