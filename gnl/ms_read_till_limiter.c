/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_read_till_limiter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 11:48:35 by flormich          #+#    #+#             */
/*   Updated: 2021/11/29 22:44:21 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

int	read_till_limiter(t_struct *st, int tr)
{
	int		i;

	i = 1;
	st->buf_tmp = (char *)gnl_calloc(1, 1);
	while (i > 0)
	{
		i = get_next_line(0, &st->buf_tmp, st->arr[tr].limiter, 0);
	}
	initialise_buf(st);
	bufferize_input(st, st->buf_tmp, 0);
	i = 0;
	while (st->buf[i] != '\0')
	{
		(write(st->arr[tr].fd_in, &(st->buf[i]), 1));
		st->buf[i++] = '\0';
	}
	close(st->arr[tr].fd_in);
	st->arr[tr].fd_in = open(st->arr[st->tr].name_in, O_RDWR, 0777);
	free(st->buf);
	free(st->buf_tmp);
	return (0);
}
