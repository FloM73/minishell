/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_2_parse_input_utils_3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnuti <pnuti@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 07:26:57 by pnuti             #+#    #+#             */
/*   Updated: 2021/12/21 08:36:41 by pnuti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

int	parse_parenthesis(t_struct *st, char *input, int i)
{
	int	n;

	n = 1;
	st->arr[st->tr].cmd[st->arg][st->digit] = input[i];
	st->digit++;
	i++;
	while (n > 0)
	{
		if (input[i] == '(')
			n++;
		else if (input[i] == ')')
			n--;
		st->arr[st->tr].cmd[st->arg][st->digit] = input[i];
		st->digit++;
		i++;
	}
	st->arr[st->tr].cmd[st->arg][st->digit] = input[i];
	st->digit++;
	return (i + 1);
}
