/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 19:25:26 by flormich          #+#    #+#             */
/*   Updated: 2021/10/22 01:43:52 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libs.h"

// just for test purpose
static void	print_cmd(t_struct *st)
{
	int	i;
	//int	j;

	printf("Infile:  fd = %3d - name = %s\n", st->fd_in, st->name_in);
	printf("Outfile: fd = %3d - name = %s\n", st->fd_out, st->name_out);
	i = 0;
	while (i < st->nb_cmd)
	{
	/*	j = 0;
		while (st->arr[i].cmd[i][j])
		{
			printf("cmd %d - Arg %d = %d\n", i, j, st->arr[i].cmd[i][j]);
			j++;
		}*/
		printf("\n");
		i++;
	}
}

// what's the trick to get ride of the -Werror: is not use ??
static void	init_st(int argc, char **argv, char **envp, t_struct *st)
{
	argc = argc;
	argv = argv;
	st->nb_cmd = 0;
	st->fd_in = 0;
	st->name_in = NULL;
	st->fd_out = 1;
	st->name_out = NULL;
	st->limiter = NULL;
	st->env = envp;
}

/*
void	free_memory(t_struct *st)
{
	int	i;
	int	j;

	if (st->name_in)
		free(st->name_in);
	if (st->name_out)
		free(st->name_out);
	i = 0;
	while (i < st->nb_cmd)
	{
		j = 0;
		while (st->arr[i][j])
		{
			free(st->arr[i][j]);
			j++;
		}
		free(st->arr[i]);
		i++;
	}
	free(st->arr);
	free(st->limiter);
}
*/
int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	*temp;
	t_struct	st;

	while (1)
	{
		temp = readline("$ ");
		input = ft_strtrim(temp, " 	");
		//printf("Input = |%s|\ntemp  = |%s|\n", input, temp);
		free(temp);
		if (input && input[0] != '\0')
		{
			init_st(argc, argv, envp, &st);
			if (extract_cmd(input, &st) == 0)
				print_cmd(&st);
			write(1, "1\n", 2);
			//free_memory(&cmd);
			write(1, "2\n", 2);
			init_st(argc, argv, envp, &st);
		}
	}
	write(1, "end\n", 4);
	//free_memory(&st);
	free(input);
	return (0);
}
