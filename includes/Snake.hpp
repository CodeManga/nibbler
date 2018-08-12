/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmthimun <hmthimun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 00:42:50 by hmthimun          #+#    #+#             */
/*   Updated: 2018/08/11 11:31:11 by hmthimun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKE_HPP
# define SNAKE_HPP

# include "SDL.h"
# include <iostream>
# include <deque>
class Snake {
private:
    SDL_Window      *_window;
    SDL_Renderer    *_renderer;
    SDL_Texture     *_sprites;
    std::deque<std::pair<int, int> > _segmentList;

    int             _speed;
    int             _score;
    // int             _highScore;
    // int             _topFiveHighScore[5];

public:
    Snake();
    ~Snake();

    int     exec(void);
    bool    tick();
    void    draw(void);

    const static auto HeadOpenMouth = 0;
    const static auto Tail = 1;
    const static auto BodyTurn = 2;
    const static auto BodyStraight = 3;
    const static auto Head = 4;
    const static auto Food = 5;
    const static auto Height = 720;
    const static auto Width = 1280;

    unsigned ticks = 0;
    int         dx = 1;
    int         dy = 0;

    
    
    int         fruitX;
    int         fruitY;

    void        generateFruit(void);



    // //WE CREATE THE COORDINATES OF THE MOUSE
    // int Mx = 0;
    // int My = 0;
    // bool play1 = false;
};
#endif