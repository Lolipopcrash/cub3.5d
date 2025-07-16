/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <kelevequ@student.42luxembourg>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-16 08:14:05 by kelevequ          #+#    #+#             */
/*   Updated: 2025-07-16 08:14:05 by kelevequ         ###   ########.lu       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_close(t_cub3d *cub3d)
{
	mlx_destroy_image(cub3d->mlx, cub3d->textures.floor.img_ptr);
	mlx_destroy_image(cub3d->mlx, cub3d->textures.north.img_ptr);
	mlx_destroy_image(cub3d->mlx, cub3d->textures.south.img_ptr);
	mlx_destroy_image(cub3d->mlx, cub3d->textures.west.img_ptr);
	mlx_destroy_image(cub3d->mlx, cub3d->textures.east.img_ptr);
	mlx_destroy_image(cub3d->mlx, cub3d->textures.door.img_ptr);
	mlx_destroy_image(cub3d->mlx, cub3d->textures.sky.img_ptr);

	mlx_destroy_image(cub3d->mlx, cub3d->screen.img_ptr);
	mlx_destroy_window(cub3d->mlx, cub3d->mlx_window);
	mlx_destory_display(cub3d->mlx);
	free(cub3d->mlx);
	exit(EXIT_SUCCESS);
}



void	ft_key_press(int keystate, t_cub3d *cub3d)
{
	if (keystate == ESC)
		ft_close(cub3d);
	else if (keycode == LEFT || keycode = RIGHT || keycode == W || keycode == A ||
			keycode == S || keycode == D)
		cub3d->keystate[keycode] = true;
	else
		ft_key(keycode, cub3d);
}