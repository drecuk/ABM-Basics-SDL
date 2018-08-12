//	##########################################################
//	By Eugene Ch'ng | www.complexity.io | 2018
//	Email: genechng@gmail.com
//	----------------------------------------------------------
//	A C++ SDL Application
//	SDL Event - Loads image and detects ESC key to quit
//
// How to compile:
// g++ -I/usr/include <filename>.cpp -o <output file> -L/usr/lib -lSDL2
// -I define the path to the includes folder
// -L define the path to the library folder
// -l ask the compiler to use the library
//	##########################################################

#include <iostream>
#include <SDL2/SDL.h>
//#include <SDL2_image/SDL_image.h>
using namespace std;

// ----------- PROTOTYPES
bool init();
bool loadmedia(string filename);
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

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gZombie = NULL;

int main()
{
    cout << "---- EVENTS ----" << endl;
    //Start up SDL and create window
    if( !init() )
    {
        cout << "Failed to initialize!" << endl;
    }
    else
    {
        //Load media
        if( !loadmedia("images/zombie.bmp") )
        {
            cout << "Failed to load media!" << endl;
        }
        else
        {
            while(!quit)
            {
                while( SDL_PollEvent( &e ) != 0)
                {
                    // user x out to quit
                    if(e.type == SDL_KEYDOWN)
                      if(e.key.keysym.sym == SDLK_ESCAPE)
                        quit = true;

                    //Apply the image
                    SDL_BlitSurface( gZombie, NULL, gScreenSurface, NULL );

                    //Update the surface
                    SDL_UpdateWindowSurface( gWindow );
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
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }

    return success;
}

bool loadmedia(string filename)
{
    cout << "Loading Media" << endl;
    bool success = true;

    gZombie = SDL_LoadBMP(filename.c_str());
    if(gZombie == NULL)
    {
        cout << "Error loading image!" << SDL_GetError() << endl;
        success = false;
    }

    return success;
}

void cleanup()
{
    cout << "---- cleaning up" << endl;
    SDL_FreeSurface(gZombie);
    gZombie = NULL;

    SDL_Quit();
}
