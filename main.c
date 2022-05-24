#include "Includes.h"

typedef struct{
    uint scale;
    Length len;
    uint **n;
}Grid;

int iwrap(const int n, const int min, const int max)
{
    if(n < min)
        return max-1;
    if(n >= max)
        return min;
    return n;
}

bool valid(const Coord pos, const Length len)
{
    return pos.x < len.x && pos.y < len.y && pos.x >= 0 && pos.y >= 0;
}

Grid makeGrid(const Length len)
{
    Grid ret = {
        .len = len,
        .n = calloc(len.x, sizeof(uint *))
    };
    for(uint x = 0; x < len.x; x++)
        ret.n[x] = calloc(len.y, sizeof(uint));

    return ret;
}

int imin(const int a, const int b)
{
    return a < b ? a : b;
}

int imax(const int a, const int b)
{
    return a > b ? a : b;
}

uint scale(const Length len)
{
    const Length win = getWindowLen();
    return imin(win.x/len.x, win.y/len.y);
}

void drawGrid(const Grid g)
{
    for(uint x = 0; x < g.len.x; x++){
        for(uint y = 0; y < g.len.y; y++){
            setColor(u32ToColor(g.n[x][y]*8));
            fillSquareCoordResize(coordMul((const Coord){.x = x, .y = y}, g.scale), g.scale, -2);
        }
    }
}

Grid clickAt(const Grid g, const Coord click)
{
    const Coord pos = coordDiv(click, g.scale);
    if(!valid(pos, g.len))
        return g;
    g.n[pos.x][pos.y]++;
    return g;
}

int main(int argc, char const *argv[])
{
    Length window = {800, 600};
    init();
    setWindowLen(window);

    Grid g = makeGrid((const Length){32, 24});

    while(1){
        Ticks t = frameStart();

        if(keyPressed(SDL_SCANCODE_ESCAPE))
            return 0;
        if(mouseBtnState(MOUSE_L)){
            clickAt(mouse.pos)
        }

        frameEnd(t);
    }
    return 0;
}
