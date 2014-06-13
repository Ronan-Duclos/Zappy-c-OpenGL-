# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/24 06:29:29 by rbernand          #+#    #+#              #
#    Updated: 2014/06/13 23:42:42 by caupetit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=Scappy
SERV_NAME=serveur
CLT_NAME=client
GFX_NAME=gfx
CC=	gcc
FLAGS=-Wall -Wextra -Werror -ggdb -Wno-deprecated -Wno-deprecated-declarations
FLAG_OPENGL= -framework GLUT -framework OpenGL -framework Cocoa
LIB=libft/
INCLUDES=includes/
CLT_H=$(INCLUDES)client.h
SERV_H=$(INCLUDES)serveur.h
GFX_H=$(INCLUDES)gfx.h \
	$(INCLUDES)mdx.h
DIROBJ=objs/
DIRSRC=srcs/
SERV_SRC=s_main.c \
	s_opt1.c \
	s_gfx.c \
	s_gfx_lst.c \
	s_generate_map.c \
	s_init.c \
	s_client_read.c \
	s_client_write.c \
	s_deal_fd.c \
	s_inv.c \
	s_moove_forward.c \
	my_time.c
CLT_SRC=c_main.c \
	c_init.c \
	c_opt.c \
	c_tools1.c
GFX_SRC=g_ipmain.c \
	g_ipv.c \
	g_serv.c \
	g_fds.c \
	g_cmd.c \
	g_map.c \
	g_connect.c \
	g_colors1.c \
	g_colors2.c \
	g_env.c \
	g_gl.c \
	g_glut.c \
	g_item_list.c \
	g_light.c \
	g_event.c \
	g_input.c \
	g_transpose.c \
	g_vec.c \
	g_time.c \
	g_display.c \
	g_display_map.c \
	g_display_grid.c \
	g_display_squares.c \
	g_display_items.c \
	g_anim.c \
	g_bmp.c \
	g_resources.c \
	g_vbo.c \
	g_parsemdx.c \
	g_parse_png.c \
	g_mdx_parser.c
COMMON_SRC=functions.c \
	buf_circle.c \
	error.c
SERV_OBJ=$(SERV_SRC:%.c=$(DIROBJ)%.o)
CLT_OBJ=$(CLT_SRC:%.c=$(DIROBJ)%.o)
GFX_OBJ=$(GFX_SRC:%.c=$(DIROBJ)%.o)
COMMON_SRC2=$(GFX_SRC:%.c=$(GFX_NAME)/%.c)
SERV_SRC2=$(SERV_SRC:%.c=$(SERV_NAME)/%.c)
OBJ_SRC2=$(CLT_SRC:%.c=$(CLT_NAME)/%.c)
GFX_SRC2=$(COMMON_SRC:%.c=$(SERV_NAME)/%.c)
COMMON_OBJ=$(COMMON_SRC:%.c=$(DIROBJ)%.o)

all: init $(NAME) end

$(NAME): $(SERV_NAME) $(CLT_NAME) $(GFX_NAME)

end :
	@echo "\033[2K\t\033[1;36mScappy\t\t\033[0;32m[Ready]\033[0m"
	@cat data/end.txt

init:
	@cat data/intro.txt
	@make -s -C $(LIB)
	@tput init

$(SERV_NAME): $(SERV_OBJ) $(COMMON_OBJ)
	@echo "==> Compiling $(SERV_NAME) : "
	@$(CC) $(FLAGS) -o $@ $(SERV_OBJ) $(COMMON_OBJ) -I$(INCLUDES) -L$(LIB) -lft -g
	@tput cuu1
	@echo "\033[2K\t\033[1;36m$(SERV_NAME)\t\t\033[0;32m[Ready]\033[0m"

$(CLT_NAME): $(CLT_OBJ) $(COMMON_OBJ)
	@echo "==> Compiling $(CLT_NAME) : "
	@$(CC) $(FLAGS) -o $@ $(CLT_OBJ) $(COMMON_OBJ) -I$(INCLUDES) -L$(LIB) -lft -g
	@tput cuu1
	@echo "\033[2K\t\033[1;36m$(CLT_NAME)\t\t\033[0;32m[Ready]\033[0m"

$(GFX_NAME): $(GFX_OBJ)
	@echo "==> Compiling $(GFX_NAME) : "
	@$(CC) $(FLAGS) $(FLAG_OPENGL) -o $@ $(GFX_OBJ) $(COMMON_OBJ) -I$(INCLUDES) -L$(LIB) -lft
	@tput cuu1
	@echo "\033[2K\t\033[1;36m$(GFX_NAME)\t\t\033[0;32m[Ready]\033[0m"

$(DIROBJ)s_%.o: $(DIRSRC)$(SERV_NAME)/s_%.c $(INCLUDES)
	@echo "--> Linking  $<"
	@$(CC) $(FLAGS) -o $@ -c $< -I$(INCLUDES) -g
	@tput cuu1

$(DIROBJ)c_%.o: $(DIRSRC)$(CLT_NAME)/c_%.c $(INCLUDES)
	@echo "--> Linking  $<"
	@$(CC) $(FLAGS) -o $@ -c $< -I$(INCLUDES) -g
	@tput cuu1

$(DIROBJ)g_%.o: $(DIRSRC)$(GFX_NAME)/g_%.c $(INCLUDES)
	@echo "--> Linking  $<"
	@$(CC) $(FLAGS) $(FLAGS_OPENGL) -o $@ -c $< -I$(INCLUDES) -g
	@tput cuu1

$(DIROBJ)%.o: $(DIRSRC)common/%.c $(INCLUDES)
	@echo "--> Linking  $<"
	@$(CC) $(FLAGS) -o $@ -c $< -I$(INCLUDES) -g
	@tput cuu1

clean:
	@make -s -C libft $@
	@rm -f $(SERV_OBJ)
	@rm -f $(CLT_OBJ)
	@rm -f $(GFX_OBJ)
	@rm -f $(COMMON_OBJ)

fclean: clean
	@make -s -C libft $@
	@rm -f $(CLT_NAME)
	@rm -f $(SERV_NAME)
	@rm -f $(GFX_NAME)

re: fclean all
