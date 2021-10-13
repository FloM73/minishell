/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_find_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 19:34:59 by flormich          #+#    #+#             */
/*   Updated: 2021/10/13 23:00:17 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell_libs.h"

// count the number of command we will have to perform
static	int count_cmd(char **arr_cmd)
{
	int	i;

	i = 0;
	while (arr_cmd[i] != NULL)
		i++;
	return (i);
}

// Parse cmd option and args in ***arr_cmd
// TO DO : deal with the redirection (might change a lot of things. Esp. ** instead of ***?)
char	***parse_cmd(char *input, t_cmd *cmd)
{
	char	**arr_cmd_line;
	char	***arr_cmd_arg;
	int		i;

	arr_cmd_line = ft_split(input, '|');
	if (!arr_cmd_line)
		return (NULL);
	cmd->nb_cmd = count_cmd(arr_cmd_line);
	arr_cmd_arg = malloc(cmd->nb_cmd * sizeof(char *));
	if (!arr_cmd_arg)
		return (NULL);
	i = 0;
	while (arr_cmd_line[i] != NULL)
	{
		arr_cmd_arg[i] = ft_split(arr_cmd_line[i], ' ');
		i++;
	}
	return (arr_cmd_arg);
}
