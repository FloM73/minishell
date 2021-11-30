/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_2_parse_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 19:09:00 by flormich          #+#    #+#             */
/*   Updated: 2021/11/29 22:29:41 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell_libs.h"

static int	malloc_cmd(t_struct *st)
{
	int	tr;
	int	arg;

	tr = 0;
	while (tr < st->nb_cmd)
	{
		arg = 0;
		while (arg <= st->arr[tr].nb_arg)
		{
			st->arr[tr].cmd[arg] = ft_calloc(st->len + 1, sizeof(char));
			//printf("MALLOC malloc_cmd  st->arr[%d].cmd[%d] = %p - size = %ld\n", tr, arg, st->arr[tr].cmd[arg], (st->len + 1) * sizeof(char));
			if (!st->arr[tr].cmd[arg])
				return (-1);
			//printf("cmd = |%s|\n", st->arr[tr].cmd[j]);
			arg++;
		}
		tr++;
	}
	return (tr);
}

// Screen the input string and save the command/opt/arg/redirection
// in the apropriate memory
static int	fill_cmd(char *input, t_struct *st, int i)
{
	char	c;

	c = '\0';
	while (i < st->len && i != -1)
	{
		if (ft_isspace(input[i]) == 1 && st->all == 0)
			i = parse_space(st, i);
		if (input[i] == '|' && st->all == 0)
			i = parse_pipe(st, i);
		if (st->all == 0 && (input[i] == '<' || input[i] == '>'))
			i = parse_redirection(st, i);
		if (i != -1 && st->all == 0 && (input[i] == '"' || input[i] == '\''))
		{
			c = input[i];
			i = parse_quote(st, input, i, 1);
		}
		else if (i != -1 && st->all == 1 && input[i] == c)
		{
			i = parse_quote(st, input, i, 0);
			c = '\0';
		}
		else if (i != -1 && i < st->len && (ft_isspace(input[i]) == 0 || st->all == 1))
			i = parse_char(st, i, input[i]);
	}
	return (i);
}

// Count for each command the number of option + argument in order to know
// whiche size to malloc
static int	count_arg(char *input, t_struct *st, int i)
{
	int		tr;

	tr = 0;
	while (i <= st->len)
	{
		st->arr[tr].nb_arg = 0;
		while (ft_isspace(input[i]) == 1)
			i++;
		while (input[i] != '|' && i <= st->len && input[i] != '\0')
		{
			if (input[i] == '"' || input[i] == '\'')
				i = skip_till(input, i + 1, input[i], st->len);
			if (ft_isspace(input[i]) == 1)
			{
				if (input[i + 1] != '|' && i < st->len)
					st->arr[tr].nb_arg++;
			}
			i++;
		}
		st->arr[tr].nb_arg++;
		tr++;
		i++;
	}
	return (tr);
}

static void	initialize_cmd(t_struct *st, int tr)
{
	st->arr[tr].fd_in = 0;
	st->arr[tr].fd_out = 1;
	st->arr[tr].name_in = NULL;
	st->arr[tr].name_out = NULL;
	st->arr[tr].limiter = NULL;
}

// Create the cmd array and lauch the parsing
int	parse_input(t_struct *st)
{
	int	tr;

	tr = 0;
	st->nb_cmd = count_arg(st->input, st, 0);
	//printf("Nb_cmd from parse_input = %d\n", st->nb_cmd);
	if (st->nb_cmd == -1)
		return (-1);
	while (tr < st->nb_cmd)
	{
		st->arr[tr].cmd = malloc((st->arr[tr].nb_arg + 1) * sizeof(char *));
		//printf("MALLOC parse_input st->arr[%d].cmd    = %p - size = %ld\n", tr, st->arr[tr].cmd, (st->arr[tr].nb_arg + 1 ) * sizeof(char *));
		if (!st->arr[tr].cmd)
			return (-1);
		initialize_cmd(st, tr);
		tr++;
	}
	if (malloc_cmd(st) == -1)
		return (-1);
	if (fill_cmd(st->input, st, 0) == -1)
		return (-1);
	clean_arr(st);
	return (0);
}
