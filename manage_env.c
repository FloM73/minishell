/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnuti <pnuti@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 17:38:59 by pnuti             #+#    #+#             */
/*   Updated: 2021/10/21 15:37:30 by pnuti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libs.h"

int	manage_env(char *name, int func(char ***, char *, int *))
{
	static int	n_env;
	static char	**env;

	if (!env)
	{
		env = (char **)malloc(1);
		env[0] = NULL;
	}
	return (func(&env, name, &n_env));
}
