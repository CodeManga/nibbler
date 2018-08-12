/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmthimun <hmthimun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 00:45:48 by hmthimun          #+#    #+#             */
/*   Updated: 2018/08/11 11:40:42 by hmthimun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Snake.hpp"
#include "includes/sdl_check.hpp"

Snake::Snake()
{
    int res = SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CHECK(res == 0, "SDL_Init");
    SDL_CreateWindowAndRenderer(Width, Height, SDL_WINDOW_BORDERLESS, &_window, &_renderer);
    SDL_CHECK(_window, "SDL_CreateWindowAndRenderer");
    SDL_CHECK(_renderer, "SDL_CreateWindowAndRenderer");

    // Positions of the window
    // TODO make the posion to be centrered
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    SDL_SetWindowPosition(_window, ((DM.w - Width) / 2), ((DM.h - Height) / 2));
    // SDL_SetWindowPosition(_window, 48, 32);


    // Load sprites from the Computer
    SDL_Surface *surface = SDL_LoadBMP("sprites.bmp");
    SDL_CHECK(surface, "SDL_LoadBMP(\"sprites\")");
    _sprites = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_CHECK(_sprites, "SDL_CreateTextureFromSurface");
    SDL_FreeSurface(surface);

    // Pushing in the segments of the snake in deque value pair
    // So we can get the basic three parts of the snake
    _segmentList.push_back((std::make_pair(6, 6))); //Head
    _segmentList.push_back((std::make_pair(5, 6))); // Body
    _segmentList.push_back((std::make_pair(5, 5))); // Tail
    _speed = 150;
    _score = 0;
    generateFruit();

    return;
}

void    Snake::generateFruit(void)
{
    // ToDo 
    // provide condition when not space left on the screen to print fruits
    bool done = false;
    do {
        fruitX = rand() % (Width / 64);
        fruitY = rand() % (Height / 64);
        done = true;
        for (const auto& segment: _segmentList){
            if (segment.first == fruitX && segment.second == fruitY){
                done = false;
                break ;
            }
        }
    } while (!done);
}

Snake::~Snake()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
    return;
}

int Snake::exec(void)
{
    auto oldTicks = SDL_GetTicks();
    for (bool done = false; !done;)
    {
        SDL_Event e;
        if (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_KEYDOWN:
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_UP:
                    dx = 0;
                    dy = -1;
                    break;
                case SDLK_DOWN:
                    dx = 0;
                    dy = 1;
                    break;
                case SDLK_LEFT:
                    dx = -1;
                    dy = 0;
                    break;
                case SDLK_RIGHT:
                    dx = 1;
                    dy = 0;
                    break;
                case SDLK_ESCAPE:
                    // ToDo Clear memory
                    // done = true;
                    return (0);
                    break;
                }
                
            }
            break;
            case SDL_QUIT:
                done = true;
                break;
            }
        }
        SDL_SetRenderDrawColor(_renderer, 0x00, 0x7f, 0x00, 0xff);
        SDL_RenderClear(_renderer);
        auto currentTicks = SDL_GetTicks();
        for (auto t = oldTicks; t < currentTicks; t++)
        {
            if (!(tick()))
                return (1);
        }
        oldTicks = currentTicks;
        draw();
        SDL_RenderPresent(_renderer);
    }

    return (0);
}

bool Snake::tick(void)
{
    if (_score >= 3 && _score < 6)
        _speed = 100;
    else if (_score >= 6 && _score < 9)
        _speed = 70;
    else if (_score >= 9 && _score < 12)
        _speed = 50;
    else if (_score >= 12)
        _speed = 30;
    std::cout << "score: " << _score << std::endl;
    if (ticks++ % _speed == 0)
    {                                         // adjusting frames per sec. in this case the snake moves four times per sec
        auto position = _segmentList.front(); // Head
        position.first += dx;
        position.second += dy;
        // Snake wall colussion detection
        if (position.first < 0 || position.first >= Width / 64 ||
            position.second < 0 || position.second >= Height / 64)
            return (false);
        // Snake body colussion detection
        for (const auto &segment: _segmentList){
            if (segment == position){
                return (false);
            }
        }
        _segmentList.push_front(position);
        if (position.first != fruitX || position.second != fruitY) {
            _segmentList.pop_back();
            // _score++;
        } else {
            _score++;
            generateFruit();
        }
    }
    return (true);
}

void Snake::draw(void)
{
    SDL_Rect src;
    src.h = 64;
    src.w = 64;
    src.x = 0; // Select segment from sprite 0 = HeadOpenMouth  64 = Tail  128 = BodyTurn  192 = BodyStraight  256 = Head  320 = Food
    src.y = 0;
    SDL_Rect dst;
    dst.h = 64;
    dst.w = 64;
    int dir[][3] = {
        {1, 0, 0},    // Move to the right and rotate sprite to 180deg. y is constatnt
        {-1, 0, 180}, // Move to the left withouth rotating. y is constatnt
        {0, 1, 90},   // Move down and rotate sprite 90deg
        {0, -1, 270}, // Move up and
    };

    // drawing snake
    int direction;
    for (auto itr = std::begin(_segmentList);
         itr != std::end(_segmentList); ++itr)
    {
        // (void) segment;
        direction = 0;
        const auto &segment = *itr;
        if (itr == std::begin(_segmentList))
        {
            // Choosing open mouth when snake is approching food
            if (itr->first + dx == fruitX && itr->second + dy == fruitY)
                src.x = HeadOpenMouth * 64;
            else
                src.x = Head * 64;
            if ((itr + 1) != std::end(_segmentList))
            {
                const auto &nextSegment = *(itr + 1);
                for (const auto &d : dir)
                {
                    if ((segment.first) == nextSegment.first + d[0] &&
                        (segment.second) == nextSegment.second + d[1])
                    {
                        direction = d[2];
                        break;
                    }
                }
            }
        }
        else if ((itr + 1) == std::end(_segmentList))
        {
            src.x = Tail * 64;
            const auto &prevSegment = *(itr - 1);
            for (const auto &d : dir)
            {
                if (segment.first + d[0] == (prevSegment.first) &&
                    segment.second + d[1] == (prevSegment.second))
                {
                    direction = d[2];
                    break;
                }
            }
        }
        else
        {
            const auto &nextSegment = *(itr + 1); // Head side
            const auto &prevSegment = *(itr - 1); // Tail side

            if (nextSegment.first == prevSegment.first)
            {
                src.x = BodyStraight * 64;
                direction = 90;
            }
            else if (nextSegment.second == prevSegment.second)
            {
                src.x = BodyStraight * 64;
                direction = 0;
            }
            else
            {
                src.x = BodyTurn * 64;
                bool up = false;
                if (segment.first == nextSegment.first && segment.second - 1 == nextSegment.second)
                    up = true;
                if (segment.first == prevSegment.first && segment.second - 1 == prevSegment.second)
                    up = true;

                bool down = false;
                if (segment.first == nextSegment.first && segment.second + 1 == nextSegment.second)
                    down = true;
                if (segment.first == prevSegment.first && segment.second + 1 == prevSegment.second)
                    down = true;

                bool left = false;
                if (segment.first - 1 == nextSegment.first && segment.second == nextSegment.second)
                    left = true;
                if (segment.first - 1 == prevSegment.first && segment.second == prevSegment.second)
                    left = true;

                bool right = false;
                if (segment.first + 1 == nextSegment.first && segment.second == nextSegment.second)
                    right = true;
                if (segment.first + 1 == prevSegment.first && segment.second == prevSegment.second)
                    right = true;

                if (up && right)
                    direction = 0;
                else if (right && down)
                    direction = 90;
                else if (left && down)
                    direction = 180;
                else if (up && left)
                    direction = 270;
            }
        }

        dst.x = 64 * (segment.first); // Move sprite left - right which modifies the first value in the _sagment(5++, 5) _segment(first, second)
        dst.y = 64 * segment.second;  // Move sprite Up - Down which modifies the second value in the _sagment(5, 5++) _segment(first, second)
        SDL_RenderCopyEx(_renderer, _sprites, &src, &dst, direction, nullptr, SDL_FLIP_NONE);
    }
    // drawing fruits
    src.x = Food * 64;
    dst.x = fruitX * 64;
    dst.y = fruitY * 64;
    SDL_RenderCopyEx(_renderer, _sprites, &src, &dst, 0, nullptr, SDL_FLIP_NONE);
}