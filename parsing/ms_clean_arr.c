/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_clean_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 09:45:01 by flormich          #+#    #+#             */
/*   Updated: 2021/10/29 15:22:18 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell_libs.h"

void	clean_arr(t_struct *st)
{
	int	tr;
	int	arg;
	int	offset;

	tr = 0;
	while (tr < st->nb_cmd)
	{
		arg = 0;
		while (st->arr[tr].cmd[arg][0] != '\0' && arg <= st->arr[tr].nb_arg)
			arg++;
		st->arr[tr].cmd[arg] = (char *)0;
		arg++;
		offset = 0;
		while (arg <= st->arr[tr].nb_arg)
		{
			free(st->arr[tr].cmd[arg]);
			st->arr[tr].cmd[arg] = 0;
			offset++;
			arg++;
		}
		st->arr[tr].nb_arg -= offset;
		tr++;
	}
}
