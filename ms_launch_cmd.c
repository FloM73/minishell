/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_launch_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 11:26:13 by flormich          #+#    #+#             */
/*   Updated: 2021/11/14 11:09:17 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libs.h"

// STDIN = 0, STDOUT = 1, STDERR = 2
static void	set_redirection(t_struct *st, int which_cmd, int *fd, int *next_fd)
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
}

static void	exec_child(t_struct *st, int tr)
{
	if (execve(st->arr[tr].cmd[0], st->arr[tr].cmd, st->env) == -1)
		perror("Child: execve failed");
}

int	launch_cmd(t_struct *st)
{
	pid_t	pid;
	int		fd[2];
	int		next_fd[2];
	int		i;

	if (pipe(fd) == -1)
		return (-1);
	close(fd[WRITE]);
	i = 0;
	while (i < st->nb_cmd)
	{
		if (st->arr[i].cmd_type == BUILDIN)
			st->arr[i].f_ptr(st, &(st->arr[i]));
		else
		{
			if (pipe(next_fd) == -1)
				return (-1);
			pid = fork();
			if (pid < 0)
				perror ("Failed to create Child");
			if (pid == 0)
			{
				set_redirection(st, i, fd, next_fd);
				exec_child(st, i);
			}
			if (i < st->nb_cmd)
				dup2(next_fd[READ], fd[READ]);
			//else
			//	close(fd[READ]);
			close(next_fd[READ]);
			close(next_fd[WRITE]);
			waitpid(pid, NULL, 0);
		}
		i++;
	}
	return (0);
}
