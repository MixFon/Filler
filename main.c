/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 13:45:41 by widraugr          #+#    #+#             */
/*   Updated: 2019/04/11 11:46:01 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

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

	if(!(tk = (t_token *)malloc(sizeof(t_token))))
		return (NULL);
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
	if (i + tk->heith > br->heith || j + tk->width > br->width )
		return (0);
	while (++iter < tk->iter)
	{
		if (br->bourd[i + tk->coor_x[iter]][j + tk->coor_y[iter]] == br->sym )
			bl++;
		if (br->bourd[i + tk->coor_x[iter]][j + tk->coor_y[iter]] == br->enemy_sym)
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
		return (NULL);
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

void	move_left(t_clst *list, t_bourd *br)
{
	int temp_y;

	temp_y = list->y_list;
	br->in_x = list->x_list;
	br->in_y = list->y_list;
	while (list != NULL)
	{
		if (list->y_list <= temp_y)
		{ 
			temp_y = list->y_list;
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
			if(br->bourd[list->x_list + tk->coor_x[iter]]
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

/*
** Search for the best options.
*/

void	search_track(t_clst *list, t_bourd *br, t_token *tk)
{
	if(search_sharp(list, br, tk))
		return ;
	if (br->sym == 'O')
		move_left(list, br);
	else
		move_right_up(list, br);
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

/*
** Enemy perimetr.
*/

void	enemy_perimetr(t_bourd *br)
{
	int		i;
	int		j;

	i = -1;
	while(++i < br->heith)
	{
		j = -1;
		while(++j < br->width)
		{
			if (br->bourd[i][j] == '.')
			{
				if (i + 1 >= br->heith || j + 1 > br->width || i - 1 < 0
						|| j - 1 < 0)
					continue ;
				infil_perimetr(br, i, j);
			}
		}
	}
}

/*
** Reading bourd.
*/

int		read_bourd(t_bourd *br, t_token *tk)
{
	int		i;
	int		j;
	t_clst	*list;

	i = -1;
	list = NULL;
	enemy_perimetr(br);
	while(++i < br->heith)
	{
		j = -1;
		while(++j < br->width)
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

t_bourd		*read_sym()
{
	t_bourd *br;
	char *line;

	if(!(br = (t_bourd *)malloc(sizeof(t_bourd))))
		return (NULL);
	if(get_next_line(0, &line) == 0)
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

void	dell(t_bourd *br, t_token *tk)
{
	ft_printf("%d %d\n", br->in_x, br->in_y);
	dell_arr(br->bourd);
	dell_arr(tk->token);
	free(tk->token);
	free(br->bourd);
	free(tk);

}

int		main(void)
{
	t_bourd *br;
	t_token	*tk;
	char	*line;

	br = read_sym();
	while (1)
	{
		if(!get_next_line(0, &line))
		{
			ft_strdel(&line);
			exit(0);
		}
		parsing_wh(line,  &br->width, &br->heith);
		ft_strdel(&line);
		get_next_line(0, &line);
		ft_strdel(&line);
		br->bourd = infill_arr(br->heith, 4);
		if(!(tk = create_token()))
			exit(0);
		if (!read_bourd(br, tk))
		{
			FINISH
		}
		dell(br, tk);
	}
	free(br);
	return (0);
}
