/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_extract_redirection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 18:43:25 by flormich          #+#    #+#             */
/*   Updated: 2021/10/17 13:11:04 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell_libs.h"

static int	extract_outfile(char *str, t_cmd *cmd)
{
	int		i;
	int		j;
	int		append;

	i = 0;
	while (str[i] == '>' && i < 2)
		i++;
	append = i - 1;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '\0' || str[i] == '\n' || str[i] == '|' || str[i] == '>')
	{
		ms_error_file(str[i]);
		return (-1);
	}
	cmd->name_out = malloc_file_name(&cmd->name_out, str);
	if (!cmd->name_out)
		ms_error("Failed to malloc outfile\n", 0, cmd);
	j = 0;
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t')
		cmd->name_out[j++] = str[i++];
	cmd->fd_out = open_outfile(cmd->name_out, append);
	if (test_file_descriptor(cmd->fd_out, cmd->name_out) == -1)
		return (-1);
	return (i);
}

char	*pilote_extract_outfile(char *input, t_cmd *cmd)
{
	int		len;
	char	*ptr;
	int		nb_to_remove;

	len = ft_strlen(input);
	if (len < 1)
		return (NULL);
	ptr = ft_strnstr(input, ">", len);
	while (ptr)
	{
		nb_to_remove = extract_outfile(ptr, cmd);
		if (nb_to_remove > 0)
			remove_redirection(input, nb_to_remove, '>');
		else
			return (NULL);
		len = ft_strlen(input);
		if (len < 1)
			return (NULL);
		ptr = ft_strnstr(input, ">", len);
	}
	return (input);
}

char	*extract_redirection(char *input, t_cmd *cmd)
{
	int		len;
	char	*ptr;

	len = ft_strlen(input);
	if (len < 1)
		return (NULL);
	ptr = ft_strnstr(input, "<<", len);
	if (ptr)
		input = extract_limiter(input, cmd);
	if (!input)
		return (NULL);
	ptr = ft_strnstr(input, "<", len);
	if (ptr)
		input = pilote_extract_infile(input, cmd);
	if (!input)
		return (NULL);
	ptr = ft_strnstr(input, ">", len);
	if (ptr)
		input = pilote_extract_outfile(input, cmd);
	if (!input)
		return (NULL);
	return (input);
}
