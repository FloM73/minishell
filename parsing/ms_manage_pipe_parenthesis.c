/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_manage_pipe_parenthesis.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:24:04 by flormich          #+#    #+#             */
/*   Updated: 2021/12/29 19:03:47 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

static int	count_pipe(t_struct *st, char *str, int i)
{
	st->nb_cmd += 1;
	if (str[i - 1] != ' ')
		st->buf = add_char_to_buf(st, ' ');
	st->buf = add_char_to_buf(st, str[i++]);
	if (str[i - 1] != '|' || str[i] != '&')
		st->buf = add_char_to_buf(st, str[i]);
	while (ft_isspace(str[i]) == 1 && str[i + 1] != '\0'
		&& ft_isspace(str[i + 1]) == 1)
		i++;
	return (i);
}

int	launch_manage_pipe_parenthesis(t_struct *st, char *str, int i)
{
	if ((str[i] == '&' && str[i + 1] == '|')
		|| (str[i] == '&' && str[i + 1] != '&' && str[i - 1] != '|'))
	{
		ms_error_synthaxe(str[i]);
		return (-2);
	}
	if (str[i] == '|' || (str[i] == '&' && str[i + 1] == '&'))
		i = count_pipe(st, str, i);
	else
	{
		if (str[i] == '(')
			st->nb_parenthesis++;
		if (str[i] == ')')
			st->nb_parenthesis--;
		st->buf = add_char_to_buf(st, str[i]);
	}
	while (ft_isspace(str[i]) == 1 && str[i + 1] != '\0'
		&& ft_isspace(str[i + 1]) == 1)
		i++;
	return (i);
}
