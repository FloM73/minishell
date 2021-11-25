/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_0_expand_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 18:18:33 by flormich          #+#    #+#             */
/*   Updated: 2021/11/25 18:19:52 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

void	bufferize_input(t_struct *st, char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '$' && is_variable_end(st, str[i + 1]) == 0) || str[i] == '~')
			i = launch_expand_variable_input(st, str, i);
		else if (str[i] == '$' && str[i + 1] == '$')
		{
			st->buf = add_number_to_buf(st, getpid());
			i++;
		}
		else if (str[i] == '\'')
		{
			st->buf = add_char_to_buf(st, str[i++]);
			while (str[i] != '\'' && str[i] != '\0')
			{
				st->buf = add_char_to_buf(st, str[i++]);
			}
			st->buf = add_char_to_buf(st, '\'');
		}
		else
			st->buf = add_char_to_buf(st, str[i]);
		i++;
	}
}

int	launch_expand_variable_input(t_struct *st, char *str, int pos_s)
{
	int		e;
	int		new_pos;

	if (str[pos_s] == '~')
	{
		e = 0;
		new_pos = 0;
		while (st->env[e])
		{
			new_pos = find_match(st, e, "HOME\0", 0);
			if (new_pos != 0)
				return (pos_s + 1);
			e++;
		}
	}
	else
	{
		e = 0;
		while (st->env[e])
		{
			new_pos = find_match(st, e, str, pos_s + 1);
			if (new_pos != 0)
				return(new_pos);
			e++;
		}
		st->buf = add_char_to_buf(st, str[pos_s++]);
		while (is_variable_end(st, str[pos_s]) == 0)
			st->buf = add_char_to_buf(st, str[pos_s++]);
	}
	return (pos_s - 1);
}
