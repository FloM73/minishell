/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 17:50:14 by pnuti             #+#    #+#             */
/*   Updated: 2021/11/19 14:23:41 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

static void	add_home_directory(t_struct *st, t_cmd *arr)
{
	char	*tmp;

	tmp= arr->cmd[1];
	st->buf = ft_strdup(getenv("HOME"));
	arr->cmd[1] = ft_strjoin(st->buf, (arr->cmd[1] + 1));
	free(tmp);
	free(st->buf);
}

int	cd(void *stt, void *cmd)
{
	t_cmd		*arr;
	t_struct	*st;

	arr = (t_cmd *)cmd;
	st = (t_struct *)stt;
	if (arr->cmd[2] != NULL)
	{
		ms_error_synthaxe('t');
		st->nb_cmd = 0;
		return (-1);
	}
	if (ft_strncmp(arr->cmd[1], "~", 1) == 0)
		add_home_directory(st, arr);
	return (chdir(arr->cmd[1]));
}
