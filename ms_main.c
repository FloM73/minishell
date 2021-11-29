/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 19:25:26 by flormich          #+#    #+#             */
/*   Updated: 2021/11/29 23:01:21 by flormich         ###   ########.fr       */
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
		printf("Infile:  fd = %3d - name = %s\n", st->arr[tr].fd_in, st->arr[tr].name_in);
		printf("Outfile: fd = %3d - name = %s\n", st->arr[tr].fd_out, st->arr[tr].name_out);
		printf("Limiter: %s\n", st->arr[tr].limiter);
		while (arg <= st->arr[tr].nb_arg)
		{
			printf("st->arr[%d].cmd[%d] = %10s (%p)\n", tr, arg, st->arr[tr].cmd[arg], st->arr[tr].cmd[arg]);
			arg++;
		}
		printf("\n");
		tr++;
	}
}

static void	init_st(int argc, char **argv, t_struct *st)
{
	st->argc = argc;
	st->argv = argv;
	st->arg = 0;
	st->tr = 0;
	st->digit = 0;
	st->all = 0;
	st->exp = 1;
	st->force_expand = -1;
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

static int	init_env(char **old_env, t_struct *st)
{
	int		i;
	int		n;
	char	path[PATH_MAX];
	char	*shell;
	char	*shell2;

	ms_sig_hook();
	st->prompt = ft_strdup("~/MAXIPAIN $ ");
	st->res = 0;
	n = ft_2darr_len(old_env);
	st->env = (char **)malloc(sizeof(char *) * (n + 1));
	if (!st->env)
		return (1);
	i = 0;
	while (old_env[i])
	{
		st->env[i] = ft_strdup(old_env[i]);
		i++;
	}
	st->env[i] = NULL;
	shell = ft_strjoin("SHELL=", getcwd(path, PATH_MAX));
	shell2 = ft_strjoin(shell, ms_get_env(st->env, "_") + 1);
	ms_export(shell2, st);
	free(shell2);
	free(shell);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_struct	st;

	init_env(envp, &st);
	while (1)
	{
		st.input = readline(st.prompt);
		if (st.input && st.input[0] != '\0')
		{
			add_history(st.input);
			if (manage_expand_variable(&st) == 0)
			{
				init_st(argc, argv, &st);
				if (extract_cmd(&st) == 0)
				{
					print_cmd(&st);
					if (launch_cmd(&st) != 0)
						st.res = 1;
				}
				free_memory(&st);
				init_st(argc, argv, &st);
			}
		}
		else if (!st.input)
			free_env(&st);
	}
	return (0);
}
