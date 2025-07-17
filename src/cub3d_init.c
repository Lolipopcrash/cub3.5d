/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <kelevequ@student.42luxembourg>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-16 05:34:18 by kelevequ          #+#    #+#             */
/*   Updated: 2025-07-16 05:34:18 by kelevequ         ###   ########.lu       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_init_player(t_player *player)
{
	player->pos.x = 1.5;
	player->pos.y = 1.5;
	player->pos.z = 0.5;
	player->look_dir.x = 1;
	player->look_dir.y = 0;
	player->pitch = 0;
	player->cam_plane.x = -player->look_dir.y * PLAYER_FOV;
	player->cam_plane.y = player->look_dir.x * PLAYER_FOV;
	player->walk_dir.x = 0;
	player->walk_dir.y = 0;
	player->is_running = false;
	player->is_walking = false;
	player->is_crouch = false;
	player->is_jump = false;
	player->speed = 0.03;
}

static void	ft_init_map(t_map *map)
{
	map[0].min_x = 0;
	map[0].min_y = 0;
	map[0].max_x = 40;
	map[0].max_y = 10;
	map[0].level_id = 0;
	static char	*level_data[] = {
	"P111111111111111111111111111111111111111",
	"1FFFFF1111111111111111111111111111111111",
	"111F1111111FFFFFFFFFFFFFFFFFFFF111111111",
	"111FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF1111",
	"111111111111FFFFFFFFFFFFFFFFFFF111111111",
	"111111111111111FFFFFFFFFFFFFF11111111111",
	"11111111111111111FFFFFFFFFFF111111111111",
	"1111111111111111111FFFFFFF11111111111111",
	"111FFFFFFFFFFFFFFFFFFFF11111111111111111",
	"1111111111111111111111111111111111111111"
	};
	map[0].level = level_data;
	map[1].min_x = 0;
	map[1].min_y = 0;
	map[1].max_x = 40;
	map[1].max_y = 10;
	map[1].level_id = 1;
	static char	*level_data2[] = {
	"P111111111111111111111111111111111111111",
	"1000001111111111111111111111111111111111",
	"1FF0111111100000000000000000000111111111",
	"1FF0000000000000000000000000000000001111",
	"1FFFFFFFFFFF0000000000000000000011111111",
	"1FFFFFFFFFFFFFF0000000000000001111111111",
	"1FFFFFFFFFFFFFFFF00000000000011111111111",
	"1FFFFFFFFFFFFFFFFFF000000011111111111111",
	"1110000000000000000000011111111111111111",
	"1111111111111111111111111111111111111111"
	};
	map[1].level = level_data2;
	/*--------IMPORTANT--------*/
	//A level above a floor cannot be a floor itself, must be '0' (open air) or '1' (wall).
	//Issue being that visually, it would look weird without raising the floor and doing half-steps.
	//All '0's and 'F's must be fully enclosed by '1's or any other walls (like 'P').
}

static void	ft_init_textures(t_cub3d *cub3d, t_tex *textures)
{
	textures->floor = ft_load_texture(cub3d->mlx, "./src/gfx/floor.xpm");
	textures->north = ft_load_texture(cub3d->mlx, "./src/gfx/nwall.xpm");
	textures->south = ft_load_texture(cub3d->mlx, "./src/gfx/swall.xpm");
	textures->west = ft_load_texture(cub3d->mlx, "./src/gfx/wwall.xpm");
	textures->east = ft_load_texture(cub3d->mlx, "./src/gfx/ewall.xpm");
	textures->door = ft_load_texture(cub3d->mlx, "./src/gfx/door.xpm");
	textures->sky = ft_load_texture(cub3d->mlx, "./src/gfx/sky2.xpm");
}

static void	ft_init_events(t_cub3d *cub3d)
{
	mlx_hook(cub3d->mlx_window, KeyPress, KeyPressMask,
			ft_key_press, cub3d);
	mlx_hook(cub3d->mlx_window, KeyRelease, KeyReleaseMask, ft_key_release,
		cub3d);
	mlx_hook(cub3d->mlx_window, DestroyNotify, StructureNotifyMask,
			ft_close, cub3d);
}

static void	ft_init_mlx(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init();
	if (!cub3d->mlx)
		exit(EXIT_FAILURE);
	cub3d->mlx_window = mlx_new_window(cub3d->mlx, WIDTH, HEIGHT, "cub3.5d");
	if (!cub3d->mlx_window)
	{
		mlx_destroy_display(cub3d->mlx);
		free(cub3d->mlx);
		exit(EXIT_FAILURE);
	}
	cub3d->screen.img_ptr = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (!cub3d->screen.img_ptr)
	{
		mlx_destroy_window(cub3d->mlx, cub3d->mlx_window);
		mlx_destroy_display(cub3d->mlx);
		free(cub3d->mlx);
		exit(EXIT_FAILURE);
	}
	cub3d->screen.pixels_ptr = mlx_get_data_addr(cub3d->screen.img_ptr,
			&cub3d->screen.bpp,
			&cub3d->screen.line_len,
			&cub3d->screen.endian);
}

void	ft_init_cub3d(t_cub3d *cub3d)
{
	int	i;

	ft_init_mlx(cub3d);
	ft_init_events(cub3d);
	ft_init_textures(cub3d, &cub3d->textures);
	cub3d->nbr_levels = 2;
	cub3d->map = malloc(sizeof(t_map) * cub3d->nbr_levels);
	ft_init_map(cub3d->map);
	ft_init_player(&cub3d->player);
	i = 0;
	while (i < KEY_MAX / BIT_PER_BYTE)
		cub3d->keystate[i++] = 0;
}