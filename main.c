

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
		free(line);
	}
	arr[i] = NULL;
	return (arr);
}

/*
** Collect information abour the bourd.
** Sym X or O. Create arr bourd.
*/

t_bourd	*info_bourd()
{
	int		i;
	char	*line;
	t_bourd *br;

	if(!(br = (t_bourd *)malloc(sizeof(t_bourd))))
		return (NULL);
	get_next_line(0, &line);
	printf("line {%s}\n", line);
	if (line[10] == '1')
		br->sym = 'O';
	else	if (line[10] == '2')
		br->sym = 'X';
	else 
		br->sym = '?';
	free(line);
	get_next_line(0, &line);
	parsing_wh(line,  &br->width, &br->heith);
	printf("P %s\n", line);
	printf("sym %c\n", br->sym);
	free(line);
	printf("heith = %d width = %d\n", br->heith, br->width);
	get_next_line(0, &line);
	free(line);
	br->bourd = infill_arr(br->heith, 4);
	return (br);
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
	print_coor_tok(tk);
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
	printf("tk->heith = %d tk->width = %d\n", tk->heith, tk->width);
	free(line);
	tk->token = infill_arr(tk->heith, 0);
	infill_coor_tok(tk);
	return (tk);
}

/*
** Check insert token.
*/

int		check_insert_tok(t_bourd *br, t_token *tk)
{

	return (0);
}

/*
** Reading bourd.
*/

void	read_bourd(t_bourd *br, t_token *tk)
{
	int	i;
	int	j;

	i = -1;
	while(++i < br->heith)
	{
		j = -1;
		while(++j < br->width)
		{
			if (br->bourd[i][j] == br->sym)
			{
				br->in_x = i;
				br->in_y = j;
			}
		}
	}
}

int		main(int ac, char **av)
{
	t_bourd *br;
	t_token	*tk;
	char	*line;

	br = info_bourd();
	tk = create_token();
	read_bourd(br, tk);
	printf("in_x = %d, in_y = %d\n", br->in_x, br->in_y);
	dell_arr(br->bourd);
	dell_arr(tk->token);
	free(tk->token);
	free(br->bourd);
	free(tk);
	free(br);
	return (0);
}
