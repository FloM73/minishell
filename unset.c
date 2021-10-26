/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnuti <pnuti@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 10:57:27 by pnuti             #+#    #+#             */
/*   Updated: 2021/10/20 19:28:42 by pnuti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libs.h"

int	ms_unset(char ***env, char *to_unset, int *size)
{
	char	**res;
	int		i;
	int		check;

	(*size)--;
	res = (char **)malloc(sizeof(char *) * (*size));
	if (!res)
		return (-1);
	i = 0;
	check = 0;
	while (env[0][i])
	{
		if (ft_strlen(ft_strchr(env[0][i], '=') + 1) == ft_strlen(to_unset) &&
			ft_strnstr(env[0][i], to_unset, ft_strlen(to_unset)))
		{
			free(env[0][i]);
			check++;
		}
		else
			res[i - check] = env[0][i];
		i++;
	}
	if (!check)
	{
		write(2, "Error: environmental variable not found\n", 41);
		(*size)++;
		free(res);
		return (1);
	}
	else
	{
		free(env[0]);
		env[0] = res;
		env[i - check] = NULL;
		return (0);
	}
}
