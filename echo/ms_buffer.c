/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_buffer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 10:42:51 by flormich          #+#    #+#             */
/*   Updated: 2021/11/07 23:24:05 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

static char	*calloc_buf(char *alt_buf, int size)
{
	char	*new_buf;

	new_buf = ft_calloc(ft_strlen(alt_buf) + size, sizeof(char));
	if (!new_buf)
		perror("Failed to malloc new_buffer\n");
	return (new_buf);
}

char	*add_char_to_buf(t_struct *st, char c)
{
	int		j;
	char	*new_buf;
	int		len;

	if (st->skip_space == 1 && c == ' ')
	{
		len = ft_strlen(st->buf);
		if (st->buf[len - 1] == ' ' || len == 0)
		{
			st->skip_space = 0;
			return (st->buf);
		}
	}
	new_buf = calloc_buf(st->buf, 2);
	if (!new_buf)
		return (NULL);
	j = 0;
	while (st->buf[j] != '\0')
	{
		new_buf[j] = st->buf[j];
		j++;
	}
	new_buf[j++] = c;
	new_buf[j] = '\0';
	free(st->buf);
	return (new_buf);
}

char	*add_number_to_buf(t_struct *st, int nb)
{
	char	*str;
	int		i;
	int		j;
	char	*new_buf;

	str = ft_itoa(nb);
	new_buf = calloc_buf(st->buf, ft_strlen(str) + 1);
	i = 0;
	while (st->buf[i] != '\0')
	{
		new_buf[i] = st->buf[i];
		i++;
	}
	j = 0;
	while (str[j] != '\0')
	{
		new_buf[i + j] = str[j];
		j++;
	}
	return (new_buf);
}
