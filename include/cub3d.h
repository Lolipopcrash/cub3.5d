/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <kelevequ@student.42luxembourg>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-16 05:33:42 by kelevequ          #+#    #+#             */
/*   Updated: 2025-07-16 05:33:42 by kelevequ         ###   ########.lu       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "cub3d_extlibs.h"
# include "cub3d_img.h"
# include "cub3d_map.h"
# include "cub3d_player.h"
# include "cub3d_engine.h"
# include "cub3d_controls.h"

# define HEIGHT	720
# define WIDTH	1280

typedef struct	s_cub3d
{
	void		*mlx;
	void		*mlx_window;
	t_img		screen;
	t_tex		textures;
	t_player	player;
	t_map		*map;
	int			nbr_levels;
	uint8_t		keystate[KEY_MAX / BIT_PER_BYTE];
}				t_cub3d;

void	ft_init_cub3d(t_cub3d *cub3d);

#endif