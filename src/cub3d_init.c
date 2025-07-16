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

static void	ft_init_textures(t_tex *textures)
{
	textures->floor = ft_load_texture(cub3d->mlx, "./gfx/floor.xpm");
	textures->north = ft_load_texture(cub3d->mlx, "./gfx/nwall.xpm");
	textures->south = ft_load_texture(cub3d->mlx, "./gfx/swall.xpm");
	textures->west = ft_load_texture(cub3d->mlx, "./gfx/wwall.xpm");
	textures->east = ft_load_texture(cub3d->mlx, "./gfx/ewall.xpm");
	textures->door = ft_load_texture(cub3d->mlx, "./gfx/door.xpm");
	textures->sky = ft_load_texture(cub3d->mlx, "./gfx/sky2.xpm");
}

static void	ft_init_events(t_cub3d *cub3d)
{
	mlx_hook(cub3d->mlx_window, KeyPress, KeyPressMask,
			ft_key, cub3d);
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
			&cub3d->scree.endian);
}

bool	ft_init_cub3d(t_cub3d *cub3d)
{
	ft_init_mlx(cub3d);
	ft_init_events(cub3d);
	ft_init_textures(&cub3d->textures);
	ft_init_map(cub3d);
	ft_init_player(cub3d);
}