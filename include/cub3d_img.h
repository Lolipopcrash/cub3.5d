/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_img.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <kelevequ@student.42luxembourg>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-16 05:33:16 by kelevequ          #+#    #+#             */
/*   Updated: 2025-07-16 05:33:16 by kelevequ         ###   ########.lu       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_MLX_H
# define CUB3D_MLX_H

# include "cub3d_extlibs.h"

typedef struct	s_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		height;
	int		width;
	int		bpp;
	int		endian;
	int		line_len;
}			t_img;

typedef struct	s_tex
{
	t_img	floor;
	t_img	north;
	t_img	south;
	t_img	west;
	t_img	east;
	t_img	door;
	t_img	sky;
}			t_tex;

t_img	ft_load_texture(void *mlx, char *file_path);
int		ft_get_texture_pixel(t_img *tex, int x, int y);

#endif