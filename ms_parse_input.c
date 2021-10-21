/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 19:09:00 by flormich          #+#    #+#             */
/*   Updated: 2021/10/22 01:30:18 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell_libs.h"

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
/*
static int	fill_cmd(char *input, t_struct *st)
{
	int		i;
	int		tr;
	int		nb_arg;
	char	c;
	int	j;

	i = 0;
	tr = 0;
	nb_arg = 0;
	while (input[i] != '\0')
	{
		j = 0;
		while (ft_isspace(input[i]) == 1)
			i++;
		while (input[i] != '|' && input[i] != '\0' && ft_isspace(input[i] != 1))
		{
			if (input[i] == '"' || input[i] == '\'')
			{
				c = input[i];
				st->arr[tr].cmd[nb_arg][j++] = input[i++];
				while (input[i] != c)
					st->arr[tr].cmd[nb_arg][j++] = input[i++];
				st->arr[tr].cmd[nb_arg][j++] = input[i++];
			}
			st->arr[tr].cmd[nb_arg][j++] = input[i++];
		}
		nb_arg++;
		tr++;
	}
	st->nb_cmd = tr;
	return (0);
}
*/
static int	count_arg(char *input, t_struct *st)
{
	int		i;
	int		tr;
	int		len;

	tr = 0;
	len = (int)ft_strlen(input);
	i = 0;
	while (i <= len)
	{
		st->arr[tr].nb_arg = 0;
		while (ft_isspace(input[i]) == 1)
			i++;
		while (input[i] != '|' && i <= len)
		{
			if (input[i] == '"' || input[i] == '\'')
			{
				i = skip_till(input, i + 1, input[i], len);
				if (i == -1)
					return (-1);
			}
			if (ft_isspace(input[i]) == 1)
			{
				while (ft_isspace (input[i + 1]) == 1)
					i++;
				if (input[i + 1] != '|' && i < len)
					st->arr[tr].nb_arg++;
			}
			i++;
		}
		st->arr[tr++].nb_arg++;
		i++;
	}
	return (tr);
}

int	parse_input(char *input, t_struct *st)
{
	//int	i;
	int	j;

	//i = 0;
	st->nb_cmd = count_arg(input, st);
	if (st->nb_cmd == -1)
		return (-1);
	j = 0;
	while (j < st->nb_cmd)
	{
		printf("Count arg %d = %d\n", j, st->arr[j].nb_arg);
		j++;
	}
	/*
	while (i < st->nb_cmd)
	{
		st->arr[i].cmd = malloc((st->arr[i].nb_arg + 1 ) * sizeof(char *));
		fill_cmd(input, st);
	}
	*/
	return (0);
}
