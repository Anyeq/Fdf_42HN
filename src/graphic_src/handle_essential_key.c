/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_essential_key.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:01:13 by asando            #+#    #+#             */
/*   Updated: 2025/10/01 13:38:38 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	redraw_img(t_app *app)
{
	mlx_delete_image(app->mlx, app->img);
	app->img = NULL;
	app->img = mlx_new_image(app->mlx, app->mlx->width, app->mlx->height);
	if (app->img == NULL || mlx_image_to_window(app->mlx, app->img, 0, 0) < 0)
	{
		mlx_terminate(app->mlx);
		exit_error(app->file_map);
	}
	ft_draw_map(app);
	return ;
}

static void	handle_essential(t_app *app, mlx_key_data_t keydata)
{
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_KP_ADD || keydata.key == MLX_KEY_EQUAL)
		app->cam.elevation *= 5.0f;
	else if (keydata.key == MLX_KEY_KP_SUBTRACT || keydata.key == MLX_KEY_MINUS)
		app->cam.elevation *= 0.2f;
	else if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(app->mlx);
		return ;
	}
	else
		return ;
	redraw_img(app);
	return ;
}

void	handle_resize(uint32_t width, uint32_t height, t_app *app)
{
	mlx_delete_image(app->mlx, app->img);
	app->img = NULL;
	app->img = mlx_new_image(app->mlx, width, height);
	if (app->img == NULL || mlx_image_to_window(app->mlx, app->img, 0, 0) < 0)
	{
		mlx_terminate(app->mlx);
		exit_error(app->file_map);
	}
	app->camera.off_x = widht / 2;
	app->camera.off_y = height / 2;
	ft_draw_map(app);
	return ;
}

void	handle_key(mlx_key_data_t keydata, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	handle_essential(app, keydata);
	return ;
}
