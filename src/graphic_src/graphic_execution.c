/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 09:37:29 by asando            #+#    #+#             */
/*   Updated: 2025/09/29 21:59:06 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point_project	ft_project(int x, int y, int z, t_camera cam)
{
	t_point_project	p;

	p.fx = (x - y) * cos(cam.angle) * cam.zoom + cam.off_x;
	p.fy = (x + y) * sin(cam.angle) * cam.zoom - (z * cam.elevation);
		+ cam.off_y;
	p.x = (int)fx;
	p.y = (int)fy;
	return (p);
}

void	ft_draw_topoint(int column, int row, t_point_project p0, t_app *app)
{
	uint32_t		color;
	t_point_project	p1;

	color = 0XFFFFFFFF;
	if (column < app->file_map->column_size - 1)
	{
		p1 = ft_project(column + 1, row,
	 				app->file_map->z_data[row][column + 1]->data, app->cam);
		if (app->file_map->z_data[row][column + 1]->has_color)
			color = app->file_map->z_data[row][column + 1]->color_data;
		ft_draw_line(app->img, p0, p1, color);
	}
	if (row < app->file_map->row_size - 1)
	{
	    p1 = ft_project(column, row + 1,
					 app->file_map->z_data[row + 1][column]->data, app->cam);
		if (app->file_map->z_data[row + 1][column]->has_color)
			color = app->file_map->z_data[row + 1][column]->color_data;
	    ft_draw_line(app->img, p0, p1, color);
	}
	return ;
}

void	ft_draw_map(t_app *app);
{
	int				row;
	int				column;
	t_point_project	p0;
	t_point_project	p1;
	uint32_t		color;

	row = 0;
	column = 0;
	color = 0XFFFFFFFF;
	while (row < app->file_map->row_size)
	{
		column = 0;
		while (column < app->file_map->column_size)
		{
			p0 = ft_project(column, row,
				   app->file_map->z_data[column][row]->data, app->cam);
			ft_draw_topoint(column, row, p0, app);
			column++;
        }
		row++;
	}
}

void	init_cam(t_app *app)
{
	app->cam->zoom;
	app->cam->angle;
	app->cam->elevation;
	app->cam->off_x;
	app->cam->off_y;
}

void	init_mouse(t_app *app)
{
	app->mouse->drag;
	app->mouse->last_x;
	app->mouse->last_y;
}

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
	//init_app(&app, mlx, img, file_map); initiate default camera and mouse value;
	//register_hook(&app); all hook function would come here
	mlx_loop(app->mlx);
	mlx_terminate(app->mlx);
}
