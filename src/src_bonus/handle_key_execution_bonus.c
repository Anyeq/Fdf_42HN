/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_execution_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:06:47 by asando            #+#    #+#             */
/*   Updated: 2025/10/02 08:42:07 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_key(mlx_key_data_t keydata, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	handle_essential(app, keydata);
	handle_zoom(app, keydata);
	handle_trans(app, keydata);
	handle_perspective(app, keydata);
	return ;
}
