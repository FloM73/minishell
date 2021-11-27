/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_0_expand_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 18:18:33 by flormich          #+#    #+#             */
/*   Updated: 2021/11/27 19:40:39 by flormich         ###   ########.fr       */
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
		else
			st->buf = add_char_to_buf(st, str[i]);
		if (str[i] == '"')
			st->force_expand *= -1;
		i++;
	}
}

int	manage_simple_quote(t_struct *st, char *str, int i)
{
	st->buf = add_char_to_buf(st, str[i++]);
	while (str[i] != '\'' && str[i] != '\0')
	{
		if (st->force_expand == 1 && (str[i] == '$' || str[i] == '~'))
			i = expand_variable(st, str, i) + 1;
		else
			st->buf = add_char_to_buf(st, str[i++]);
	}
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

int	expand_variable(t_struct *st, char *str, int i)
{
	int		e;
	int		new_pos;

	if (str[i] == '~')
	{
		st->buf_tmp = st->buf;
		st->buf = ft_strjoin(st->buf, ms_get_env(st->env, "HOME"));
		free(st->buf_tmp);
		return (i);
	}
	else
	{
		e = 0;
		while (st->env[e])
		{
			new_pos = find_match(st, e, str, i + 1);
			if (new_pos != 0)
				return (new_pos);
			e++;
		}
		i++;
		while (is_variable_end(st, str[i]) == 0)
			i++;
	}
	return (i - 1);
}

//@ && * make nothing
int	expand_special_variable(t_struct *st, char *str, int i)
{
	if (str[i + 1] == '$')
		st->buf = add_number_to_buf(st, getpid());
	else if (str[i + 1] == '?')
		st->buf = add_number_to_buf(st, st->res);
	else if (str[i + 1] == '{')
	{
		if (str[i + 2] == '}')
		{
			st->cancel = 1;
			ms_error_synthaxe('}');
			return (-2);
		}
		i = expand_variable(st, str, i + 1);
	}
	return (i + 1);
}
