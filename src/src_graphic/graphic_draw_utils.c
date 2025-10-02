/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_draw_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 10:44:13 by asando            #+#    #+#             */
/*   Updated: 2025/10/02 15:12:05 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_elevation_range(t_app *app)
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
	return (z_max - z_min);
}

void	init_app(t_app *app)
{
	t_map_data	*map;

	map = malloc(sizeof(t_map_data) * 1);
	if (map == NULL)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	app->mlx = NULL;
	app->img = NULL;
	app->file_map = map;
}

static float	ft_zoom(t_app *app)
{
	float	zoomx;
	float	zoomy;
	float	project_width;
	float	project_height;

	project_width = (app->file_map->row_size + app->file_map->column_size)
		* cos(app->cam.angle);
	project_height = (app->file_map->row_size + app->file_map->column_size)
		* sin(app->cam.angle);
	zoomx = app->mlx->width / project_width;
	zoomy = app->mlx->height / project_height;
	if (zoomx < zoomy)
		return (zoomx * 0.5f);
	return (zoomy * 0.5f);
}

void	init_cam(t_app *app)
{
	float	map_dim;

	app->cam.angle = 45.0f * (M_PI / 180.0f);
	app->cam.pitch = 30.0f * (M_PI / 180.0f);
	app->cam.elevation_range = ft_elevation_range(app);
	map_dim = app->file_map->row_size + app->file_map->column_size;
	app->cam.zoom = ft_zoom(app) * 1.5f;
	if (app->cam.elevation_range == 0)
		app->cam.elevation_project = map_dim / 1.0f;
	else
		app->cam.elevation_project = map_dim / app->cam.elevation_range;
	app->cam.off_x = app->mlx->width / 2;
	app->cam.off_y = app->mlx->height / 2 - (2 * app->cam.zoom);
	app->cam.perspective = false;
	return ;
}
