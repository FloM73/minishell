/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_extract_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 18:28:43 by flormich          #+#    #+#             */
/*   Updated: 2021/11/22 22:52:05 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

static char	*expand_name(char **name)
{
	char	*tmp;
	char	*new_name;
	int		len;
	int		j;

	tmp = getenv(*name);
	if (!tmp)
		return (NULL);
	len = 0;
	while (tmp[len] != '\0' && ft_isalnum(tmp[len]) == 1)
		len++;
	new_name = ft_calloc(len, sizeof(char));
	j = 0;
	while (j < len)
	{
		new_name[j] = tmp[j];
		j++;
	}
	new_name[j] = '\0';
	free(*name);
	return (new_name);
}

int	extract_limiter(t_struct *st, int i)
{
	int	len;
	int	j;

	i = test_synthaxe(st, i, LIMITER);
	if (i == -1)
		return (-1);
	len = count_lengh_name(st, i);
	st->arr[st->tr].limiter = malloc_file_name(&(st->arr[st->tr].limiter), len);
	if (!st->arr[st->tr].limiter)
		ms_error("Failed to malloc limiter\n", 0, st);
	j = 0;
	while (j < len)
		st->arr[st->tr].limiter[j++] = st->input[i++];
	if (st->expand == 1)
		st->arr[st->tr].limiter = expand_name(&(st->arr[st->tr].limiter));
	st->arr[st->tr].name_in = ft_strdup("tmp_limite");
	st->arr[st->tr].fd_in = open(st->arr[st->tr].name_in, O_CREAT | O_RDWR, 0777);
	if (test_file_descriptor(st->arr[st->tr].fd_in, "tmp_limite") == -1)
		return (-1);
	return (i);
}

// Find input file name and test if valid
int	extract_infile(t_struct *st, int i)
{
	int	len;
	int	j;

	i = test_synthaxe(st, i, INFILE);
	if (i == -1)
		return (-1);
	len = count_lengh_name(st, i);
	st->arr[st->tr].name_in = malloc_file_name(&(st->arr[st->tr].name_in), len);
	if (!st->arr[st->tr].name_in)
		ms_error("Failed to malloc infile\n", 0, st);
	j = 0;
	while (j < len)
		st->arr[st->tr].name_in[j++] = st->input[i++];
	if (st->expand == 1)
		st->arr[st->tr].name_in = expand_name(&(st->arr[st->tr].name_in));
	st->arr[st->tr].fd_in = open(st->arr[st->tr].name_in, O_RDWR, 0777);
	if (test_file_descriptor(st->arr[st->tr].fd_in, st->arr[st->tr].name_in) == -1)
		return (-1);
	return (i);
}

// Find output file name and test if valid and put it in the cmd struct
int	extract_outfile(t_struct *st, int i)
{
	int	len;
	int	j;
	int	append;

	append = 0;
	if (st->input[i] == '>')
		append = 1;
	i = test_synthaxe(st, i, OUTFILE);
	if (i == -1)
		return (-1);
	len = count_lengh_name(st, i);
	st->arr[st->tr].name_out = malloc_file_name(&(st->arr[st->tr].name_out), len);
	if (!st->arr[st->tr].name_out)
		ms_error("Failed to malloc infile\n", 0, st);
	j = 0;
	while (j < len)
		st->arr[st->tr].name_out[j++] = st->input[i++];
	if (st->expand == 1)
		st->arr[st->tr].name_out = expand_name(&(st->arr[st->tr].name_out));
	st->arr[st->tr].fd_out = open_outfile(st->arr[st->tr].name_out, append);
	if (test_file_descriptor(st->arr[st->tr].fd_out, st->arr[st->tr].name_out) == -1)
		return (-1);
	return (i);
}
