/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_find_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 19:49:07 by flormich          #+#    #+#             */
/*   Updated: 2021/11/07 00:17:07 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libs.h"

static void	write_variable(t_struct *st, int e, int j)
{
	while (st->env[e][j + 2] != '\0')
	{
		write(1, &(st->env[e][j + 2]), 1);
		j++;
	}
}

static int	is_variable_end(char c)
{
	if (c == ' ' || c == '"' || c == '\'' || c == '*' || c == '#'
		|| c == '%' || c == '\\' || c == '$' || c == '}' || c == '\0')
		return (1);
	return (0);
}

static int	find_match(t_struct *st, int e, char *var, int pos)
{
	int	j;

	j = 0;
	while (st->env[e][j] == var[pos] && is_variable_end(var[pos] == 0))
	{
		if (st->env[e][j + 1] == '=' && is_variable_end(var[pos + 1]) == 1)
		{
			write_variable(st, e, j);
			return (pos);
		}
		pos++;
		j++;
	}
	return (0);
}

int	launch_write_variable(t_struct *st, t_cmd *arr, int arg, int pos_$)
{
	int		e;
	int		new_pos;

	if (is_variable_end(arr->cmd[arg][pos_$ + 1]) == 1)
	{
		if (arr->cmd[arg][pos_$ + 1] == ' ' || arr->cmd[arg][pos_$ + 1] == '\0')
			//|| arr->cmd[arg][pos_$ + 1] == '"')
			write(1, "$", 1);
		if (arr->cmd[arg][pos_$ + 1] == '$')
		{
			e = getpid();
			ft_putnbr_fd(e, 1);
		}
		return (pos_$ + 1);
	}
	if (arr->cmd[arg][pos_$ + 1] == '{')
		pos_$ ++;
	e = 0;
	new_pos = pos_$ + 1;
	while (st->env[e])
	{
		new_pos = find_match(st, e, arr->cmd[arg], pos_$ + 1);
		if (new_pos != 0)
			return (new_pos);
		e++;
	}
	while(arr->cmd[arg][pos_$ + 1] != ' ' && arr->cmd[arg][pos_$ + 1] != '\0')
		pos_$++;
	//arr->skip_space = 1;
	return(pos_$ + 1);
}
