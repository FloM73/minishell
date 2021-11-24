/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_manage_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnuti <pnuti@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 10:14:36 by pnuti             #+#    #+#             */
/*   Updated: 2021/11/22 12:22:03 by pnuti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

int	ms_run_env(void *stt, void *cmd)
{
	t_cmd		*arr;
	t_struct	*st;

	arr = (t_cmd *)cmd;
	st = (t_struct *)stt;
	if (arr->cmd[1])
	{
		perror("Unexpected argument");
		return (-1);
	}
	st->digit += 1;
	st->digit -= 1;
	ms_env();
	return (0);
}

int	ms_run_export(void *stt, void *cmd)
{
	t_cmd		*arr;
	t_struct	*st;
	int			n;
	int			i;


	arr = (t_cmd *)cmd;
	st = (t_struct *)stt;
	n = 1;
	while (arr->cmd[n])
	{
		if (ft_strrchr(arr->cmd[n], '='))
			ms_export(arr->cmd[n], st, n == arr->nb_arg - 1);
		n++;
	}
	return (0);
}

int	ms_run_unset(void *stt, void *cmd)
{
	t_cmd		*arr;
	t_struct	*st;
	int			n;


	arr = (t_cmd *)cmd;
	st = (t_struct *)stt;
	n = 1;
	while (arr->cmd[n])
	{
		if (ms_unset(arr->cmd[n], st, n == arr->nb_arg - 1) != 0)
			return (-1);
		n++;
	}
	return (0);
}