/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_2_parse_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 19:09:00 by flormich          #+#    #+#             */
/*   Updated: 2021/11/27 16:54:48 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell_libs.h"

// Skipp the portion in-between "" or ''
// (used by count_arg)
static int	skip_till(char *input, int from, char c, int max)
{
	while (input[from] != c && from <= max)
	{
		if (from == max || input[from] == '\0')
			return (from);
		from++;
	}
	return (from);
}

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

// Screen the input string and save the command/opt/arg/redirection in the apropriate memory
static int	fill_cmd(char *input, t_struct *st)
{
	int		i;
	char	c;

	c = '\0';
	i = 0;
	if (malloc_cmd(st) == -1)
		return (-1);
	while (i < st->len)
	{
		while (ft_isspace(input[i]) == 1 && st->all == 0)
		{
			i++;
			if (st->digit != 0)
			{
				st->arg++;
				st->digit = 0;
			}
		}
		if (input[i] == '|' && st->all == 0)
		{
			st->tr++;
			st->arg = 0;
			st->digit = 0;
			i++;
		}
		if (st->all == 0 && (input[i] == '<' || input[i] == '>'))
		{
			st->arg = 0;
			st->digit = 0;
			i = extract_redirection(st, i);
			if (i == -1)
				return (-1);
		}
		if ((st->all == 0 && (input[i] == '"' || input[i] == '\''))
			|| (st->all == 1 && input[i] == c))
		{
			if (st->all == 0)
			{
				c = input[i];
				st->all = 1;
				st->arr[st->tr].cmd[st->arg][st->digit] = input[i];
				st->digit++;
				i++;
			}
			else
			{
				st->arr[st->tr].cmd[st->arg][st->digit] = input[i];
				st->all = 0;
				st->digit++;
				c = '\0';
				i++;
			}
		}
		else if (i < st->len && (ft_isspace(input[i]) == 0 || st->all == 1))
		{
			st->arr[st->tr].cmd[st->arg][st->digit] = input[i];
			st->digit++;
			i++;
		}
	}
	return (0);
}

// Count for each command the number of option + argument in order to know
// whiche size to malloc
static int	count_arg(char *input, t_struct *st)
{
	int		i;
	int		tr;

	tr = 0;
	i = 0;
	while (i <= st->len)
	{
		st->arr[tr].nb_arg = 0;
		while (ft_isspace(input[i]) == 1)
			i++;
		while (input[i] != '|' && i <= st->len && input[i] != '\0')
		{
			if (input[i] == '"' || input[i] == '\'')
			{
				i = skip_till(input, i + 1, input[i], st->len);
				//st->arr[tr].nb_arg++;
			}
			if (input[i] == '<' || input[i] == '>')
			{
				if (input[i + 1] == '<' || input[i + 1] == '>')
					i += 2;
				while (ft_isspace(input[i + 1] == 1) && i < st->len)
					i++;
				while (ft_isspace(input[i + 1]) == 0 && i < st->len)
					i++;
			}
			if (ft_isspace(input[i]) == 1)
			{
				while (ft_isspace (input[i + 1]) == 1)
					i++;
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

// Create the cmd array and lauch the parsing
int	parse_input(t_struct *st)
{
	int	tr;

	tr = 0;
	st->nb_cmd = count_arg(st->input, st);
	//printf("Nb_cmd from parse_input = %d\n", st->nb_cmd);
	if (st->nb_cmd == -1)
		return (-1);
	while (tr < st->nb_cmd)
	{
		st->arr[tr].cmd = malloc((st->arr[tr].nb_arg + 1 ) * sizeof(char *));
		//printf("MALLOC parse_input st->arr[%d].cmd    = %p - size = %ld\n", tr, st->arr[tr].cmd, (st->arr[tr].nb_arg + 1 ) * sizeof(char *));
		if (!st->arr[tr].cmd)
			return (-1);
		st->arr[tr].fd_in = 0;
		st->arr[tr].fd_out = 1;
		st->arr[tr].name_in = NULL;
		st->arr[tr].name_out = NULL;
		st->arr[tr].limiter = NULL;
		tr++;
	}
	if (fill_cmd(st->input, st) == -1)
		return (-1);
	clean_arr(st);
	return (0);
}
