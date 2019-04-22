/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 13:45:41 by widraugr          #+#    #+#             */
/*   Updated: 2019/04/22 15:48:33 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/filler.h"

/*
** Enemy perimetr.
*/

void		enemy_perimetr(t_bourd *br)
{
	int		i;
	int		j;

	i = -1;
	while (++i < br->heith)
	{
		j = -1;
		while (++j < br->width)
		{
			if (br->bourd[i][j] == '.')
			{
				if (i + 1 >= br->heith || j + 1 > br->width || i - 1 < 0
						|| j - 1 < 0)
					continue ;
				infil_perimetr(br, i, j);
			}
			start_cor(br, i, j);
		}
	}
}

/*
** Reading bourd.
*/

int			read_bourd(t_bourd *br, t_token *tk)
{
	int		i;
	int		j;
	t_clst	*list;

	i = -1;
	list = NULL;
	enemy_perimetr(br);
	while (++i < br->heith)
	{
		j = -1;
		while (++j < br->width)
		{
			if (check_insert_tok(br, tk, i, j))
				list = add_list(list, i, j);
		}
	}
	if (list == NULL)
		return (0);
	search_track(list, br, tk);
	delete_list(list);
	return (1);
}

t_bourd		*read_sym(void)
{
	t_bourd *br;
	char	*line;

	if (!(br = (t_bourd *)malloc(sizeof(t_bourd))))
		return (NULL);
	init_start_cor(br);
	if (get_next_line(0, &line) == 0)
		return (NULL);
	if (ft_strncmp(line, "$$$ exec p", 10))
	{
		write(1, "Error name playr.\n", 18);
		exit(1);
	}
	if (line[10] == '1')
	{
		br->sym = 'O';
		br->enemy_sym = 'X';
	}
	else	if (line[10] == '2')
	{
		br->sym = 'X';
		br->enemy_sym = 'O';
	}
	ft_strdel(&line);
	return (br);
}

/*
** Delete and free arres.
*/

void		dell(t_bourd *br, t_token *tk)
{
	ft_printf("%d %d\n", br->in_x, br->in_y);
	dell_arr(br->bourd);
	dell_arr(tk->token);
	free(tk->token);
	free(br->bourd);
	free(tk);
}

int			main(void)
{
	t_bourd *br;
	t_token	*tk;
	char	*line;

	br = read_sym();
	while (1)
	{
		get_next_line(0, &line);
		parsing_wh(line, &br->width, &br->heith);
		ft_strdel(&line);
		get_next_line(0, &line);
		ft_strdel(&line);
		br->bourd = infill_arr(br->heith, 4);
		if (!(tk = create_token()))
			exit(0);
		if (!read_bourd(br, tk))
		{
			ft_printf("%d %d\n", 0, 0);
			exit(0);
		}
		dell(br, tk);
	}
	free(br);
	return (0);
}
