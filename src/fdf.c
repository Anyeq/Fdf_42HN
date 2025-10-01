/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:49:53 by asando            #+#    #+#             */
/*   Updated: 2025/10/01 13:47:35 by asando           ###   ########.fr       */
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

void	clean_map(t_map_data *map, uint32_t n_deep)
{
	uint32_t	i;

	i = 0;
	while (i < n_deep)
	{
		free(map->z_data[i]);
		i++;
	}
	free(map->z_data);
	free(map);
	return ;
}

void	graphic_exec(t_app *app)
{
	mlx_set_setting(MLX_MAXIMIZED, true);
	app->mlx = mlx_init(WIDTH, HEIGHT, "fdf viewer", true);
	if (app->mlx == NULL)
		exit_error(app->file_map);
	app->img = mlx_new_image(app->mlx, WIDTH, HEIGHT);
	if (app->img == NULL || mlx_image_to_window(app->mlx, app->img, 0, 0) < 0)
	{
		mlx_terminate(app->mlx);
		exit_error(app->file_map);
	}
	init_cam(app);
	ft_draw_map(app);
	mlx_resize_hook(app->mlx, handle_resize, app);
	mlx_key_hook(app->mlx, handle_key, app);
	//init_mouse(app);
	//register_hook(&app); all hook function would come here
	mlx_loop(app->mlx);
	mlx_terminate(app->mlx);
}

int	main(int argc, char **argv)
{
	t_app	app;
	int		file_fd;
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
