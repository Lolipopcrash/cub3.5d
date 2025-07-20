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
		return;
	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

static int	ft_get_color(t_2int_point screen_pixel, t_vray ray)
{
	int	d;

	d = (screen_pixel.y + ray.level_offset) * 256 - HEIGHT * 128 + ray.line_height * 128;
	ray.tex_pixel.y = ((d * ray.tex->height) / ray.line_height) / 256;
	return (ft_get_texture_pixel(ray.tex, ray.tex_pixel.x, ray.tex_pixel.y));
}

static void	ft_render_background(t_cub3d *cub3d)
{
	int color;
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		if (y < HEIGHT / 2)
			color = DEFAULT_ROOF_COLOR;
		else
			color = DEFAULT_FLOOR_COLOR;
		x = 0;
		while (x < WIDTH)
		{
			ft_put_pixel(&cub3d->screen, x, y, color);
			x++;
		}
		y++;
	}
}

static void	ft_render_floor(t_cub3d *cub3d, int draw_floor, int *loop_count)
{
	t_2int_point	pixel;
	t_2db_point		dir_left;
	t_2db_point		dir_right;
	t_hray			ray;

	dir_left.x = cub3d->player.look_dir.x - cub3d->player.cam_plane.x;
	dir_left.y = cub3d->player.look_dir.y - cub3d->player.cam_plane.y;
	dir_right.x = cub3d->player.look_dir.x + cub3d->player.cam_plane.x;
	dir_right.y = cub3d->player.look_dir.y + cub3d->player.cam_plane.y;
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
					ft_put_pixel(&cub3d->screen, pixel.x, pixel.y, color);
				}
			}
			ray.pos.x += ray.step.x;
			ray.pos.y += ray.step.y;
			pixel.x++;
			(*loop_count)++;
		}
		pixel.y++;
	}
}

static void	ft_render_wall(t_cub3d *cub3d, int draw_level, int *loop_count)
{
	t_2int_point	pixel;
	t_vray			ray;
	int				color;

	pixel.x = 0;
	while (pixel.x < WIDTH)
	{
		ray = ft_new_vray(pixel.x, cub3d->player);
		ft_calculate_vray(cub3d, &ray, draw_level);
		if (ray.render == false)
		{
			pixel.x++;
			continue ;
		}
		pixel.y = ray.draw_bound.x - FIX_PIXEL_GAP;
		if (pixel.y < 0)
			pixel.y = 0;
		while (pixel.y < HEIGHT && pixel.y <= ray.draw_bound.y + FIX_PIXEL_GAP)
		{
			color = ft_get_color(pixel, ray);
			ft_put_pixel(&cub3d->screen, pixel.x, pixel.y, color);
			pixel.y++;
			(*loop_count)++;
		}
		pixel.x++;
	}
}

static void	ft_render_image(t_cub3d *cub3d, int *loop_count)
{
	int				player_z;
	int				draw_z;

	ft_render_background(cub3d);
	player_z = (int)cub3d->player.pos.z;
	draw_z = 0;
	while (draw_z < player_z)
	{
		ft_render_floor(cub3d, draw_z, loop_count);
		ft_render_wall(cub3d, draw_z, loop_count);
		draw_z++;
	}
	draw_z = cub3d->nbr_levels - 1;
	while (draw_z > player_z)
	{
		ft_render_wall(cub3d, draw_z, loop_count);
		draw_z--;
	}
	ft_render_floor(cub3d, player_z, loop_count);
	ft_render_wall(cub3d, player_z, loop_count);
}

static bool	ft_valid_position(t_cub3d *cub3d, t_map map)
{
	t_2int_point	player;

	player.x = (int)cub3d->player.pos.x;
	player.y = (int)cub3d->player.pos.y;
	if (player.x < map.min_x || player.x >= map.max_x ||
		player.y < map.min_y || player.y >= map.max_y ||
		map.level[player.y][player.x] == WALL)
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
	int	loop_count;

	loop_count = 0;
	ft_update_frame_info(cub3d);
	if (ft_valid_position(cub3d, cub3d->map[(int)cub3d->player.pos.z]))
		ft_render_image(cub3d, &loop_count);
	else
		ft_render_background(cub3d);
	//printf("loop_count = %d\n", loop_count);
	mlx_put_image_to_window(cub3d->mlx, cub3d->mlx_window, cub3d->screen.img_ptr, 0, 0);
	return (1);
}