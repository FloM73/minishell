/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnuti <pnuti@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 17:50:14 by pnuti             #+#    #+#             */
/*   Updated: 2021/11/29 21:54:00 by pnuti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

static int	update_vars(t_struct *st)
{
	char		*old_wd;
	char		*current_wd;
	char		cwd[PATH_MAX];

	old_wd = ft_strjoin("OLDPWD=", ms_get_env(st->env, "PWD"));
	if (!old_wd)
		return (1);
	if (ms_export(old_wd, st) != 0)
		return (1);
	free(old_wd);
	if (!getcwd(cwd, PATH_MAX))
		return (1);
	current_wd = ft_strjoin("PWD=", cwd);
	if (!current_wd)
		return (1);
	if (ms_export(current_wd, st) != 0)
		return (1);
	free(current_wd);
	return (0);
}

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
	if (chdir(arr->cmd[1]) < 0)
	{
		perror("cd");
		return (1);
	}
	update_vars(st);
	return (0);
}
