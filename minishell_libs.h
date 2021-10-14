/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_libs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 17:51:13 by pnuti             #+#    #+#             */
/*   Updated: 2021/10/14 23:53:33 by flormich         ###   ########.fr       */
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
	int		fd_infile;
	char	*name_infile;
	int		fd_outfile;
	char	*name_outfile;
	char	**env;
	char	***arr_cmd;

} t_cmd;

// find_cmd.c
char	***parse_cmd(char *input, t_cmd *cmd);

// extract_redirection.c
char	*extract_redirection(char *input, t_cmd *cmd);
#endif
