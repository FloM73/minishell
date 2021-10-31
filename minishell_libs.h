/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_libs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 17:51:13 by pnuti             #+#    #+#             */
/*   Updated: 2021/10/31 13:11:02 by flormich         ###   ########.fr       */
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
# include <sys/wait.h>
# include "libft/libft.h"
# include <unistd.h>

# define READ 0
# define WRITE 1
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
	int		cmd_type;
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
	int		pid;
	int		ppid;
} t_struct;

// main.c
void	free_memory(t_struct *cmd);

// parsing: extract_cmd.c
int		extract_cmd(t_struct *st);
// parsing: extract_redirection.c
int		count_lengh_name(t_struct *st, int i);
int		extract_redirection(t_struct *st, int i);
// parsing: extract_infile_limiter.c
int		extract_infile(t_struct *st, int i);
int		extract_limiter(t_struct *st, int i);
// parsing: extract_infile_limiter.c
int		extract_outfile(t_struct *st, int i);
// parsing: parse_input.c
int		parse_input(t_struct *st);
//parsing: add_path.c
int		add_path(t_struct *st);
// parsing: extract_utils.c
char	*malloc_file_name(char *file, int len);
int		test_file_descriptor(int fd, char *name);
int		open_outfile(char *name, int append);
void	remove_redirection(char *input, int nb, char c);
// parsing: clean_arr
void clean_arr(t_struct *st);

//error.c
void	ms_error(char *txt, int	*exit_level, t_struct *st);
void	ms_error_synthaxe(char c);

// ms_launch_cmd.c
int		launch_cmd(t_struct *st);

#endif
