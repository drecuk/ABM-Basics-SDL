//	##########################################################
//	By Eugene Ch'ng | www.complexity.io | 2018
//	Email: genechng@gmail.com
//	----------------------------------------------------------
//	A C++ SDL Application
//	Loading and displaying a bitmap
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

SDL_Window *gWindow = NULL;
SDL_Surface *gSurface = NULL;
SDL_Surface* gImage = NULL;

int main()
{
    SDL_Init( SDL_INIT_VIDEO ); // initialize SDL

    // create an SDL window
    gWindow = SDL_CreateWindow( "Basic Image", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN );

    gSurface = SDL_GetWindowSurface( gWindow );     // Get the surface of the window
    gImage = SDL_LoadBMP( "images/zombie.bmp" );    // load bitmap

    // apply the image to the surface of the window
    SDL_BlitSurface( gImage, NULL, gSurface, NULL );
    SDL_UpdateWindowSurface( gWindow );             // update the surface

    SDL_Delay( 5000 );  // wait five seconds

    // freeing and destroying memory objects
    SDL_FreeSurface( gImage );
    SDL_FreeSurface( gSurface );
    gImage = NULL;
    gSurface = NULL;
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    SDL_Quit(); // quit SDL

    return 0;
}
