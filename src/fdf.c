/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:49:53 by asando            #+#    #+#             */
/*   Updated: 2025/09/25 17:44:36 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	int			file_fd;
	t_map_data	file_map;

	file_fd = 0;
	file_map.z_data = NULL;
	error_check(argc, argv[1], &file_fd);
	if (parse_file(file_fd, &file_map) == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}
