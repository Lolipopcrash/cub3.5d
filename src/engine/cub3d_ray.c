/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <kelevequ@student.42luxembourg>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-16 05:34:03 by kelevequ          #+#    #+#             */
/*   Updated: 2025-07-16 05:34:03 by kelevequ         ###   ########.lu       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray	ft_new_ray(int x, t_player player)
{
	double	camera_x; //could be precalculated based on window WIDTH
	t_ray	ray;
	
	camera_x = 2.0 * x / WIDTH - 1;
	ray.dir.x = player.look_dir.x + player.cam_plane.x * camera_x;
	ray.dir.y = player.look_dir.y + player.cam_plane.y * camera_x;
	ray.map_pos.x = (int)player.pos.x;
	ray.map_pos.y = (int)player.pos.y;
	ray.delta.x = fabs(1.0 / ray.dir.x);
	ray.delta.y = fabs(1.0 / ray.dir.y);
	ray.step.x = (ray.dir.x < 0) ? -1 : 1;
	ray.step.y = (ray.dir.y < 0) ? -1 : 1;
	ray.side.x = (ray.dir.x < 0)
		? (player.pos.x - ray.map_pos.x) * ray.delta.x
		: (ray.map_pos.x + 1.0 - player.pos.x) * ray.delta.x;
	ray.side.y = (ray.dir.y < 0)
		? (player.pos.y - ray.map_pos.y) * ray.delta.y
		: (ray.map_pos.y + 1.0 - player.pos.y) * ray.delta.y;
	ray.hit = false;
	return (ray);
}

static void	ft_hit_loop(t_map map, t_ray *ray)
{
	bool	ray_inside_map;

	ray_inside_map = (map.level[ray->map_pos.y][ray->map_pos.x] != '1');
	while (!ray->hit)
	{
		if (ray->side.x < ray->side.y)
		{
			ray->side.x += ray->delta.x;
			ray->map_pos.x += ray->step.x;
			ray->axis = X_AXIS;
		}
		else
		{
			ray->side.y += ray->delta.y;
			ray->map_pos.y += ray->step.y;
			ray->axis = Y_AXIS;
		}
		if (ray->map_pos.x < map.min_x || ray->map_pos.x >= map.max_x ||
			ray->map_pos.y < map.min_y || ray->map_pos.y >= map.max_y)
			return ;
		if (ray_inside_map && map.level[ray->map_pos.y][ray->map_pos.x] == '1')
			ray->hit = true;
		else if (!ray_inside_map && map.level[ray->map_pos.y][ray->map_pos.x] != '1')
			ray_inside_map = true;
	}
}

void	ft_calculate_ray(t_cub3d *cub3d, t_ray *ray, int level)
{
	ft_hit_loop(cub3d->map[level], ray);
	ray->distance = (ray->axis == X_AXIS)
		? (ray->map_pos.x - cub3d->player.pos.x + (1 - ray->step.x) / 2) / ray->dir.x
		: (ray->map_pos.y - cub3d->player.pos.y + (1 - ray->step.y) / 2) / ray->dir.y;
	ray->line_height = (int)(HEIGHT / ray->distance);
	ray->level_offset = ((level - (int)cub3d->player.pos.z) * HEIGHT) / ray->distance;
	ray->draw_bound.x = -ray->line_height / 2 + HEIGHT / 2 - ray->level_offset;
	ray->draw_bound.y = ray->line_height / 2 + HEIGHT / 2 - ray->level_offset;
	ray->wall_x = (ray->axis == X_AXIS)
		? cub3d->player.pos.y + ray->distance * ray->dir.y
		: cub3d->player.pos.x + ray->distance * ray->dir.x;
	ray->wall_x -= floor(ray->wall_x);
	if (ray->axis == X_AXIS)
		ray->tex = (ray->dir.x < 0) ? &cub3d->textures.west : &cub3d->textures.east;
	else
		ray->tex = (ray->dir.y < 0) ? &cub3d->textures.north : &cub3d->textures.south;
	ray->tex_pixel.x = (int)(ray->wall_x * ray->tex->width);
	if ((ray->axis == X_AXIS && ray->dir.x > 0) || (ray->axis == Y_AXIS && ray->dir.y < 0))
		ray->tex_pixel.x = ray->tex->width - ray->tex_pixel.x - 1;
}
