# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/24 06:29:29 by rbernand          #+#    #+#              #
#    Updated: 2014/06/08 21:34:43 by rduclos          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=Scappy
SERV_NAME=serveur
CLT_NAME=client
CC=	gcc
FLAGS=-Wall -Wextra -Werror -ggdb
LIB=libft/
INCLUDES=includes/
CLT_H=$(INCLUDES)client.h
SERV_H=$(INCLUDES)serveur.h
DIROBJ=objs/
DIRSRC=srcs/

SERV_SRC=s_main.c \
	s_opt1.c \
	s_generate_map.c \
	s_init.c \
	s_client_read.c \
	s_client_write.c \
	s_deal_fd.c 
CLT_SRC=c_main.c \
	c_init.c \
	c_opt.c \
	c_tools1.c
COMMON_SRC=functions.c \
	buf_circle.c \
	error.c
SERV_OBJ=$(SERV_SRC:%.c=$(DIROBJ)%.o)
CLT_OBJ=$(CLT_SRC:%.c=$(DIROBJ)%.o)
COMMON_OBJ=$(COMMON_SRC:%.c=$(DIROBJ)%.o)

all: init $(NAME) end

$(NAME): $(SERV_NAME) $(CLT_NAME)

end :
	@echo "\033[2K\t\033[1;36mScappy\t\t\033[0;32m[Ready]\033[0m"
	@cat end.txt

init:
	@cat intro.txt
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

$(DIROBJ)%.o: $(DIRSRC)%.c $(INCLUDES)
	@echo "--> Linking  $<"
	@$(CC) $(FLAGS) -o $@ -c $< -I$(INCLUDES) -g
	@tput cuu1

clean:
	@make -s -C libft $@
	@rm -f $(SERV_OBJ)
	@rm -f $(CLT_OBJ)

fclean: clean
	@make -s -C libft $@
	@rm -f $(CLT_NAME)
	@rm -f $(SERV_NAME)

re: fclean all
