/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnuti <pnuti@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 18:01:33 by pnuti             #+#    #+#             */
/*   Updated: 2021/10/21 15:59:31 by pnuti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libs.h"

int	ms_env(char ***env, char *empty, int *size)
{
	int	i;

	if (empty[0])
	{
		write(2, "Error: unexpected token \"", 25);
		write(2, empty, ft_strlen(empty));
		write(2, "\", this command takes no arguments\n", 36);
		return (1);
	}
	i = 0;
	while (__environ[i])
	{
		printf("%s\n", __environ[i]);
		i++;
	}
	i = 0;
	while (i < (*size) - 1)
	{
		printf("%s\n", env[0][i]);
		i++;
	}
	return (0);
}