//	##########################################################
//	By Eugene Ch'ng | www.complexity.io | 2018
//	Email: genechng@gmail.com
//	----------------------------------------------------------
//	A C++ SDL Application
//	Displaying Text, ESC to quit
//
// install SDL2_TTF
// sudo apt-get install libsdl2-ttf-dev libsdl2-ttf-2.0-0
//
// How to compile:
// g++ -I/usr/include <filename>.cpp -o <output file> -L/usr/lib -lSDL2 -lSDL2_TTF
// -I define the path to the includes folder
// -L define the path to the library folder
// -l ask the compiler to use the library
//	##########################################################

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
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

SDL_Renderer *gRenderer;

//SDL_Surface *gScreenSurface;

//The window we'll be rendering to
SDL_Window *gWindow = NULL;

int main()
{
    cout << "---- TEXT ----" << endl;
    //Start up SDL and create window
    if( !init() )
        cout << "Failed to initialise! SDL_Error:" << SDL_GetError() << endl;
    else
    {
        // ------------ SETUP EVERYTHING HERE
        // Initialize SDL_ttf library
        if (TTF_Init() != 0)
        {
          cout << "TTF_Init() failed: " << TTF_GetError() << endl;
          SDL_Quit();
          exit(1);
        }

        // Load a font from the fonts directory
        //cout<<"LOADING FONT"<<endl;
        TTF_Font *font = TTF_OpenFont("fonts/Arial.ttf", 24);
        if (font == NULL)
        {
          cout << "TTF_OpenFont() failed: " << TTF_GetError() << endl;
          TTF_Quit();
          SDL_Quit();
          exit(1);
        }

        SDL_Color color = { 255, 255, 255 };
        SDL_Surface * surface = TTF_RenderText_Solid(
            font,
            "I'm the greatest!",
            color
        );

        SDL_Texture * texture = SDL_CreateTextureFromSurface(gRenderer, surface);
        SDL_Rect textRect = { 0, 0, 200, 50 };

        // ------------ SETUP EVERYTHING HERE END
        while(!quit)
        {
            while( SDL_PollEvent( &e ) != 0)
            {
                // user x out to quit
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

                // ------------ DRAW EVERYTHING HERE
                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
                SDL_RenderClear( gRenderer );

                SDL_RenderCopy(gRenderer, texture, NULL, &textRect);
                SDL_RenderPresent(gRenderer);

                //SDL_UpdateWindowSurface( gWindow );
                // ------------ DRAW EVERYTHING HERE ENDS
            }
        }

        //Free resources and close SDL
        cout << "----- cleaning up" << endl;
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);

        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        TTF_Quit();
        SDL_Quit();
    }

    return 0;
}

bool init()
{
    cout << "---- init SDL ----" << endl;
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        cout << "Error initialising! SDL_Error:" << SDL_GetError() << endl;
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow(
                "SDL",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
                SDL_WINDOW_SHOWN
                );

        if( gWindow == NULL )
        {
            cout <<  "Error creating Window! SDL_Error: " << SDL_GetError() << endl;
            success = false;
        }
        else
            gRenderer = SDL_CreateRenderer(gWindow, -1, 0);

    }

    return success;
}
