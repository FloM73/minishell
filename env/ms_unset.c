/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnuti <pnuti@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 10:57:27 by pnuti             #+#    #+#             */
/*   Updated: 2021/11/23 14:16:41 by pnuti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

static int	del_and_sort(char *varname, char **env)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (env[i] && !check)
	{
		if (!ft_strncmp(varname, env[i], ft_len_until_char(env[i], '=')))
			check += 1;
		else
			i++;
	}
	while (env[i])
	{
		env[i] = env[i + 1];
		i++;
	}
	return (check);
}

static void	copy_and_del(char *varname, char **old_env, char **new_env)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (old_env[i + check])
	{
		if (!ft_strncmp(varname, old_env[i], ft_len_until_char(old_env[i], '=')))
		{
			free(old_env[i]);
			check += 1;
		}
		else
			new_env[i] = old_env[i + check];
		i++;
	}
	new_env[i] = NULL;
}

int	ms_unset(char *var_name, t_struct *st, int done)
{
	char	**env;
	int		n;

	if (!ms_get_env(st->env, var_name) || !del_and_sort(var_name, st->env[0]))
		return (0);
	n = ft_2darr_len(st->env[1]);
	env = (char **)malloc(sizeof(char *) * n);
	if (!env)
		return (1);
	copy_and_del(var_name, st->env[1], env);
	free(st->env[1]);
	st->env[1] = env;
	return (0);
}
