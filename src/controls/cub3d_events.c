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
	mlx_destroy_display(cub3d->mlx);
	free(cub3d->mlx);
	free(cub3d->map);
	exit(EXIT_SUCCESS);
}

int	ft_key_release(int keycode, t_cub3d *cub3d)
{
	if (keycode >= 0 && keycode < KEY_MAX)
		cub3d->keystate[keycode / BIT_PER_BYTE] &= ~(1 << keycode % BIT_PER_BYTE);
	return (0);
}

static void	ft_key(int keycode, t_cub3d *cub3d)
{
	if (keycode == Q)
		cub3d->player.pos.z += 0.1;
	if (keycode == E)
		cub3d->player.pos.z -= 0.1;
}

int	ft_key_press(int keycode, t_cub3d *cub3d)
{
	if (keycode == ESC)
		ft_close(cub3d);
	else if (keycode == LEFT || keycode == RIGHT || keycode == W || keycode == A ||
			keycode == S || keycode == D)
		cub3d->keystate[keycode / BIT_PER_BYTE] |= (1 << keycode % BIT_PER_BYTE);
	else
		ft_key(keycode, cub3d);
	return (0);
}