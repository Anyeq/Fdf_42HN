/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:04:23 by asando            #+#    #+#             */
/*   Updated: 2025/10/01 13:42:39 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_putpixel(mlx_image_t *img, uint32_t x, uint32_t y,
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

static void	ft_draw_line(mlx_image_t *img, t_point_project p0,
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
		ft_putpixel(img, (uint32_t)p0.x, (uint32_t)p0.y, color);
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		err = modify_err_value(err, delta_point, &p0);
	}
	return ;
}

static void	ft_draw_topoint(uint32_t column, uint32_t row, t_point_project p0,
							t_app *app)
{
	uint32_t		color;
	t_point_project	p1;

	color = 0XFFFFFFFF;
	if (column < app->file_map->column_size - 1)
	{
		p1 = ft_project((int)(column + 1), (int)row,
				app->file_map->z_data[row][column + 1].data, app->cam);
		if (app->file_map->z_data[row][column + 1].has_color)
			color = app->file_map->z_data[row][column + 1].color_data;
		ft_draw_line(app->img, p0, p1, color);
	}
	if (row < app->file_map->row_size - 1)
	{
		p1 = ft_project((int)column, (int)(row + 1),
				app->file_map->z_data[row + 1][column].data, app->cam);
		if (app->file_map->z_data[row + 1][column].has_color)
			color = app->file_map->z_data[row + 1][column].color_data;
		ft_draw_line(app->img, p0, p1, color);
	}
	return ;
}

void	ft_draw_map(t_app *app)
{
	uint32_t		row;
	uint32_t		column;
	t_point_project	p0;
	uint32_t		color;

	row = 0;
	column = 0;
	color = 0XFFFFFFFF;
	while (row < app->file_map->row_size)
	{
		column = 0;
		while (column < app->file_map->column_size)
		{
			p0 = ft_project((int)column, (int)row,
					app->file_map->z_data[row][column].data, app->cam);
			p0.color = color;
			ft_draw_topoint(column, row, p0, app);
			column++;
		}
		row++;
	}
}
