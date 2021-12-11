/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnuti <pnuti@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:45:21 by pnuti             #+#    #+#             */
/*   Updated: 2021/12/11 09:15:02 by pnuti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

void	free_env(t_struct *st)
{
	int	i;

	i = 0;
	while (st->env[i])
	{
		free(st->env[i]);
		i++;
	}
	free(st->env);
	free(st->prompt);
	exit(0);
}
