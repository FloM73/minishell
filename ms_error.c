/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 19:55:53 by flormich          #+#    #+#             */
/*   Updated: 2021/10/22 01:46:40 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libs.h"

void	ms_error(char *txt, int	*exit_level, t_struct *st)
{
	perror(txt);
	if (st->name_in)
		free(st->name_in);
	if (st->name_out)
		free(st->name_out);
	if (exit_level == 0)
		exit (-1);
}

void	ms_error_file(char c)
{
	if (c == '\0' || c == '\n')
		printf("-bash: syntax error near unexpected token `newline'\n");
	else if (c == '|')
		printf("-bash: syntax error near unexpected token `|'\n");
	else if (c == '>')
		printf("-bash: syntax error near unexpected token `>'\n");
	else if (c == '<')
		printf("-bash: syntax error near unexpected token `<'\n");
	else
		printf("-bash: syntax error near unexpected token %c\n", c);
}
