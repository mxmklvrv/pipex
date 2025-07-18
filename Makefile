# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/18 14:24:11 by mklevero          #+#    #+#              #
#    Updated: 2025/07/18 18:18:07 by mklevero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc 
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a


OBJ_DIR = obj/
SRC_DIR = src/

HEADERS = -I ./include  -I $(LIBFT_DIR)

SRCS = main.c

OBJ = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
.SECONDARY: ${OBJS}

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) -c $< -o $@ $(HEADERS)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(C_FLAGS) $(OBJ) $(LIBFT) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME) $(LIBFT)

re: fclean all

.PHONY: all re clean fclean