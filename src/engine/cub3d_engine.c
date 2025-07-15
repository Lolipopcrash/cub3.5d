/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_engine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <kelevequ@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-15 04:47:41 by kelevequ          #+#    #+#             */
/*   Updated: 2025-07-15 04:47:41 by kelevequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_render_image(t_cub3d *cub3d)
{
	t_3int_point	screen_pixel;
	t_ray			ray;
	int				color;

	screen_pixel.x = 0;
	while (screen_pixel.x < WIDTH)
	{
		ray = ft_new_ray(screen_pixel.x, cub3d->player);
		ft_calculate_ray(cub3d, &ray);
		screen_pixel.y = 0;
		while (screen_pixel.y < HEIGHT)
		{
			color = ft_get_color(ray);
			ft_put_pixel(&cub3d->img, screen_pixel.x, screen_pixel.y, color)
			screen_pixel.y++;
		}
		screen_pixel.x++;
	}
}

static bool	ft_valid_position(t_cub3d *cub3d, t_map map)
{
	t_2int_point	player;

	player.x = (int)cub3d->player.pos.x;
	player.y = (int)cub3d->player.pos.y;
	if (player.x < 0 || player.x >= map.width ||
		player.y < 0 || player.y >= map.height ||
		map.level[player_y][player_x] != PLAYABLE_AREA)
		return (0);
	return (1);
}

int	ft_engine(t_cub3d *cub3d)
{
	//ft_update_frame_info(cub3d);
	if (ft_valid_position(cub3d))
		ft_render_image(cub3d);
	else
		ft_render_outofbounds(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->mlx_window, cub3d->img.img_ptr, 0, 0);
}