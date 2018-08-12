//	##########################################################
//	By Eugene Ch'ng | www.complexity.io | 2018
//	Email: genechng@gmail.com
//	----------------------------------------------------------
//	A C++ SDL Application
//	Tracking mouse position, ESC to quit
//
// How to compile:
// g++ -I/usr/include <filename>.cpp -o <output file> -L/usr/lib -lSDL2
// -I define the path to the includes folder
// -L define the path to the library folder
// -l ask the compiler to use the library
//	##########################################################

#include <iostream>
#include <SDL2/SDL.h>
using namespace std;

// ----------- PROTOTYPES
bool init();
SDL_Surface* loadSurface( std::string path );
bool loadmedia(string filename);
void cleanup();

// ----------- flags
bool quit = false;

// ----------- SDL events
SDL_Event e;

// ----------- SCREEN INFO
int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;


int main()
{
    cout << "---- KEYBOARD EVENTS ----" << endl;
    //Start up SDL and create window
    if( !init() )
        cout << "Failed to initialise! SDL_Error:" << SDL_GetError() << endl;
    else
    {
        while(!quit)
        {

            while( SDL_PollEvent( &e ) != 0)
            {
                // ---- KEYBOARD EVENT
                if (e.type == SDL_KEYDOWN)
                {
                    switch(e.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            quit = true;
                        break;

                        default:
                            //cout << "default" << endl;
                        break;
                    }
                }

                // ---- MOUSE EVENT
                if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN
                        || e.type == SDL_MOUSEBUTTONUP)
                {
                    // get mouse position
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    cout << x << "," << y << endl;

                    // check mouse button
                    switch(e.type)
                    {
                        case SDL_MOUSEMOTION:
                            // mouse is moving
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            // mouse button down
                            cout << "mouse down" << endl;
                            break;
                        case SDL_MOUSEBUTTONUP:
                            // mouse button up
                            cout << "mouse up" << endl;
                            break;
                        default:
                        break;
                    }
                }

                // ------------ DRAW EVERYTHING HERE

                // ------------ DRAW EVERYTHING HERE END
            }
        }

    }

    //Free resources and close SDL
    cleanup();

    return 0;
}

bool init()
{
    cout << "---- init SDL ----" << endl;
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        cout << "SDL could not initialize! SDL_Error:" << SDL_GetError() << endl;
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow(
                "SDL Tutorial",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
                SDL_WINDOW_SHOWN
                );

        if( gWindow == NULL )
        {
            cout <<  "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
            success = false;
        }
    }

    return success;
}

void cleanup()
{
    cout << "---- cleaning up" << endl;
    gWindow = NULL;

    SDL_Quit();
}
