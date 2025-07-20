/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <kelevequ@student.42luxembourg>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-16 17:23:13 by kelevequ          #+#    #+#             */
/*   Updated: 2025-07-16 17:23:13 by kelevequ         ###   ########.lu       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_MAP_H
# define CUB3D_MAP_H

# include "cub3d_extlibs.h"

# define AIR	'0'
# define WALL	'1'
# define DOOR	'D'
# define FLOOR	'F'

typedef struct	s_map
{
	int		offset_x;
	int		offset_y;
	int		min_x;
	int		min_y;
	int		max_x;
	int		max_y;
	int		level_id;
	char	**level;
}			t_map;

#endif