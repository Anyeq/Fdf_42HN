/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:49:53 by asando            #+#    #+#             */
/*   Updated: 2025/09/30 13:29:24 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_app(t_app *app)
{
	t_map_data	*map;

	map = malloc(sizeof(t_map_data) * 1);
	if (map == NULL)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	app->mlx = NULL;
	app->img = NULL;
	app->file_map = map;
}

int	main(int argc, char **argv)
{
	int		file_fd;
	t_app	app;
	int		parse_status;

	file_fd = 0;
	parse_status = 0;
	init_app(&app);
	error_check(argc, argv[1], &file_fd, app.file_map);
	parse_status = parse_file(file_fd, app.file_map);
	if (parse_status < 0)
	{
		free(app.file_map);
		if (parse_status == -1)
			perror("Error");
		exit(EXIT_FAILURE);
	}
	graphic_exec(&app);
	clean_map(app.file_map, app.file_map->row_size);
	return (0);
}
