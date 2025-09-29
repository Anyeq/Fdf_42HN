/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_execution_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:01:13 by asando            #+#    #+#             */
/*   Updated: 2025/09/29 21:07:41 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point_project	ft_project(int x, int y, int z, t_camera cam)
{
	t_point_project	p;

	p.fx = (x - y) * cos(cam.angle) * cam.zoom + cam.off_x;
	p.fy = (x + y) * sin(cam.angle) * cam.zoom - (z * cam.elevation)
		+ cam.off_y;
	p.x = (int)fx;
	p.y = (int)fy;
	return (p);
}
