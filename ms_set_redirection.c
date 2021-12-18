/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_set_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 11:52:27 by flormich          #+#    #+#             */
/*   Updated: 2021/12/17 09:10:53 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libs.h"

static void	set_red_one_cmd(t_struct *st, int which_cmd)
{
	if (st->arr[which_cmd].limiter != NULL)
		dup2(st->fd[READ], STDIN_FILENO);
	else
		dup2(st->arr[which_cmd].fd_in, STDIN_FILENO);
	dup2(st->arr[which_cmd].fd_out, STDOUT_FILENO);
}

static void	set_red_first_cmd(t_struct *st, int which_cmd, int *next_fd)
{
	if (st->arr[which_cmd].limiter != NULL)
		dup2(st->fd[READ], STDIN_FILENO);
	else
		dup2(st->arr[which_cmd].fd_in, STDIN_FILENO);
	if (st->arr[which_cmd].fd_out != 1)
		dup2(st->arr[which_cmd].fd_out, STDOUT_FILENO);
	else
		dup2(next_fd[WRITE], STDOUT_FILENO);
}

// STDIN = 0, STDOUT = 1, STDERR = 2
void	set_red_shell(t_struct *st, int which_cmd, int *next_fd)
{
	if (st->nb_cmd == 1)
		set_red_one_cmd(st, which_cmd);
	else if (which_cmd == 0)
		set_red_first_cmd(st, which_cmd, next_fd);
	else
	{
		dup2(st->fd[READ], STDIN_FILENO);
		if (which_cmd == st->nb_cmd - 1)
			dup2(st->arr[which_cmd].fd_out, STDOUT_FILENO);
		else
			dup2(next_fd[WRITE], STDOUT_FILENO);
	}
	close(st->fd[READ]);
	close(st->fd[WRITE]);
}
