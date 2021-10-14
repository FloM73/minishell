/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 19:25:26 by flormich          #+#    #+#             */
/*   Updated: 2021/10/15 00:04:13 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libs.h"

// just for test purpose
static void	print_cmd(t_cmd *cmd)
{
	int	i;
	int	j;

	printf("Infile:  fd = %3d - name = %s\n", cmd->fd_infile, cmd->name_infile);
	printf("Outfile: fd = %3d - name = %s\n", cmd->fd_outfile, cmd->name_outfile);
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

static void	init_cmd(int argc, char ** argv, char ** envp, t_cmd *cmd)
{
	// what's the trick to get ride of the -Werror: is not use ??
	argc = argc;
	argv = argv;
	cmd->nb_cmd = 0;
	cmd->fd_infile = 0;
	cmd->name_infile = NULL;
	cmd->fd_outfile = 1;
	cmd->name_outfile = NULL;
	cmd->env = envp;
}

static void	free_memory(t_cmd *cmd)
{
	int	i;
	int	j;

	if( cmd->name_infile)
		free(cmd->name_infile);
	if (cmd->name_outfile)
		free(cmd->name_outfile);
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
		print_cmd(&cmd);						//just for test
	}
	free_memory(&cmd);
	free(input);
	return (0);
}
