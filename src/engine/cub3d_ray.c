/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_vray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <kelevequ@student.42luxembourg>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-16 05:34:03 by kelevequ          #+#    #+#             */
/*   Updated: 2025-07-16 05:34:03 by kelevequ         ###   ########.lu       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vray	ft_new_vray(int x, t_player player, int nbr_levels)
{
	double	camera_x; //could be precalculated based on window WIDTH
	t_vray	ray;
	
	camera_x = 2.0 * x / WIDTH - 1;
	ray.origin.x = player.pos.x;
	ray.origin.y = player.pos.y;
	ray.dir.x = player.look_dir.x + player.cam_plane.x * camera_x;
	ray.dir.y = player.look_dir.y + player.cam_plane.y * camera_x;
	ray.map_pos.x = (int)ray.origin.x;
	ray.map_pos.y = (int)ray.origin.y;
	ray.delta.x = fabs(1.0 / ray.dir.x);
	ray.delta.y = fabs(1.0 / ray.dir.y);
	ray.step.x = (ray.dir.x < 0) ? -1 : 1;
	ray.step.y = (ray.dir.y < 0) ? -1 : 1;
	ray.side.x = (ray.dir.x < 0)
		? (ray.origin.x - ray.map_pos.x) * ray.delta.x
		: (ray.map_pos.x + 1.0 - ray.origin.x) * ray.delta.x;
	ray.side.y = (ray.dir.y < 0)
		? (ray.origin.y - ray.map_pos.y) * ray.delta.y
		: (ray.map_pos.y + 1.0 - ray.origin.y) * ray.delta.y;
	ray.hit_list = calloc(sizeof(t_vhit *), nbr_levels);
	return (ray);
}

static bool	ft_isdoor_ray(t_vray *ray)
{
	if (ray->door_axis == X_AXIS)
	{
		t_dray	hit_check;

		hit_check.target = ray->map_pos.x + ((ray->dir.x > 0) ? DOOR_DEPTH : 1 - DOOR_DEPTH);
		hit_check.distance = hit_check.target - ray->origin.x;
		hit_check.ratio = hit_check.distance / ray->dir.x;
		hit_check.intersect = ray->origin.y + ray->dir.y * hit_check.ratio;

		if ((int)hit_check.intersect == ray->map_pos.y)
			return (true);
	}
	else
	{
		t_dray	hit_check;

		hit_check.target = ray->map_pos.y + ((ray->dir.y > 0) ? DOOR_DEPTH : 1 - DOOR_DEPTH);
		hit_check.distance = hit_check.target - ray->origin.y;
		hit_check.ratio = hit_check.distance / ray->dir.y;
		hit_check.intersect = ray->origin.x + ray->dir.x * hit_check.ratio;

		if ((int)hit_check.intersect == ray->map_pos.x)
			return (true);
	}
	return (false);
}

static t_vhit	*ft_cpycalc_vhit(double pos_z, t_vhit *hit, int level)
{
	t_vhit	*cpy;

	cpy = malloc(sizeof(t_vhit));
	cpy->render = hit->render;
	cpy->door = hit->door;
	cpy->door_axis = hit->door_axis;
	cpy->distance = hit->distance;
	cpy->line_height = hit->line_height;

	cpy->level_offset = ((level - pos_z + 0.5) * HEIGHT) / cpy->distance;
	cpy->draw_bound.x = -cpy->line_height / 2 + HEIGHT / 2 - cpy->level_offset;
	cpy->draw_bound.y = cpy->line_height / 2 + HEIGHT / 2 - cpy->level_offset;

	cpy->wall_x = hit->wall_x;
	cpy->tex = hit->tex;
	cpy->tex_pixel = hit->tex_pixel;
	cpy->next = NULL;
	return (cpy);
}

static t_vhit	*ft_calculate_vhit(t_cub3d *cub3d, t_vray *ray, bool door)
{
	t_2db_point	door_offset;
	t_vhit		*new;

	new = malloc(sizeof(t_vhit));
	new->render = true;
	new->door = door;
	if (door == false)
	{
		new->distance = (ray->axis == X_AXIS)
			? (ray->map_pos.x - ray->origin.x + (1 - ray->step.x) / 2) / ray->dir.x
			: (ray->map_pos.y - ray->origin.y + (1 - ray->step.y) / 2) / ray->dir.y;
	}
	else
	{
		door_offset.x = ray->map_pos.x + ((ray->dir.x > 0) ? DOOR_DEPTH : -DOOR_DEPTH);
		door_offset.y = ray->map_pos.y + ((ray->dir.y > 0) ? DOOR_DEPTH : -DOOR_DEPTH);
		new->distance = (ray->axis == X_AXIS)
			? (door_offset.x - ray->origin.x + (1 - ray->step.x) / 2) / ray->dir.x
			: (door_offset.y - ray->origin.y + (1 - ray->step.y) / 2) / ray->dir.y;
	}
	new->line_height = (int)(HEIGHT / new->distance);

	new->wall_x = (ray->axis == X_AXIS)
		? ray->origin.y + new->distance * ray->dir.y
		: ray->origin.x + new->distance * ray->dir.x;
	new->wall_x -= floor(new->wall_x);

	if (door == true)
		new->tex = &cub3d->textures.door;
	else if (ray->axis == X_AXIS)
		new->tex = (ray->dir.x < 0) ? &cub3d->textures.west : &cub3d->textures.east;
	else
		new->tex = (ray->dir.y < 0) ? &cub3d->textures.north : &cub3d->textures.south;
	new->tex_pixel.x = (int)(new->wall_x * new->tex->width);
	if ((ray->axis == X_AXIS && ray->dir.x > 0) || (ray->axis == Y_AXIS && ray->dir.y < 0))
		new->tex_pixel.x = new->tex->width - new->tex_pixel.x - 1;

	new->next = NULL;
	return (new);
}

static void	ft_vhit_addfront(t_vhit **list, t_vhit *new)
{
	if (new == NULL)
		return ;
	if (*list != NULL)
		new->next = *list;
	*list = new;
}

static void	ft_save_hit(t_cub3d *cub3d, t_vray *ray, bool *hit, bool *door)
{
	int		level;
	t_vhit	*temp;
	t_vhit	*temp_door;

	temp = ft_calculate_vhit(cub3d, ray, 0);
	if (door[0] == true)
		temp_door = ft_calculate_vhit(cub3d, ray, 1);
	level = 0;
	while (level < cub3d->nbr_levels)
	{
		if (hit[level + 1] == true)
		{
			if (door[level + 1] == true)
				ft_vhit_addfront(&ray->hit_list[level], ft_cpycalc_vhit(cub3d->player.pos.z, temp_door, level));
			else
				ft_vhit_addfront(&ray->hit_list[level], ft_cpycalc_vhit(cub3d->player.pos.z, temp, level));
		}
		level++;
	}
	free(temp);
	if (door[0] == true)
		free(temp_door);
}

static void	ft_verify_hit(t_cub3d *cub3d, t_map *map, t_vray *ray, bool *ray_inside_map)
{
	bool	*hit;
	bool	*door;
	int		level;

	hit = calloc(sizeof(bool), (cub3d->nbr_levels + 1));
	door = calloc(sizeof(bool), (cub3d->nbr_levels + 1));
	level = 0;
	while (level < cub3d->nbr_levels)
	{
		char	tile = map[level].level[ray->map_pos.y][ray->map_pos.x];
		if (ray_inside_map[level] && tile == WALL)
		{
			if (hit[0] != true)
				hit[0] = true;
			hit[level + 1] = true;
			ray_inside_map[level] = false;
		}
		else if (ray_inside_map[level] && tile == DOOR)
		{
			ray->door_axis = (map[level].level[ray->map_pos.y - 1][ray->map_pos.x] != WALL);
			if (ft_isdoor_ray(ray))
			{
				if (hit[0] != true)
					hit[0] = true;
				if (door[0] != true)
					door[0] = true;
				hit[level + 1] = true;
				door[level + 1] = true;
			}
		}
		else if (!ray_inside_map[level] && tile != WALL)
			ray_inside_map[level] = true;
		level++;
	}
	if (hit[0] == true)
		ft_save_hit(cub3d, ray, hit, door);
	free(hit);
	free(door);
}

void	ft_hit_loop(t_cub3d *cub3d, t_map *map, t_vray *ray)
{
	bool	*ray_inside_map;
	int		level;

	ray_inside_map = calloc(sizeof(bool), cub3d->nbr_levels);
	level = 0;
	while (level < cub3d->nbr_levels)
	{
		ray_inside_map[level] = (map[level].level[ray->map_pos.y][ray->map_pos.x] != WALL);
		level++;
	}
	while (true)
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

		if (ray->map_pos.x < map[0].min_x || ray->map_pos.x >= map[0].max_x ||
			ray->map_pos.y < map[0].min_y || ray->map_pos.y >= map[0].max_y)
		{
			free(ray_inside_map);
			return ;
		}
		ft_verify_hit(cub3d, map, ray, ray_inside_map);
	}
}

t_hray	ft_new_hray(t_2int_point pixel, t_2db_point dir_left, t_2db_point dir_right, t_3db_point player_pos, int floor)
{
	t_hray	ray;

	ray.pixel_horizon = pixel.y - HEIGHT / 2;
	ray.pixel_camera_height = player_pos.z * HEIGHT - floor * HEIGHT;
	ray.distance = ray.pixel_camera_height / ray.pixel_horizon;
	ray.step.x = ray.distance * (dir_right.x - dir_left.x) / WIDTH;
	ray.step.y = ray.distance * (dir_right.y - dir_left.y) / WIDTH;
	ray.pos.x = player_pos.x + ray.distance * dir_left.x;
	ray.pos.y = player_pos.y + ray.distance * dir_left.y;
	return (ray);
}