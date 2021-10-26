/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnuti <pnuti@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:23:00 by pnuti             #+#    #+#             */
/*   Updated: 2021/10/21 15:36:10 by pnuti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libs.h"

int	ms_export(char ***env, char *new_var, int *size)
{
	char		**res;
	int			i;

	if (!(*size))
		(*size) = 1;
	(*size)++;
	res = (char **)malloc(sizeof(char *) * (*size));
	if (!res)
		return (-1);
	i = 0;
	while (env[0][i])
	{
		res[i] = env[0][i];
		i++;
	}
	res[i] = (char *)malloc(sizeof(char) * (ft_strlen(new_var) + 1));
	if (!res)
		return (-1);
	ft_strlcpy(res[i], new_var, ft_strlen(new_var) + 1);
	free(*env);
	env[0] = res;
	env[0][(*size) - 1] = NULL;
	return (0);
}
