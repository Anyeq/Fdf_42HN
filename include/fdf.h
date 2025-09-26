/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:50:35 by asando            #+#    #+#             */
/*   Updated: 2025/09/26 08:48:54 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
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
	int				row_size;
	int				column_size;
	t_point_data	**z_data;
}	t_map_data;

//parsing function and utils
void	deep_free(void *content);
int		parse_file(int file_fd, t_map_data *file_map);

//fdf_utils
void	clean_map(t_map_data *map, int n_deep);
void	exit_malloc_failed(t_list **raw_data, void (*del)(void *));

//error management function
void	error_check(int n_arg, char *file_path, int *fd_file);

#endif
