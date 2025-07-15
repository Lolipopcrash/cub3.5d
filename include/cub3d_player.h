/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_player.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <kelevequ@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:38:32 by kelevequ          #+#    #+#             */
/*   Updated: 2025/07/14 19:38:32 by kelevequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_PLAYER_H
# define CUB3D_PLAYER_H

# include "libft.h"
# include "cub3d_point.h"

typedef struct	s_player
{
	t_3db_point	pos;
	t_2db_point	look_dir;
	int			pitch;
	t_2db_point	cam_plane;
	t_2db_point	walk_dir;
	bool		is_running;
	bool		is_walking;
	bool		is_crouch;
	bool		is_jump;
}				t_player;

#endif