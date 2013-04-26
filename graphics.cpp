#include "graphics.hpp"

Grid::Grid(int cllcnt, int cllsz, QObject *parent) :
    QObject(parent), cellCount(cllcnt), cellSize(cllsz){}

Grid &Grid::operator =(const Grid &right)
{
    if (this == &right)
        return *this;
    cellCount = right.cellCount;
    cellSize = right.cellSize;
    return *this;
}

int Grid::GetCellCount() const
{
    return cellCount;
}

int Grid::GetCellsize() const
{
    return cellSize;
}

void Grid::DrawBorder()
{
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(0, (cellSize+1)*cellCount+1);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f((cellSize+1)*cellCount, 0);
    glVertex2f((cellSize+1)*cellCount, (cellSize+1)*cellCount+1);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f((cellSize+1)*cellCount, 0);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0, (cellSize+1)*cellCount);
    glVertex2f((cellSize+1)*cellCount, (cellSize+1)*cellCount);
    glEnd();
}

void Grid::DrawGrid()
{
    glColor3f(0.8, 0.8, 0.8);
    for(int i = 1; i<=cellCount; i++) {
        if (i == cellCount/2) glColor3f(0.2, 0.723, 0.32);
        glBegin(GL_LINES);
        glVertex2f(cellSize*i+i, 0);
        glVertex2f(cellSize*i+i, (cellSize+1)*cellCount);
        glEnd();
        if (i == cellCount/2) glColor3f(0.8, 0.8, 0.8);
    }
    for(int i = 1; i<=cellCount; i++) {
        if (i == cellCount/2) glColor3f(0.2, 0.723, 0.32);
        glBegin(GL_LINES);
        glVertex2f(0, cellSize*i+i);
        glVertex2f((cellSize+1)*cellCount, cellSize*i+i);
        glEnd();
        if (i == cellCount/2) glColor3f(0.8, 0.8, 0.8);
    }
}

void Grid::DrawWithMap(Automaton &a)
{
    for (int i=0; i<cellCount; i++)
        for(int j=0; j<cellCount; j++) {
            statecode cell_state = a(i,j);
            double lcolor[3];
            if (cell_state == LLIVE) {
                lcolor[0] = 0.3;
                lcolor[1] = 0.8765;
                lcolor[2] = 0.3;
            } else {
                lcolor[0] = 0.0;
                lcolor[1] = 0.0;
                lcolor[2] = 0.0;
            }
            FillCell(i, j, lcolor);
        }
}

inline void Grid::FillCell(int x, int y, double *color)
{
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_QUADS);
#define CSZ (cellSize+1)
    glVertex2f(CSZ*x+1, CSZ*y+1);
    glVertex2f(CSZ*x+CSZ, CSZ*y+1);
    glVertex2f(CSZ*x+CSZ, CSZ*y+CSZ);
    glVertex2f(CSZ*x+1, CSZ*y+CSZ);
#undef CSZ
    glEnd();
}


/* --=== Graphics class ===-- */
Graphics::Graphics(QObject *parent) : Grid(40,10,parent)
{
    vwidth = vheight = 800;
}

double Graphics::Getdx()
{
    return dx;
}

double Graphics::Getdy()
{
    return dy;
}

Graphics::Graphics(int w, int h, QObject *parent) :
     Grid(40,10,parent), vwidth(w), vheight(h)
{
    dx = (vwidth - 40 * 10 - 40) / 2;
    dy = (vheight - 40 * 10 - 40) / 2;
}

Graphics &Graphics::operator = (const Graphics &right)
{
    if (this == &right)
        return *this;
    vwidth = right.vwidth;
    vheight = right.vheight;
    return *this;
}

void Graphics::Draw()
{
    glPushMatrix();
    glTranslatef(dx,dy,0.0);
    DrawGrid();
    DrawBorder();
    glPopMatrix();
}

void Graphics::Draw(Automaton &a)
{
    glPushMatrix();
    glTranslatef(dx,dy,0.0);
    DrawWithMap(a);
    DrawBorder();
    glPopMatrix();
}
