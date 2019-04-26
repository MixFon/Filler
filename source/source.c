/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 10:31:26 by widraugr          #+#    #+#             */
/*   Updated: 2019/04/26 11:29:47 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/filler.h"

void	parsing_infillarr(char *line, t_bourd *br)
{
	parsing_wh(line, &br->width, &br->heith);
	ft_strdel(&line);
	get_next_line(0, &line);
	ft_strdel(&line);
	br->bourd = infill_arr(br->heith, 4);
}
