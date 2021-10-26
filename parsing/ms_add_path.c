/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_add_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 19:34:59 by flormich          #+#    #+#             */
/*   Updated: 2021/10/25 21:36:42 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell_libs.h"

static void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (*(arr + i) != 0)
	{
		free(arr[i]);
		i++;
	}
	free(arr[i]);
	free(arr);
}

static int	find_path(t_struct *st)
{
	int	i;

	i = 0;
	while (st->env[i])
	{
		if (!ft_strnstr(st->env[i], "PATH", ft_strlen(st->env[i])))
			i++;
		else
			return (i);
	}
	exit (-1);
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

static char *test_path(char **arr_path, char *cmd)
{
	int		j;
	char	*str_cmd;

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
	return (NULL);
}

int	add_path(t_struct *st)
{
	char	**arr_path;
	int		i;
	int		where_is_path;

	where_is_path = find_path(st);
	if (where_is_path == -1)
		return (-1);
	arr_path = ft_split(st->env[where_is_path], ':');
	i = 0;
	while (i <= st->tr)
	{
		st->arr[i].cmd[0] = test_path(arr_path, st->arr[i].cmd[0]);
		if (!st->arr[i].cmd[0])
		{
			free_arr(arr_path);
			perror("Command-not-found\n");
			return (-1);
		}
		i++;
	}
	free_arr(arr_path);
	return (0);
}
