/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 19:25:26 by flormich          #+#    #+#             */
/*   Updated: 2021/11/24 09:38:26 by flormich         ###   ########.fr       */
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
		//printf("Infile:  fd = %3d - name = %s\n", st->arr[tr].fd_in, st->arr[tr].name_in);
		//printf("Outfile: fd = %3d - name = %s\n", st->arr[tr].fd_out, st->arr[tr].name_out);
		//printf("Limiter: %s\n", st->arr[tr].limiter);
		while (arg <= st->arr[tr].nb_arg)
		{
			//printf("st->arr[%d].cmd[%d] = %10s (%p)\n", tr, arg, st->arr[tr].cmd[arg], st->arr[tr].cmd[arg]);
			arg++;
		}
		//printf("\n");
		tr++;
	}
}

static void	init_st(int argc, char **argv, char **envp, t_struct *st)
{
	st->argc = argc;
	st->argv = argv;
	st->nb_cmd = 0;
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

	tr = 0;
	while (tr < st->nb_cmd)
	{
		arg = 0;
		if (st->arr[tr].name_out)
			free(st->arr[tr].name_out);
		if (st->arr[tr].name_in)
			free(st->arr[tr].name_in);
		if (st->arr[tr].limiter)
		{
			unlink("tmp_limite");
			free(st->arr[tr].limiter);
		}
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
}

int	main(int argc, char **argv, char **envp)
{
	t_struct	st;

	ms_sig_hook();
	while (1)
	{
		st.input = readline(BL "~/MAXIPAIN $ " D);
		if (st.input && st.input[0] != '\0')
		{
			add_history(st.input);
			init_st(argc, argv, envp, &st);
			if (extract_cmd(&st) == 0)
			{
				print_cmd(&st);
				st.tr = 0;
				launch_cmd(&st);
			}
			free_memory(&st);
			init_st(argc, argv, envp, &st);
		}
		else if (!st.input)
			return (0);
	}
	return (0);
}
