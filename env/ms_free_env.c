/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:45:21 by pnuti             #+#    #+#             */
/*   Updated: 2021/12/07 19:15:41 by flormich         ###   ########.fr       */
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
	free(st->input);
	exit(0);
}
