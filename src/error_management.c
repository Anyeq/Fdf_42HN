/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:57:23 by asando            #+#    #+#             */
/*   Updated: 2025/09/29 09:29:44 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	valid_nparameter(int n_arg)
{
	if (n_arg != 2)
	{
		ft_putstr_fd("Need one file as a parameter", 2);
		exit(EXIT_FAILURE);
	}
}

static int	valid_open_file(char *file_path)
{
	int	fd_file;

	fd_file = open(file_path, O_RDONLY);
	if (fd_file == -1)
	{
		perror("Error open file");
		exit(EXIT_FAILURE);
	}
	return (fd_file);
}

void	error_check(int n_arg, char *file_path, int *fd_file)
{
	valid_nparameter(n_arg);
	*fd_file = valid_open_file(file_path);
}

void	exit_error(t_map_data *file_map)
{
	clean_map(file_map, file_map->row_size);
	perror("Error");
	exit(EXIT_FAILURE);
	return ;
}
