/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_variable_utils_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 22:31:57 by flormich          #+#    #+#             */
/*   Updated: 2021/12/18 23:56:53 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

int	check_is_wildcard(char *str, int i)
{
	int	wild_card;

	wild_card = 0;
	while (str[i] != '\0' && ft_isspace(str[i]) == 0)
	{
		if (str[i] == '"' || str[i] == '\'')
			return (0);
		if (str[i] == '*')
			wild_card = 1;
		i++;
	}
	return (wild_card);
}

static int	find_wildcard_match(t_struct *st, struct dirent *dirp)
{
	int		len_post;
	int		len_dir;

	if (st->pre && ft_strncmp(st->pre, dirp->d_name, ft_strlen(st->pre)) != 0)
		return (0);
	if (st->post)
	{
		len_post = ft_strlen(st->post);
		len_dir = ft_strlen(dirp->d_name);
		while (len_post > 0)
		{
			if (st->post[len_post - 1] == dirp->d_name[len_dir - 1])
			{
				len_post--;
				len_dir--;
			}
			else
				return (0);
		}
	}
	return (1);
}

int	launch_expand_wildcard(t_struct *st, char *str, int i)
{
	DIR				*cur_dir;
	struct dirent	*dirp;
	int				j;

	i = find_prefixe(st, str, i);
	cur_dir = opendir(ms_get_env(st->env, "PWD"));
	while (dirp != NULL)
	{
		dirp = readdir(cur_dir);
		if (dirp && dirp->d_name[0] != '.'
			&& (find_wildcard_match(st, dirp) == 1 || (!st->pre && !st->post)))
		{
			j = 0;
			while (dirp->d_name[j])
				st->buf = add_char_to_buf(st, dirp->d_name[j++]);
			st->buf = add_char_to_buf(st, ' ');
		}
	}
	closedir(cur_dir);
	free(dirp);
	if (st->pre)
		free(st->pre);
	if (st->post)
		free(st->post);
	return (i);
}
