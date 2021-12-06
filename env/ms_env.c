/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnuti <pnuti@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 18:01:33 by pnuti             #+#    #+#             */
/*   Updated: 2021/12/06 16:05:39 by pnuti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_libs.h"

void	ms_env(t_struct *st)
{
	int	i;

	i = 0;
	while (st->env[i])
	{
		ft_putendl_fd(st->env[i], st->fd_tmp);
		i++;
	}
}
