/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_check.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmthimun <hmthimun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 00:54:14 by hmthimun          #+#    #+#             */
/*   Updated: 2018/08/07 03:23:58 by hmthimun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_CHECK_HPP
# define SDL_CHECK_HPP

# include <string>
# include <stdexcept>

# include "Snake.hpp"

# define SDL_CHECK(x, msg) if (!(x)) throw std::runtime_error(std::string(msg": ") + SDL_GetError())

#endif