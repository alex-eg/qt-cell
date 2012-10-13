#ifndef _L_GRAPHICS
#define _L_GRAPHICS

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <SDL/SDL_ttf.h>
#include "LMatrix.hpp"
#include <iostream>
#include <string>
#include <math.h>
#include "Automaton.hpp"

struct RelativePosition {
    double x;
    double y;
};

class Grid {
private:
    int height, width;
    inline void FillCell(int x, int y, double *color);
public:
    Grid(){}
    int cellsize;
    Grid(int h, int w, int cllsz) :
        height(h), width(w), cellsize(cllsz) {}

    Grid &operator = (const Grid &right)
    {
        if (this == &right)
            return *this;
        width = right.width;
        height = right.height;
        cellsize = right.cellsize;
        return *this;
    }

    int GetHeight(void)
    {
        return height;
    }

    int GetWidth(void)
    {
        return width;
    }

    void Draw();
    void DrawWithMap(Automaton &M);
    void DrawBorder();
};

class Graphics {
public:
    int width, height; /* SDL window */
    double dx, dy; /* Scaling displacement */
    Grid grid;
    SDL_Surface *display;
    struct RelativePosition SDL_OGL;

    Graphics()
    {
        display = NULL;
        SDL_OGL.x = SDL_OGL.y = 0.375;
        width = height = 800;
    }

    Graphics(unsigned int w, unsigned int h) : width(w), height(h)
    {
        display = NULL;
        SDL_OGL.x = 0.375;
        SDL_OGL.y = 0.375;
    }

    Graphics &operator = (const Graphics &right)
    {
        if (this == &right)
            return *this;
        if (display != NULL) SDL_FreeSurface(display);
        display = right.display;
        SDL_OGL.x = right.SDL_OGL.x;
        SDL_OGL.y = right.SDL_OGL.y;
        width = right.width;
        height = right.height;
        return *this;
    }

    ~Graphics() {}
    bool Init();
};

#endif
