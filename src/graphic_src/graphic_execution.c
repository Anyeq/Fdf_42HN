/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 09:37:29 by asando            #+#    #+#             */
/*   Updated: 2025/09/30 20:13:27 by asando           ###   ########.fr       */
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

void	handle_key(mlx_key_data_t keydata, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	handle_zoom(app, keydata);
	handle_essential(app, keydata);
	handle_trans(app, keydata);
	return ;
}

void	graphic_exec(t_app *app)
{
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
	mlx_key_hook(app->mlx, handle_key, app);
	//init_mouse(app);
	//register_hook(&app); all hook function would come here
	mlx_loop(app->mlx);
	mlx_terminate(app->mlx);
}
