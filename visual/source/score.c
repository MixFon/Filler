/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 11:38:45 by widraugr          #+#    #+#             */
/*   Updated: 2019/04/26 14:10:16 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/visual.h"

/*
**  Calculete score for input on table.
*/

void	score(char *line, int *score_o, int *score_x)
{
	while (*line != '\0')
	{
		if (*line == 'o')
			*score_o = *score_o + 1;
		if (*line == 'x')
			*score_x = *score_x + 1;
		line++;
	}
}

void	delete_map_square(t_vis *vis)
{
	dell_arr(vis->map_score);
	free(vis->map_score);
	vis->map_score = NULL;
	dell_arr(vis->map_bourd);
	free(vis->map_bourd);
	vis->map_bourd = NULL;
	dell_arr(vis->map_obd);
	free(vis->map_obd);
	vis->map_obd = NULL;
	dell_arr(vis->map_obl);
	free(vis->map_obl);
	vis->map_obl = NULL;
	dell_arr(vis->map_xp);
	free(vis->map_xp);
	vis->map_xp = NULL;
	dell_arr(vis->map_xr);
	free(vis->map_xr);
	vis->map_xr = NULL;
}

void	print_fon(t_vis *vis)
{
	int		i;
	int		j;
	int		y;
	int		x;

	i = -1;
	read_input(vis);
	coor_centr(&x, &y, vis->row * (vis->heith + 1),
			vis->col * (vis->width + 1));
	vis->y_it = y;
	vis->x_it = x;
	while (++i < vis->row)
	{
		j = -1;
		while (++j < vis->col)
		{
			if (vis->map[i][j] == '.')
				mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr,
						vis->img_bourd, vis->x_it, vis->y_it);
			vis->x_it += vis->width + 1;
		}
		vis->x_it = x;
		vis->y_it += (vis->heith + 1);
	}
}

int		close_win(void)
{
	err_sys("Close window.\n");
	return (0);
}
