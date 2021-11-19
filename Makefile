# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pnuti <pnuti@student.42wolfsburg.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/18 22:32:44 by flormich          #+#    #+#              #
#    Updated: 2021/11/19 08:30:34 by pnuti            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ms
CFLAGS = -Wall -Wextra -Werror -g
DIR_LIB = libft
DIR_P = parsing
DIR_E = echo
DIR_ENV = env
DIR_D = dir
HEADER = $(DIR_LIB)/libft.h minishell_libs.h

SRC = ms_main.c ms_error.c ms_launch_cmd.c ms_sig_hook.c ms_run_exit.c
SRC_P = $(DIR_P)/ms_1_extract_cmd.c $(DIR_P)/ms_2_parse_input.c \
	$(DIR_P)/ms_extract_utils.c $(DIR_P)/ms_extract_infile_limiter.c \
	$(DIR_P)/ms_3_extract_redirection.c $(DIR_P)/ms_extract_outfile.c\
	$(DIR_P)/ms_add_path.c $(DIR_P)/ms_clean_arr.c
SRC_E = $(DIR_E)/ms_echo.c $(DIR_E)/ms_find_variable.c $(DIR_E)/ms_buffer.c
SRC_ENV =	$(DIR_ENV)/ms_env.c $(DIR_ENV)/ms_export.c $(DIR_ENV)/ms_unset.c \
			$(DIR_ENV)/ms_manage_env.c
SRC_D = $(DIR_D)/ms_cd.c $(DIR_D)/ms_pwd.c

OBJ = $(SRC:.c=.o)
OBJ_P = $(SRC_P:.c=.o)
OBJ_E = $(SRC_E:.c=.o)
OBJ_LIB = $(SRC_LIB:.c=.o)
OBJ_ENV = $(SRC_ENV:.c=.o)
OBJ_D = $(SRC_D:.c=.o)

all: $(NAME)

$(NAME): $(HEADER) $(OBJ) $(OBJ_P) $(OBJ_E) $(OBJ_LIB) $(OBJ_ENV) $(OBJ_D)
	make all -C ./$(DIR_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(OBJ_P) $(OBJ_E) $(OBJ_ENV) $(OBJ_D) -o $(NAME) -L libft/ -lft -lreadline

clean:
	make clean -C ./$(DIR_LIB)
	rm -f $(OBJ) $(OBJ_P) $(OBJ_E) $(OBJ_ENV) $(OBJ_D) minishell.o

fclean:	clean
	rm -f $(NAME)
	make fclean -C ./$(DIR_LIB)

re: fclean all

.PHONY: all clean fclean re
