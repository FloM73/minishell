/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_set_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 11:52:27 by flormich          #+#    #+#             */
/*   Updated: 2021/12/03 22:45:46 by flormich         ###   ########.fr       */
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
	else if (which_cmd == st->nb_cmd - 1)
	{
		dup2(fd[READ], STDIN_FILENO);
		dup2(st->arr[which_cmd].fd_out, STDOUT_FILENO);
	}
	else
	{
		dup2(fd[READ], STDIN_FILENO);
		dup2(next_fd[WRITE], STDOUT_FILENO);
	}
	close(fd[READ]);
	close(fd[WRITE]);
}
