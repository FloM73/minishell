/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_run_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnuti <pnuti@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 08:10:56 by pnuti             #+#    #+#             */
/*   Updated: 2021/11/19 08:31:33 by pnuti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libs.h"

int	run_exit(void *stt, void *cmd)
{
	t_cmd		*arr;
	t_struct	*st;

	arr = (t_cmd *)cmd;
	st = (t_struct *)stt;
	arr->cmd[arr->nb_arg] = NULL;
	free_memory(st);
	exit(0);
	return (0);
}
