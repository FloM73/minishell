/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_add_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 19:34:59 by flormich          #+#    #+#             */
/*   Updated: 2021/12/11 18:55:21 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell_libs.h"

static void	free_arr(char **arr)
{
	int	tr;

	tr = 0;
	while (*(arr + tr) != 0)
	{
		free(arr[tr]);
		tr++;
	}
	free(arr[tr]);
	free(arr);
}

static int	find_path(t_struct *st)
{
	int	i;

	i = 0;
	while (st->env[i])
	{
		if (ft_strncmp(st->env[i], "PATH=", 5) != 0)
			i++;
		else
			return (i);
	}
	ms_error_synthaxe('C');
	return (-1);
}

static char	*join_path(char const *s1, char const *s2)
{
	char			*conc;
	unsigned int	len;
	int				i;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 2;
	conc = (char *)malloc(sizeof(*s1) * len);
	if (! conc)
		return (NULL);
	i = 0;
	while (*s1 != '\0')
	{
		conc[i++] = *s1;
		s1++;
	}
	conc[i++] = '/';
	while (*s2 != '\0')
	{
		conc[i++] = *s2;
		s2++;
	}
	conc[i] = '\0';
	return (conc);
}

static char	*test_path(char **arr_path, char *cmd)
{
	int		j;
	char	*str_cmd;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	j = 1;
	while (arr_path[j] != NULL)
	{
		str_cmd = join_path(arr_path[j++], cmd);
		if (access(str_cmd, X_OK) == 0)
		{
			free(cmd);
			return (str_cmd);
		}
		free(str_cmd);
	}
	free(cmd);
	return (NULL);
}

int	add_path(t_struct *st)
{
	char	**arr_path;
	int		tr;
	int		where_is_path;

	where_is_path = find_path(st);
	if (where_is_path == -1)
		return (-1);
	arr_path = ft_split(st->env[where_is_path], ':');
	tr = 0;
	while (tr <= st->tr)
	{
		if (st->arr[tr].cmd_type != BUILTIN)
		{
			st->arr[tr].cmd[0] = test_path(arr_path, st->arr[tr].cmd[0]);
			if (!st->arr[tr].cmd[0])
			{
				free_arr(arr_path);
				ms_error_synthaxe('C');
				return (-1);
			}
		}
		tr++;
	}
	free_arr(arr_path);
	return (0);
}
