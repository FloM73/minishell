/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_extract_outfile.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 18:28:43 by flormich          #+#    #+#             */
/*   Updated: 2021/10/24 01:10:41 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

// Find output file name and test if valid
int	extract_outfile(t_struct *st, int i)
{
	int	len;
	int	j;
	int	append;

	append = 0;
	if (st->input[i] == '>')
	{
		i++;
		append = 1;
	}
	while (ft_isspace(st->input[i]) == 1)
		i++;
	if (st->input[i] == '|' || st->input[i] == '<')
	{
		ms_error_synthaxe(st->input[i]);
		return (-1);
	}
	len = count_lengh_name(st, i);
	st->name_out = malloc_file_name(st->name_out, len);
	if (!st->name_out)
		ms_error("Failed to malloc infile\n", 0, st);
	j = 0;
	while (j < len)
		st->name_out[j++] = st->input[i++];
	st->fd_out = open_outfile(st->name_out, append);
	if (test_file_descriptor(st->fd_out, st->name_out) == -1)
		return (-1);
	return (i);
}
