/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_clean_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnuti <pnuti@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 09:45:01 by flormich          #+#    #+#             */
/*   Updated: 2021/12/02 16:20:22 by pnuti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell_libs.h"

static void	trim_quote(t_cmd *arr, char c)
{
	char	*tmp;

	if (c == '"')
		tmp = ft_strtrim(arr->cmd[0], "\"");
	else
		tmp = ft_strtrim(arr->cmd[0], "'");
	if (tmp)
	{
		free(arr->cmd[0]);
		arr->cmd[0] = tmp;
	}
}
/*
static void	implement_cmd_typ(t_cmd *arr)
{
	if (arr->cmd[0][0] == '"' || arr->cmd[0][0] == '"')
		trim_quote(arr, arr->cmd[0][0]);
	if (ft_strncmp(arr->cmd[0], "echo", ft_strlen(arr->cmd[0])) == 0)
		arr->f_ptr = &run_echo;
	else if (ft_strncmp(arr->cmd[0], "env", ft_strlen(arr->cmd[0])) == 0)
		arr->f_ptr = &ms_run_env;
	else if (ft_strncmp(arr->cmd[0], "export", ft_strlen(arr->cmd[0])) == 0)
		arr->f_ptr = &ms_run_export;
	else if (ft_strncmp(arr->cmd[0], "unset", ft_strlen(arr->cmd[0])) == 0)
		arr->f_ptr = &ms_run_unset;
	else if (ft_strncmp(arr->cmd[0], "pwd", ft_strlen(arr->cmd[0])) == 0)
		arr->f_ptr = &pwd;
	else if (ft_strncmp(arr->cmd[0], "cd", ft_strlen(arr->cmd[0])) == 0)
		arr->f_ptr = &cd;
	else if (ft_strncmp(arr->cmd[0], "exit", ft_strlen(arr->cmd[0])) == 0)
		arr->f_ptr = &run_exit;
	else
	{
		arr->cmd_type = SHELL;
		return ;
	}
	arr->cmd_type = BUILTIN;
}
*/

static void	implement_cmd_typ(t_cmd *arr)
{
	if (arr->cmd[0][0] == '"' || arr->cmd[0][0] == '"')
		trim_quote(arr, arr->cmd[0][0]);
	if (ft_strncmp(arr->cmd[0], "echo", ft_strlen(arr->cmd[0])) == 0)
		arr->f_ptr = &run_echo;
	else if (ft_strncmp(arr->cmd[0], "env", ft_strlen(arr->cmd[0])) == 0)
		arr->f_ptr = &ms_run_env;
	else if (ft_strncmp(arr->cmd[0], "export", ft_strlen(arr->cmd[0])) == 0)
		arr->f_ptr = &ms_run_export;
	else if (ft_strncmp(arr->cmd[0], "unset", ft_strlen(arr->cmd[0])) == 0)
		arr->f_ptr = &ms_run_unset;
	else if (ft_strncmp(arr->cmd[0], "pwd", ft_strlen(arr->cmd[0])) == 0)
		arr->f_ptr = &pwd;
	else if (ft_strncmp(arr->cmd[0], "cd", ft_strlen(arr->cmd[0])) == 0)
		arr->f_ptr = &cd;
	else if (ft_strncmp(arr->cmd[0], "exit", ft_strlen(arr->cmd[0])) == 0)
		arr->f_ptr = &run_exit;
	else
	{
		arr->cmd_type = SHELL;
		return ;
	}
	arr->cmd_type = BUILTIN;
	//printf("cmd = %s - type = %d\n", arr->cmd[0], arr->cmd_type);
}

void	clean_arr(t_struct *st)
{
	int	tr;
	int	arg;
	int	offset;

	tr = 0;
	while (tr < st->nb_cmd)
	{
		arg = 0;
		implement_cmd_typ(&(st->arr[tr]));
		while (tr < st->nb_cmd && arg < st->arr[tr].nb_arg
			&& st->arr[tr].cmd[arg][0] != '\0')
			arg++;
		free(st->arr[tr].cmd[arg]);
		st->arr[tr].cmd[arg] = (char *)0;
		arg++;
		offset = 0;
		while (arg <= st->arr[tr].nb_arg)
		{
			free(st->arr[tr].cmd[arg]);
			offset++;
			arg++;
		}
		st->arr[tr].nb_arg -= offset;
		tr++;
	}
}
