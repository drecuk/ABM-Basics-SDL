//	##########################################################
//	By Eugene Ch'ng | www.complexity.io | 2018
//	Email: genechng@gmail.com
//	----------------------------------------------------------
//	A C++ SDL Application
//	Initialising SDL and a Window that opens for 5 seconds
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

int main()
{
    // init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        // outputs error if init not successful
        cout << "ERROR SDL_Init" << endl;

        return -1; // quits the application
    }

    // create a window
    SDL_Window * window = SDL_CreateWindow(
        "SDL 2 window",             // window title
        SDL_WINDOWPOS_CENTERED,     // x position, centered
        SDL_WINDOWPOS_CENTERED,     // y position, centered
        640,                        // width, in pixels
        480,                        // height, in pixels
        SDL_WINDOW_OPENGL           // flags (preparing for OpenGL)
    );

    // wait 5 secs
    SDL_Delay(5000);

    // clean up
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
