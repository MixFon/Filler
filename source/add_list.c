/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 12:57:14 by widraugr          #+#    #+#             */
/*   Updated: 2019/04/26 10:59:16 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/filler.h"

/*
** Infill coordinates x and y for token.
*/

void	infill_coor_tok(t_token *tk)
{
	int	i;
	int	j;

	i = -1;
	tk->iter = 0;
	while (++i < tk->heith)
	{
		j = -1;
		while (++j < tk->width)
		{
			if (tk->token[i][j] == '*')
			{
				tk->coor_x[tk->iter] = i;
				tk->coor_y[tk->iter] = j;
				tk->iter++;
			}
		}
	}
}

/*
** Create token size widht_tok and heith_tok.
*/

t_token	*create_token(void)
{
	t_token *tk;
	char	*line;

	if (!(tk = (t_token *)malloc(sizeof(t_token))))
		err_sys("Error malloc in infill_arr");
	get_next_line(0, &line);
	parsing_wh(line, &tk->width, &tk->heith);
	ft_strdel(&line);
	tk->token = infill_arr(tk->heith, 0);
	infill_coor_tok(tk);
	return (tk);
}

/*
** Check insert token.
*/

int		check_insert_tok(t_bourd *br, t_token *tk, int i, int j)
{
	int		iter;
	int		bl;

	iter = -1;
	bl = 0;
	if (i + tk->heith > br->heith || j + tk->width > br->width)
		return (0);
	while (++iter < tk->iter)
	{
		if (br->bourd[i + tk->coor_x[iter]][j + tk->coor_y[iter]] == br->sym)
			bl++;
		if (br->bourd[i + tk->coor_x[iter]][j + tk->coor_y[iter]]
				== br->enemy_sym)
			return (0);
	}
	if (bl == 1)
		return (1);
	return (0);
}

/*
** Create new list.
*/

t_clst	*creat_clst(void)
{
	t_clst	*new;

	if (!(new = (t_clst *)malloc(sizeof(t_clst))))
		err_sys("Error malloc in creat_clst");
	new->x_list = 0;
	new->y_list = 0;
	new->next = NULL;
	return (new);
}

/*
** Add list in top.
*/

t_clst	*add_list(t_clst *list, int i, int j)
{
	t_clst *new;

	if (list == NULL)
	{
		list = creat_clst();
		list->x_list = i;
		list->y_list = j;
		return (list);
	}
	new = creat_clst();
	new->x_list = i;
	new->y_list = j;
	new->next = list;
	return (new);
}
