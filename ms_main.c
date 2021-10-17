/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 19:25:26 by flormich          #+#    #+#             */
/*   Updated: 2021/10/16 23:50:00 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libs.h"

// just for test purpose
static void	print_cmd(t_cmd *cmd)
{
	int	i;
	int	j;

	printf("Infile:  fd = %3d - name = %s\n", cmd->fd_in, cmd->name_in);
	printf("Outfile: fd = %3d - name = %s\n", cmd->fd_out, cmd->name_out);
	i = 0;
	while (i < cmd->nb_cmd)
	{
		j = 0;
		while (cmd->arr_cmd[i][j] != NULL)
		{
			printf("cmd %d - Arg %d = %s\n", i, j, cmd->arr_cmd[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

// what's the trick to get ride of the -Werror: is not use ??
static void	init_cmd(int argc, char **argv, char **envp, t_cmd *cmd)
{
	argc = argc;
	argv = argv;
	cmd->nb_cmd = 0;
	cmd->fd_in = 0;
	cmd->name_in = NULL;
	cmd->fd_out = 1;
	cmd->name_out = NULL;
	cmd->limiter = NULL;
	cmd->env = envp;
}

void	free_memory(t_cmd *cmd)
{
	int	i;
	int	j;

	if (cmd->name_in)
		free(cmd->name_in);
	if (cmd->name_out)
		free(cmd->name_out);
	i = 0;
	while (i < cmd->nb_cmd)
	{
		j = 0;
		while (cmd->arr_cmd[i][j])
		{
			free(cmd->arr_cmd[i][j]);
			j++;
		}
		free(cmd->arr_cmd[i]);
		i++;
	}
	free(cmd->arr_cmd);
	free(cmd->limiter);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_cmd	cmd;

	while (1)
	{
		input = readline("$ ");
		if (!input || input[0] == '\0')
			return (-1);
		init_cmd(argc, argv, envp, &cmd);
		cmd.arr_cmd = parse_cmd(input, &cmd);
		if (cmd.arr_cmd)
			print_cmd(&cmd);
		free_memory(&cmd);
		init_cmd(argc, argv, envp, &cmd);
	}
	write(1, "end\n", 4);
	free_memory(&cmd);
	free(input);
	return (0);
}
