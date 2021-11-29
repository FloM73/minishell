/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:45:21 by pnuti             #+#    #+#             */
/*   Updated: 2021/11/29 09:27:08 by flormich         ###   ########.fr       */
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
