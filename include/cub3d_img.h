/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_mlx.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <kelevequ@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-15 05:01:48 by kelevequ          #+#    #+#             */
/*   Updated: 2025-07-15 05:01:48 by kelevequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_MLX_H
# define CUB3D_MLX_H

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

#endif