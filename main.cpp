/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmthimun <hmthimun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 23:33:53 by hmthimun          #+#    #+#             */
/*   Updated: 2018/08/11 11:30:51 by hmthimun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Snake.hpp"
#include "includes/sdl_check.hpp"
#include "includes/Menu.hpp"
#include <iostream>
#include <stdexcept>

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    // try {
        Menu menu;
        bool runMenu = false;
        if (menu.run() == 1){
            while (!runMenu)
            {
                Snake s;
                // if (s.exec() == 2)
                int snakeExec = s.exec();
                std::cout << "return value of exec: " << snakeExec << std::endl;
                // Game Over
                if (snakeExec == 1){
                    runMenu = false;
                }else { // Pressed Escape (pause/exit)
                //!will deal  with later
                    runMenu = false;                    
                }
                if (runMenu == false){
                    Menu menu1;
                    int menuRun = menu1.run();
                    
                    if (menuRun == 1)
                        runMenu = false;
                    else
                        runMenu = true;
                }
            }
            
        }
      return (0);
    // } catch (std::exception &e){
    //     std::cerr << "\nGAME CRASH EXCEPTION:\n\t" << e.what() << "\n" << std::endl;
    //     return (1);
    // }
}