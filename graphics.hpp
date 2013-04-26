#ifndef _L_GRAPHICS
#define _L_GRAPHICS

#include <QObject>

#include <qgl.h>
#include "lmatrix.hpp"
#include <iostream>
#include <string>
#include <math.h>
#include "automaton.hpp"

class Grid : public QObject {
    Q_OBJECT
private:
    int  cellCount, cellSize; /* Grid dimensions */
    inline void FillCell(int x, int y, double *color);
public:
    Grid(int cllcnt, int cllsz, QObject *parent = 0);
    Grid &operator = (const Grid &right);
    int GetHeight() const;
    int GetWidth() const;
    int GetCellsize() const;
    int GetCellCount() const;
    void DrawGrid();
    void DrawWithMap(Automaton &a);
    void DrawBorder();
};


/*---==============================================---*/


class Graphics : public Grid {
    Q_OBJECT
private:
    int vwidth, vheight; /* Viewport */
    double dx, dy; /* Viewport-scene relative displacement */
public:
    Graphics(QObject *parent = 0);
    Graphics(int w, int h, QObject *parent = 0);
    Graphics &operator = (const Graphics &right);
    void Draw(void);
    void Draw(Automaton &a);
    double Getdx();
    double Getdy();
};

#endif
