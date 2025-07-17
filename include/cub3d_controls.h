/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_controls.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <kelevequ@student.42luxembourg>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-16 08:24:53 by kelevequ          #+#    #+#             */
/*   Updated: 2025-07-16 08:24:53 by kelevequ         ###   ########.lu       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_CONTROLS_H
# define CUB3D_CONTROLS_H

# include "cub3d_extlibs.h"
# include "cub3d.h"

# define KEY_MAX 65536
# define BIT_PER_BYTE 8

	/* ----------------- */
 /* Movement Controls */
/* ----------------- */

# define UP			0xff52
# define DOWN		0xff54
# define LEFT		0xff51
# define RIGHT	0xff53
# define W			0x0077
# define A			0x0061
# define S			0x0073
# define D			0x0064
# define SPACE	0x0020
# define C			0x0063
# define SHIFT	0xffe1
# define F			0x0066
# define Q			0x0071
# define E			0x0065
# define ESC		0xff1b

void	ft_controls(t_cub3d *cub3d);
int		ft_close(t_cub3d *cub3d);
int		ft_key_press(int keycode, t_cub3d *cub3d);
int		ft_key_release(int keycode, t_cub3d *cub3d);

#endif