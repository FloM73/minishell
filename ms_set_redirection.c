/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_set_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 11:52:27 by flormich          #+#    #+#             */
/*   Updated: 2021/12/05 19:18:49 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libs.h"

// STDIN = 0, STDOUT = 1, STDERR = 2
void	set_red_shell(t_struct *st, int which_cmd, int *fd, int *next_fd)
{
	if (st->nb_cmd == 1)
	{
		dup2(st->arr[which_cmd].fd_in, STDIN_FILENO);
		dup2(st->arr[which_cmd].fd_out, STDOUT_FILENO);
	}
	else if (which_cmd == 0)
	{
		dup2(st->arr[which_cmd].fd_in, STDIN_FILENO);
		dup2(next_fd[WRITE], STDOUT_FILENO);
	}
	else
	{
		if (st->arr[which_cmd].fd_in != 0)
			dup2(st->arr[which_cmd].fd_in, STDIN_FILENO);
		else if (st->fd_tmp != 0)
			dup2(st->fd_tmp, STDIN_FILENO);
		else
			dup2(fd[READ], STDIN_FILENO);
		if (which_cmd == st->nb_cmd - 1)
			dup2(st->arr[which_cmd].fd_out, STDOUT_FILENO);
		else
			dup2(next_fd[WRITE], STDOUT_FILENO);
	}
	close(fd[READ]);
	close(fd[WRITE]);
}

static int	create_fd_tmp(t_struct *st)
{
	st->name_tmp = ft_strdup("tmp_fd");
	st->fd_tmp = open(st->name_tmp, O_CREAT | O_RDWR, 0777);
	if (test_fd(st->arr[st->tr].fd_in, st->name_tmp) == -1)
		return (-1);
	return (0);
}

int	launch_builtin(t_struct *st)
{
	int	i;

	st->no_output = 0;
	st->fd_tmp = 0;
	if (st->tr + 1 < st->nb_cmd && st->arr[st->tr + 1].cmd_type == SHELL
		&& st->arr[st->tr].fd_out == 1)
	{
		st->no_output = 1;
		if (create_fd_tmp(st) == -1)
			return (-1);
	}
	st->res = st->arr[st->tr].f_ptr(st, &(st->arr[st->tr]));
	if (st->no_output == 1)
	{
		i = 0;
		while (st->buf[i] != '\0')
			write(st->fd_tmp, &(st->buf[i++]), 1);
		close(st->fd_tmp);
		free(st->buf);
		st->fd_tmp = open(st->name_tmp, O_RDWR, 0777);
		free(st->name_tmp);
	}
	return (0);
}
