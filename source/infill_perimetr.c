/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infill_perimetr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 13:06:54 by widraugr          #+#    #+#             */
/*   Updated: 2019/04/22 15:48:38 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/filler.h"

/*
** Track move to right and up.
*/

void	move_right_dowm(t_clst *list, t_bourd *br)
{
	int temp_x;
	int temp_y;

	temp_y = list->y_list;
	temp_x = list->x_list;
	br->in_x = list->x_list;
	br->in_y = list->y_list;
	while (list != NULL)
	{
		if (list->y_list > temp_y && list->x_list <= temp_x)
		{
			temp_y = list->y_list;
			temp_x = list->x_list;
			br->in_x = list->x_list;
			br->in_y = list->y_list;
		}
		list = list->next;
	}
}

/*
** Search for the best options.
*/

void	search_track(t_clst *list, t_bourd *br, t_token *tk)
{
	if (search_sharp(list, br, tk))
		return ;
	if (br->cor_en[0] <= br->cor_us[0] && br->cor_en[1] <= br->cor_us[1])
		move_left_up(list, br);
	else	if (br->cor_en[0] <= br->cor_us[0] &&
			br->cor_en[1] >= br->cor_us[1])
		move_right_up(list, br);
	else	if (br->cor_en[0] >= br->cor_us[0] &&
			br->cor_en[1] <= br->cor_us[1])
		move_left_down(list, br);
	else	if (br->cor_en[0] >= br->cor_us[0] &&
			br->cor_en[1] >= br->cor_us[1])
		move_right_dowm(list, br);
}

/*
** Infill perimert.
*/

void	infil_perimetr(t_bourd *br, int i, int j)
{
	if (br->bourd[i + 1][j] == br->enemy_sym)
		br->bourd[i][j] = '#';
	if (br->bourd[i - 1][j] == br->enemy_sym)
		br->bourd[i][j] = '#';
	if (br->bourd[i][j + 1] == br->enemy_sym)
		br->bourd[i][j] = '#';
	if (br->bourd[i][j - 1] == br->enemy_sym)
		br->bourd[i][j] = '#';
	if (br->bourd[i + 1][j + 1] == br->enemy_sym)
		br->bourd[i][j] = '#';
	if (br->bourd[i - 1][j - 1] == br->enemy_sym)
		br->bourd[i][j] = '#';
	if (br->bourd[i - 1][j + 1] == br->enemy_sym)
		br->bourd[i][j] = '#';
	if (br->bourd[i + 1][j - 1] == br->enemy_sym)
		br->bourd[i][j] = '#';
}

void	start_cor(t_bourd *br, int i, int j)
{
	if (!br->cor_en[0] && !br->cor_en[1])
		if (br->bourd[i][j] == br->enemy_sym)
		{
			br->cor_en[0] = i;
			br->cor_en[1] = j;
		}
	if (!br->cor_us[0] && !br->cor_us[1])
		if (br->bourd[i][j] == br->sym)
		{
			br->cor_us[0] = i;
			br->cor_us[1] = j;
		}
}

void	init_start_cor(t_bourd *br)
{
	br->cor_en[0] = 0;
	br->cor_en[1] = 0;
	br->cor_us[0] = 0;
	br->cor_us[1] = 0;
}
