/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:57:23 by asando            #+#    #+#             */
/*   Updated: 2025/09/24 20:23:40 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

static int	valid_nparameter(int n_arg)
{
	if (n_arg != 2)
		return (-1);
	return (0);
}

static int	valid_open_file(char *file_path)
{
	int	fd_file;

	fd_file = open(file_path, O_RDONLY);
	if (fd_file == -1)
		//use exit with perror or strerror
		return (-1);
	return (fd_file);
}

void	error_check(int n_arg, char *file_path, int *fd_file)
{
	valid_nparameter(n_arg);
	*fd_file = valid_open_file(file_path);
}
