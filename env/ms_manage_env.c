/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_manage_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnuti <pnuti@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 10:14:36 by pnuti             #+#    #+#             */
/*   Updated: 2021/11/19 07:59:11 by pnuti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

static int	sort_and_exp(t_struct *st, int i, int done)
{
	char	*tmp;

	tmp = st->argv[i];
	while (st->argv[i + 1])
	{
		st->argv[i] = st->argv[i + 1];
		i++;
	}
	st->argv[i] = NULL;
	return (ms_export(tmp, st, done));
}

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
		else
		{
			i = 0;
			while (st->argv[i])
			{
				if (!ft_strncmp(arr->cmd[n], st->argv[i], 
					ft_len_until_char(st->argv[i], '=')))
				{
					if (sort_and_exp(st, i, n == arr->nb_arg - 1) != 0)
						return (-1);
				}
				i++;
			}
		}
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