//	##########################################################
//	By Eugene Ch'ng | www.complexity.io | 2018
//	Email: genechng@gmail.com
//	----------------------------------------------------------
//	A C++ SDL Application
//	Timer, s to reset timer, ESC to quit
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
void cleanup();

// ----------- flags
bool quit = false;

// ----------- SDL events
SDL_Event e;

// ----------- SCREEN INFO
int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 800;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

// ----------- TIMER
Uint32 gStartTime = 0;

int main()
{
    cout << "---- TIMER ----" << endl;
    //Start up SDL and create window
    if( !init() )
        cout << "Failed to initialise! SDL_Error:" << SDL_GetError() << endl;
    else
    {
        // ------------ TIMER
        gStartTime = SDL_GetTicks();
        cout << "Start Time: " << gStartTime << endl;

        while(!quit)
        {
            // ------------ TIMER
            cout << "Elapsed Time: " << SDL_GetTicks() - gStartTime << endl;

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
                        case SDLK_s:
                            gStartTime = SDL_GetTicks();
                            cout << "---- Timer reset: " << gStartTime << endl;
                            break;

                        default:
                            //cout << "default" << endl;
                        break;
                    }
                }
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
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 )
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
