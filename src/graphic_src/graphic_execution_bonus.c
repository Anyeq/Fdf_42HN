/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_execution_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:01:13 by asando            #+#    #+#             */
/*   Updated: 2025/09/30 20:15:46 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	redraw_img(t_app *app)
{
		mlx_delete_image(app->mlx, app->img);
		app->img = NULL;
		app->img = mlx_new_image(app->mlx, WIDTH, HEIGHT);
		if (app->img == NULL || mlx_image_to_window(app->mlx, app->img, 0, 0) < 0)
		{
			mlx_terminate(app->mlx);
			exit_error(app->file_map);
		}
		ft_draw_map(app);
}

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
	redraw_img(app);
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
