# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: f0rsunka <f0rsunka@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/04 17:57:04 by cvernius          #+#    #+#              #
#    Updated: 2020/06/12 14:54:24 by f0rsunka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL = /bin/zsh

PINK = \033[38;2;200;150;200m
BLUE = \033[38;2;200;200;250m
DEFAULT = "\033[0;0m"
GREEN = "\033[0;32m"
DEEP_BLUE = "\033[0;34m"

NAME = tests

SRC_DIR = ./srcs
SRC_3D_DIR = ./3d

OBJ_DIR = ./obj

INCL_DIR = ./includes

C_FILES = main.c \
		 init_window.c \
		 main_loop.c \
		 error.c \
		 simple_parse.c \
		 dda.c \
		 add_walls.c \
		 mouse_events.c \
		 key_event.c \
		 is_inside.c \
		 possible_vision.c

C_FILES_3D = 	init_3d.c \
                update_image.c \
                draw_wall.c \
                textures.c \
                wall_params.c

OBJ_FILES = $(C_FILES:.c=.o)
OBJ_FILES_3D = $(C_FILES_3D:.c=.o)

RAW_OBJ_FILES = $(addprefix $(OBJ_DIR)/1_,$(OBJ_FILES))
RAW_OBJ_FILES_3D = $(addprefix $(OBJ_DIR)/2_,$(OBJ_FILES_3D))
DEPS = $(RAW_OBJ_FILES:.o=.d)
DEPS_PARSING = $(RAW_OBJ_FILES_3D:.o=.d)

SDL_DIR		=	./SDL
SDL_DIST	=	$(PWD)/SDL/dist
SDL_INCLUDE =	$(SDL_DIR)/dist/include/SDL2
SDL_LINK	=	`$(SDL_DIST)/bin/sdl2-config --cflags --libs`

LIBFT_FLAGS = -L ./libft -lft

detected_OS := $(shell uname)

ifeq ($(detected_OS),Linux)

	SDL_FLAGS := -lOpenCL

endif

ifeq ($(detected_OS),Darwin) 

	SDL_FLAGS = -framework OpenCL

endif

CFLAGS_ERRORS = -Wall -Wextra #-Werror
CFLAGS_DEPENDENCIES = -MMD -MP
CFLAGS_INCLUDES = -I $(INCL_DIR) -I $(SDL_INCLUDE) -I ./libft/include

CFLAGS_FINAL =	$(CFLAGS_INTERNAL) \
				$(CFLAGS_ERRORS) \
				$(CFLAGS_DEPENDENCIES) $(CFLAGS_INCLUDES) \
				$(CFLAGS)

LDFLAGS =	$(LIBFT_FLAGS) $(LIBVECTOR_FLAGS) -lm $(SDL_LINK)

.PHONY: all clean clean_libs clean_SDL clean_self fclean re

all:
	@echo "$(BLUE)" "Making libft" $(DEFAULT)
	@echo -n $(DEEP_BLUE)
	$(MAKE) -C ./libft
	@echo -n $(DEFAULT)

	@echo "$(BLUE)" "Making tests" $(DEFAULT)
	@echo -n $(GREEN)
	$(MAKE) $(NAME)
	@echo -n $(DEFAULT)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): ./libft/libft.a $(SDL_DIST) $(RAW_OBJ_FILES) $(RAW_OBJ_FILES_3D)
	gcc -o $(NAME) $(RAW_OBJ_FILES) $(RAW_OBJ_FILES_3D) $(LDFLAGS)
	@echo "$(PINK)(*≧ω≦*)  $(BLUE)Mama, ya sobralsya  $(PINK)(*≧ω≦*)"

$(SDL_DIST):
	$(info ************ Compiling SDL *************)
	$(info --prefix=$(SDL_DIST))
	mkdir -p $(SDL_DIR)/tmp
	cd $(SDL_DIR)/tmp; ../configure --prefix=$(SDL_DIST)
	make -C $(SDL_DIR)/tmp
	make -C $(SDL_DIR)/tmp install > /dev/null
	$(info SDL_LINK: $(SDL_LINK))

#### К о м п и л я ц и я ####

-include $(DEPS)
$(OBJ_DIR)/1_%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	gcc $(CFLAGS_FINAL) -c $< -o $@

-include $(DEPS)
$(OBJ_DIR)/2_%.o: $(SRC_3D_DIR)/%.c | $(OBJ_DIR)
	gcc $(CFLAGS_FINAL) -c $< -o $@

clean: clean_libs clean_SDL clean_self

clean_libs:
	$(MAKE) -C ./libft clean

clean_SDL:
	rm -rf $(SDL_DIR)/tmp

clean_self:
	rm -rfv $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C ./libft fclean
	rm -rf $(SDL_DIST)

re: fclean all
