/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_run_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 08:10:56 by pnuti             #+#    #+#             */
/*   Updated: 2021/12/05 22:11:07 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libs.h"

int	run_exit(void *stt, void *cmd)
{
	t_struct	*st;

	st = (t_struct *)stt;
	if (st->nb_cmd != 1)
		return (-1);
	if (!cmd)
		cmd = NULL;
	free_memory(st);
	free_env(st);
	return (0);
}
