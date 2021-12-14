/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_run_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnuti <pnuti@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 08:10:56 by pnuti             #+#    #+#             */
/*   Updated: 2021/12/14 15:35:20 by pnuti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libs.h"

int	run_exit(void *stt, void *cmd)
{
	t_struct	*st;
	t_cmd		*arr;

	st = (t_struct *)stt;
	arr = (t_cmd *)cmd;
	if (st->nb_cmd != 1)
		return (-1);
	if (!arr->cmd[1])
		g_exit_value = 0;
	else
	{
		g_exit_value = ft_atoi(arr->cmd[1]);
		if (g_exit_value == 0 && arr->cmd[1][0] != '0'
			&& ft_strlen(arr->cmd[1]) > 1)
		{
			g_exit_value = 2;
			write(2, "exit: numeric argument required\n", 33);
		}
	}
	free_memory(st);
	free_env(st);
	return (0);
}
