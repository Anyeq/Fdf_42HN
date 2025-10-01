/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:01:13 by asando            #+#    #+#             */
/*   Updated: 2025/10/01 15:06:00 by asando           ###   ########.fr       */
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

void	handle_essential(t_app *app, mlx_key_data_t keydata)
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

void	handle_resize(int32_t width, int32_t height, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	mlx_delete_image(app->mlx, app->img);
	app->img = NULL;
	app->img = mlx_new_image(app->mlx, width, height);
	if (app->img == NULL || mlx_image_to_window(app->mlx, app->img, 0, 0) < 0)
	{
		mlx_terminate(app->mlx);
		exit_error(app->file_map);
	}
	app->cam.off_x = width / 2;
	app->cam.off_y = height / 2;
	ft_draw_map(app);
	return ;
}
