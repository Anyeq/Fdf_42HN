/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_bonus_key.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:16:19 by asando            #+#    #+#             */
/*   Updated: 2025/10/01 13:17:01 by asando           ###   ########.fr       */
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
