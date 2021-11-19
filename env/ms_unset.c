/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnuti <pnuti@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 10:57:27 by pnuti             #+#    #+#             */
/*   Updated: 2021/11/19 07:58:16 by pnuti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"
/*
static int	same_varname(char *to_del, char *env_var)
{
	char	*varname1;
	int		i;

	i = 0;
	while (env_var[i] && env_var[i] != '=')
		i++;
	varname1 = ft_substr(env_var, 0, i);
	if (ft_strlen(to_del) == ft_strlen(varname1) && ft_strnstr(varname1, to_del, i))
		i = 1;
	else
		i = 0;
	free(varname1);
	return (i);
}*/

int	ms_unset(char *var_name, t_struct *st, int done)
{
	char		**tmp;
	static char	**env;
	static int	n[2];
	int			i;
	int			check;

	if (!getenv(var_name))
		return (0);
	n[1]++;
	if (!env)
		env = __environ;
	tmp = env;
	n[0] = ft_2darr_len(tmp);
	env = (char **)malloc(sizeof(char *) * n[0]);
	if (!env)
		return (1);
	i = 0;
	check = 0;
	while (tmp[i + check])
	{
		if (ft_strncmp(var_name, tmp[i + check], ft_len_until_char(tmp[i + check], '=')))
		{
			env[i] = tmp[i + check];
			i++;
		}
		else
			check++;
	}
	env[i] = NULL;
	if (n[1] > 1)
		free(tmp);
	if (done)
		return (execve("./ms", st->argv, env));
	return (0);
}
