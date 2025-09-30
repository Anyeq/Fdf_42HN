/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 09:37:29 by asando            #+#    #+#             */
/*   Updated: 2025/09/30 10:30:04 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_point_project	ft_project(int x, int y, int z, t_camera cam)
{
	t_point_project	p;

	p.fx = (x - y) * cos(cam.angle) * cam.zoom + cam.off_x;
	p.fy = (x + y) * sin(cam.angle) * cam.zoom - (z * cam.elevation)
		+ cam.off_y;
	p.x = (int)(p.fx);
	p.y = (int)(p.fy);
	return (p);
}

static void	ft_draw_topoint(uint32_t column, uint32_t row, t_point_project p0, t_app *app)
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

static void	ft_draw_map(t_app *app)
{
	uint32_t		row;
	uint32_t		column;
	t_point_project	p0;

	row = 0;
	column = 0;
	while (row < app->file_map->row_size)
	{
		column = 0;
		while (column < app->file_map->column_size)
		{
			p0 = ft_project((int)column, (int)row,
				   app->file_map->z_data[row][column].data, app->cam);
			ft_draw_topoint(column, row, p0, app);
			column++;
        }
		row++;
	}
}

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
	return (app->cam.zoom / (z_max - z_min));
}

static void	init_cam(t_app *app)
{
	float	project_width;
	float	project_height;
	float	angle_deg;
	float	zoomx;
	float	zoomy;

	angle_deg = 30.0f;
	app->cam.angle = angle_deg * (M_PI / 180.0f);
	project_width = (app->file_map->row_size + app->file_map->column_size) * cos(app->cam.angle);
	project_height = (app->file_map->row_size + app->file_map->column_size) * sin(app->cam.angle);
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

void	graphic_exec(t_app *app)
{
	app->mlx = NULL;
	app->img = NULL;
	mlx_set_setting(MLX_MAXIMIZED, true);
	app->mlx = mlx_init(WIDTH, HEIGHT, "fdf viewer", true);
	if (app->mlx == NULL)
		exit_error(app->file_map);
	app->img = mlx_new_image(app->mlx, WIDTH, HEIGHT);
	if (app->img == NULL || mlx_image_to_window(app->mlx, app->img, 0, 0) < 0)
	{
		mlx_terminate(app->mlx);
		exit_error(app->file_map);
	}
	init_cam(app);
	ft_draw_map(app);
	//init_mouse(app);
	//register_hook(&app); all hook function would come here
	mlx_loop(app->mlx);
	mlx_terminate(app->mlx);
}
