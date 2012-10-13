#include "LApp.hpp"

void LApp::Event(SDL_Event *Event)
{
    if (help) Event_Help(Event);
    else Event_Field(Event);
}

void LApp::Event_Help(SDL_Event *Event)
{
    switch (Event->type) {
    case SDL_KEYDOWN: {
        HelpKeyDown(Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);
        break;
    }
    case SDL_QUIT: {
        running = false;
        break;
    }
    default: break;
    }
}

void LApp::HelpKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch (sym) {
    case SDLK_F1:
    case SDLK_ESCAPE: {
	help = false;
	break;
    }
    default: break;
    }
}

void LApp::Event_Field(SDL_Event *Event)
{
    switch (Event->type) {
    case SDL_KEYDOWN: {
        KeyDown(Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);
        break;
    }
    case SDL_KEYUP: {
        KeyUp(Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);
        break;
    }
    case SDL_QUIT: {
        running = false;
        break;
    }
    case SDL_MOUSEBUTTONDOWN: {
	MouseButtonDown(Event->button.button, Event->button.x, Event->button.y);
	break;
    }
    case SDL_MOUSEMOTION: {
	bool Left, Right, Middle;
	Left = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1);
	Middle = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(2);
	Right = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(3);
	MouseMove(Event->motion.x, Event->motion.y, Event->motion.xrel, Event->motion.yrel, Left, Right, Middle);
	break;
    }
    default:
        break;
    }
}

void LApp::KeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch (sym) {
    case SDLK_SPACE: {
	if (updating) updating = false;
	else updating = true;
	break;
    }
    case SDLK_ESCAPE: {
	running = false;
	break;
    }
    case SDLK_s: {
	updatingstep = true;
	break;
    }
    case SDLK_r: {
	life.Randomize();
	break;
    }
    case SDLK_c: {
	life.Clear();
	break;
    }
    case SDLK_LCTRL: {
	//nowDrawing = true;
	break;
    }
    case SDLK_b: {
    	graphics.Bloom.Switch();
    	break;
    }
    case SDLK_h: {
    	graphics.Shade.Switch();
	graphics.Shade.Invoke();
    	break;
    }
    case SDLK_KP_PLUS: {
	if (speed > 0) {
	    updating = updating || true;
	    speed--;
	    counter = 0;
	}
	break;
    }
    case SDLK_KP_MINUS: {
	if (speed < 30) speed++;
	else updating = false;
	counter = 0;
	break;
    }
    case SDLK_F1: {
	if (help) {
	    
	    help = false;
	} else {
	    help = true;
	    updating = false;
	}
	break;
    }
    default: break;
    }
}

void LApp::KeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch (sym) {
    case SDLK_LCTRL: {
	//nowDrawing = false;
	break;
    }
    case SDLK_s: {
	updatingstep = false;
	update_counter = 0;
	break;
    }
    default: break;
    }
}
    
void LApp::MouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
    if (nowDrawing && Right && !updating) {
	int i,j;
	i = (mX-graphics.SDL_OGL.x-graphics.dx)/(graphics.grid.cellsize+1);
	j = (mY-graphics.SDL_OGL.y-graphics.dy)/(graphics.grid.cellsize+1);
	if (i>=0 && j>=0 && i<(int)Board.x && j<(int)Board.y) life.Draw(i,j,whatDraw);
    }

    if (Left) {
	glTranslatef (relX, relY, 0);
	graphics.SDL_OGL.x+=relX;
	graphics.SDL_OGL.y+=relY;
    }
}

void LApp::MouseButtonDown(Uint8 button, int x, int y)
{
    switch (button) {
    case SDL_BUTTON_WHEELUP: {
	if (graphics.grid.cellsize == 1) graphics.grid.cellsize++;
	else graphics.grid.cellsize+=2;
	if (graphics.grid.cellsize>100) graphics.grid.cellsize = 100;

	graphics.dx = (graphics.width - graphics.grid.GetWidth() * graphics.grid.cellsize)/2;
	graphics.dy = (graphics.height - graphics.grid.GetHeight() * graphics.grid.cellsize)/2;
	break;
    }
    case SDL_BUTTON_WHEELDOWN: {
	graphics.grid.cellsize-=2;
	if (graphics.grid.cellsize<1) graphics.grid.cellsize = 1;

	graphics.dx = (graphics.width - graphics.grid.GetWidth() * graphics.grid.cellsize)/2;
	graphics.dy = (graphics.height - graphics.grid.GetHeight() * graphics.grid.cellsize)/2;
	break;
    }
    case SDL_BUTTON_RIGHT: {
	if (!updating) {
	    nowDrawing = true;
	    int i,j;
	    i = (x-graphics.SDL_OGL.x-graphics.dx)/(graphics.grid.cellsize+1);
	    j = (y-graphics.SDL_OGL.y-graphics.dy)/(graphics.grid.cellsize+1);
	    if (i>=0 && j>=0 && i<(int)Board.x && j<(int)Board.y) {
		if ((*life.front)(i, j) == 0) whatDraw = 1;
		else whatDraw = 0;
		life.Draw(i,j,whatDraw);
	    }
	}
	break;
    }
    default: break;
    }
}
	
void LApp::MouseButtonUp(Uint8 button, int x, int y)
{
    switch (button) {
    case SDL_BUTTON_RIGHT: {
	nowDrawing = false;
	whatDraw = 1;
	break;
    }
    default:break;
    }
}	
    
