/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_sig_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:48:42 by pnuti             #+#    #+#             */
/*   Updated: 2021/11/23 19:30:30 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libs.h"

void	sigint_handle(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sigquit_handle(int signum)
{
	if (signum == SIGQUIT)
		signum++;
}

int	ms_sig_hook(void)
{
	struct sigaction	sa1;
	struct sigaction	sa2;

	sa1.sa_handler = &sigint_handle;
	sa2.sa_handler = &sigquit_handle;
	sa1.sa_flags = SA_RESTART;
	sa2.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa1, NULL) == -1)
		return (-1);
	if (sigaction(SIGQUIT, &sa2, NULL) == -1)
		return (-1);
	return (0);
}
