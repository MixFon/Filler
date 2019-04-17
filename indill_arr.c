
#include "filler.h"

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
		//write(2, arr[i], ft_strlen(arr[i]));
		//write(2, "\n", 1);
		//ft_printf("i = %d line {%s}\n", i, arr[i]);
		ft_strdel(&line);
	}
	arr[i] = NULL;
	return (arr);
}

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
** Print bourd.
*/

void	print_arr(char **arr)
{
	int i;

	i = 0;
	while (*arr != NULL)
	{
		//ft_printf("i = %d, '%s'\n", i, *arr);
		//write(2, *arr, ft_strlen(*arr));
		//write(2, "\n", 1);
		i++;
		arr++;
	}
}

/*
** Delete arr.
*/

void	dell_arr(char **arr)
{
	//ft_printf("delete\n");
	while(*arr != NULL)
	{
		//ft_strdel(arr);
		free(*arr);
		arr++;
	}
}



