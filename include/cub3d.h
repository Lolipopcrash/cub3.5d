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

# include "cub3d_engine.h"
# include "cub3d_player.h"
# include "cub3d_img.h"

# define PLAYABLE_AREA -1
# define HEIGHT	1280
# define WIDTH	720

typedef struct	s_cub3d
{
	void		*mlx;
	void		*mlx_window;
	t_img		screen;
	t_tex		textures;
	t_player	player;
	t_map		map;
}				t_cub3d;

#endif