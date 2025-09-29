/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 09:37:29 by asando            #+#    #+#             */
/*   Updated: 2025/09/29 21:05:57 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point_project	ft_project(int x, int y, int z, t_camera cam)
{
	t_point_project	p;

	p.fx = (x - y) * cos(cam.angle) * cam.zoom + cam.off_x;
	p.fy = (x + y) * sin(cam.angle) * cam.zoom - (z * cam.elevation)
		+ cam.off_y;
	p.x = (int)fx;
	p.y = (int)fy;
	return (p);
}

void	ft_draw_map(mlx_image_t *img, t_map_data *file_map)
{
	int				row;
	int				column;
	t_point_project	p0;
	t_point_project	p1;
	uint32_t		color;

	row = 0;
	column = 0;
	color = 0XFFFFFFFF;
	while (row < file_map->row_size)
	{
		column = 0;
		while (column < file_map->column_size)
		{
			p0 = ft_project(column, row, file_map->z_data[column][row]->data, cam);
			if (column < file_map->column_size - 1)
			{
				p1 = ft_project(column + 1, row, file_map->z_data[row][column + 1]->data
					, cam);
				if (file_map->z_data[row][column + 1]->has_color)
					color = file_map->z_data[row][column + 1]->color_data;
            	ft_draw_line(img, p0, p1, color);
			}
			if (row < file_map->row_size - 1)
			{
        	    p1 = ft_project(column, row + 1, file_map->z_data[row + 1][column]->data
							, cam);
				if (file_map->z_data[row + 1][column]->has_color)
					color = file_map->z_data[row + 1][column]->color_data;
        	    ft_draw_line(img, p0, p1, color);
			}
			column++;
        }
		row++;
	}
	return ;
}

void	graphic_exec(t_map_data *file_map)
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_app			app;

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
	//init_app(&app, mlx, img, file_map); initiate default camera and mouse value;
	//register_hook(&app); all hook function would come here
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
