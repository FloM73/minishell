/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_launch_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 11:26:13 by flormich          #+#    #+#             */
/*   Updated: 2021/10/25 23:36:43 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libs.h"

static void	exec_child(char **cmd)
{
	write(1, "exec\n", 5);
	if (execve(cmd[0], cmd, NULL) == -1)
	{
		write(1, "error exec\n", 11);
		perror("Child: execve failed");
	}
}

// STDIN = 0, STDOUT = 1, STDERR = 2
static void	set_redirection(t_struct *st, int which_cmd, int *fd)
{
	if (st->nb_cmd == 1)
	{
		dup2(st->fd_in, STDIN_FILENO);
		dup2(st->fd_out, STDOUT_FILENO);
	}
	else if (which_cmd == 0)
	{
		dup2(st->fd_in, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
	}
	else if (which_cmd == st->nb_cmd - 1)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(st->fd_out, STDOUT_FILENO);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
	}
	close(fd[0]);
	close(fd[1]);
}

int	launch_cmd(t_struct *st)
{
	pid_t	pid;
	int		fd[2];
	int		i;

	i = 0;
	while (i < st->nb_cmd)
	{
		write(1, "1\n", 2);
		if (pipe(fd) == -1)
			return (-1);
		write(1, "2\n", 2);
		set_redirection(st, i, fd);
		write(1, "3\n", 2);
		pid = fork();
		if (pid < 0)
			perror ("Failed to create Child");
		if (pid == 0)
		{
			st->arr[i].cmd[1] = NULL;
			//printf("cmd[0] = %s - cmd[1] = %s\n", st->arr[i].cmd[0], st->arr[i].cmd[1]);
			exec_child(st->arr[i].cmd);
		}
		close(fd[0]);
		close(fd[1]);
		waitpid(pid, NULL, 0);
		write(1, "4\n", 2);
		i++;
	}
	return (0);
}
