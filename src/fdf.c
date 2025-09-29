/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:49:53 by asando            #+#    #+#             */
/*   Updated: 2025/09/29 21:55:30 by asando           ###   ########.fr       */
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
//		{
//			printf("%d", file_map->z_data[i][j].data);
//			if (file_map->z_data[i][j].has_color == true)
//				printf(",%X", file_map->z_data[i][j].color_data);
//			printf(" ");
//			j++;
//		}
//		printf("\n");
//		i++;
//	}
//	return ;
//}

int	main(int argc, char **argv)
{
	int		file_fd;
	t_app	app;

	file_fd = 0;
	app->file_map.z_data = NULL;
	error_check(argc, argv[1], &file_fd);
	if (parse_file(file_fd, app->file_map) == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	graphic_exec(&app);
	clean_map(app->file_map, app->file_map->row_size);
	return (0);
}
