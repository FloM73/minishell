/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 13:30:48 by flormich          #+#    #+#             */
/*   Updated: 2021/11/23 18:28:48 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

int	initialise_buf(t_struct *st)
{
	if (st->tr < st->nb_cmd - 1 && st->arr[st->tr].fd_out == 1)
		return (-1);
	st->all = 0;
	st->expand = 1;
	st->skip_space = 0;
	st->cancel = 0;
	st->buf = ft_calloc(1, sizeof(char *));
	return(0);
}

static int	test_flag_n(t_cmd *arr)
{
	int	i;
	int	j;

	i = 1;
	while (arr->cmd[i])
	{
		j = 2;
		if (ft_strncmp(arr->cmd[i], "-n", 2) == 0)
		{
			while (arr->cmd[i][j] == 'n' && arr->cmd[i][j] != '\0')
				j++;
			if (arr->cmd[i][j] == '\0')
				i++;
			else
				return (i);
		}
		else
			return (i);
	}
	return (i);
}

int	is_writable(t_struct *st, char c, int all)
{
	if (all == 0)
	{
		if (c == '\\')
			return (0);
		if (c == '(' || c == ')' )
		{
			st->cancel = 1;
			ms_error_synthaxe(c);
			return (0);
		}
		if (c == '>' || c == '<' )
		{	//if no file name => changer le parsing pour arriver jusque là
			st->cancel = 1;
			ms_error_synthaxe('\n');
			return (0);
		}
	}
	return (1);
}

void	bufferize_cmd(t_struct *st, t_cmd *arr, int arg)
{
	int		i;

	while (arr->cmd[arg] && st->cancel == 0)
	{
		i = 0;
		while (arr->cmd[arg][i] != '\0')
		{
			if (st->all == 0 && st->expand == 1 && arr->cmd[arg][i] == '"')
				st->all = 1;
			else if (st->all == 1 && st->expand == 1 && arr->cmd[arg][i] == '"')
				st->all = 0;
			else if (st->all == 0 && st->expand == 1 && arr->cmd[arg][i] == '\'')
			{
				st->all = 1;
				st->expand = 0;
			}
			else if (st->all == 1 && st->expand == 0 && arr->cmd[arg][i] == '\'')
			{
				st->all = 0;
				st->expand = 1;
			}
			else if (st->expand == 1 && (arr->cmd[arg][i] == '$' || arr->cmd[arg][i] == '~') && arr->cmd[arg][i + 1] != '%')
				i = launch_bufferize_variable(st, arr, arg, i);
			else if (is_writable(st, arr->cmd[arg][i], st->all) == 1)
				st->buf = add_char_to_buf(st, arr->cmd[arg][i]);
			i++;
		}
		st->buf = add_char_to_buf(st, ' ');
		arg++;
	}
}

// if pos_arg > 1: there is a valid -n flag
int	run_echo(void *stt, void *cmd)
{
	t_cmd		*arr;
	t_struct	*st;
	int			pos_arg;

	arr = (t_cmd *)cmd;
	st = (t_struct *)stt;
	if (initialise_buf(st) == 0)
	{
		pos_arg = test_flag_n(arr);
		bufferize_cmd(st, arr, pos_arg);
		if (st->cancel == 0)
		{
			ft_putstr_fd(st->buf, arr->fd_out);
			if (pos_arg == 1)
				write(arr->fd_out, "\n", 1);
		}
		free(st->buf);
	}
	return (0);
}
