/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_find_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 19:49:07 by flormich          #+#    #+#             */
/*   Updated: 2021/11/23 18:30:22 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

void	write_variable(t_struct *st, int e, int j)
{
	while (st->env[e][j + 2] != '\0')
	{
		st->buf = add_char_to_buf(st, st->env[e][j + 2]);
		j++;
	}
}

// How to put § : error: multi-character character constant [-Werror=multichar]
int	is_variable_end(t_struct *st, unsigned char c)
{
	if (c == ' ' || c == '"' || c == '\'' || c == '*' || c == '#'
		|| c == '%' || c == '\\' || c == '$' || c == '}' || c == '\0')
		return (1);
	else if (c == '!' || c == '&' || c == '/' || c == '='
		|| c == '?' || c == '-' || c == '@' )
		return (1);
	else if (c == '>' || c == '<' )
	{
		st->cancel = 1;
		perror("-bash: syntax error near unexpected token 'newline'\n");
	}
	return (0);
}

int	find_match(t_struct *st, int e, char *var, int pos)
{
	int	j;

	j = 0;
	while (st->env[e][j] == var[pos] && is_variable_end(st, var[pos] == 0))
	{
		if (st->env[e][j + 1] == '=' && is_variable_end(st, var[pos + 1]) == 1)
		{
			write_variable(st, e, j);
			return (pos);
		}
		pos++;
		j++;
	}
	return (0);
}

int	launch_bufferize_variable(t_struct *st, t_cmd *arr, int arg, int pos_s)
{
	int		e;
	int		new_pos;

	if (is_variable_end(st, arr->cmd[arg][pos_s + 1]) == 1 && arr->cmd[arg][pos_s] != '~')
	{
		if (arr->cmd[arg][pos_s] == '$' && (arr->cmd[arg][pos_s + 1] == ' ' || arr->cmd[arg][pos_s + 1] == '\0'
			|| (arr->cmd[arg][pos_s + 1] == '"' && st->all == 1)))
			st->buf = add_char_to_buf(st, '$');
		else if (arr->cmd[arg][pos_s + 1] == '$')
		{
			st->buf = add_number_to_buf(st, getpid());
			pos_s ++;
		}
		else if (arr->cmd[arg][pos_s + 1] == '#')
		{
			st->buf = add_number_to_buf(st, st->argc);
			pos_s ++;
		}
		else if (arr->cmd[arg][pos_s + 1] == '?')
		{
			// last return code
			st->buf = add_number_to_buf(st, 999);
			pos_s ++;
		}
		else if (arr->cmd[arg][pos_s + 1] == '@' || arr->cmd[arg][pos_s + 1] == '*')
			pos_s ++;
		return (pos_s);
	}
	if (arr->cmd[arg][pos_s + 1] == '{')
	{
		if (arr->cmd[arg][pos_s + 2] == '}')
		{
			st->cancel = 1;
			ms_error_synthaxe('}');
			return (0);
		}
		pos_s ++;
	}
	if (arr->cmd[arg][pos_s] == '~')
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
			new_pos = find_match(st, e, arr->cmd[arg], pos_s + 1);
			if (new_pos != 0)
			{
				if (arr->cmd[arg][new_pos + 1] == '}')
					new_pos += 2;
				return (new_pos);
			}
			e++;
		}
	}
	while(is_variable_end(st, arr->cmd[arg][pos_s + 1]) == 0)
		pos_s++;
	st->skip_space = 1;
	return(pos_s);
}

