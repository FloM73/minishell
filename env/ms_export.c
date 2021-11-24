/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnuti <pnuti@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:23:00 by pnuti             #+#    #+#             */
/*   Updated: 2021/11/23 14:11:45 by pnuti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

static int	env_exists(char *new_var, char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(new_var, env[i], ft_len_until_char(new_var, '=')) &&
			!ft_strncmp(new_var, env[i], ft_len_until_char(env[i], '=')))
			return (1);
		i++;
	}
	return (0);
}

static int	del_and_sort(char *new_var, t_struct *st)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (st->env[0][i] && !check)
	{
		if (!ft_strncmp(new_var, st->env[0][i], ft_len_until_char(new_var, '=')))
			check += 1;
		else
			i++;
	}
	while (st->env[0][i])
	{
		st->env[0][i] = st->env[0][i + 1];
		i++;
	}
	return (check);
}

static void	sub_or_append(char *new_var, t_struct *st, char **new_env)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (st->env[1][i] && !check)
	{
		if (!ft_strncmp(new_var, st->env[1][i], ft_len_until_char(new_var, '=')))
		{
			free(st->env[1][i]);
			new_env[i] = new_var;
			check += 1;
		}
		else
			new_env[i] = st->env[1][i];
		i++;
	}
	if (!check)
	{
		new_env[i] = new_var;
		i++;
	}
	new_env[i] = NULL;
}

int	ms_export(char *new_var, t_struct *st, int done)
{
	char	**env;
	int		i;
	int		n;

	
	n = ft_2darr_len(st->env[1]);
	if (!env_exists(new_var, st->env[1]))
		n++;
	env = (char **)malloc(sizeof(char *) * (n + 1));
	if (!env)
		return (-1);
	i = 0;
	del_and_sort(new_var, st);
	sub_or_append(new_var, st, env);
	free(st->env[1]);
	st->env[1] = env;
	return (0);
}
