#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 60
#define HEIGHT 20
#define MAX_OBJECTS 100
#define MAX_HISTORY 20

typedef enum
{
    SHAPE_LINE,
    SHAPE_RECT,
    SHAPE_CIRCLE,
    SHAPE_TRIANGLE
} ShapeKind;

typedef struct
{
    int id;
    int visible;

    ShapeKind kind;

    int a, b;
    int c, d;
    int e, f;

    int radius;

} GraphicObject;

GraphicObject objects[MAX_OBJECTS];
GraphicObject snapshots[MAX_HISTORY][MAX_OBJECTS];

char screen[HEIGHT][WIDTH];

int objectCount = 0;
int nextID = 1;

int historyIndex = 0;
int historyCount = 1;

/* ---------- Canvas ---------- */

void clearScreen()
{
    int r, c;

    for (r = 0; r < HEIGHT; r++)
        for (c = 0; c < WIDTH; c++)
            screen[r][c] = ' ';
}

void putPixel(int x, int y)
{
    if (x >= 0 && x < WIDTH &&
        y >= 0 && y < HEIGHT)
    {
        screen[y][x] = '*';
    }
}

/* ---------- Drawing ---------- */

void drawLine(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while (1)
    {
        putPixel(x1, y1);

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

void drawRectangle(int cx, int cy, int w, int h)
{
    int left = cx - w / 2;
    int right = cx + w / 2;

    int top = cy - h / 2;
    int bottom = cy + h / 2;

    drawLine(left, top, right, top);
    drawLine(left, bottom, right, bottom);

    drawLine(left, top, left, bottom);
    drawLine(right, top, right, bottom);
}

void drawTriangle(
    int x1, int y1,
    int x2, int y2,
    int x3, int y3)
{
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x1, y1);
}

void drawCircle(int xc, int yc, int r)
{
    int x = 0;
    int y = r;

    int p = 3 - 2 * r;

    while (x <= y)
    {
        putPixel(xc + x, yc + y);
        putPixel(xc - x, yc + y);

        putPixel(xc + x, yc - y);
        putPixel(xc - x, yc - y);

        putPixel(xc + y, yc + x);
        putPixel(xc - y, yc + x);

        putPixel(xc + y, yc - x);
        putPixel(xc - y, yc - x);

        if (p < 0)
        {
            p += 4 * x + 6;
        }
        else
        {
            p += 4 * (x - y) + 10;
            y--;
        }

        x++;
    }
}

/* ---------- History ---------- */

void saveState()
{
    if (historyCount < MAX_HISTORY)
    {
        memcpy(
            snapshots[historyCount],
            objects,
            sizeof(objects));

        historyIndex = historyCount;
        historyCount++;
    }
}

void undo()
{
    if (historyIndex == 0)
    {
        printf("Nothing to undo!\n");
        return;
    }

    historyIndex--;

    memcpy(
        objects,
        snapshots[historyIndex],
        sizeof(objects));

    printf("Undo Done.\n");
}

/* ---------- Render ---------- */

void render()
{
    int i;

    clearScreen();

    for (i = 0; i < MAX_OBJECTS; i++)
    {
        if (!objects[i].visible)
            continue;

        switch (objects[i].kind)
        {
        case SHAPE_LINE:
            drawLine(
                objects[i].a,
                objects[i].b,
                objects[i].c,
                objects[i].d);
            break;

        case SHAPE_RECT:
            drawRectangle(
                objects[i].a,
                objects[i].b,
                objects[i].c,
                objects[i].d);
            break;

        case SHAPE_CIRCLE:
            drawCircle(
                objects[i].a,
                objects[i].b,
                objects[i].radius);
            break;

        case SHAPE_TRIANGLE:
            drawTriangle(
                objects[i].a,
                objects[i].b,
                objects[i].c,
                objects[i].d,
                objects[i].e,
                objects[i].f);
            break;
        }
    }
}

void showCanvas()
{
    int r, c;

    render();

    printf("\n");

    for (r = 0; r < HEIGHT; r++)
    {
        for (c = 0; c < WIDTH; c++)
        {
            putchar(screen[r][c]);
        }

        printf("\n");
    }
}

/* ---------- Add Shape ---------- */

void createShape()
{
    int type;
    int slot = -1;

    for (int i = 0; i < MAX_OBJECTS; i++)
    {
        if (!objects[i].visible)
        {
            slot = i;
            break;
        }
    }

    if (slot == -1)
    {
        printf("Storage Full\n");
        return;
    }

    printf("\n1.Line\n2.Rectangle\n3.Circle\n4.Triangle\n");
    scanf("%d", &type);

    objects[slot].id = nextID++;
    objects[slot].visible = 1;

    switch (type)
    {
    case 1:
        objects[slot].kind = SHAPE_LINE;
        scanf("%d%d%d%d",
              &objects[slot].a,
              &objects[slot].b,
              &objects[slot].c,
              &objects[slot].d);
        break;

    case 2:
        objects[slot].kind = SHAPE_RECT;
        scanf("%d%d%d%d",
              &objects[slot].a,
              &objects[slot].b,
              &objects[slot].c,
              &objects[slot].d);
        break;

    case 3:
        objects[slot].kind = SHAPE_CIRCLE;
        scanf("%d%d%d",
              &objects[slot].a,
              &objects[slot].b,
              &objects[slot].radius);
        break;

    case 4:
        objects[slot].kind = SHAPE_TRIANGLE;
        scanf("%d%d%d%d%d%d",
              &objects[slot].a,
              &objects[slot].b,
              &objects[slot].c,
              &objects[slot].d,
              &objects[slot].e,
              &objects[slot].f);
        break;

    default:
        objects[slot].visible = 0;
        return;
    }

    saveState();
}

/* ---------- Main ---------- */

int main()
{
    memset(objects, 0, sizeof(objects));

    memcpy(snapshots[0], objects, sizeof(objects));

    int choice;

    while (1)
    {
        printf("\n===== GRAPHICS ENGINE =====\n");
        printf("1.Add Shape\n");
        printf("2.Undo\n");
        printf("3.Display\n");
        printf("4.Reset\n");
        printf("5.Exit\n");

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createShape();
            break;

        case 2:
            undo();
            break;

        case 3:
            showCanvas();
            break;

        case 4:
            memset(objects, 0, sizeof(objects));
            printf("Canvas Cleared\n");
            break;

        case 5:
            return 0;
        }
    }
}
