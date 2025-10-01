/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_execution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:05:02 by asando            #+#    #+#             */
/*   Updated: 2025/10/01 15:05:31 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_key(mlx_key_data_t keydata, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	handle_essential(app, keydata);
	return ;
}
