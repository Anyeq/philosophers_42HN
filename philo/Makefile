# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asando <asando@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/12 19:56:18 by asando            #+#    #+#              #
#    Updated: 2025/10/13 14:09:09 by asando           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC ?= cc
DEBUG ?= 0
CFLAGS := -Wall -Wextra -Wall -pthread
HEADER := include

SRC_DIR := src
SRCS := action.c init_prog.c main.c parse_input.c utils.c

OBJ_DIR := obj
OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)

NAME := philo

all: $(NAME)
	@echo "Execution file is created (philo)"

$(NAME): $(OBJS)
	@$(CC) -o $@ $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(HEADER) -c $< -o $@

$(OBJ_DIR):
	@echo "Creating obj folder..."
	@mkdir -p $(OBJ_DIR)
	@echo "Obj folder is created"

clean:
	@echo "Deleting obj files..."
	@rm -rf $(OBJ_DIR)
	@echo "Obj files are deleted"

fclean: clean
	@echo "Deleting philo execution file..."
	@rm -rf $(NAME)
	@echo "philo is deleted"

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re
