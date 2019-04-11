/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 13:45:41 by widraugr          #+#    #+#             */
/*   Updated: 2019/04/09 15:54:54 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** Parsing width and heith bourd and token.
*/

void	parsing_wh(char *line, int *width, int *heith)
{
	char *fir_num;
	char *sec_num;

	fir_num = NULL;
	sec_num = NULL;
	if (*line == '\0')
		return ;
	while(*line != '\0')
	{
		if (*line == ' ' && ft_isdigit(*(line + 1)) && !sec_num)
			fir_num = (line + 1);
		if (*line == ' ' && ft_isdigit(*(line + 1)) && fir_num)
			sec_num = (line + 1);
		line++;
	}
	*heith = ft_atoi(fir_num);
	*width = ft_atoi(sec_num);
}

/*
** Delete arr.
*/

void	dell_arr(char **arr)
{
	while(*arr != NULL)
	{
		ft_strdel(arr);
		arr++;
	}
}

/*
** Infill array (bourd and token).
*/

char	**infill_arr(int hieth, int iter)
{
	int		i;
	char	*line;
	char	**arr;

	arr = (char **)malloc(sizeof(char*) * (hieth + 1));
	i = -1;
	while (++i < hieth)
	{
		get_next_line(0, &line);
		arr[i] = ft_strdup(line + iter);
		write(2, arr[i], ft_strlen(arr[i]));
		write(2, "\n", 1);
	//	printf("i = %d line {%s}\n", i, arr[i]);
		free(line);
	}
	arr[i] = NULL;
	return (arr);
}

/*
** Print coordinates token.
*/

void	print_coor_tok(t_token *tk)
{
	int	i;

	i = -1;
	while (++i < tk->iter)
		printf("i = %d, coor_x =  %d, coor_y %d\n",
				i, tk->coor_x[i], tk->coor_y[i]);
}

/*
** Infill coordinates x and y for token.
*/

void	infill_coor_tok(t_token *tk)
{
	int	i;
	int	j;
	int	iter;

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

t_token *create_token()
{
	t_token *tk;
	char	*line;

	tk = (t_token *)malloc(sizeof(t_token));
	get_next_line(0, &line);
	parsing_wh(line, &tk->width, &tk->heith);
	free(line);
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
** Print list.
*/

void	print_list(t_clst *list)
{
	while (list != NULL)
	{
		ft_printf("list x = %d, y = %d\n", list->x_list, list->y_list);
		list = list->next;
	}
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
** Track move to fift and up.
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
		if (list->y_list < temp_y && list->x_list < temp_x)
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
	if (br->sym_x[0] > br->sym_o[0])
		move_right_up(list, br);
	else
		move_right_up(list, br);
}

/*
** Captures coordinate the first element for X and ending element for O.
*/

void	first_end(t_bourd *br, int i, int j)
{
	if (br->bourd[i][j] == 'X' && br->sym_x[0] == 0 && br->sym_x[1] == 0)
	{
		br->sym_x[0] = i;
		br->sym_x[1] = j;
	}
	if (br->bourd[i][j] == 'O')
	{
		br->sym_o[0] = i;
		br->sym_o[1] = j;
	}
}	

/*
** Initialization top X and bottom O zero.
*/

void	init_zero(t_bourd *br)
{
	br->sym_x[0] = 0;
	br->sym_x[1] = 0;
	br->sym_o[0] = 0;
	br->sym_o[1] = 0;
}

/*
** Print bourd.
*/

void	print_bourd(char **arr)
{
	while (*arr != NULL)
	{
		write(2, *arr, ft_strlen(*arr));
		write(2, "\n", 1);
		arr++;
	}
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
		}
	}
	print_bourd(br->bourd);
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
	init_zero(br);
	enemy_perimetr(br);
	while(++i < br->heith)
	{
		j = -1;
		while(++j < br->width)
		{
			if (check_insert_tok(br, tk, i, j))
				list = add_list(list, i, j);
			first_end(br, i, j);
		}
	}
	if (list == NULL)
		return (0);
	//print_list(list);
	//ft_printf("X %d %d, O %d %d\n", br->sym_x[0], br->sym_x[1], br->sym_o[0], br->sym_o[1]);  
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

int		main(void)
{
	t_bourd *br;
	t_token	*tk;
	char	*line;
	int		i;
	int		w;

	i = 0;
	br = read_sym();
	while (1)
	{
		if((w = get_next_line(0, &line)) == 0)
		{
			ft_strdel(&line);
			return (0);
		}
		parsing_wh(line,  &br->width, &br->heith);
		ft_strdel(&line);
		get_next_line(0, &line);
		ft_strdel(&line);
		br->bourd = infill_arr(br->heith, 4);
		tk = create_token();
		if (!read_bourd(br, tk))
			exit(0);
		ft_printf("%d %d\n", br->in_x, br->in_y);
		dell_arr(br->bourd);
		dell_arr(tk->token);
		free(tk->token);
		free(br->bourd);
		free(tk);
	}
	free(br);
	return (0);
}

/*
** Collect information abour the bourd.
** Sym X or O. Create arr bourd.
*/
/*
t_bourd	*info_bourd()
{
	int		i;
	char	*line;
	
	t_bourd *br;

	if(!(br = (t_bourd *)malloc(sizeof(t_bourd))))
		return (NULL);
	if(get_next_line(0, &line) == 0)
	{
		//write(2, "No line\n", 8);
		write(2, line, ft_strlen(line));
		return (NULL);
	}
	//printf("line {%s}\n", line);
	if (line[10] == '1')
		br->sym = 'O';
	else	if (line[10] == '2')
		br->sym = 'X';
	else 
		br->sym = '?';
	free(line);
	get_next_line(0, &line);
	parsing_wh(line,  &br->width, &br->heith);
	//printf("P %s\n", line);
	//printf("sym %c\n", br->sym);
	free(line);
	//printf("heith = %d width = %d\n", br->heith, br->width);
	//Пропускаем 12345...
	get_next_line(0, &line);
	free(line);
	br->bourd = infill_arr(br->heith, 4);
	return (br);
}
*/
