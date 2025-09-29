/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:56:40 by asando            #+#    #+#             */
/*   Updated: 2025/09/29 10:03:28 by asando           ###   ########.fr       */
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
	return ;
}

void	exit_malloc_failed(t_list **raw_data, void (*del)(void *))
{
	ft_lstclear(raw_data, del);
	perror("Error");
	exit(EXIT_FAILURE);
}
