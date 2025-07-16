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

# include "cub3d_point.h"
# include "cub3d_img.h"

# define X_AXIS	0
# define Y_AXIS	1
# define DEFAULT_FLOOR_COLOR 0xFFF8DC
# define DEFAULT_ROOF_COLOR 0x87CEFA

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
	t_2int_point	draw_bound; //x start, y end
	double			wall_x;
	t_img			*tex;
	t_2int_point	tex_pixel;
}					t_ray;

#endif