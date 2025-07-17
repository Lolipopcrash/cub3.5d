/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <kelevequ@student.42luxembourg>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-17 05:48:06 by kelevequ          #+#    #+#             */
/*   Updated: 2025-07-17 05:48:06 by kelevequ         ###   ########.lu       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define W_BYTE	W / BIT_PER_BYTE
#define W_BIT	W % BIT_PER_BYTE
#define A_BYTE	A / BIT_PER_BYTE
#define A_BIT	A % BIT_PER_BYTE
#define S_BYTE	S / BIT_PER_BYTE
#define S_BIT	S % BIT_PER_BYTE
#define D_BYTE	D / BIT_PER_BYTE
#define D_BIT	D % BIT_PER_BYTE

static void	ft_update_player_pos(uint8_t *keystate, t_player *player)
{
	if ((keystate[W_BYTE] & (1 << W_BIT)) != 0)
	{
		player->pos.x += player->look_dir.x * player->speed;
		player->pos.y += player->look_dir.y * player->speed;
	}
	if ((keystate[A_BYTE] & (1 << A_BIT)) != 0)
	{
		player->pos.x += player->look_dir.y * player->speed;
		player->pos.y -= player->look_dir.x * player->speed;
	}
	if ((keystate[S_BYTE] & (1 << S_BIT)) != 0)
	{
		player->pos.x -= player->look_dir.x * player->speed;
		player->pos.y -= player->look_dir.y * player->speed;
	}
	if ((keystate[D_BYTE] & (1 << D_BIT)) != 0)
	{
		player->pos.x -= player->look_dir.y * player->speed;
		player->pos.y += player->look_dir.x * player->speed;
	}
}

#define UP_BYTE		UP / BIT_PER_BYTE
#define UP_BIT		UP % BIT_PER_BYTE
#define LEFT_BYTE	LEFT / BIT_PER_BYTE
#define LEFT_BIT	LEFT % BIT_PER_BYTE
#define RIGHT_BYTE	RIGHT / BIT_PER_BYTE
#define RIGHT_BIT	RIGHT % BIT_PER_BYTE
#define DOWN_BYTE	DOWN / BIT_PER_BYTE
#define DOWN_BIT	DOWN % BIT_PER_BYTE

static void	ft_update_player_dir(uint8_t *keystate, t_player *player)
{
	double	old_look_dir_x;
	double	old_cam_plane_x;


	old_look_dir_x = player->look_dir.x;
	old_cam_plane_x = player->cam_plane.x;
	if ((keystate[RIGHT_BYTE] & (1 << RIGHT_BIT)) != 0)
	{
		player->look_dir.x = player->look_dir.x * cos(0.035) - player->look_dir.y * sin(0.035);
		player->look_dir.y = old_look_dir_x * sin(0.035) + player->look_dir.y * cos(0.035);
		player->cam_plane.x = player->cam_plane.x * cos(0.035) - player->cam_plane.y * sin(0.035);
		player->cam_plane.y = old_cam_plane_x * sin(0.035) + player->cam_plane.y * cos(0.035);
	}
	else if ((keystate[LEFT_BYTE] & (1 << LEFT_BIT)) != 0)
	{
		player->look_dir.x = player->look_dir.x * cos(-0.035) - player->look_dir.y * sin(-0.035);
		player->look_dir.y = old_look_dir_x * sin(-0.035) + player->look_dir.y * cos(-0.035);
		player->cam_plane.x = player->cam_plane.x * cos(-0.035) - player->cam_plane.y * sin(-0.035);
		player->cam_plane.y = old_cam_plane_x * sin(-0.035) + player->cam_plane.y * cos(-0.035);
	}
}

void	ft_controls(t_cub3d *cub3d)
{
	ft_update_player_pos(cub3d->keystate, &cub3d->player);
	ft_update_player_dir(cub3d->keystate, &cub3d->player);
}