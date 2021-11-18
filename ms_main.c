/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnuti <pnuti@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 19:25:26 by flormich          #+#    #+#             */
/*   Updated: 2021/11/18 09:26:55 by pnuti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libs.h"

// just for test purpose
static void	print_cmd(t_struct *st)
{
	int	tr;
	int	arg;

	//printf("Infile:  fd = %3d - name = %s\n", st->fd_in, st->name_in);
	//printf("Outfile: fd = %3d - name = %s\n", st->fd_out, st->name_out);
	tr = 0;
	while (tr < st->nb_cmd)
	{
		arg = 0;
		//printf("Infile: fd = %3d - name = %s\n", st->arr[tr].fd_in, st->arr[tr].name_in);
		//printf("Outfile: fd = %3d - name = %s\n", st->arr[tr].fd_out, st->arr[tr].name_out);
		while (arg <= st->arr[tr].nb_arg)
		{
			//printf("st->arr[%d].cmd[%d] = %10s (%p)\n", tr, arg, st->arr[tr].cmd[arg], st->arr[tr].cmd[arg]);
			arg++;
		}
		//printf("\n");
		tr++;
	}
}

// what's the trick to get ride of the -Werror: is not use ??
static void	init_st(int argc, char **argv, char **envp, t_struct *st)
{
	st->argc = argc;
	st->argv = argv;
	st->nb_cmd = 0;
/*	st->fd_in = 0;
	st->name_in = NULL;
	st->fd_out = 1;
	st->name_out = NULL;
	st->limiter = NULL;*/
	st->env = envp;
	st->arg = 0;
	st->tr = 0;
	st->digit = 0;
	st->all = 0;
	st->expand = 0;
	st->len = (int)ft_strlen(st->input);
}

void	free_memory(t_struct *st)
{
	int	tr;
	int	arg;

	/*if (st->name_in)
		free(st->name_in);
	if (st->name_out)
		free(st->name_out);*/
	tr = 0;
	while (tr < st->nb_cmd)
	{
		arg = 0;
		if (st->arr[tr].name_out)
			free(st->arr[tr].name_out);
		if (st->arr[tr].name_in)
			free(st->arr[tr].name_in);
		if (st->arr[tr].limiter)
			free(st->arr[tr].limiter);
		while (arg <= st->arr[tr].nb_arg)
		{
			//printf("FREE st->arr[%d].cmd[%d] = %p\n", tr, arg, st->arr[tr].cmd[arg]);
			free(st->arr[tr].cmd[arg]);
			arg++;
		}
		//printf("FREE st->arr[%d].cmd = %p\n", tr, st->arr[tr].cmd);
		free(st->arr[tr].cmd);
		tr++;
	}
	//printf("FREE st->arr = %p\n", st->arr);
	free(st->arr);
	free(st->input);
	//printf("FREE st->limiter = %p\n", st->limiter);
	//free(st->limiter);
}

int	main(int argc, char **argv, char **envp)
{
	//char		*temp;
	t_struct	st;

	ms_sig_hook();
	while (1)
	{
		//temp = readline("SHELL $ ");
		//st.input = ft_strtrim(temp, " 	");
		st.input = readline("SHELL $ ");
		//printf("Input   = |%s|\ntemp    = |%s|\n", st.input, temp);
		//free(temp);
		if (st.input && st.input[0] != '\0')
		{
			add_history(st.input);
			init_st(argc, argv, envp, &st);
			if (extract_cmd(&st) == 0)
			{
				print_cmd(&st);
				launch_cmd(&st);
			}
			free_memory(&st);
			init_st(argc, argv, envp, &st);
		}
		else
			return (0);
	}
	return (0);
}
