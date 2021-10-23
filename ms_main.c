/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 19:25:26 by flormich          #+#    #+#             */
/*   Updated: 2021/10/24 01:16:21 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libs.h"

// just for test purpose
static void	print_cmd(t_struct *st)
{
	int	tr;
	int	arg;

	printf("Infile:  fd = %3d - name = %s\n", st->fd_in, st->name_in);
	printf("Outfile: fd = %3d - name = %s\n", st->fd_out, st->name_out);
	tr = 0;
	while (tr < st->nb_cmd)
	{
		arg = 0;
		while (arg <= st->arr[tr].nb_arg)
		{
			printf("st->arr[%d].cmd[%d] = %10s (%p)\n", tr, arg, st->arr[tr].cmd[arg], st->arr[tr].cmd[arg]);
			arg++;
		}
		printf("\n");
		tr++;
	}
}

// what's the trick to get ride of the -Werror: is not use ??
static void	init_st(int argc, char **argv, char **envp, t_struct *st)
{
	argc = argc + 1;
	argv[0] = NULL;
	st->nb_cmd = 0;
	st->fd_in = 0;
	st->name_in = NULL;
	st->fd_out = 1;
	st->name_out = NULL;
	st->limiter = NULL;
	st->env = envp;
	st->arg = 0;
	st->tr = 0;
	st->digit = 0;
	st->take_all = 0;
	st->len = (int)ft_strlen(st->input);
}

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
		while (j <= st->arr[i].nb_arg)
		{
			//printf("FREE st->arr[%d].cmd[%d] = %p\n", i, j, st->arr[i].cmd[j]);
			free(st->arr[i].cmd[j]);
			j++;
		}
		//printf("FREE st->arr[%d].cmd = %p\n", i, st->arr[i].cmd);
		free(st->arr[i].cmd);
		i++;
	}
	//printf("FREE st->arr = %p\n", st->arr);
	free(st->arr);
	//printf("FREE st->limiter = %p\n", st->limiter);
	free(st->limiter);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	char		*temp;
	t_struct	st;

	while (1)
	{
		temp = readline("$ ");
		st.input = ft_strtrim(temp, " 	");
		//printf("Input = |%s|\ntemp    = |%s|\n", input, temp);
		free(temp);
		if (st.input && st.input[0] != '\0')
		{
			init_st(argc, argv, envp, &st);
			if (extract_cmd(&st) == 0)
				print_cmd(&st);
			free_memory(&st);
			init_st(argc, argv, envp, &st);
		}
	}
	//free_memory(&st);
	free(input);
	return (0);
}
