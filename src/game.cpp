#include <stdio.h>
#include <memory>
#include "framework/window.h"
#include "msg.h"
#include "framework/draw.h"
//#include "framework/text.h"
#include <SDL2/SDL_ttf.h>

//=========================================================
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

std::shared_ptr<game::MessageBus> messageBus = nullptr;
std::shared_ptr<SDL_Window> window = nullptr;
//SDL_Renderer *gRenderer = nullptr;

bool init()
{
    messageBus = std::make_shared<game::MessageBus>();
    if (messageBus == nullptr)
    {
        std::cout << "messageBus creation failed!" << std::endl;
        return false;
    }

    window = framework::createWindow("game 23", SCREEN_WIDTH, SCREEN_HEIGHT);
    if (window == nullptr)
    {
        std::cout << "Window creation failed!" << std::endl;
        return false;
    }

    //gRenderer = SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    TTF_Init();

    return true;
}

void close()
{
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *argv[])
{
    if (!init())
    {
        std::cout << "Failed to initialize!" << std::endl;
        return -1;
    }

    std::shared_ptr<framework::Draw> draw = std::make_shared<framework::Draw>(window.get());
    std::shared_ptr<game::Console> console = std::make_shared<game::Console>(messageBus, draw, 0, 0, 0, 0);
    std::shared_ptr<game::StartScreen> start = std::make_shared<game::StartScreen>(draw, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (console == nullptr || start == nullptr)
    {
        std::cout << "error";
    }

    bool quit = false;
    SDL_Event e;
    auto screenSurface = SDL_GetWindowSurface(window.get());

    int lctrl = 0, rctrl = 0;
    bool inputText = false;
    while (!quit)
    {
        SDL_RenderClear(draw->renderer.get());
        SDL_RenderSetViewport(draw->renderer.get(), NULL);
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            //frameStart = SDL_GetTicks();

            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_c:
                    if (lctrl)
                        console->openConsole(inputText);
                    break;

                //Handle backspace
                case SDLK_BACKSPACE:
                    console->backSpace();
                    break;
                case SDLK_RETURN:
                    console->enter();
                    break;

                case SDLK_RCTRL:
                    rctrl = 1;
                    break;
                case SDLK_LCTRL:
                    lctrl = 1;
                    break;
                }
            }
            else if (e.type == SDL_KEYUP)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_RCTRL:
                    rctrl = 0;
                    break;
                case SDLK_LCTRL:
                    lctrl = 0;
                    break;
                }
            }

            else if (e.type == SDL_TEXTINPUT && inputText)
            {
                console->writeToConsole(e.text.text);
            }
        }
        start->update();
        console->update();
        messageBus->notify();
        draw->update();
        SDL_Delay(40);
    }

    close();
    return 0;
}