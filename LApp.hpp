#include <SDL/SDL.h>
#include "Automaton.hpp"
#include "Graphics.hpp"

struct BoardSize {
    unsigned int x;
    unsigned int y;
};

class LApp {
 private:
    bool running;
    bool updating, updatingstep;
    int update_counter;
    int counter, speed;
    Automaton life;
    bool nowDrawing;
    statecode whatDraw;
    struct BoardSize Board;
    Graphics graphics;

    bool help;

    inline void __Init__(void);
    std::string rule;
 public:
    LApp();
    LApp(unsigned int x, unsigned int y, std::string r);
 public:
    bool Init();
    int Execute();

    void Event(SDL_Event *event);
    void Event_Field(SDL_Event *event);
    void Event_Help(SDL_Event *event);

    void Loop();

    void Render();
    void Render_Field();

    void Clean();
 public:
    void Exit();
    void KeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
    void HelpKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
    void KeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
    void MouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
    void MouseButtonDown(Uint8 button, int x, int y);
    void MouseButtonUp(Uint8 button, int x, int y);
};

inline void CatchErrorOpengl(int l);
