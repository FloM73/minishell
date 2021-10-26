/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 19:09:00 by flormich          #+#    #+#             */
/*   Updated: 2021/10/24 01:29:22 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell_libs.h"

static int	skip_till(char *input, int from, char c, int max)
{
	while (input[from] != c && from <= max)
	{
		if (from == max || input[from] == '\0')
			return (-1);
		from++;
	}
	return (from);
}

static int	malloc_cmd(t_struct *st)
{
	int	i;
	int	j;

	i = 0;
	while (i < st->nb_cmd)
	{
		j = 0;
		while (j <= st->arr[i].nb_arg)
		{
			st->arr[i].cmd[j] = ft_calloc(st->len + 1, sizeof(char));
			//printf("MALLOC malloc_cmd st->arr[%d].cmd[%d] = %p\n", i, j, st->arr[i].cmd[j]);
			if (!st->arr[i].cmd[j])
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

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
		while (ft_isspace(input[i]) == 1 && st->take_all == 0)
		{
			i++;
			if (st->digit != 0)
			{
				st->arg++;
				st->digit = 0;
			}
		}
		if (input[i] == '|' && st->take_all == 0)
		{
			if (st->digit == 0 && st->arg == 0)
			{
				ms_error_synthaxe(input[i]);
				return (-1);
			}
			st->tr++;
			st->arg = 0;
			st->digit = 0;
			i++;
		}
		if (st->take_all == 0 && (input[i] == '<' || input[i] == '>'))
		{
			if (st->arr[st->tr].cmd[0][0] != '\0')
				st->tr++;
			st->arg = 0;
			st->digit = 0;
			i = extract_redirection(st, i);
			if (i == -1)
				return (-1);
		}
		if ((st->take_all == 0 && (input[i] == '"' || input[i] == '\''))
			|| (st->take_all == 1 && input[i] == c))
		{
			if (st->take_all == 0)
			{
				c = input[i];
				st->take_all = 1;
				if (st->digit != 0)
				{
					st->arg++;
					st->digit = 0;
				}
				st->arr[st->tr].cmd[st->arg][st->digit] = input[i];
				st->digit++;
				i++;
			}
			else
			{
				st->arr[st->tr].cmd[st->arg][st->digit] = input[i];
				st->take_all = 0;
				st->arg++;
				st->digit = 0;
				c = '\0';
				i++;
			}
		}
		else if (ft_isspace(input[i]) == 0 || st->take_all == 1)
		{
			st->arr[st->tr].cmd[st->arg][st->digit] = input[i];
			st->digit++;
			i++;
		}
	}
	return (0);
}

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
		while (input[i] != '|' && input[i] != '<' && input[i] != '>' && i <= st->len)
		{
			if (input[i] == '"' || input[i] == '\'')
			{
				i = skip_till(input, i + 1, input[i], st->len);
				if (i == -1)
					return (-1);
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

int	parse_input(t_struct *st)
{
	int	i;
	int	j;

	i = 0;
	st->nb_cmd = count_arg(st->input, st);
	if (st->nb_cmd == -1)
		return (-1);
	j = 0;
	while (j < st->nb_cmd)
		j++;
	while (i < st->nb_cmd)
	{
		st->arr[i].cmd = malloc((st->arr[i].nb_arg + 1 ) * sizeof(char *));
		//printf("MALLOC parse_input st->arr[%d].cmd = %p\n", i, st->arr[i].cmd);
		if (!st->arr[i].cmd)
			return (-1);
		i++;
	}
	if (fill_cmd(st->input, st) == -1)
		return (-1);
	return (0);
}
