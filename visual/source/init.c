/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 10:52:13 by widraugr          #+#    #+#             */
/*   Updated: 2019/04/26 14:10:20 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/visual.h"

/*
** Read input. Create size bourd.Create map.
*/

int		read_input(t_vis *vis)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line))
	{
		if (*line == '<')
			return (0);
		if (!ft_strncmp(line, "    0", 5))
			rewrite_arr(vis);
		ft_strdel(&line);
	}
	return (0);
}

/*
** Print matrics of rectengle. Starn coordinate matrics (x, y).
** Count lines - row. Count colloms - col.
*/

int		print_bourd(t_vis *vis)
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
	print_score(vis);
	while (++i < vis->row)
	{
		j = -1;
		while (++j < vis->col)
		{
			put_square(vis, i, j);
			vis->x_it += vis->width + 1;
		}
		vis->x_it = x;
		vis->y_it += (vis->heith + 1);
	}
	return (0);
}

/*
** Init background and menu.
*/

int		init_back(t_vis *vis)
{
	if (!(vis->img_back = mlx_xpm_file_to_image(vis->mlx_ptr,
			IMGPATH, &vis->heith, &vis->width)))
	{
		write(2, "Error image background.\n", 24);
		return (0);
	}
	return (1);
}

void	init_image(t_vis *vis)
{
	if (!(init_back(vis)))
		exit(0);
	if (!(init_image_squer(vis)))
		exit(0);
}

/*
** Init value struct.
*/

void	init_val(t_vis *vis)
{
	vis->mlx_ptr = NULL;
	vis->win_ptr = NULL;
	vis->img_back = NULL;
	vis->img_bourd = NULL;
	vis->img_obd = NULL;
	vis->img_obl = NULL;
	vis->img_xr = NULL;
	vis->img_xp = NULL;
	vis->heith = 0;
	vis->width = 0;
	vis->col = 0;
	vis->row = 0;
	vis->map = NULL;
	vis->map_xr = NULL;
	vis->map_xp = NULL;
	vis->map_obd = NULL;
	vis->map_obl = NULL;
	vis->map_bourd = NULL;
	vis->map_back = NULL;
	ft_memset(vis->name_o, '\0', 30);
	ft_memset(vis->name_x, '\0', 30);
	vis->score_o = 0;
	vis->score_x = 0;
	vis->x_it = 0;
	vis->y_it = 0;
}
