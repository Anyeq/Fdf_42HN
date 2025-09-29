/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 09:37:29 by asando            #+#    #+#             */
/*   Updated: 2025/09/29 12:55:19 by asando           ###   ########.fr       */
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

static int	modify_err_value(int err, t_delta_point delta, t_point_project *p0)
{
	int result;
	int	err2;

	err2 = 2 * err;
	result = 0;
	if (err2 > -(delta.dy))
	{
		result = err - delta.dy;
		p0->x += delta.stepx;
	}
	if (err2 < delta.dx)
	{
		result = err + delta.dx;
		p0->y += delta.stepy;
	}
	return (result);
}

static void	ft_draw_line(mlx_image_t *img, t_point_project p0,
						 t_point_project p1, uint32 color)
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

static void	test_init_draw_line(t_point_project *p0, t_point_project *p1)
{
	p0->x = 0;
	p0->y = 1;
	p1->x = 100;
	p1->y = 1;
}

void	graphic_exec(t_map_data *file_map)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_point_project p0;
	t_point_project p1;
	uint32_t	color;

	p0 = NULL;
	p1 = NULL;
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
	test_init_draw_line(&p0, &p1);
	ft_draw_line(img, p0, p1, color);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
