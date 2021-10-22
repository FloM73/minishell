/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_libs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 17:51:13 by pnuti             #+#    #+#             */
/*   Updated: 2021/10/23 00:27:08 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_LIBS_H
# define MINISHELL_LIBS_H
# define PATH_MAX 4097

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <unistd.h>

# define RED "\033[0;31m"
# define GR "\033[0;32m"
# define YE "\033[0;33m"
# define BL "\033[0;34m"
# define PU "\033[0;35m"
# define CY "\033[0;36m"
# define WH "\033[0;37m"
# define D "\033[0m"
//# define PATH = "~/minishell/sbin/"

typedef struct command
{
	char	**cmd;
	int		nb_arg;
} t_cmd;

typedef struct structure
{
	int		nb_cmd;
	int		tr;
	int		arg;
	int		digit;
	int		take_all;
	char	*input;
	int		len;
	int		fd_in;
	char	*name_in;
	char	*limiter;
	int		fd_out;
	char	*name_out;
	char	**env;
	t_cmd	*arr;
} t_struct;

// main.c
//void	free_memory t_struct *cmd);

// extract_cmd.c
int		extract_cmd(t_struct *st);

// parse_input
int		parse_input(t_struct *st);

// extract_utils.c
char	*malloc_file_name(char *file, char *str);
int		test_file_descriptor(int fd, char *name);
int		open_outfile(char *name, int append);

//error.c
void	ms_error(char *txt, int	*exit_level, t_struct *st);
void	ms_error_synthaxe(char c);

#endif
