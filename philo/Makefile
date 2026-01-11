# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asando <asando@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/12 19:56:18 by asando            #+#    #+#              #
#    Updated: 2026/01/11 19:37:23 by asando           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC ?= cc
DEBUG ?= 0
FSANITIZE ?= 0
CFLAGS := -Wall -Wextra -Wall -pthread
ifeq ($(DEBUG), 1)
	CFLAGS += -g -O0
$(info debug -g -O0 flag is added)
endif
ifeq ($(FSANITIZE), 1)
	CFLAGS += -fsanitize=thread
$(info fsanitize=thread flag is added)
$(info cannot run valgrind with fsanitize=thread flag)
endif
HEADER := include

SRC_DIR := src
SRCS := philo_action.c init_program.c main.c parse_input.c utils.c \
		error_management.c monitor_thread_action.c one_philo_action.c

OBJ_DIR := obj
OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)

NAME := philo

all: $(NAME)
	@echo "Execution file is created (philo)"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $(OBJS)

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
