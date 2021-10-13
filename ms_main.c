/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 19:25:26 by flormich          #+#    #+#             */
/*   Updated: 2021/10/13 23:02:19 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libs.h"

// just for test purpose
static void	print_cmd(t_cmd *cmd)
{
	int	i;
	int	j;

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
	cmd->env = envp;
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_cmd	cmd;

	while (1)
	{
		input = readline("$");
		if (!input || input[0] == '\0')
			return (-1);
		init_cmd(argc, argv, envp, &cmd);
		cmd.arr_cmd = parse_cmd(input, &cmd);
		print_cmd(&cmd);						//just for test
	}
	return (0);
}
