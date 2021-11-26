/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_3_extract_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 18:43:25 by flormich          #+#    #+#             */
/*   Updated: 2021/11/25 10:44:50 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell_libs.h"

// only allow alphanumeric => to implement
int	count_lengh_name(t_struct *st, int i)
{
	int	len;

	len = 0;
	while (ft_isspace(st->input[i]) == 0 && ft_isalnum(st->input[i]) == 1 && st->input[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

int	test_synthaxe(t_struct *st, int i, e_red red_type)
{
	if (st->input[i] == '>')
	{
		if (red_type == LIMITER)
		{
			ms_error_synthaxe(st->input[i]);
			return (-1);
		}
		i++;
	}
	while (ft_isspace(st->input[i]) == 1)
		i++;
	if (st->input[i] == '|' || st->input[i] == '>')
	{
		ms_error_synthaxe(st->input[i]);
		return (-1);
	}
	if (st->input[i] == '$')
		st->expand = 1;
	else
		st->expand = 0;
	return (i + st->expand);
}

int	extract_redirection(t_struct *st, int i)
{
	if (st->input[i] == '<' && st->input[i + 1] == '<')
		i = extract_limiter(st, i + 2);
	else if (st->input[i] == '<')
		i = extract_infile(st, i + 1);
	else
		i = extract_outfile(st, i + 1);
	return (i);
}
