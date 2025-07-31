/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_engine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <kelevequ@student.42luxembourg>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-16 05:33:54 by kelevequ          #+#    #+#             */
/*   Updated: 2025-07-16 05:33:54 by kelevequ         ###   ########.lu       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_put_pixel(t_img *img, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

static int	ft_cpy_color(int x, int y, t_img img)
{
	int	offset;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return (0);
	offset = (y * img.line_len) + (x * (img.bpp / 8));
	return (*(unsigned int *)(img.pixels_ptr + offset));
}

static int	ft_get_color(int y, t_vhit *hit)
{
	int	d;

	d = (y + hit->level_offset) * 256 - HEIGHT * 128 + hit->line_height * 128;
	hit->tex_pixel.y = ((d * hit->tex->height) / hit->line_height) / 256;
	return (ft_get_texture_pixel(hit->tex, hit->tex_pixel.x, hit->tex_pixel.y));
}

static void	ft_draw_sky(t_cub3d *cub3d, t_img *sky)
{
	double	angle;
	int		tex_offset;
	int		color;
	int		x;
	int		y;

	angle = atan2(cub3d->player.look_dir.y, cub3d->player.look_dir.x);
	if (angle < 0)
		angle += 2 * M_PI;

	tex_offset = (int)(angle / (2 * M_PI) * sky->width * 3);
	
	y = 0;
	while (y < (HEIGHT / 2) + cub3d->player.pos.z * Z_FACTOR && y < HEIGHT)
	{
		t_2int_point	tex_pixel;
		double			v;

		v = (double)(y + HEIGHT / 2 + cub3d->player.pos.z * Z_FACTOR) / (HEIGHT / 2);
		v = pow(v, 0.7);
		tex_pixel.y = (int)(v * sky->height) % sky->height;
		x = 0;
		while (x < WIDTH)
		{
			tex_pixel.x = (int)(tex_offset + x * sky->width / WIDTH) % sky->width;
			color = ft_get_texture_pixel(sky, tex_pixel.x, tex_pixel.y);
			ft_put_pixel(&cub3d->screen, x, y, color);
			x++;
		}
		y++;
	}
}

static void	ft_render_background(t_cub3d *cub3d)
{
	int color;
	int	x;
	int	y;

	y = HEIGHT / 2 + 1 + cub3d->player.pos.z * 20;
	while (y < HEIGHT)
	{
		color = DEFAULT_FLOOR_COLOR;
		x = 0;
		while (x < WIDTH)
		{
			ft_put_pixel(&cub3d->screen, x, y, color);
			x++;
		}
		y++;
	}
	ft_draw_sky(cub3d, &cub3d->textures.sky);
}

static void	ft_render_floor(t_cub3d *cub3d, int player_floor)
{
	t_2int_point	pixel;
	t_2db_point		dir_left;
	t_2db_point		dir_right;
	t_hray			ray;
	int				draw_floor;

	dir_left.x = cub3d->player.look_dir.x - cub3d->player.cam_plane.x;
	dir_left.y = cub3d->player.look_dir.y - cub3d->player.cam_plane.y;
	dir_right.x = cub3d->player.look_dir.x + cub3d->player.cam_plane.x;
	dir_right.y = cub3d->player.look_dir.y + cub3d->player.cam_plane.y;
	draw_floor = 0;
	while (draw_floor <= player_floor)
	{
		pixel.y = HEIGHT / 2 + 1;
		while (pixel.y < HEIGHT)
		{
			ray = ft_new_hray(pixel, dir_left, dir_right, cub3d->player.pos, draw_floor);
			pixel.x = 0;
			while (pixel.x < WIDTH)
			{
				ray.map_pos.x = (int)ray.pos.x;
				ray.map_pos.y = (int)ray.pos.y;
				if (cub3d->map[draw_floor].min_x < ray.map_pos.x && ray.map_pos.x < cub3d->map[draw_floor].max_x &&
					cub3d->map[draw_floor].min_y < ray.map_pos.y && ray.map_pos.y < cub3d->map[draw_floor].max_y)
				{
					if (cub3d->map[draw_floor].level[ray.map_pos.y][ray.map_pos.x] == FLOOR ||
						cub3d->map[draw_floor].level[ray.map_pos.y][ray.map_pos.x] == DOOR)
					{
						ray.tex_pixel.x = (int)(ray.pos.x * cub3d->textures.floor.width) % cub3d->textures.floor.width;
						ray.tex_pixel.y = (int)(ray.pos.y * cub3d->textures.floor.height) % cub3d->textures.floor.height;
						if (ray.tex_pixel.x < 0)
							ray.tex_pixel.x += cub3d->textures.floor.width;
						if (ray.tex_pixel.y < 0)
							ray.tex_pixel.y += cub3d->textures.floor.height;
						int	color = ft_get_texture_pixel(&cub3d->textures.floor, ray.tex_pixel.x, ray.tex_pixel.y);
						ft_put_pixel(&cub3d->floor_img, pixel.x, pixel.y, color);
						cub3d->floor_height[pixel.y][pixel.x] = draw_floor + 1;
					}
				}
				ray.pos.x += ray.step.x;
				ray.pos.y += ray.step.y;
				pixel.x++;
			}
			pixel.y++;
		}
		draw_floor++;
	}
}

static void	ft_draw_hitlist(t_cub3d *cub3d, int x, t_vhit *hit_list, int floor)
{
	int		y;
	int		color;
	t_vhit	*tmp;

	tmp = hit_list;
	while (tmp != NULL)
	{
		y = tmp->draw_bound.x - FIX_PIXEL_GAP;
		if (y < 0)
			y = 0;
		if (y >= HEIGHT)
		{
			tmp = tmp->next;
			continue ;
		}
		while (y < HEIGHT)
		{
			if (y <= tmp->draw_bound.y + FIX_PIXEL_GAP)
				color = ft_get_color(y, tmp);
			else if (cub3d->floor_height[y][x] == floor + 1)
				color = ft_cpy_color(x, y, cub3d->floor_img);
			else
			{
				y++;
				continue ;
			}
			ft_put_pixel(&cub3d->screen, x, y, color);
			y++;
		}
		tmp = tmp->next;
	}
}

static void	ft_free_vray(t_vray *ray, int nbr_levels)
{
	int	level;

	level = 0;
	while (level < nbr_levels)
	{
		t_vhit	*tmp;
		t_vhit	*byebye;

		tmp = ray->hit_list[level];
		while (tmp != NULL)
		{
			byebye = tmp;
			tmp = tmp->next;
			free(byebye);
		}
		level++;
	}
	free(ray->hit_list);
}

static void	ft_render_wall(t_cub3d *cub3d)
{
	int		screen_x;
	int		player_level;
	int		level;
	t_vray	ray;

	player_level = (int)cub3d->player.pos.z;
	screen_x = 0;
	while (screen_x < WIDTH)
	{
		ray = ft_new_vray(screen_x, cub3d->player, cub3d->nbr_levels);
		ft_hit_loop(cub3d, cub3d->map, &ray);
		//ft_check_draw_boundaries(ray);
		level = 0;
		while (level < player_level)
		{
			ft_draw_hitlist(cub3d, screen_x, ray.hit_list[level], level);
			level++;
		}
		level = cub3d->nbr_levels - 1;
		while (level > player_level)
		{
			ft_draw_hitlist(cub3d, screen_x, ray.hit_list[level], level);
			level--;
		}
		ft_draw_hitlist(cub3d, screen_x, ray.hit_list[player_level], level);
		screen_x++;
		ft_free_vray(&ray, cub3d->nbr_levels);
	}
}

static void	ft_render_image(t_cub3d *cub3d)
{
	for (int j = 0; j < HEIGHT; j++)
		for (int i = 0; i < WIDTH; i++)
			cub3d->floor_height[j][i] = 0;
	ft_render_background(cub3d);
	ft_render_floor(cub3d, (int)cub3d->player.pos.z);
	ft_render_wall(cub3d);
}

static bool	ft_valid_position(t_cub3d *cub3d, t_map map)
{
	t_2int_point	player;

	player.x = (int)cub3d->player.pos.x;
	player.y = (int)cub3d->player.pos.y;
	if (player.x < map.min_x || player.x >= map.max_x ||
		player.y < map.min_y || player.y >= map.max_y)
		return (0);
	return (1);
}

static void	ft_update_frame_info(t_cub3d *cub3d)
{
	ft_controls(cub3d); //temporary for testing
	//When multi-threading introduced will update/duplicate threaded player data once for current frame
}

int	ft_engine(t_cub3d *cub3d)
{
	ft_update_frame_info(cub3d);
	if (ft_valid_position(cub3d, cub3d->map[(int)cub3d->player.pos.z]))
		ft_render_image(cub3d);
	else
		ft_render_background(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->mlx_window, cub3d->screen.img_ptr, 0, 0);
	cub3d->frames++;
	if ((time(NULL) - cub3d->start_time) != cub3d->last_time)
	{
		printf("FPS = %d\n", cub3d->frames);
		cub3d->last_time = time(NULL) - cub3d->start_time;
		cub3d->frames = 0;
	}
	return (1);
}