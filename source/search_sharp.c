/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_sharp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 13:03:48 by widraugr          #+#    #+#             */
/*   Updated: 2019/04/26 10:59:13 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/filler.h"

/*
** Delete list.
*/

void	delete_list(t_clst *list)
{
	t_clst *prev;

	prev = list;
	while (list != NULL)
	{
		list = list->next;
		free(prev);
		prev = list;
	}
}

/*
** Track move to left and up.
*/

void	move_left_up(t_clst *list, t_bourd *br)
{
	int temp_x;
	int temp_y;

	temp_y = list->y_list;
	temp_x = list->x_list;
	br->in_x = list->x_list;
	br->in_y = list->y_list;
	while (list != NULL)
	{
		if (list->y_list < temp_y || list->x_list < temp_x)
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
** Track move to right and up.
*/

void	move_right_up(t_clst *list, t_bourd *br)
{
	int temp_x;
	int temp_y;

	temp_y = list->y_list;
	temp_x = list->x_list;
	br->in_x = list->x_list;
	br->in_y = list->y_list;
	while (list != NULL)
	{
		if (list->y_list > temp_y || list->x_list < temp_x)
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
** Track move to left.
*/

void	move_left_down(t_clst *list, t_bourd *br)
{
	int temp_y;
	int temp_x;

	temp_y = list->y_list;
	temp_x = list->x_list;
	br->in_x = list->x_list;
	br->in_y = list->y_list;
	while (list != NULL)
	{
		if (list->y_list < temp_y && list->x_list <= temp_x)
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
** Search overlya whith sharp.
*/

int		search_sharp(t_clst *list, t_bourd *br, t_token *tk)
{
	int	iter;

	while (list != NULL)
	{
		iter = -1;
		while (++iter < tk->iter)
		{
			if (br->bourd[list->x_list + tk->coor_x[iter]]
					[list->y_list + tk->coor_y[iter]] == '#')
			{
				br->in_x = list->x_list;
				br->in_y = list->y_list;
				return (1);
			}
		}
		list = list->next;
	}
	return (0);
}
