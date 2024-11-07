#include <exception>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <fstream>

#include <gl/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <gl/glu.h>

#include "Global.h"

#include "Shader.h"
#include "Ball.h"
#include "Line.h"
#include "Texture.h"
#include "Skeleton.h"

//eee
int main( int argc, char * argv[] )
{
    int width = 640, height = 480;
    bool running = true;

    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		std::cout << "Failed to initialize SDL:\n" << SDL_GetError() << std::endl;
		return -1;
	}
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    //Define the window and context
	SDL_Window* win = NULL;
	SDL_GLContext ctx = NULL;

    win = SDL_CreateWindow( "Catz", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );

    if( win == NULL )
	{
		std::cout << "Failed to create Window:\n" <<SDL_GetError() << std::endl;
		return -1;
	}

	ctx = SDL_GL_CreateContext( win );
    if( ctx == NULL )
    {
        std::cout << "Failed to initialize OpenGL context:\n" << SDL_GetError() << std::endl;
        return -1;
    }

    GLenum glewError = glewInit();
    if( glewError != GLEW_OK )
    {
        std::cout << "Failed to initialize GLEW:\n" << glewGetErrorString(glewError) << std::endl;
        return -1;
    }

    //Use Vsync
    /*if( SDL_GL_SetSwapInterval( 1 ) < 0 )
    {
        std::cout << "[WARNING] Unable to set VSync:\n" << SDL_GetError() << std::endl;
    }*/

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //-------------------------------------------------------------------------

    Global.Configure(width, height);

    //-------------------------------------------------------------------------

    Texture tex;

    //tex.Init("art/texture/hair24.bmp");
    tex.InitBlankState();
    tex.Use();


    //Spooky* Scary* Skeletons* (to do: do it better)
    //Skeleton skeleton;
    //skeleton.Init();

    /* TEMPORARY */

    Ball* ball1 = new Ball();
    Ball* ball2 = new Ball();

    ball1->SetDiameter(200);
    ball2->SetDiameter(200);

    ball1->SetCoords(150.f, 200.f, 0.f);
    ball2->SetCoords(490.f, 200.f, 0.f);

    //line

    Line* line = new Line();

    line->SetStartAndEndBalls(ball1, ball2);

    /*END TEMPORARY*/

    SDL_Event event;

    //

    while (running){
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
        }

        glViewport(0, 0, width, height);
        glClearColor( 156.f / 255.f, 226.f/255.f, 218.f/255.f, 1.f );
        glClear(GL_COLOR_BUFFER_BIT);

        /*TEMP*/

        line->Draw();

        ball1->Draw();
        ball2->Draw();

        /*END TEMP*/

        //skeleton.Update();

        //skeleton.Render();

        SDL_GL_SwapWindow(win);
        SDL_Delay(30);
    }

    return 0;
}
