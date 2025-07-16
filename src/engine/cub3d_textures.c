/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <kelevequ@student.42luxembourg>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-16 06:11:17 by kelevequ          #+#    #+#             */
/*   Updated: 2025-07-16 06:11:17 by kelevequ         ###   ########.lu       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	ft_load_texture(void *mlx, char *file_path)
{
	t_img	tex;

	tex.img_ptr = mlx_xpm_file_to_image(mlx, file_path,
			&tex.width,
			&tex.height);
	if (!tex.img_ptr)
		return(tex);
	tex.pixels_ptr = mlx_get_data_addr(tex.img_ptr,
			&tex.bpp,
			&tex.line_len,
			&tex.endian);
	return (tex);
}