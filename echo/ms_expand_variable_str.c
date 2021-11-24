/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_variable_str.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 18:18:33 by flormich          #+#    #+#             */
/*   Updated: 2021/11/23 18:22:53 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

void	bufferize_str(t_struct *st, char *str)
{
	int		i;

	while (str && st->cancel == 0)
	{
		i = 0;
		while (str[i] != '\0')
		{
			if (st->all == 0 && st->expand == 1 && str[i] == '"')
				st->all = 1;
			else if (st->all == 1 && st->expand == 1 && str[i] == '"')
				st->all = 0;
			else if (st->all == 0 && st->expand == 1 && str[i] == '\'')
			{
				st->all = 1;
				st->expand = 0;
			}
			else if (st->all == 1 && st->expand == 0 && str[i] == '\'')
			{
				st->all = 0;
				st->expand = 1;
			}
			else if (st->expand == 1 && (str[i] == '$' || str[i] == '~') && str[i + 1] != '%')
				i = launch_bufferize_variable_str(st, str, i);
			else if (is_writable(st, str[i], st->all) == 1)
				st->buf = add_char_to_buf(st, str[i]);
			i++;
		}
		st->buf = add_char_to_buf(st, ' ');
	}
}

int	launch_bufferize_variable_str(t_struct *st, char *str, int pos_s)
{
	int		e;
	int		new_pos;

	if (is_variable_end(st, str[pos_s + 1]) == 1 && str[pos_s] != '~')
	{
		if (str[pos_s] == '$' && (str[pos_s + 1] == ' ' || str[pos_s + 1] == '\0'
			|| (str[pos_s + 1] == '"' && st->all == 1)))
			st->buf = add_char_to_buf(st, '$');
		else if (str[pos_s + 1] == '$')
		{
			st->buf = add_number_to_buf(st, getpid());
			pos_s ++;
		}
		else if (str[pos_s + 1] == '#')
		{
			st->buf = add_number_to_buf(st, st->argc);
			pos_s ++;
		}
		else if (str[pos_s + 1] == '?')
		{
			// last return code
			st->buf = add_number_to_buf(st, 999);
			pos_s ++;
		}
		else if (str[pos_s + 1] == '@' || str[pos_s + 1] == '*')
			pos_s ++;
		return (pos_s);
	}
	if (str[pos_s + 1] == '{')
	{
		if (str[pos_s + 2] == '}')
		{
			st->cancel = 1;
			ms_error_synthaxe('}');
			return (0);
		}
		pos_s ++;
	}
	if (str[pos_s] == '~')
	{
		e = 0;
		new_pos = 0;
		while (st->env[e])
		{
			find_match(st, e, "HOME", 0);
			if (new_pos != 0)
				return (pos_s + 1);
			e++;
		}
	}
	else
	{
		e = 0;
		new_pos = pos_s + 1;
		while (st->env[e])
		{
			new_pos = find_match(st, e, str, pos_s + 1);
			if (new_pos != 0)
			{
				if (str[new_pos + 1] == '}')
					new_pos += 2;
				return (new_pos);
			}
			e++;
		}
	}
	while(is_variable_end(st, str[pos_s + 1]) == 0)
		pos_s++;
	st->skip_space = 1;
	return(pos_s);
}
