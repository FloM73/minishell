/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnuti <pnuti@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:39:27 by pnuti             #+#    #+#             */
/*   Updated: 2021/11/23 13:48:48 by pnuti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

char	*ms_get_env(char ***env, char *varname)
{
	int	i;

	i = 0;
	while (env[0][i])
	{
		if (!ft_strncmp(env[0][i], varname, ft_len_until_char(env[0][i], '=')))
			return (ft_strchr(env[0][i], '=') + 1);
	}
	i = 0;
	while (env[1][i])
	{
		if (!ft_strncmp(env[1][i], varname, ft_len_until_char(env[1][i], '=')))
			return (ft_strchr(env[1][i], '=') + 1);
	}
	return (NULL);
}
