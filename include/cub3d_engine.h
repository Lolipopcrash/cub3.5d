/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_engine.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <kelevequ@student.42luxembourg>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-16 05:32:59 by kelevequ          #+#    #+#             */
/*   Updated: 2025-07-16 05:32:59 by kelevequ         ###   ########.lu       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_ENGINE_H
# define CUB3D_ENGINE_H

# include "cub3d_extlibs.h"
# include "cub3d_point.h"
# include "cub3d_img.h"
# include "cub3d.h"

# define X_AXIS	0
# define Y_AXIS	1
# define PLAYER_FOV 0.66
# define DEFAULT_FLOOR_COLOR 0xFFF8DC
# define DEFAULT_ROOF_COLOR 0x87CEFA
# define DEFAULT_WALL_COLOR 0xB0B0B0

typedef struct	s_draw_elements
{
	t_2int_point	sky;
	t_2int_point	wall;
	t_2int_point	door;
	t_2int_point	floor;
	int				vert_offset;
}					t_draw_elements;

typedef struct	s_ray
{
	//double			camera_x; //could be precalculated based on window WIDTH
	t_2db_point		dir;
	t_2int_point	map_pos;
	t_2db_point		delta;
	t_2int_point	step;
	t_2db_point		side;
	bool			hit;
	bool			axis;
	double			distance;
	int				line_height;
	int				level_offset;
	t_2int_point	draw_bound; //x start, y end
	double			wall_x;
	t_img			*tex;
	t_2int_point	tex_pixel;
}					t_ray;

typedef struct s_cub3d t_cub3d;
typedef struct s_player t_player;

int		ft_engine(t_cub3d *cub3d);
t_ray	ft_new_ray(int x, t_player player);
void	ft_calculate_ray(t_cub3d *cub3d, t_ray *ray, int level);

#endif