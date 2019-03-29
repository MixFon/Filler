

#include "filler.h"

/*
** Parsing width and heith bourd .
*/

void	parsing_wh(char *line, t_plyer *pl)
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
	pl->heith = ft_atoi(fir_num);
	pl->width = ft_atoi(sec_num);
	printf("heith = %d width = %d\n", pl->heith, pl->width);
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
	parsing_wh(line, pl);
	printf("P %s\n", line);
	printf("sym %c\n", pl->sym);
	return (pl);
}

int		main(int ac, char **av)
{
	t_plyer *pl;
	char *line;
	int	i;

	
	//get_next_line(0, &line);
	pl = info_plyer();
	//while (1)
	//{
		i = 0;
		while(++i < 66)
		{
			get_next_line(0, &line);
			write(2, line, ft_strlen(line));
			write(2, "\n", 1);
			i++;
			//ft_printf("%d %d\n", i , i);
		}
		ft_putstr("3");
		ft_putstr(" ");
		ft_putstr("2");
		ft_putstr("\n");
		write(2, "a\n", 2);
	//}
	//exit(1);
	//ft_printf("19 32\n");
	//write(2, "Hello\n", 6);
	return (0);
}
