# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmthimun <hmthimun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/07 03:40:34 by hmthimun          #+#    #+#              #
#    Updated: 2018/08/12 17:25:30 by hmthimun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    nibbler.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmthimun <hmthimun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/03 23:08:53 by hmthimun          #+#    #+#              #
#    Updated: 2018/08/07 03:19:25 by hmthimun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SFML_FILE_NAME	=

DOWNLOADLINK	=

EXTRACT			=

CC 				=

ifeq ($(OS),Windows_NT)
	CC += g++ -g -std=c++11
	DOWNLOADLINK += https://www.sfml-dev.org/files/SFML-2.5.0-windows-vc12-64-bit.zip
	SFML_FILE_NAME += SFML-2.5.0-windows-vc12-64-bit.zip
	EXTRACT += unzip -o $(SFML_FILE_NAME) 
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CC += g++ -g -std=c++11
		DOWNLOADLINK += https://www.sfml-dev.org/files/SFML-2.5.0-linux-gcc-64-bit.tar.gz
		SFML_FILE_NAME += SFML-2.5.0-linux-gcc-64-bit.tar.gz
		EXTRACT += unzip -o $(SFML_FILE_NAME) 
	endif
	ifeq ($(UNAME_S),Darwin)
		CC += clang++ -g -std=c++11
		DOWNLOADLINK += https://www.sfml-dev.org/files/SFML-2.5.0-macOS-clang.tar.gz
		SFML_FILE_NAME += SFML-2.5.0-macOS-clang.tar.gz
		EXTRACT += gunzip -c $(SFML_FILE_NAME) | tar xf -
	endif
endif

all:
	@echo $(CC)
# NAME = nibbler

# CC = g++ -g -std=c++11

# CFLGS = -Wall -Wextra -Werror

# SDL = SDL/SDL2-2.0.8/

# SDL2 = -L $(SDL)lib -lm -I $(SDL)include -l SDL2 

# SRC = main.cpp Snake.cpp \

# HEADER = includes


# all: run $(NAME)

# $(NAME): exec

# run:
# 	# wget -N https://libsdl.org/release/SDL2-2.0.8.zip
# 	touch $@
# 	unzip -o SDL2-2.0.8.zip  -d SDL
# 	$(SDL)./configure
# 	make
# 	make install
# #	./nibbler map.txt

# exec: fclean
# 	@echo "\nCompiling nibbler files"
# 	@$(CC) -o $(NAME) $(CFLGS) $(SRC) -I $(HEADER) $(SDL2)
# 	@./$(NAME)

# clean:
# 	@echo "\nCleaning nibbler object files\n"	
# 	@/bin/rm -f $(OBJ)

# fclean: clean
# 	@echo "\nRemoving nibbler binary file"	
# 	@/bin/rm -f $(NAME)

# re: fclean all



# 
# NAME = nibbler

# CFLGS = -Wall -Wextra -Werror

# SDL2 = -L ~/lib -lm -I includes/SDL2/ -l SDL2 

# SRC = main.cpp Snake.cpp Menu.cpp \

# LIBFT = libft/

# HEADER = includes

# $(SFML):
# 	curl -O 

# $(FREESTYLE):
# 	curl -O https://download.savannah.gnu.org/releases/freetype/ft291.zip
# 	gunzip -c freetype-2.9.1.tar.gz | tar xf -
# $(SDL_LIB):
# 	@echo "\nCompiling SDL2"
# 	curl -O https://libsdl.org/release/SDL2-2.0.8.tar.gz
# 	gunzip -c SDL2-2.0.8.tar.gz | tar xf -
# 	cd SDL2-2.0.8; \
# 	mkdir build; \
# 	cd build; \
# 	../configure; \
# 	make
# 	mkdir -p ~/lib/
# 	cp SDL2-2.0.8/build/build/.libs/libSDL2-2.0.0.dylib ~/lib/
# 	ln -F -s ~/lib/libSDL2-2.0.0.dylib ~/lib/libSDL2.dylib
# 	mkdir -p includes/SDL2
# 	cp SDL2-2.0.8/include/*.h includes/SDL2/

# $(SDL_TTF):
# 	@echo "\nCompiling SDL2_TTF"
# 	curl -O https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.14.tar.gz
# 	gunzip -c SDL2_ttf-2.0.14.tar.gz | tar xf -
# 	cd SDL2_ttf-2.0.14
# 	mkdir build; \
# 	cd build; \
# 	../configure; \
# 	make
# 	mkdir -p ~/lib/

# $(NAME):
# 	@echo "\nCompiling nibbler files"
# 	@$(CC) -o $(NAME) $(CFLGS) $(SRC) -I $(HEADER) $(SDL2)

# all: $(NAME) $(SDL_LIB) $(FREESTYLE) $(SDL_TTF) 

# clean:
# 	@echo "\nCleaning nibbler object files\n"	
# 	@/bin/rm -f $(OBJ)

# fclean: clean
# 	@echo "\nRemoving nibbler binary file"	
# 	@/bin/rm -f $(NAME)
# 	# rm -rf SDL2-2.0.8
# 	# rm -rf ./includes/SDL2
# 	# rm -rf ~/lib
# 	# rm -rf SDL2-2.0.8.tar.gz

# re: fclean all

# run:
# 	@echo "\nCompiling nibbler files"
# 	@$(CC) -o $(NAME) $(CFLGS) $(SRC) -I $(HEADER) $(SDL2)
# 	@echo "\nCleaning nibbler object files\n"	
# 	@/bin/rm -f $(OBJ)
# 	reset
# 	./nibbler
