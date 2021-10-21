/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_st.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 19:34:59 by flormich          #+#    #+#             */
/*   Updated: 2021/10/21 19:49:50 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell_libs.h"

static int	count_pipe(char *input)
{
	int	nb;
	int	i;

	i = 0;
	nb = 1;
	while (input[i] != '\0')
	{
		if (input[i] == '|')
			nb++;
		i++;
	}
	return (nb);
}

// create the maximum size ***arr according to the number of pipes
// eventually too big if some pipes are in "" or ''
static t_cmd	*create_arr(char *input, t_struct *st)
{
	t_cmd	*arr;

	st->nb_cmd = count_pipe(input);
	arr = malloc(st->nb_cmd * sizeof(t_cmd));
	if (!arr)
		ms_error("Fail to malloc arr_st_arg in ***parse_st", 0, st);
	printf("nb st = %d - ARR = %p\n", st->nb_cmd, arr);
	return (arr);
}

// Parse st option and args in ***arr_st
int	extract_cmd(char *input, t_struct *st)
{

	st->arr = create_arr(input, st);
	if (parse_input(input, st) == -1)
		return (-1);
	return (0);
}
