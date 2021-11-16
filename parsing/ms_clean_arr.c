/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_clean_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 09:45:01 by flormich          #+#    #+#             */
/*   Updated: 2021/11/16 11:48:41 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell_libs.h"

static void	trim_quote(t_cmd *arr, char c)
{
	char	*tmp;

	if (c == '"')
		tmp = ft_strtrim(arr->cmd[0], "\"");
	else if (c == '\'')
		tmp = ft_strtrim(arr->cmd[0], "'");
	if (tmp)
	{
		free(arr->cmd[0]);
		arr->cmd[0] = tmp;
	}
}

static void	implement_cmd_typ(t_cmd *arr)
{
	if (arr->cmd[0][0] == '"' || arr->cmd[0][0] == '"')
		trim_quote(arr, arr->cmd[0][0]);
	if (ft_strncmp(arr->cmd[0], "echo", ft_strlen(arr->cmd[0])) == 0)
	{
		arr->cmd_type = BUILTIN;
		arr->f_ptr = &run_echo;
	}
	else
		arr->cmd_type = SHELL;
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
		while (st->arr[tr].cmd[arg][0] != '\0' && arg <= st->arr[tr].nb_arg)
			arg++;
		free(st->arr[tr].cmd[arg]);
		st->arr[tr].cmd[arg] = (char *)0;
		//st->arr[tr].skip_space = 0;
		arg++;
		offset = 0;
		while (arg <= st->arr[tr].nb_arg)
		{
			//printf("FREE_clean_arr st->arr[%d].cmd[%d] %p\n", tr, arg, st->arr[tr].cmd[arg]);
			free(st->arr[tr].cmd[arg]);
			//st->arr[tr].cmd[arg] = 0;
			offset++;
			arg++;
		}
		st->arr[tr].nb_arg -= offset;
		tr++;
	}
}