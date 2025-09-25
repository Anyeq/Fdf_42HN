/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:56:40 by asando            #+#    #+#             */
/*   Updated: 2025/09/25 17:31:41 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clean_map(t_map_data *map, int n_deep)
{
	int	i;
	int	j;

	i = 0;
	while (i < n_deep)
	{
		j = 0;
		while (j <= map->column_size)
			free(map->z_map[i][j++]);
		i++;
	}
	while (i <= map->row_size)
		free(map->z_map[i]);
	free(map->z_map);
	return ;
}

void	exit_malloc_failed(t_list **raw_data, void (*del)(void *))
{
	ft_lstclear(raw_data, del);
	perror("Error");
	exit(EXIT_FAILURE);
}
