# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: valentin <valentin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/13 14:55:08 by valentin          #+#    #+#              #
#    Updated: 2022/12/01 01:16:14 by valentin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME2 = pipex_bonus

C_FILES = pipex.c utils.c check_access.c

BONUS_DIR = ./bonus/

BONUS_SRC = pipex_bonus.c utils_bonus.c error_bonus.c free_bonus.c \
			check_access_bonus.c

DIR_OBJ = objs/

DIR_OBJ2 = obj2/

SRC_DIR = ./src/

INCS	= -I ./include/

OBJS = ${C_FILES:%.c=$(DIR_OBJ)%.o}

OBJS2 = ${BONUS_SRC:%.c=$(DIR_OBJ2)%.o}

CFLAGS += -Wall -Wextra -Werror

LIBSFLAGS	=  libft/libft.a

CC		= cc
RM		= rm -f

$(NAME): ${OBJS} maker
		@$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(LIBSFLAGS)
		@echo " [ \x1b[32mOK\\x1b[0m ] Pipex"
		
$(NAME2): ${OBJS2} maker
		@$(CC) -o $(NAME) $(OBJS2) $(CFLAGS) $(LIBSFLAGS)
		@echo " [ \x1b[32mOK\\x1b[0m ] Pipex bonus"

$(DIR_OBJ)%.o : $(SRC_DIR)%.c
		@mkdir -p $(DIR_OBJ)
		@$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

$(DIR_OBJ2)%.o : $(BONUS_DIR)%.c
		@mkdir -p $(DIR_OBJ2)
		@$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

all: ${NAME}

bonus: ${NAME2}

maker:
		@make -C libft
		@echo "[ OK ] libft"

clean:
		@${RM} -rf ${DIR_OBJ}
		@${RM} -rf ${DIR_OBJ2}
		@make clean -C libft

fclean:	clean
		@make fclean -C libft
		@${RM} ${NAME}
		@${RM} ${NAME2}
		@echo " [ OK ] pipex clean"

re:		fclean all

norm:
	norminette $(SRC_DIR)*.c $(BONUS_DIR)*.c include/*.h 
