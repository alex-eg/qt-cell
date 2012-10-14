#ifndef _L_GRAPHICS
#define _L_GRAPHICS

#include <QObject>

#include <qgl.h>
#include "lmatrix.hpp"
#include <iostream>
#include <string>
#include <math.h>
#include "automaton.hpp"

struct RelativePosition {
    double x;
    double y;
};

class Grid {
private:
    int  height, width, cellsize;
    int dx, dy; //Displacement
    inline void FillCell(int x, int y, double *color);
public:
    Grid(int w, int h, int cllsz);
    Grid &operator = (const Grid &right);
    int GetHeight(void);
    int GetWidth(void);
    void Draw();
    void DrawWithMap(Automaton &M);
    void DrawBorder();
};

class Graphics {

private:
    int width, height; /* Viewport */
    double dx, dy; /* Viewport-scene relative displacement */
    Grid *grid;
    struct RelativePosition SDL_OGL;
public:
    Graphics();
    Graphics(int w, int h);
    Graphics &operator = (const Graphics &right);
    void Draw(void);
    void Draw(Automaton &a);
    ~Graphics();
};

#endif
