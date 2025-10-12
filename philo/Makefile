# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asando <asando@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/12 19:56:18 by asando            #+#    #+#              #
#    Updated: 2025/10/12 20:14:37 by asando           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC ?= cc
DEBUG ?= 0
CFLAGS := -Wall -Wextra -Wall -pthread
HEADER := .

SRC_DIR := .
SRCS := action.c init_prog.c main.c parse_input.c

OBJ_DIR := obj
OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)

NAME := philo

all: $(NAME)
	@echo "Execution file is created (philo)"

$(NAME): $(OBJS)
	@$(CC) -o $@ $(OBJS)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

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
