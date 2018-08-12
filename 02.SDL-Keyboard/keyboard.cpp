//	##########################################################
//	By Eugene Ch'ng | www.complexity.io | 2018
//	Email: genechng@gmail.com
//	----------------------------------------------------------
//	A C++ SDL Application
//	SDL Keyboard event - arrow keys and ESC for quit
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

// ----------- PROTOTYPES DECLARATION
bool init();
void cleanup();

// ----------- flags
bool quit = false;

// ----------- SDL events
SDL_Event e;

// ----------- SCREEN INFO
int SCREEN_WIDTH = 1024;
int SCREEN_HEIGHT = 1024;

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
        while(!quit) // keep looping until quit
        {
            while( SDL_PollEvent( &e ) != 0)
            {
                // keyboard key pressed
                if (e.type == SDL_KEYDOWN)
                {
                    // determine which key is pressed
                    switch(e.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            quit = true;
                        break;

                        case SDLK_UP:
                            cout << "keyup" << endl;
                        break;

                        case SDLK_DOWN:
                            cout << "keydown" << endl;
                        break;

                        case SDLK_LEFT:
                            cout << "left key" << endl;
                        break;

                        case SDLK_RIGHT:
                            cout << "right key" << endl;
                        break;

                        default:
                            cout << "default" << endl;
                        break;
                    }
                }

                // ------------ DRAW EVERYTHING HERE (using SDL or OpenGL)

                // ------------ DRAW EVERYTHING HERE END
            }
        }

    }

    //Free resources and close SDL
    cleanup();

    return 0;
}

// init SDL is now moved to a function for
// good software engineering practice - manageability
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

// cleanup is also separated
void cleanup()
{
    cout << "---- cleaning up" << endl;
    gWindow = NULL;

    SDL_Quit();
}
