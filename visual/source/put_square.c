/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_square.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 11:33:06 by widraugr          #+#    #+#             */
/*   Updated: 2019/04/22 16:39:25 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/visual.h"

/*
** Create map for squares.
*/

void	create_map_square(t_vis *vis)
{
	vis->map_score = crea_color_map(H_REC, W_REC, C_SCORE);
	vis->map_bourd = crea_color_map(vis->heith, vis->width, C_BOURD);
	vis->map_obd = crea_color_map(vis->heith, vis->width, C_BD);
	vis->map_obl = crea_color_map(vis->heith, vis->width, C_BL);
	vis->map_xp = crea_color_map(vis->heith, vis->width, C_P);
	vis->map_xr = crea_color_map(vis->heith, vis->width, C_R);
}

/*
** Init image.
*/

int		init_image_squer(t_vis *vis)
{
	int a;

	a = 0;
	colc_size_squre(vis);
	create_map_square(vis);
	if (!(vis->img_score = mlx_xpm_to_image(vis->mlx_ptr,
			vis->map_score, &a, &a)))
		return (0);
	if (!(vis->img_bourd = mlx_xpm_to_image(vis->mlx_ptr,
			vis->map_bourd, &vis->heith, &vis->width)))
		return (0);
	if (!(vis->img_obd = mlx_xpm_to_image(vis->mlx_ptr,
			vis->map_obd, &vis->heith, &vis->width)))
		return (0);
	if (!(vis->img_obl = mlx_xpm_to_image(vis->mlx_ptr,
			vis->map_obl, &vis->heith, &vis->width)))
		return (0);
	if (!(vis->img_xp = mlx_xpm_to_image(vis->mlx_ptr,
			vis->map_xp, &vis->heith, &vis->width)))
		return (0);
	if (!(vis->img_xr = mlx_xpm_to_image(vis->mlx_ptr,
			vis->map_xr, &vis->heith, &vis->width)))
		return (0);
	delete_map_square(vis);
	return (1);
}

/*
** Calculates the coordinates of the Bourd in the Centr.
** heith - heith bourd, width - width bourd.
*/

void	coor_centr(int *x, int *y, int heith, int width)
{
	*y = (HEITH / 2) - (heith / 2);
	*x = (WIDTH / 2) - (width / 2);
}

/*
** Print rectangle in down whith scores.
*/

void	print_score(t_vis *vis)
{
	mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr,
			vis->img_score, 900, 660);
	mlx_string_put(vis->mlx_ptr, vis->win_ptr, 920, 695, 0x2056B6,
			vis->name_o);
	mlx_string_put(vis->mlx_ptr, vis->win_ptr, 920, 670, 0xBF2956,
			vis->name_x);
	mlx_string_put(vis->mlx_ptr, vis->win_ptr, 1200, 695, 0x2056B6,
			ft_itoa(vis->score_o));
	mlx_string_put(vis->mlx_ptr, vis->win_ptr, 1200, 670, 0xBF2956,
		ft_itoa(vis->score_x));
}

/*
** Put square to bouard.
*/

void	put_square(t_vis *vis, int i, int j)
{
	static int bl = 1;

/*	if (vis->map[i][j] == '.' && bl)
		mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr,
				vis->img_bourd, vis->x_it, vis->y_it);
	else*/	if (vis->map[i][j] == 'X')
		mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr,
				vis->img_xr, vis->x_it, vis->y_it);
	else	if (vis->map[i][j] == 'x')
		mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr,
				vis->img_xp, vis->x_it, vis->y_it);
	else	if (vis->map[i][j] == 'O')
		mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr,
				vis->img_obd, vis->x_it, vis->y_it);
	else	if (vis->map[i][j] == 'o')
		mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr,
				vis->img_obl, vis->x_it, vis->y_it);
}
