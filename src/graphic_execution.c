/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 09:37:29 by asando            #+#    #+#             */
/*   Updated: 2025/09/29 19:24:21 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_putpixel(mlx_image_t *img, uint32_t x, uint32_t y,
						uint32_t color)
{
	uint32_t	pixel_index;

	pixel_index = 0;
	if (x >= img->width || y >= img->height)
		return ;
	pixel_index = (y * img->width + x) * 4;
	img->pixels[pixel_index + 0] = (color >> 24) & 0xFF;
	img->pixels[pixel_index + 1] = (color >> 16) & 0XFF;
	img->pixels[pixel_index + 2] = (color >> 8) & 0XFF;
	img->pixels[pixel_index + 3] = (color >> 0) & 0XFF;
	return ;
}

static int	modify_err_value(int err, t_point_delta delta, t_point_project *p0)
{
	int	err2;

	err2 = 2 * err;
	if (err2 > -(delta.dy))
	{
		err -= delta.dy;
		p0->x += delta.stepx;
	}
	if (err2 < delta.dx)
	{
		err += delta.dx;
		p0->y += delta.stepy;
	}
	return (err);
}

void	ft_draw_line(mlx_image_t *img, t_point_project p0,
						t_point_project p1, uint32_t color)
{
	t_point_delta	delta_point;
	int				err;

	delta_point.dx = abs(p1.x - p0.x);
	delta_point.dy = abs(p1.y - p0.y);
	delta_point.stepx = 1;
	delta_point.stepy = 1;
	err = delta_point.dx - delta_point.dy;
	if (p1.x < p0.x)
		delta_point.stepx = -1;
	if (p1.y < p0.y)
		delta_point.stepy = -1;
	while (1)
	{
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		ft_putpixel(img, (uint32_t)p0.x, (uint32_t)p0.y, color);
		err = modify_err_value(err, delta_point, &p0);
	}
	return ;
}

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
				p1 = ft_project(column + 1, row, file_map->z_data[column][row + 1]->data
					, cam);
				if (file_map->z_data[column][row + 1]->has_color)
					color = file_map->z_data[column][row + 1]->color_data;
            	ft_draw_line(img, p0, p1, file_map->z_data[column][row + 1]->color_data);
			}
			if (row < file_map->row_size - 1)
			{
        	    p1 = t_project(column, row + 1, file_map->z_data[column + 1][row]->data
							, cam);
				if (file_map->z_data[column + 1][row]->has_color)
					color = file_map->z_data[column + 1][row]->color_data;
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
	t_point_project	p0;
	t_point_project	p1;
	uint32_t		color;

	mlx = NULL;
	img = NULL;
	color = 0XFFFFFFFF;
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
	//do loop hook	
	//draw_map
	//loop hook
	test_init_draw_line(&p0, &p1);
	ft_draw_line(img, p0, p1, color);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
