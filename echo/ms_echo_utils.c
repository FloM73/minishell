/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:23:50 by flormich          #+#    #+#             */
/*   Updated: 2021/12/02 09:32:00 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

int	echo_double_quote(t_struct *st, t_cmd *arr, int arg, int i)
{
	while (arr->cmd[arg][i] != '"' && arr->cmd[arg][i] != '\0')
	{
		if (arr->cmd[arg][i] == '\\' && arr->cmd[arg][i + 1] == '"')
		{
			i++;
		}
		st->buf = add_char_to_buf(st, arr->cmd[arg][i++]);
	}
	return (i);
}

int	echo_simple_quote(t_struct *st, t_cmd *arr, int arg, int i)
{
	while (arr->cmd[arg][i] != '\'' && arr->cmd[arg][i] != '\0')
		st->buf = add_char_to_buf(st, arr->cmd[arg][i++]);
	return (i);
}
