/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_libs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 17:51:13 by pnuti             #+#    #+#             */
/*   Updated: 2021/10/13 23:00:53 by flormich         ###   ########.fr       */
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
# include "libft/libft.h"

typedef struct command
{
	int		nb_cmd;
	char	**env;
	char	***arr_cmd;

} t_cmd;

// find_cmd.c
char	***parse_cmd(char *input, t_cmd *cmd);

#endif
