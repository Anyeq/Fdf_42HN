/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_execution_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 10:44:13 by asando            #+#    #+#             */
/*   Updated: 2025/09/30 10:49:37 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static float	ft_cam_elevation(t_app *app)
{
	int			z_min;
	int			z_max;
	uint32_t	i;
	uint32_t	j;

	i = 0;
	j = 0;
	z_min = 0;
	z_max = 0;
	while (i < app->file_map->row_size)
	{
		j = 0;
		while (j < app->file_map->column_size)
		{
			if (app->file_map->z_data[i][j].data < z_min)
				z_min = app->file_map->z_data[i][j].data;
			if (app->file_map->z_data[i][j].data > z_max)
				z_max = app->file_map->z_data[i][j].data;
			j++;
		}
		i++;
	}
	if (z_max - z_min == 0)
		return (1.0f);
	return ((app->cam.zoom * 10) / (z_max - z_min));
}

void	init_cam(t_app *app)
{
	float	project_width;
	float	project_height;
	float	angle_deg;
	float	zoomx;
	float	zoomy;

	angle_deg = 30.0f;
	app->cam.angle = angle_deg * (M_PI / 180.0f);
	project_width = (app->file_map->row_size + app->file_map->column_size)
		* cos(app->cam.angle);
	project_height = (app->file_map->row_size + app->file_map->column_size)
		* sin(app->cam.angle);
	zoomx = app->mlx->width / project_width;
	zoomy = app->mlx->height / project_height;
	if (zoomx < zoomy)
		app->cam.zoom = zoomx * 0.5;
	else
		app->cam.zoom = zoomy * 0.5;
	app->cam.elevation = ft_cam_elevation(app);
	app->cam.off_x = app->mlx->width / 2;
	app->cam.off_y = app->mlx->height / 2;
	return ;
}

//void	init_mouse(t_app *app)
//{
//	app->mouse->drag;
//	app->mouse->last_x;
//	app->mouse->last_y;
//}
