#pragma once

#include <stdio.h>
#include <iostream>
#include <memory>
#include <SDL2/SDL_ttf.h>
#include "OWL/globals.h"
#include "OWL/window.h"
#include "OWL/msg.h"
#include "OWL/draw.h"
#include "OWL/screen.h"
#include "screens.h"
#include "OWL/input.h"

class Game : public OWL::BusNode
{
public:
    Game();

protected:
    std::shared_ptr<OWL::MessageBus> messageBus = nullptr;
    std::shared_ptr<SDL_Window> window = nullptr;
    std::shared_ptr<OWL::Draw> draw = nullptr;          //std::make_shared<OWL::Draw>(messageBus, window.get());
    std::shared_ptr<game::Console> console = nullptr;   //std::make_shared<game::Console>(messageBus, draw, 0, OWL::SCREEN_HEIGHT - OWL::SCREEN_HEIGHT / 4, OWL::SCREEN_WIDTH, OWL::SCREEN_HEIGHT / 4);
    std::shared_ptr<game::StartScreen> start = nullptr; //std::make_shared<game::StartScreen>(messageBus, draw, 0, 0, OWL::SCREEN_WIDTH, OWL::SCREEN_HEIGHT);
    std::shared_ptr<OWL::Input> input = nullptr;        //std::make_shared<OWL::Input>(messageBus);
};