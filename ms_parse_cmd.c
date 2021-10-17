/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 19:34:59 by flormich          #+#    #+#             */
/*   Updated: 2021/10/17 00:23:43 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell_libs.h"

// count the number of command we will have to perform
static int	count_arg(char **arr_cmd)
{
	int	i;

	i = 0;
	while (arr_cmd[i] != NULL)
		i++;
	return (i);
}

static char	*join_path(char const *s1, char const *s2)
{
	char			*conc;
	unsigned int	len;
	int				i;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 2;
	conc = (char *)malloc(sizeof(char) * len);
	if (! conc)
		return (NULL);
	i = 0;
	while (*s1 != '\0')
	{
		conc[i++] = *s1;
		s1++;
	}
	while (*s2 != '\0')
	{
		conc[i++] = *s2;
		s2++;
	}
	conc[i] = '\0';
	return (conc);
}

void	free_arr_cmd_line(char **arr, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->nb_cmd)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static char	***create_arr_cmd_arg(char **arr_line, t_cmd *cmd)
{
	char	***arr_cmd_arg;

	cmd->nb_cmd = count_arg(arr_line);
	arr_cmd_arg = malloc(cmd->nb_cmd * sizeof(char *));
	if (!arr_cmd_arg)
	{
		free_arr_cmd_line(arr_line, cmd);
		ms_error("Fail to malloc arr_cmd_arg in ***parse_cmd", 0, cmd);
	}
	return (arr_cmd_arg);
}

// Parse cmd option and args in ***arr_cmd
char	***parse_cmd(char *input, t_cmd *cmd)
{
	char	**arr_cmd_line;
	char	***arr_cmd_arg;
	char	*str_cmd;
	int		i;

	input = extract_redirection(input, cmd);
	if (input == NULL)
		return (NULL);
	arr_cmd_line = ft_split(input, '|');
	if (!arr_cmd_line)
		ms_error("Fail to malloc arr_cmd_line in ***parse_cmd", 0, cmd);
	arr_cmd_arg = create_arr_cmd_arg(arr_cmd_line, cmd);
	i = 0;
	while (arr_cmd_line[i] != NULL)
	{
		arr_cmd_arg[i] = ft_split(arr_cmd_line[i], ' ');
		str_cmd = join_path("~/minishell/sbin/", arr_cmd_arg[i][0]);
		free(arr_cmd_arg[i][0]);
		arr_cmd_arg[i][0] = str_cmd;
		i++;
	}
	free_arr_cmd_line(arr_cmd_line, cmd);
	return (arr_cmd_arg);
}
