/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_launch_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 11:26:13 by flormich          #+#    #+#             */
/*   Updated: 2021/12/01 09:06:33 by flormich         ###   ########.fr       */
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
	close(fd[WRITE]);
}

static void	exec_child(t_struct *st, int tr, int *fd, int *next_fd)
{
	if (st->arr[tr].limiter != NULL)
		read_till_limiter(st, tr);
	set_redirection(st, st->tr, fd, next_fd);
	if (st->arr[tr].fd_out != 1)
		dup2(st->arr[tr].fd_out, STDOUT_FILENO);
	if (execve(st->arr[tr].cmd[0], st->arr[tr].cmd, NULL) == -1)
		perror("Child: execve failed");
}

static void	manage_fd(t_struct *st, int *fd, int *next_fd)
{
	if (st->tr < st->nb_cmd)
		dup2(next_fd[READ], fd[READ]);
	close(next_fd[READ]);
	close(next_fd[WRITE]);
}

static int	launch_pipe(t_struct*st, int *fd)
{
	pid_t	pid;
	int		status;
	int		next_fd[2];

	if (pipe(next_fd) == -1)
		return (-1);
	pid = fork();
	if (pid < 0)
		perror ("Failed to create Child");
	if (pid == 0)
		exec_child(st, st->tr, fd, next_fd);
	manage_fd(st, fd, next_fd);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		st->res = WEXITSTATUS(status);
	return (0);
}

int	launch_cmd(t_struct *st)
{
	int		fd[2];

	if (pipe(fd) == -1)
		return (-1);
	while (st->tr < st->nb_cmd)
	{
		if (st->arr[st->tr].cmd_type == BUILTIN)
			st->res = st->arr[st->tr].f_ptr(st, &(st->arr[st->tr]));
		else
		{
			if (launch_pipe(st, fd) == -1)
				return (-1);
		}
		st->tr++;
	}
	return (0);
}
