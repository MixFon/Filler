/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crea_color_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 10:50:51 by widraugr          #+#    #+#             */
/*   Updated: 2019/04/26 14:10:23 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/visual.h"

/*
**  Create new map.
*/

void	new_map(t_vis *vis)
{
	int i;

	i = -1;
	if(!(vis->map = (char **)malloc(sizeof(char*) * (vis->row + 1))))
		err_sys("Error malloc in mew_map\n");
	while (++i < vis->row)
		vis->map[i] = ft_strnew(vis->col);
	vis->map[i] = NULL;
}

/*
**  Rewrite bourd. No malloc.
*/

void	rewrite_arr(t_vis *vis)
{
	int		i;
	char	*line;

	if (vis->map == NULL)
		new_map(vis);
	i = -1;
	while (++i < vis->row)
	{
		get_next_line(0, &line);
		score(line, &vis->score_o, &vis->score_x);
		ft_strcpy(vis->map[i], line + 4);
		ft_strdel(&line);
	}
	vis->map[i] = NULL;
}

int		size_square(t_vis *vis)
{
	int i;

	i = -1;
	while (++i < 20)
	{
		if (((HEITH - INDENT) <= vis->row * i)
				|| ((WIDTH - INDENT) <= vis->col * i))
			break ;
	}
	if (i < 1)
		return (1);
	return (i);
}

void	colc_size_squre(t_vis *vis)
{
	ft_printf("square size = %d\n", size_square(vis));
	vis->heith = size_square(vis);
	vis->width = vis->heith;
}

char	**crea_color_map(int heith, int width, const char *color)
{
	char	**map;
	int		i;
	int		j;

	if(!(map = (char **)malloc(sizeof(char *) * (heith + 3))))
		err_sys("Error malloc crea_color_map");
	map[0] = ft_multi_strdup(4, ft_itoa(width), " ", ft_itoa(heith), " 1 1 ");
	map[1] = ft_multi_strdup(2, "b c #", color);
	i = 1;
	while (++i < heith + 2)
	{
		j = -1;
		map[i] = ft_strnew(width + 1);
		while (++j < width)
			map[i][j] = 'b';
	}
	map[i] = NULL;
	return (map);
}
