# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/18 11:32:11 by rbernand          #+#    #+#              #
#    Updated: 2014/06/13 12:06:52 by rbernand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a
SRCDIR=srcs/
OBJDIR=objs/
HEADER=includes/
FLAGS=-Wall -Wextra -Werror -g
SRC = 	ft_putchar.c ft_putstr.c ft_putnbr.c ft_strcat.c ft_strchr.c \
		ft_strcpy.c ft_strdup.c ft_strlcat.c ft_strlen.c ft_strncat.c \
		ft_strncpy.c ft_strrchr.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		ft_memset.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c \
		ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
		ft_isprint.c ft_toupper.c ft_tolower.c ft_memccpy.c ft_memchr.c \
		ft_memcmp.c ft_memalloc.c ft_memdel.c ft_striter.c ft_striteri.c \
		ft_count_char_befor.c ft_match.c ft_strclr.c ft_strnew.c ft_strdel.c \
		ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c \
		ft_count_nb.c ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putendl.c \
		ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstnew.c \
		ft_putnbr_fd.c ft_nmatch.c ft_putlnbr.c ft_putpnbr.c \
		ft_realloc_str.c ft_reverse_str.c ft_lstmap.c get_next_line.c \
		ft_verify_word.c ft_tabdel.c
OBJO=$(SRC:%.c=$(OBJDIR)%.o)
i=10

all: $(NAME) end

end:
	@echo "\033[A\033[K\t\033[1;36m$(NAME)\t\t\033[0;32m[Ready]\033[0m"

$(NAME): $(OBJO)
	@ranlib $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@echo "\033[A\r\033[2KLinking : $<"
	@gcc $(FLAGS) -o $@ -c $< -I$(HEADER)
	@ar -c -q $(NAME) $@

clean:
	@rm -f $(OBJO)

fclean: clean
	@rm -f $(NAME)

re: fclean all
