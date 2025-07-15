/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <kelevequ@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-15 05:52:32 by kelevequ          #+#    #+#             */
/*   Updated: 2025-07-15 05:52:32 by kelevequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray	ft_new_ray(int x, t_player player)
{
	double	camera_x; //could be precalculated based on window WIDTH
	t_ray	result;
	
	camera_x = 2.0 * x / WIDTH - 1;
	result.ray_dir.x = player.look_dir.x + player.cam_plane.x * camera_x;
	result.ray_dir.y = player.look_dir.y + player.cam_plane.y * camera_x;
	result.map_pos.x = (int)player.pos.x;
	result.map_pos.y = (int)player.pos.y;
	result.delta.x = fabs(1.0 / result.ray_dir.x);
	result.delta.y = fabs(1.0 / result.ray_dir.y);
	result.step.x = (result.ray_dir.x < 0) ? -1 : 1;
	result.step.y = (result.ray_dir.y < 0) ? -1 : 1;
	result.side.x = (result.ray_dir.x < 0)
		? (player.pos.x - result.map_pos.x) * result.delta.x
		: (result.map_pos.x + 1.0 - player.pos.x) * result.delta.x;
	result.side.y = (result.ray_dir.y < 0)
		? (player.pos.y - result.map_pos.y) * result.delta.y
		: (result.map_pos.y + 1.0 - player.pos.y) * result.delta.y;
	result.hit = false;
	return (result);
}

void	ft_calculate_ray(t_cub3d *cub3d, t_ray *ray)
{
	ft_hit_loop(ray);
}