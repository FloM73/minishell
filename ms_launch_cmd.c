/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_launch_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 11:26:13 by flormich          #+#    #+#             */
/*   Updated: 2021/10/14 18:16:51 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minshell_libs.h"
/*
static void	pip_exec_child1(t_files *fi, int fd[2])
{
	dup2(fi->input, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (execve(fi->cmd1[0], fi->cmd1, NULL) == -1)
		pip_print_error("Child 1: execve failed", 3, fi);
}
*/

static void	exec_child(t_cmd *cmd, int fd[2], int which_cmd)
{
	if (execve(fi->cmd1[0], fi->cmd1, NULL) == -1)
		pip_print_error("Child: execve failed");
}

// STDIN = 0, STDOUT = 1, STDERR = 2
static void	set_redirection(t_cmd *cmd, int which_cmd)
{
	if (which_cmd == 1)
	{
		dup2(cmd->fd_infile, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
	}
	if (which_cmd == cmd_nb_cmd)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(cmd->fd_outfile, STDOUT_FILENO);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
	}
	close(fd[0]);
	close(fd[1]);
}

int	launch_cmd(t_cmd *cmd)
{
	pid_t	pid;
	int		fd[2];
	int		i;

	i = 0;
	while (i < cmd->nb_cmd)
	{
		if (pipe(fd) == -1)
			return (-1);
		pid = fork();
		if (pid < 0)
			perror ("Failed to create Child");
		if (pid == 0)
			exec_child(cmd, fd);
		close(fd[0]);
		close(fd[1]);
		waitpid(pid, NULL, 0);
		i++;
	}
	return (0);
}
