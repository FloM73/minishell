/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_extract_infile_limiter.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 18:28:43 by flormich          #+#    #+#             */
/*   Updated: 2021/10/17 13:09:00 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libs.h"

char	*extract_limiter(char *input, t_cmd *cmd)
{
	cmd->limiter = "a faire";
	return (input);
}

// Find input file name and test if valid
int	extract_infile(char *str, t_cmd *cmd)
{
	int		i;
	int		j;

	i = 0;
	while (str[i] == '<')
		i++;
	if (str[i] == '>')
		i++;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '\0' || str[i] == '\n' || str[i] == '|' || str[i] == '>')
	{
		ms_error_file(str[i]);
		return (-1);
	}
	cmd->name_in = malloc_file_name(&cmd->name_in, str);
	if (!cmd->name_in)
		ms_error("Failed to malloc infile\n", 0, cmd);
	j = 0;
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t')
		cmd->name_in[j++] = str[i++];
	cmd->fd_in = open(cmd->name_in, O_RDWR, 0777);
	if (test_file_descriptor(cmd->fd_in, cmd->name_in) == -1)
		return (-1);
	return (i);
}

char	*pilote_extract_infile(char *input, t_cmd *cmd)
{
	int		len;
	char	*ptr;
	int		nb_to_remove;

	len = ft_strlen(input);
	if (len < 1)
		return (NULL);
	ptr = ft_strnstr(input, "<", len);
	while (ptr)
	{
		nb_to_remove = extract_infile(ptr, cmd);
		if (nb_to_remove > 0)
			remove_redirection(input, nb_to_remove, '<');
		else
			return (NULL);
		len = ft_strlen(input);
		if (len < 1)
			return (NULL);
		ptr = ft_strnstr(input, "<", len);
	}
	return (input);
}
