/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 19:55:53 by flormich          #+#    #+#             */
/*   Updated: 2021/11/23 19:29:20 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libs.h"

void	ms_error(char *txt, int	*exit_level, t_struct *st)
{
	perror(txt);
		st = st;
	if (exit_level == 0)
		exit(-1);
}

void	ms_error_synthaxe(char c)
{
	if (c == '\0' || c == '\n')
		printf("-bash: syntax error near unexpected token `newline'\n");
	else if (c == '|')
		printf("-bash: syntax error near unexpected token `|'\n");
	else if (c == '>')
		printf("-bash: syntax error near unexpected token `>'\n");
	else if (c == '<')
		printf("-bash: syntax error near unexpected token `<'\n");
	else if (c == '}')
		printf("-bash: ${}: bad substitution\n");
	else if (c == 't')
		printf("-bash: cd: too many arguments\n");
	else
		printf("-bash: syntax error near unexpected token '%c'\n", c);
}
