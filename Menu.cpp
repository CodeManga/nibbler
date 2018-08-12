/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Menu.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmthimun <hmthimun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 20:17:25 by hmthimun          #+#    #+#             */
/*   Updated: 2018/08/11 11:34:28 by hmthimun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL2/SDL.h>
#include <iostream>
#include <deque>
#include "includes/Menu.hpp"

// Todo list
// ?Draw boarder
// ?Memory Leaks
// ?Create and implement special food for bonus points
// ?implements start new game and continue under key events
// ?draw High score on the screen
// ?implement top 10 high feature
// ?Convert this into a class and
// ?Destroy all method

Menu::Menu(void)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(Width, Height, SDL_WINDOW_BORDERLESS, &_window, &_renderer);

    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    SDL_SetWindowPosition(_window, ((DM.w - Width) / 2), ((DM.h - Height) / 2));

    SDL_Surface *surface = SDL_LoadBMP("backround1.bmp");
    _backroundTexture = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_FreeSurface(surface);

    // Load sprites from the Computer
    SDL_Surface *surfaceMenu = SDL_LoadBMP("gamemenu.bmp");
    _gameMenuTexture = SDL_CreateTextureFromSurface(_renderer, surfaceMenu);
    SDL_FreeSurface(surfaceMenu);

    init();
}

Menu::Menu(const Menu &src)
{
    *this = src;
}

Menu::~Menu(void)
{
    return;
}

// Menu &Menu::operator=(Menu const &rhs)
// {
//     return (*this);
// }

void Menu::init(void)
{
    _pos[0][0] = _menu.newgame.y = Height * 55.3 / 100; // Move sprite Up - Down which modifies the second value in the _sagment(5, 5++) _segment(first, second)
    _pos[0][1] = _menu.newgame.x = Width * 41.2 / 100;  // Move sprite left - right which modifies the first value in the _sagment(5++, 5) _segment(first, second)

    // High Score
    _pos[1][0] = _menu.highscore.y = Height * 68.1 / 100; // Move sprite Up - Down which modifies the second value in the _sagment(5, 5++) _segment(first, second)
    _pos[1][1] = _menu.highscore.x = Width * 41.2 / 100;  // Move sprite left - right which modifies the first value in the _sagment(5++, 5) _segment(first, second)

    // Exit Game
    _pos[2][0] = _menu.exit.y = Height * 80.8 / 100;
    _pos[2][1] = _menu.exit.x = Width * 40.9 / 100; // Move sprite left - right which modifies the first value in the _sagment(5++, 5) _segment(first, second)

    _drawMenuSeg[0] = NewGameRed;
    _drawMenuSeg[1] = HighScoreRed;
    _drawMenuSeg[2] = ExitRed;
}

int Menu::run(void)
{
    auto oldTime = SDL_GetTicks();

    for (bool done = false; !done;)
    {
        if (manageKeys(done))
            return (1);
        drawBackround();
        drawMenu(_drawMenuSeg[0]);
        drawMenu(_drawMenuSeg[1]);
        drawMenu(_drawMenuSeg[2]);
        SDL_RenderPresent(_renderer);

        auto currentTime = SDL_GetTicks();
        if (1000 / 30 > currentTime - oldTime)
        {
            SDL_Delay(1000 / 30 - (currentTime - oldTime));
        }
    }
    return (0);
}

int Menu::manageKeys(bool &done)
{
    // Key Events for the _menu
    if (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
        case SDL_KEYDOWN:
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                // !Clear memory
                done = true;
                break;
            }
        }
        break;
        case SDL_QUIT:
            done = true;
            break;
        case SDL_MOUSEMOTION:
            _mouseX = e.motion.x;
            _mouseY = e.motion.y;
            mouseHover();
            break;
        // When pressing a button of the mouse
        case SDL_MOUSEBUTTONDOWN:
            _mouseX = e.button.x;
            _mouseY = e.button.y;
            // Implement New Game action
            if (mouseClick(done))
                return (1);
            break;
        }
    }
    return (0);
}

int Menu::mouseClick(bool &done)
{
    if (_mouseX >= 285 && _mouseX <= (285 + 129) && _mouseY >= 383 && _mouseY <= (383 + 25))
        return (1);
    else
        _drawMenuSeg[0] = NewGameRed;
    // Implement High Score Action
    if (_mouseX >= 285 && _mouseX <= (285 + 129) && _mouseY >= 472 && _mouseY <= (472 + 25))
        _drawMenuSeg[1] = HighScoreGreen;
    else
        _drawMenuSeg[1] = HighScoreRed;
    // Implenet Exit Action
    // ToDo
    // Exit the entire game or go back to the main game _menu
    if (_mouseX >= 283 && _mouseX <= (285 + 129) && _mouseY >= 560 && _mouseY <= (560 + 25))
        done = true;
    else
        _drawMenuSeg[2] = ExitRed;
    return (0);
}

void Menu::mouseHover(void)
{
    // New Gamge
    if (_mouseX >= 285 && _mouseX <= (285 + 129) && _mouseY >= 383 && _mouseY <= (383 + 25))
        _drawMenuSeg[0] = NewGameGreen;
    else
        _drawMenuSeg[0] = NewGameRed;
    // High Score
    if (_mouseX >= 285 && _mouseX <= (285 + 129) && _mouseY >= 472 && _mouseY <= (472 + 25))
        _drawMenuSeg[1] = HighScoreGreen;
    else
        _drawMenuSeg[1] = HighScoreRed;
    // Exit
    if (_mouseX >= 283 && _mouseX <= (285 + 129) && _mouseY >= 560 && _mouseY <= (560 + 25))
        _drawMenuSeg[2] = ExitGreen;
    else
        _drawMenuSeg[2] = ExitRed;
}

void Menu::drawMenu(const int nextSegment)
{
    SDL_Rect src;
    src.h = 25;
    src.w = 129;
    src.x = 0;
    src.y = nextSegment * 25;
    SDL_Rect dst;
    dst.h = 25;
    dst.w = 129;

    if (nextSegment == NewGameGreen || nextSegment == NewGameRed)
    {
        // New Game
        dst.x = _menu.newgame.x;
        dst.y = _menu.newgame.y;
    }
    else if (nextSegment == HighScoreGreen || nextSegment == HighScoreRed)
    {
        // High Score
        dst.x = _menu.highscore.x;
        dst.y = _menu.highscore.y;
    }
    else if (nextSegment == ExitGreen || nextSegment == ExitRed)
    {
        // Exit Game
        dst.x = _menu.exit.x;
        dst.y = _menu.exit.y;
    }
    SDL_RenderCopyEx(_renderer, _gameMenuTexture, &src, &dst, 0, nullptr, SDL_FLIP_NONE);
}

void Menu::drawBackround(void)
{
    SDL_Rect src;
    src.h = 694;
    src.w = 694;
    src.x = 0; // Select segment from sprite 0 = HeadOpenMouth  64 = Tail  128 = BodyTurn  192 = BodyStraight  256 = Head  320 = Food
    src.y = 0;
    SDL_Rect dst;
    dst.h = 694;
    dst.w = 694;

    dst.x = 0; // Move sprite left - right which modifies the first value in the _sagment(5++, 5) _segment(first, second)
    dst.y = 0; // Move sprite Up - Down which modifies the second value in the _sagment(5, 5++) _segment(first, second)
    SDL_RenderCopyEx(_renderer, _backroundTexture, &src, &dst, 0, nullptr, SDL_FLIP_NONE);
}

bool Menu::tick(void)
{
    if (ticks++ % 150 == 0)
    {
        return (false);
    }
    return (true);
}
