/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 17:50:14 by pnuti             #+#    #+#             */
/*   Updated: 2021/11/25 11:18:33 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

int	cd(void *stt, void *cmd)
{
	t_cmd		*arr;
	t_struct	*st;

	arr = (t_cmd *)cmd;
	st = (t_struct *)stt;
	if (arr->cmd[2] != NULL)
	{
		st->nb_cmd = 0;
		return (1);
	}
	return (chdir(arr->cmd[1]));
}
