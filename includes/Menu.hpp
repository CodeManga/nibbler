/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Menu.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmthimun <hmthimun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 06:10:21 by hmthimun          #+#    #+#             */
/*   Updated: 2018/08/11 11:34:21 by hmthimun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_HPP
#define MENU_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <deque>
#include "Snake.hpp"

typedef struct  s_newgame
{
        int x;
        int y;
}               t_newgame;

typedef struct  s_highscore
{
        int x;
        int y;
}               t_highscore;

typedef struct  s_exit
{
        int x;
        int y;
}               t_exit;

typedef struct  s_menu
{
        t_newgame       newgame;
        t_highscore     highscore;
        t_exit          exit;
}               t_menu;

class Menu
{
      private:
        unsigned        ticks = 0;
        SDL_Window      *_window;
        SDL_Renderer    *_renderer;
        SDL_Texture     *_backroundTexture;
        SDL_Texture     *_gameMenuTexture;
        SDL_Event       e;
        t_menu          _menu;
       
        const static auto Height = 694;
        const static auto Width = 694;
        const static auto NewGameRed = 0;
        const static auto NewGameGreen = 1;
        const static auto HighScoreRed = 2;
        const static auto HighScoreGreen = 3;
        const static auto ExitRed = 4;
        const static auto ExitGreen = 5;
       
        int _mouseX;
        int _mouseY;
        int _pos[3][2];
        int _drawMenuSeg[3];
        

      public:

        Menu(void);
        Menu(const Menu &src);
        ~Menu(void);

        // Menu    &operator=(Menu const &rhs);
        
        void    drawMenu(const int nextSegment);
        int     showMenu(void);
        void    drawBackround(void);
        bool    tick(void);
        int     run(void);
        void    mouseHover(void);
        int     mouseClick(bool &done);
        int    manageKeys(bool &done);
        void    init(void);
};


#endif