# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/18 22:32:44 by flormich          #+#    #+#              #
#    Updated: 2021/10/24 01:03:24 by flormich         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ms
CFLAGS = -Wall -Wextra -Werror
DIR_LIB = libft
DIR_P = parsing
HEADER = $(DIR_LIB)/libft.h minishell_libs.h

SRC_LIB = $(DIR_LIB)/ft_memset.c $(DIR_LIB)/ft_bzero.c $(DIR_LIB)/ft_memcpy.c \
		$(DIR_LIB)/ft_memccpy.c $(DIR_LIB)/ft_memmove.c \
		$(DIR_LIB)/ft_memchr.c $(DIR_LIB)/ft_memcmp.c $(DIR_LIB)/ft_strlen.c \
		$(DIR_LIB)/ft_isalpha.c $(DIR_LIB)/ft_isdigit.c \
		$(DIR_LIB)/ft_isalnum.c $(DIR_LIB)/ft_isascii.c $(DIR_LIB)/ft_isprint.c \
		$(DIR_LIB)/ft_toupper.c $(DIR_LIB)/ft_tolower.c \
		$(DIR_LIB)/ft_strchr.c $(DIR_LIB)/ft_strrchr.c $(DIR_LIB)/ft_strncmp.c \
		$(DIR_LIB)/ft_strlcpy.c $(DIR_LIB)/ft_strlcat.c \
		$(DIR_LIB)/ft_strnstr.c $(DIR_LIB)/ft_atoi.c $(DIR_LIB)/ft_calloc.c \
		$(DIR_LIB)/ft_strdup.c $(DIR_LIB)/ft_substr.c \
		$(DIR_LIB)/ft_strjoin.c $(DIR_LIB)/ft_strtrim.c $(DIR_LIB)/ft_split.c \
		$(DIR_LIB)/ft_itoa.c $(DIR_LIB)/ft_itoa_unsigned_int.c \
		$(DIR_LIB)/ft_itohex.c \
		$(DIR_LIB)/ft_itoa_with_sign.c $(DIR_LIB)/ft_itoa_without_sign.c \
		$(DIR_LIB)/ft_strmapi.c $(DIR_LIB)/ft_putchar_fd.c $(DIR_LIB)/ft_putstr_fd.c \
		$(DIR_LIB)/ft_putendl_fd.c $(DIR_LIB)/ft_putnbr_fd.c $(DIR_LIB)/ft_isspace.c

SRC = ms_main.c ms_error.c
SRC_P = $(DIR_P)/ms_extract_cmd.c $(DIR_P)/ms_parse_input.c \
	$(DIR_P)/ms_extract_utils.c $(DIR_P)/ms_extract_infile_limiter.c \
	$(DIR_P)/ms_extract_redirection.c $(DIR_P)/ms_extract_outfile.c \

OBJ = $(SRC:.c=.o)
OBJ_P = $(SRC_P:.c=.o)
OBJ_LIB = $(SRC_LIB:.c=.o)

all: $(NAME)

$(NAME): $(HEADER) $(OBJ) $(OBJ_P) $(OBJ_LIB)
	make all -C ./$(DIR_LIB)
	$(CC) $(CFLAGS) ms_cd.c -o ./sbin/cd
	$(CC) $(CFLAGS) $(OBJ) $(OBJ_P) $(OBJ_LIB) -o $(NAME) -lreadline

clean:
	make clean -C ./$(DIR_LIB)
	rm -f $(OBJ) $(OBJ_P) minishell.o

fclean:	clean
	rm -f $(NAME)
	make fclean -C ./$(DIR_LIB)

re: fclean all

.PHONY: all clean fclean re
