

#include "filler.h"

/*
** Parsing width and heith bourd .
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
** Collect information abour plyer and the bourd.
*/

t_plyer	*info_plyer()
{
	int		i;
	char	*line;
	t_plyer *pl;

	if(!(pl = (t_plyer *)malloc(sizeof(t_plyer))))
		return (NULL);
	get_next_line(0, &line);
	printf("line %s\n", line);
	if (line[10] == '1')
		pl->sym = 'O';
	else	if (line[10] == '2')
		pl->sym = 'X';
	else 
		pl->sym = '?';
	free(line);
	get_next_line(0, &line);
	parsing_wh(line,  &pl->width, &pl->heith);
	printf("P %s\n", line);
	printf("sym %c\n", pl->sym);
	free(line);
	printf("heith = %d width = %d\n", pl->heith, pl->width);
	get_next_line(0, &line);
	free(line);
	pl->bourd = infill_arr(pl->heith, 4);
	return (pl);
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
	return (tk);
}

/*
** Reading bourd.
*/

void	read_bourd(t_plyer *pl)
{
	int	i;
	int	j;

	i = 0;
	while(i < pl->heith)
	{
		j = 0;
		while(j < pl->width)
		{
			if (pl->bourd[i][j] == pl->sym)
			{
				pl->in_x = i;
				pl->in_y = j;
			}
			j++;
		}
		i++;
	}
}

int		main(int ac, char **av)
{
	t_plyer *pl;
	t_token	*tk;
	char	*line;
	int		i;

	pl = info_plyer();
	tk = create_token();
	read_bourd(pl);
	printf("in_x = %d, in_y = %d", pl->in_x, pl->in_y);
	dell_arr(pl->bourd);
	dell_arr(tk->token);
	free(tk->token);
	free(pl->bourd);
	free(pl);
	return (0);
}
