/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:56:40 by asando            #+#    #+#             */
/*   Updated: 2025/09/30 14:16:50 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	exit_malloc_failed(t_list **raw_data, void (*del)(void *),
						t_map_data *file_map)
{
	ft_lstclear(raw_data, del);
	free(file_map);
	perror("Error");
	exit(EXIT_FAILURE);
}
