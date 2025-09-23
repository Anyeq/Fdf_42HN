/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:49:53 by asando            #+#    #+#             */
/*   Updated: 2025/09/23 16:52:25 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int handle_key(int keycode, void *param) {
    if (keycode == 65307)
        exit(0);
    return 0;
}

int handle_close(void *param) {
    (void)param;
    exit(0);
    return 0;
}

int main() {
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "MLX Test");

    mlx_key_hook(win, handle_key, NULL);     // Handle Esc key
    mlx_hook(win, 17, 0, handle_close, NULL); // Handle X button

    mlx_loop(mlx);
    return 0;
}
