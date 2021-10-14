/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_extract_redirection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 18:43:25 by flormich          #+#    #+#             */
/*   Updated: 2021/10/15 00:16:19 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell_libs.h"

// TO CHECK=
// - what are all the space characters ?
// - shall we test >>> ?
static int	extract_output(char *str, t_cmd *cmd)
{
	int		len;
	int		i;
	int		j;
	int		append;

	len = ft_strlen(str);
	cmd->name_outfile = ft_calloc(len + 1, sizeof(char));
	i = 0;
	while (str[i] == '>')
		i++;
	append = i - 1;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
	{
		perror(RED"Output file needed\n"D);
		return (-1);
	}
	j = 0;
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t')
	{
		cmd->name_outfile[j] = str[i];
		i++;
		j++;
	}
	if (append == 1)
		cmd->fd_outfile = open(cmd->name_outfile, O_RDWR | O_CREAT | O_APPEND, 0777);
	else if (append == 0)
		cmd->fd_outfile = open(cmd->name_outfile, O_RDWR | O_CREAT | O_TRUNC, 0777);
	else
		cmd->fd_outfile = -1;	// >>> or more
	if (cmd->fd_outfile == -1)
		perror(RED"Failed to open/create outfile\n"D);
	return (i);
}

static int	extract_input(char *str, t_cmd *cmd)
{
	int		len;
	int		i;
	int		j;

	len = ft_strlen(str);
	cmd->name_infile = ft_calloc(len + 1, sizeof(char));
	i = 0;
	while (str[i] == '<')
		i++;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
	{
		perror(RED"Input file needed\n"D);
		return (-1);
	}
	j = 0;
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t')
	{
		cmd->name_infile[j] = str[i];
		i++;
		j++;
	}
	cmd->fd_infile = open(cmd->name_infile, O_RDWR, 0777);
	if (cmd->fd_infile == -1)
		perror(RED"Failed to open infile\n"D);
	return (i);
}

// remove file name from input
static void	remove_redirection(char *input, int nb, char c)
{
	int	len;
	int	i;

	len = ft_strlen(input);
	i = 0;
	while (input[i] != c)
		i++;
	if (i + nb == len)
		input[i] = '\0';
	else
	{
		while (i + nb < len)
		{
			input[i] = input[i + nb];
			i++;
		}
		input[i] = '\0';
	}
}

char	*extract_redirection(char *input, t_cmd *cmd)
{
	int		len;
	char	*ptr;
	int		nb_to_remove;

	len = ft_strlen(input);
	ptr = ft_strnstr(input, ">", len);
	if (ptr)
		nb_to_remove = extract_output(ptr, cmd);
	if (nb_to_remove > 0)
		remove_redirection(input, nb_to_remove, '>');
	len = ft_strlen(input);
	ptr = ft_strnstr(input, "<", len);
	if (ptr)
		nb_to_remove = extract_input(ptr, cmd);
	if (nb_to_remove > 0)
		remove_redirection(input, nb_to_remove, '<');
	return (input);
}
