/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_projection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:45:07 by asando            #+#    #+#             */
/*   Updated: 2025/10/03 14:27:44 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_point_project	rotate_point(int x, int y, t_app *app)
{
	t_point_project	p;
	float			map_center_x;
	float			map_center_y;

	map_center_x = (float)app->file_map->column_size / 2.0f;
	map_center_y = (float)app->file_map->row_size / 2.0f;
	p.fx = (x - map_center_x) * cosf(app->cam.angle)
		- (y - map_center_y) * sinf(app->cam.angle);
	p.fy = (x - map_center_x) * sinf(app->cam.angle)
		+ (y - map_center_y) * cosf(app->cam.angle);
	p.x = 0;
	p.y = 0;
	return (p);
}

static void	ft_set_depth(int y, t_app *app)
{
	int		map_dim;
	float	depth;

	map_dim = (app->file_map->row_size + app->file_map->column_size);
	app->cam.cam_z = map_dim * 0.5f + app->cam.elevation_range * 0.5f;
	app->cam.fov = 60.0f / logf(map_dim + 10.f);
	depth = app->cam.cam_z - y;
	if (depth < 1.0f)
		app->cam.depth = 1.0f;
	else
		app->cam.depth = depth;
}

static float	ft_tilt_y(int z, t_point_project rot_point, t_app *app)
{
	float	fy_tiled;
	float	z_centered;

	z_centered = z - app->cam.elevation_range / 2;
	fy_tiled = rot_point.fy * cosf(app->cam.pitch + 0.5f)
		- z_centered * sinf(app->cam.pitch + 0.5f)
		* app->cam.elevation_project / 2;
	return (fy_tiled);
}

t_point_project	ft_project(int x, int y, int z, t_app *app)
{
	t_point_project	p;
	t_point_project	rot_point;

	rot_point = rotate_point(x, y, app);
	if (app->cam.perspective)
	{
		ft_set_depth(y, app);
		p.fx = (rot_point.fx * app->cam.fov / app->cam.depth) * app->cam.zoom
			+ app->cam.off_x;
		p.fy = ft_tilt_y(z, rot_point, app) * (app->cam.fov / app->cam.depth)
			* app->cam.zoom + app->cam.off_y;
	}
	else
	{
		p.fx = rot_point.fx * app->cam.zoom + app->cam.off_x;
		p.fy = ft_tilt_y(z, rot_point, app) * app->cam.zoom + app->cam.off_y;
	}
	p.x = (int)p.fx;
	p.y = (int)p.fy;
	return (p);
}
