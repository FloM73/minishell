/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_0_expand_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 18:18:33 by flormich          #+#    #+#             */
/*   Updated: 2021/11/29 11:38:45 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

void	bufferize_input(t_struct *st, char *str, int i)
{
	while (str[i] != '\0' && i != -1)
	{
		if (str[i] == '\\' && (str[i + 1] == '$' || str[i] == '~'))
			st->buf = add_char_to_buf(st, str[i++]);
		else if ((str[i] == '$' && is_variable_end(st, str[i + 1]) == 0)
			|| (str[i] == '~' && is_variable_end(st, str[i + 1]) == 1)
			|| (str[i] == '$' && is_special_variable(str[i + 1]) == 1))
			i = launch_expand_variable(st, str, i);
		else if (str[i] == '\'')
			i = manage_simple_quote(st, str, i);
		else if (str[i] == '"')
			i = manage_doppel_quote(st, str, i);
		else
		{
			st->buf = add_char_to_buf(st, str[i]);
			i = count_pipe_skip_space(st, str, i);
		}
		i++;
	}
	st->buf = add_char_to_buf(st, '\0');
}

int	manage_doppel_quote(t_struct *st, char *str, int i)
{
	st->buf = add_char_to_buf(st, str[i++]);
	while (str[i] != '"' && str[i] != '\0')
	{
		if ((str[i] == '$' && is_variable_end(st, str[i + 1]) == 0)
			|| (str[i] == '~' && is_variable_end(st, str[i + 1]) == 1)
			|| (str[i] == '$' && is_special_variable(str[i + 1]) == 1))
			i = launch_expand_variable(st, str, i) + 1;
		else
		{
			if (str[i] == '\\' && str[i + 1] == '"')
				st->buf = add_char_to_buf(st, str[i++]);
			st->buf = add_char_to_buf(st, str[i++]);
		}
	}
	st->buf = add_char_to_buf(st, '"');
	return (i);
}

int	manage_simple_quote(t_struct *st, char *str, int i)
{
	st->buf = add_char_to_buf(st, str[i++]);
	while (str[i] != '\'' && str[i] != '\0')
		st->buf = add_char_to_buf(st, str[i++]);
	st->buf = add_char_to_buf(st, '\'');
	return (i);
}

int	launch_expand_variable(t_struct *st, char *str, int i)
{
	if ((str[i] == '$' && is_variable_end(st, str[i + 1]) == 0)
		|| (str[i] == '~' && is_variable_end(st, str[i + 1]) == 1))
		return (expand_variable(st, str, i));
	else if (str[i] == '$' && is_special_variable(str[i + 1]) == 1)
		return (expand_special_variable(st, str, i));
	return (expand_variable(st, str, i));
}