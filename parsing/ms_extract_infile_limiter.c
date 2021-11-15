/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_extract_infile_limiter.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 18:28:43 by flormich          #+#    #+#             */
/*   Updated: 2021/11/11 19:42:52 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

int	extract_limiter(t_struct *st, int i)
{
	st->arr[st->tr].limiter = "a faire";
	i = i * 1;
	return (i);
}

// Find input file name and test if valid
int	extract_infile(t_struct *st, int i)
{
	int	len;
	int	j;

	if (st->input[i] == '>')
		i++;
	while (ft_isspace(st->input[i]) == 1)
		i++;
	if (st->input[i] == '|' || st->input[i] == '>')
	{
		ms_error_synthaxe(st->input[i]);
		return (-1);
	}
	len = count_lengh_name(st, i);
	st->arr[st->tr].name_in = malloc_file_name(&(st->arr[st->tr].name_in), len);
	if (!st->arr[st->tr].name_in)
		ms_error("Failed to malloc infile\n", 0, st);
	j = 0;
	while (j < len)
		st->arr[st->tr].name_in[j++] = st->input[i++];
	st->arr[st->tr].fd_in = open(st->arr[st->tr].name_in, O_RDWR, 0777);
	if (test_file_descriptor(st->arr[st->tr].fd_in, st->arr[st->tr].name_in) == -1)
		return (-1);
	return (i);
}
