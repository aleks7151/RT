# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/23 17:12:18 by vkaron            #+#    #+#              #
#    Updated: 2020/02/19 16:00:51 by vabraham         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re, libr

FLAGS = -Wall -Wextra -Werror -Ofast -O3 -g
#FLAGS = -g

C_FILES =	key_press.c move_multy.c main.c light.c events.c scene.c trace.c\
			matrix.c init.c clear.c	read_fig1.c read_fig2.c read_light.c\
			read_scn.c tools.c intersection.c vec1.c vec2.c read_material1.c\
			read_material2.c post_effects.c save_scene.c blur_and_pp.c get.c\
			write_figure_materials.c act_sdl.c screenshot.c read_fig_light_mat.c\
			read_scn0.c scene0.c tools0.c vec3.c clear0.c light0.c read_uv.c\
			cls_isec.c get_color.c get_refl_refr.c trace0.c bgc_mixcol.c\
			isec_sphere.c isec_inv_sph.c isec_cyl.c isec_con.c isec_pln.c\
			text_menu.c text_menu0.c text_menu1.c text_menu2.c service_stuff.c\
			gui.c get_shadow.c read_scene0.c free_get.c

O_FILES =	$(C_FILES:.c=.o)

H_DIR =		-Ilibft -Iusr/L -Iinclude

LIBS =		-Llibft -lft
#-Llib -lSDL2 -lSDL2_image -lSDL2_ttf
#-dynamiclib -o lib/libSDL2.dylib -o lib/libSDL2_image.dylib

FRAME =		-F ./Frameworks/ -framework SDL2 -framework SDL2_image\
			-framework SDL2_ttf 

LIBS = -Llibft -lft 
#-Llib 
#-lSDL2 -lSDL2_image -lSDL2_ttf
#-dynamiclib -o libSDL2.dylib -o libSDL2_image.dylib

S_DIR = src

OBJ = $(addprefix $(S_DIR)/, $(O_FILES))

NAME = RT

all: libr $(NAME)

libr:
	make -C libft/ all

$(NAME): $(OBJ)
	gcc -v $(FLAGS) -o $@ $^ $(H_DIR) $(LIBS) $(FRAME)

$(S_DIR)/%.o: $(S_DIR)/%.c include/rt.h
	gcc $(FLAGS) -c $< -o $@ $(H_DIR)

clean:
	make -C libft/ clean
	rm -f $(OBJ)

fclean : clean
	make -C libft/ fclean
	rm -f $(NAME)

re: fclean all
