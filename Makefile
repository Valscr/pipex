# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: valentin <valentin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/13 14:55:08 by valentin          #+#    #+#              #
#    Updated: 2023/01/19 13:29:11 by valentin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME2 = pipex_bonus

COLOUR_GREEN=\033[0;32m
COLOUR_END=\033[0m

C_FILES = pipex.c utils.c utils2.c free.c

BONUS_DIR = ./bonus/

BONUS_SRC = pipex_bonus.c utils_bonus.c error_bonus.c free_bonus.c \
			 get_next_line_bonus.c here_doc_bonus.c \
			get_next_line_utils_bonus.c utils2_bonus.c

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
		@echo " [ $(COLOUR_GREEN)OK$(COLOUR_END) ] ./pipex"
		
$(NAME2): ${OBJS2} maker
		@$(CC) -o $(NAME) $(OBJS2) $(CFLAGS) $(LIBSFLAGS)
		@echo " [ $(COLOUR_GREEN)OK$(COLOUR_END) ] ./pipex (bonus)"

$(DIR_OBJ)%.o : $(SRC_DIR)%.c
		@mkdir -p $(DIR_OBJ)
		@$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

$(DIR_OBJ2)%.o : $(BONUS_DIR)%.c
		@mkdir -p $(DIR_OBJ2)
		@$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

all: ${NAME}

bonus: ${NAME2}

maker:
		@make -s -C libft
		@echo "[ OK ] libft"

clean:
		@${RM} -rf ${DIR_OBJ}
		@${RM} -rf ${DIR_OBJ2}
		@make fclean -s -C libft

fclean:	clean
		@${RM} ${NAME}
		@${RM} ${NAME2}
		@echo " [ OK ] pipex clean"

re:		fclean all

norm:
	norminette $(SRC_DIR)*.c $(BONUS_DIR)*.c include/*.h 

.PHONY:         all clean fclean bonus re
