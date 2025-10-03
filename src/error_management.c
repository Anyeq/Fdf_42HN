/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:57:23 by asando            #+#    #+#             */
/*   Updated: 2025/10/03 15:12:45 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error_check(int n_arg, char *file_path, int *fd_file,
				t_map_data *file_map)
{
	if (n_arg != 2)
	{
		ft_putstr_fd("Usage : <path_to_fdf>/fdf <filename>", 2);
		free(file_map);
		exit(EXIT_FAILURE);
	}
	*fd_file = open(file_path, O_RDONLY);
	if (*fd_file == -1)
		perror("Error open file");
	if (*fd_file == -1)
	{
		free(file_map);
		exit(EXIT_FAILURE);
	}
	return ;
}

void	clean_map(t_map_data *map, uint32_t n_deep)
{
	uint32_t	i;

	i = 0;
	while (i < n_deep)
	{
		free(map->z_data[i]);
		i++;
	}
	free(map->z_data);
	free(map);
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
