/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:57:23 by asando            #+#    #+#             */
/*   Updated: 2025/10/01 12:56:05 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	valid_nparameter(int n_arg)
{
	if (n_arg != 2)
	{
		ft_putstr_fd("Need one file as a parameter", 2);
		return (-1);
	}
	return (0);
}

static int	valid_open_file(char *file_path)
{
	int	fd_file;

	fd_file = open(file_path, O_RDONLY);
	if (fd_file == -1)
		perror("Error open file");
	return (fd_file);
}

void	error_check(int n_arg, char *file_path, int *fd_file,
				 t_map_data *file_map)
{
	*fd_file = 0;
	if (valid_nparameter(n_arg) == 0)
	{
		*fd_file = valid_open_file(file_path);
		if (*fd_file == -1)
		{
			free(file_map);
			exit(EXIT_FAILURE);
			return ;
		}
		return ;
	}
	free(file_map);
	exit(EXIT_FAILURE);
	return ;
}

void	exit_error(t_map_data *file_map)
{
	clean_map(file_map, file_map->row_size);
	free(file_map);
	perror("Error");
	exit(EXIT_FAILURE);
	return ;
}

void	exit_malloc_failed(t_list **raw_data, void (*del)(void *),
						t_map_data *file_map)
{
	ft_lstclear(raw_data, del);
	free(file_map);
	perror("Error");
	exit(EXIT_FAILURE);
}
