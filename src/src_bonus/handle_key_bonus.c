/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:16:19 by asando            #+#    #+#             */
/*   Updated: 2025/10/02 12:32:47 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_zoom(t_app *app, mlx_key_data_t keydata)
{
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_I)
		app->cam.zoom *= 2.0f;
	else if (keydata.key == MLX_KEY_O)
		app->cam.zoom *= 0.5f;
	else
		return ;
	if (app->cam.elevation_range == 0)
		app->cam.elevation_project = app->cam.zoom / 1.0f;
	else
		app->cam.elevation_project = app->cam.zoom / app->cam.elevation_range;
	app->cam.off_x = app->mlx->width / 2;
	app->cam.off_y = app->mlx->height / 2 - (2 * app->cam.zoom);
	redraw_img(app);
	return ;
}

void	handle_trans(t_app *app, mlx_key_data_t keydata)
{
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_W)
		app->cam.off_y -= 5.0f;
	else if (keydata.key == MLX_KEY_S)
		app->cam.off_y += 5.0f;
	else if (keydata.key == MLX_KEY_A)
		app->cam.off_x -= 5.0f;
	else if (keydata.key == MLX_KEY_D)
		app->cam.off_x += 5.0f;
	else
		return ;
	redraw_img(app);
	return ;
}

void	handle_perspective(t_app *app, mlx_key_data_t keydata)
{
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_P)
		app->cam.perspective = true;
	else if (keydata.key == MLX_KEY_N)
		app->cam.perspective = false;
	else
		return ;
	redraw_img(app);
	return ;
}
