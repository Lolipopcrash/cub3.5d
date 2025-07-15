/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <kelevequ@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-15 12:09:12 by kelevequ          #+#    #+#             */
/*   Updated: 2025-07-15 12:09:12 by kelevequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(void)
{
	t_cub3d	cub3d;

	if (!ft_init_cub3d(&cub3d, argv[1]))
		return (0);
	mlx_loop_hook(cub3d.mlx, &ft_engine, &cub3d);
	mlx_loop(cub3d.mlx);
}