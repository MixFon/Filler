/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 13:45:41 by widraugr          #+#    #+#             */
/*   Updated: 2019/04/08 16:34:11 by widraugr         ###   ########.fr       */
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
** Search for the best options.
*/

void	search_option(t_clst *list, t_bourd *br)
{
	int temp;

	temp = list->y_list;
	br->in_x = list->x_list;
	br->in_y = list->y_list;
	while (list != NULL)
	{
		if (list->y_list < temp)
		{
			temp = list->y_list;
			br->in_x = list->x_list;
			br->in_y = list->y_list;

		}
		list = list->next;
	}
}

/*
** Reading bourd.
*/

void	read_bourd(t_bourd *br, t_token *tk)
{
	int		i;
	int		j;
	t_clst	*list;

	i = -1;
	list = NULL;
	while(++i < br->heith)
	{
		j = -1;
		while(++j < br->width)
		{
			if (check_insert_tok(br, tk, i, j))
			{
				list = add_list(list, i, j);
				//br->in_x = i;
				//br->in_y = j;
				//if (j % 2 == 0)
				//	continue ;
				//if (br->sym == 'X')
				//	return ;
			//	return ;	//Фиксирует первое удожное место вставки ближе к верхнему левому углу. Если убрать, то по последнему 	
			}
		}
	}
	//print_list(list);
	search_option(list, br);
	delete_list(list);
}

t_bourd		*read_sym()
{
	t_bourd *br;
	char *line;

	if(!(br = (t_bourd *)malloc(sizeof(t_bourd))))
		return (NULL);
	if(get_next_line(0, &line) == 0)
	{
		write(2, "No line\n", 8);
		write(2, line, ft_strlen(line));
		ft_strdel(&line);
		return (NULL);
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
	else 
		br->sym = '?';
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
		free(line);
		get_next_line(0, &line);
		ft_strdel(&line);
		br->bourd = infill_arr(br->heith, 4);
		tk = create_token();
		read_bourd(br, tk);
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
