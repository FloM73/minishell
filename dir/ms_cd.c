/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnuti <pnuti@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 17:50:14 by pnuti             #+#    #+#             */
/*   Updated: 2021/11/24 21:12:17 by pnuti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

/*
static void	add_home_directory(t_struct *st, t_cmd *arr)
{
	char	*tmp;

	tmp= arr->cmd[1];
	st->buf = ft_strdup(getenv("HOME"));
	arr->cmd[1] = ft_strjoin(st->buf, (arr->cmd[1] + 1));
	free(tmp);
	free(st->buf);
}
*/
int	cd(void *stt, void *cmd)
{
	t_cmd		*arr;
	t_struct	*st;
	int			i;
	int			len;

	arr = (t_cmd *)cmd;
	st = (t_struct *)stt;
	if (arr->cmd[2] != NULL)
	{
		ms_error_synthaxe('t');
		st->nb_cmd = 0;
		return (1);
	}
	if (initialise_buf(st) == 0)
	{
		bufferize_cmd(st, arr, 1);
		//chdir(st->buf);
		free(arr->cmd[1]);
		i = 0;
		len = ft_strlen(st->buf);
		arr->cmd[1] = ft_calloc(len + 1, sizeof(char));
		while (st->buf[i] != '\0')
		{
			arr->cmd[1][i] = st->buf[i];
			i++;
		}
	}
	printf("st->buf = %s - arr->cmd[0] = %s - arr->cmd[1] = %s - arr->cmd[2] = %s\n", st->buf, arr->cmd[0], arr->cmd[1], arr->cmd[2]);
	free(st->buf);
	return (chdir(arr->cmd[1]));
}
