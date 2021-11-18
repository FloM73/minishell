/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnuti <pnuti@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:23:00 by pnuti             #+#    #+#             */
/*   Updated: 2021/11/17 15:49:30 by pnuti            ###   ########.fr       */
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

static int	same_varname(char *new_var, char *env_var)
{
	char	*varname1;
	char	*varname2;
	int		i;

	i = 0;
	while (new_var[i] && new_var[i] != '=')
		i++;
	varname1 = ft_substr(new_var, 0, i);
	i = 0;
	while (env_var[i] && env_var[i] != '=')
		i++;
	varname2 = ft_substr(env_var, 0, i);
	if (ft_strlen(varname1) == ft_strlen(varname2) && ft_strnstr(varname1, varname2, i))
		i = 1;
	else
		i = 0;
	free(varname1);
	free(varname2);
	return (i);
}

int	ms_export(char *new_var, t_struct *st, int done)
{
	static char	**env;
	char		**tmp;
	int			i;
	static int	n[2];
	int			check;

	if (!env)
		tmp = __environ;
	else
		tmp = env;
	n[0] = ft_2darr_len(tmp);
	n[1]++;
	if (!env_exists(new_var, tmp))
		n[0]++;
	env = (char **)malloc(sizeof(char *) * (n[0] + 1));
	if (!env)
		return (-1);
	i = 0;
	check = 1;
	while (i < n[0] - 1)
	{
		if (same_varname(new_var, tmp[i]))
		{
			env[i] = new_var;
			check *= 0;
		}
		else
			env[i] = tmp[i];
		i++;
	}
	if (check)
	{
		env[i] = new_var;
		i++;
	}
	env[i] = NULL;
	if (n[1] > 1)
		free (tmp);
	if (done)
		return (execve("./ms", st->argv, env));
	return (0);
}
