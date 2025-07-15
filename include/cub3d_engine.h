/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_engine.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <kelevequ@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:38:25 by kelevequ          #+#    #+#             */
/*   Updated: 2025/07/14 19:38:25 by kelevequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_ENGINE_H
# define CUB3D_ENGINE_H

# include "cub3d_point.h"

typedef struct	s_ray
{
	double	camera_x; //could be precalculated based on window WIDTH
	t_2db_point		ray_dir;
	t_2int_point	map_pos;
	t_2db_point		delta;
	t_2int_point	step;
	t_2db_point		side;
	bool			hit;
	bool			axis;
	double			distance;
	int				line_height;
	t_2int_point	draw_boundaries; //x start, y end
	double			wall_x;
}			t_ray;

#endif