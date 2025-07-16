/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_point.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <kelevequ@student.42luxembourg>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-16 05:33:35 by kelevequ          #+#    #+#             */
/*   Updated: 2025-07-16 05:33:35 by kelevequ         ###   ########.lu       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_POINT_H
# define CUB3D_POINT_H

typedef struct	s_2int_point
{
	int	x;
	int	y;
}		t_2int_point;

typedef struct	s_3int_point
{
	int	x;
	int	y;
	int	z;
}		t_3int_point;

typedef struct	s_2db_point
{
	double	x;
	double	y;
}			t_2db_point;

typedef struct	s_3db_point
{
	double	x;
	double	y;
	double	z;
}			t_3db_point;

#endif