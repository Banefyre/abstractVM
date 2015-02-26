# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msagodir <msagodir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/06 10:13:32 by msagodir          #+#    #+#              #
#    Updated: 2015/02/25 16:20:56 by msagodir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = /usr/local/bin/g++
CFLAGS = -Wall -Wextra -Werror
NAME = abstractVM
SRC = srcs/main.cpp
PATH_OBJ = .objs
OBJ = $(addprefix $(PATH_OBJ)/, $(SRC:.cpp=.o))

$(addprefix $(PATH_OBJ)/, %.o): %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

all: $(NAME)

$(NAME) : $(PATH_OBJ) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(PATH_OBJ):
	mkdir $(PATH_OBJ)

clean :
	rm -rf $(PATH_OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: re, clean, fclean
