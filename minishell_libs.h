/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_libs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 17:51:13 by pnuti             #+#    #+#             */
/*   Updated: 2021/10/17 00:08:45 by flormich         ###   ########.fr       */
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
	int		nb_cmd;
	int		fd_in;
	char	*name_in;
	char	*limiter;
	int		fd_out;
	char	*name_out;
	char	**env;
	char	***arr_cmd;
} t_cmd;

// main.c
void	free_memory(t_cmd *cmd);

// find_cmd.c
char	***parse_cmd(char *input, t_cmd *cmd);

// extract_redirection.c
char	*extract_redirection(char *input, t_cmd *cmd);

// extract_limiter.c
char	*extract_limiter(char *input, t_cmd *cmd);
int		extract_infile(char *str, t_cmd *cmd);
char	*pilote_extract_infile(char *input, t_cmd *cmd);

// extract_utils.c
void	remove_redirection(char *input, int nb, char c);
char	*malloc_file_name(char **file, char *str);
int		test_file_descriptor(int fd, char *name);
int		open_outfile(char *name, int append);

//error.c
void	ms_error(char *txt, int	*exit_level, t_cmd *cmd);
void	ms_error_file(char c);

#endif
