/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:49:53 by asando            #+#    #+#             */
/*   Updated: 2025/09/26 08:32:40 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//void	print_map(t_map_data *file_map)
//{
//	int	i;
//	int	j;
//
//	i = 0;
//	j = 0;
//	printf("%d\n", file_map->row_size);
//	printf("%d\n", file_map->column_size);
//	while (i < file_map->row_size)
//	{
//		j = 0;
//		while (j < file_map->column_size)
//			printf("%d", file_map->z_data[i][j++]);
//		printf("\n");
//		i++;
//	}
//	return ;
//}

int	main(int argc, char **argv)
{
	int			file_fd;
	t_map_data	file_map;

	file_fd = 0;
	file_map.z_data = NULL;

	error_check(argc, argv[1], &file_fd);
	if (parse_file(file_fd, &file_map) == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	//print_map(&file_map);
	clean_map(&file_map, file_map.row_size);
	return (0);
}
