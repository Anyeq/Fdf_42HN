/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:50:35 by asando            #+#    #+#             */
/*   Updated: 2025/09/29 12:58:11 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdint.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "libft.h"
# include "get_next_line_bonus.h"
# include "MLX42/MLX42.h"

typedef struct	s_point_data
{
	int				data;
	bool			has_color;
	uint32_t		color_data;
}	t_point_data;

typedef struct	s_map_data
{
	uint32_t		row_size;
	uint32_t		column_size;
	t_point_data	**z_data;
}	t_map_data;

typedef struct	s_point_project
{
	int	x;
	int	y;
}	t_point_project;

typedef struct	s_point_delta
{
	int	dx;
	int	dy;
	int	stepx;
	int	stepy;
}	t_point_delta;

//parsing function and utils
void	deep_free(void *content);
void	grab_color_data(char *str, t_point_data *data);
int		parse_file(int file_fd, t_map_data *file_map);

//fdf_utils
void	clean_map(t_map_data *map, uint32_t n_deep);
void	exit_malloc_failed(t_list **raw_data, void (*del)(void *));

//error management function
void	error_check(int n_arg, char *file_path, int *fd_file);
void	exit_error(t_map_data *file_map);

//graphic management
void	graphic_exec(t_map_data *file_map);

#endif
