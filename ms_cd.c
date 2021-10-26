/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 17:50:14 by pnuti             #+#    #+#             */
/*   Updated: 2021/10/14 18:28:51 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libs.h"

void	cd(char *path)
{
	int	err;

	err = chdir(path);
	if (err)
		printf("%s\n", strerror(err));
}

int	main(int argc, char ** argv)
{
	if (argc <= 1)
		return (-1);
	cd(argv[1]);
	return (0);
}
