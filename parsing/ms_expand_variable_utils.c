/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_variable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:01:48 by flormich          #+#    #+#             */
/*   Updated: 2021/11/28 14:49:22 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

int	manage_expand_variable(t_struct *st)
{
	st->force_expand = -1;
	if (initialise_buf(st) == -1)
		return (-1);
	bufferize_input(st, st->input, 0);
	transfert_buf_input(st);
	if (st->input && st->input[0] != '\0')
		return (0);
	return (-1);
}

// How to put § : error: multi-character character constant [-Werror=multichar]
int	is_variable_end(t_struct *st, unsigned char c)
{
	if (c == ' ' || c == '"' || c == '\'' || c == '*' || c == '#'
		|| c == '%' || c == '\\' || c == '$' || c == '{' || c == '}'
		|| c == '\0' || c == '\n')
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

int	is_special_variable(unsigned char c)
{
	if (c == '$' || c == '?' || c == '@' || c == '*' || c == '{' || c == '"')
		return (1);
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

void	write_variable(t_struct *st, int e, int j)
{
	while (st->env[e][j + 2] != '\0')
	{
		st->buf = add_char_to_buf(st, st->env[e][j + 2]);
		j++;
	}
}
