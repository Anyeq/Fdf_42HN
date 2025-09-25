/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:50:35 by asando            #+#    #+#             */
/*   Updated: 2025/09/25 14:16:33 by asando           ###   ########.fr       */
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

typedef struct	s_map_data
{
	int	**z_data;
}	t_map_data;

typedef	struct	s_map_data
{
	char **raw_data;

}	t_raw_data;
#endif
