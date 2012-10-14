#include "graphics.hpp"

Grid::Grid(int w, int h, int cllsz) :
    height(h), width(w), cellsize(cllsz){}

Grid &Grid::operator =(const Grid &right)
{
    if (this == &right)
        return *this;
    width = right.width;
    height = right.height;
    cellsize = right.cellsize;
    return *this;
}

int Grid::GetHeight(void)
{
    return height;
}

int Grid::GetWidth(void)
{
    return width;
}

void Grid::DrawBorder()
{
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(0, (cellsize+1)*height+1);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f((cellsize+1)*width, 0);
    glVertex2f((cellsize+1)*width, (cellsize+1)*height+1);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f((cellsize+1)*width, 0);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0, (cellsize+1)*width);
    glVertex2f((cellsize+1)*width, (cellsize+1)*width);
    glEnd();
}

void Grid::Draw()
{
    glColor3f(0.8, 0.8, 0.8);
    for(int i = 1; i<=width; i++) {
        if (i == width/2) glColor3f(0.2, 0.723, 0.32);
        glBegin(GL_LINES);
        glVertex2f(cellsize*i+i, 0);
        glVertex2f(cellsize*i+i, (cellsize+1)*height);
        glEnd();
        if (i == width/2) glColor3f(0.8, 0.8, 0.8);
    }
    for(int i = 1; i<=height; i++) {
        if (i == height/2) glColor3f(0.2, 0.723, 0.32);
        glBegin(GL_LINES);
        glVertex2f(0, cellsize*i+i);
        glVertex2f((cellsize+1)*width, cellsize*i+i);
        glEnd();
        if (i == width/2) glColor3f(0.8, 0.8, 0.8);
    }
}

void Grid::DrawWithMap(Automaton &life)
{
    for (int i=0; i<height; i++)
        for(int j=0; j<width; j++) {
            statecode cell_state = life(i,j);
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
#define CSZ (cellsize+1)
    glVertex2f(CSZ*x+1, CSZ*y+1);
    glVertex2f(CSZ*x+CSZ, CSZ*y+1);
    glVertex2f(CSZ*x+CSZ, CSZ*y+CSZ);
    glVertex2f(CSZ*x+1, CSZ*y+CSZ);
#undef CSZ
    glEnd();
}


/* --=== Graphics class ===-- */
Graphics::Graphics()
{
    SDL_OGL.x = SDL_OGL.y = 0.375;
    width = height = 800;
    grid = new Grid(40,40,10);
}

Graphics::~Graphics()
{
    delete grid;
}

Graphics::Graphics(int w, int h) : width(w), height(h)
{
    SDL_OGL.x = 0.375;
    SDL_OGL.y = 0.375;
    grid = new Grid(40,40,10);
    dx = (width - 40 * 10 - 40) / 2;
    dy = (height - 40 * 10 - 40) / 2;
}

Graphics &Graphics::operator = (const Graphics &right)
{
    if (this == &right)
        return *this;
    SDL_OGL.x = right.SDL_OGL.x;
    SDL_OGL.y = right.SDL_OGL.y;
    width = right.width;
    height = right.height;
    *grid = *right.grid;
    return *this;
}

void Graphics::Draw(void)
{
    glPushMatrix();
    glTranslatef(dx,dy,0.0);
    grid->Draw();
    grid->DrawBorder();
    glPopMatrix();
}

void Graphics::Draw(Automaton &a)
{
    glPushMatrix();
    glTranslatef(dx,dy,0.0);
    grid->DrawWithMap(a);
    grid->DrawBorder();
    glPopMatrix();
}
