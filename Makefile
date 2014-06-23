# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/24 06:29:29 by rbernand          #+#    #+#              #
#    Updated: 2014/06/23 23:00:28 by rbernand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=Zappy
SERV_NAME=serveur
CLT_NAME=client
GFX_NAME=gfx
LIB_PNG_DIR=libpng-1.6.12/
CC=	gcc
FLAGS=-Wall -Wextra -Werror -ggdb -Wno-deprecated -Wno-deprecated-declarations
FLAG_OPENGL= -framework GLUT -framework OpenGL -framework Cocoa -lpng -L./lib
LIB=libft/
LIBDIR=lib/
INCLUDES=include/
# CLT_H=$(INCLUDES)client.h
# SERV_H=$(INCLUDES)serveur.h
# GFX_H=$(INCLUDES)gfx.h \
#	$(INCLUDES)mdx.h
DIROBJ=objs/
DIRSRC=srcs/
DIRBIN=bin/
SERV_SRC=s_incantation.c \
	s_main.c \
	s_opt1.c \
	s_opt2.c \
	s_gfx.c \
	s_gfx_cmd.c \
	s_gfx_init.c \
	s_gfx_lst.c \
	s_generate_map.c \
	s_init.c \
	s_client_read.c \
	s_client_write.c \
	s_deal_fd.c \
	s_inv.c \
	s_move_forward.c \
	s_turn_right.c \
	s_turn_left.c \
	s_watch_east.c \
	s_watch_west.c \
	s_watch_north.c \
	s_watch_south.c \
	s_watch_sight.c \
	s_drop_item.c \
	s_take_item.c \
	my_time.c \
	s_user_on_map.c \
	s_connect_nbr.c \
	s_expulse.c \
	s_less_hp.c \
	s_fork.c \
	s_end.c \
	s_broadcast.c
CLT_SRC=c_main.c \
	c_ia.c \
	c_todo.c \
	c_init.c \
	c_opt.c \
	c_serveur_read.c \
	c_serveur_write.c \
	c_lex_inv.c \
	c_lex_vision.c \
	c_dead.c \
	c_broadcast.c \
	c_connect_nbr.c \
	c_drop_item.c \
	c_expulse.c \
	c_fork.c \
	c_incantation.c \
	c_inv.c \
	c_move_forward.c \
	c_take_item.c \
	c_turn_left.c \
	c_turn_right.c \
	c_watch_sight.c \
	c_receive_answer.c \
	c_ia.c \
	c_tools1.c
GFX_SRC=g_main.c \
	g_ipv.c \
	g_serv.c \
	g_fds.c \
	g_cmd_check.c \
	g_cmd.c \
	g_cmd_send.c \
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
	g_mdx_parser.c \
	g_lists.c \
	g_item_actions.c \
	g_move.c \
	g_npc_action.c \
	g_npc.c \
	g_display_players.c \
	g_rot.c
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
PWD:=$(shell pwd)

all: libpng init $(NAME) end

$(NAME): $(SERV_NAME) $(CLT_NAME) $(GFX_NAME)

init:
	@cat data/intro.txt
	@make -s -C $(LIB)
	@if [ -f $(LIBDIR)libft.a ] ; then ln -s $(LIB)libft.a $(LIBDIR) ; fi
	@tput init
	@if [ ! -d $(DIROBJ) ]; then mkdir $(DIROBJ); fi

libpng:
	-@if [ ! -d $(LIB_PNG_DIR) ] ; then \
	 echo "Extracting libpng-1.6.12.tar.gz" ;\
	 tar -xf libpng-1.6.12.tar.gz $(LIB_PNG_DIR) ;\
	 cd $(LIB_PNG_DIR) ; \
	 ./configure --prefix=$(PWD) ; \
	 make -s ; \
	 make -s install ; \
	fi ;

end :
	@cp $(GFX_NAME) $(SERV_NAME) $(CLT_NAME) $(DIRBIN)
	@echo "\033[2K\t\033[1;36m$(NAME)\t\t\033[0;32m[Ready]\033[0m"
	@cat data/end.txt

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
	@$(CC) $(FLAGS) $(FLAG_OPENGL) -o $@ $(GFX_OBJ) $(COMMON_OBJ) -I$(INCLUDES) -L$(LIB) -lft -g -I$(LIB_PNG_DIR)
	@tput cuu1
	@echo "\033[2K\t\033[1;36m$(GFX_NAME)\t\t\033[0;32m[Ready]\033[0m"

$(DIROBJ)s_%.o: $(DIRSRC)$(SERV_NAME)/s_%.c $(INCLUDES)
	@echo "\033[2K--> Linking  $<"
	@$(CC) $(FLAGS) -o $@ -c $< -I$(INCLUDES) -g
	@tput cuu1

$(DIROBJ)c_%.o: $(DIRSRC)$(CLT_NAME)/c_%.c $(INCLUDES)
	@echo "\033[2K--> Linking  $<"
	@$(CC) $(FLAGS) -o $@ -c $< -I$(INCLUDES) -g
	@tput cuu1

$(DIROBJ)g_%.o: $(DIRSRC)$(GFX_NAME)/g_%.c $(INCLUDES)
	@echo "\033[2K--> Linking  $<"
	@$(CC) $(FLAGS) $(FLAG_OPENGL) -o $@ -c $< -I$(INCLUDES) -g -I$(LIB_PNG_DIR)

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

delpng:
	@cd $(LIB_PNG_DIR) && make uninstall
	@rm -rf $(LIB_PNG_DIR)

fclean: clean
	@make -s -C libft $@
	@rm -f $(CLT_NAME)
	@rm -f $(SERV_NAME)
	@rm -f $(GFX_NAME)
	@cd $(DIRBIN) && rm -f $(GFX_NAME) $(SERV_NAME) $(CLT_NAME)

ffclean: delpng fclean
	@rm -rf $(DIROBJ)
	@rm -f $(LIBDIR)libft.a
	@make -s -C $(LIB) fclean


re: fclean all

fre: ffclean all
