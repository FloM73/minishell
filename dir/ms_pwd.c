/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnuti <pnuti@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 10:24:11 by pnuti             #+#    #+#             */
/*   Updated: 2021/11/18 09:48:43 by pnuti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

int	pwd(void *stt, void *cmd)
{
	t_cmd		*arr;
	t_struct	*st;
	char		buf[PATH_MAX];

	arr = (t_cmd *)cmd;
	st = (t_struct *)stt;
	arr->cmd[1] = NULL;
	st->arr[0].cmd[1] = NULL;
	if (!getcwd(buf, PATH_MAX))
	{
		perror("Something went wrong");
		return (-1);
	}
	printf("%s\n", buf);
	return (0);
}
