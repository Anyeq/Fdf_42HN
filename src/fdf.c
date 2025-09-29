/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:49:53 by asando            #+#    #+#             */
/*   Updated: 2025/09/29 09:30:23 by asando           ###   ########.fr       */
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

static void	graphic_exec(t_map_data *file_map)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = NULL;
	img = NULL;
	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx = mlx_init(WIDTH, HEIGHT, "fdf viewer", true);
	if (mlx == NULL)
		exit_error(file_map);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (img == NULL || mlx_image_to_window(mlx, img, 0, 0) < 0)
	{
		mlx_terminate(mlx);
		exit_error(file_map);
	}
	//do loop hook here
	mlx_loop(mlx);
	mlx_terminate(mlx);
}

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
	graphic_exec(&file_map);
	clean_map(&file_map, file_map.row_size);
	return (0);
}
